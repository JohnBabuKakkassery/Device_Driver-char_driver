#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

static dev_t dev_num;                // stores major+minor
static struct cdev my_cdev;          // cdev structure
static struct class *my_class;       // device class
static char text[64];                // buffer

static ssize_t driver_read(struct file *file_p, char __user *user_buf, size_t len, loff_t *offset)
{
    int not_copied;
    int delta;
    int to_copy = (len + *offset) < sizeof(text) ? len : (sizeof(text) - *offset);

    if (*offset >= sizeof(text))
    {
        return 0;
    }

    not_copied = copy_to_user(user_buf, &text[*offset], to_copy);
    delta = to_copy - not_copied;

    if (not_copied)
    {
        printk(KERN_WARNING "Copy was not fully done, %d bytes not copied\n", not_copied);
    }

    *offset += delta;
    return delta;
}

static ssize_t driver_write(struct file *file_p, const char __user *user_buf, size_t len, loff_t *offset)
{
    int not_copied;
    int delta;
    int to_copy = (len + *offset) < sizeof(text) ? len : (sizeof(text) - *offset);

    if (*offset >= sizeof(text))
    {
        return 0;
    }

    not_copied = copy_from_user(&text[*offset], user_buf, to_copy);
    delta = to_copy - not_copied;

    if (not_copied)
    {
        printk(KERN_WARNING "Copy was not fully done, %d bytes not copied\n", not_copied);
    }

    *offset += delta;
    return delta;
}

static int driver_open(struct inode *node, struct file *file_p)
{
    printk(KERN_DEBUG "The char_driver file is open\n");
    printk(KERN_INFO "Major number: %d and Minor number: %d\n", imajor(node), iminor(node));
    printk(KERN_INFO "File permissions 0x%x\n", file_p->f_mode);
    printk(KERN_INFO "File position %lld\n", file_p->f_pos);
    printk(KERN_INFO "Flags 0x%x\n", file_p->f_flags);
    return 0;
}

static int driver_release(struct inode *node, struct file *file_p)
{
    printk(KERN_INFO "The file has been closed\n");
    return 0;
}

static struct file_operations fops =
{
    .owner   = THIS_MODULE,
    .read    = driver_read,
    .write   = driver_write,
    .open    = driver_open,
    .release = driver_release
};

static int __init char_driver_init(void)
{
    int ret;

    ret = alloc_chrdev_region(&dev_num, 0, 1, "char_driver");
    if (ret < 0) {
        printk(KERN_ERR "Failed to allocate major/minor\n");
        return ret;
    }

    printk(KERN_INFO "Allocated Major=%d Minor=%d\n", MAJOR(dev_num), MINOR(dev_num));

    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;
    ret = cdev_add(&my_cdev, dev_num, 1);
    if (ret < 0) {
        printk(KERN_ERR "Failed to add cdev\n");
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    my_class = class_create("char_class");
    if (IS_ERR(my_class)) {
        printk(KERN_ERR "Failed to create class\n");
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(my_class);
    }

    if (IS_ERR(device_create(my_class, NULL, dev_num, NULL, "char_driver"))) {
        printk(KERN_ERR "Failed to create device\n");
        class_destroy(my_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return -1;
    }

    printk(KERN_INFO "Driver initialized successfully\n");
    return 0;
}

static void __exit char_driver_exit(void)
{
    device_destroy(my_class, dev_num);
    class_destroy(my_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "Driver exited\n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Babu Kakkassery");
MODULE_DESCRIPTION("A simple character driver using alloc_chrdev_region");

