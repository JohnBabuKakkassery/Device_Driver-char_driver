# Simple Linux Character Driver

This repository contains a simple Linux kernel **character driver** written in C, along with a user-space Python test script. It serves as a practical demonstration of how to write, build, and test a basic Linux device driver.

---

## 📂 Repository Structure

The project is organized into the following directories and files:
char_driver/
│
├── source/
│   └── char_driver.c     # The core C source code for the kernel module.
│
├── tests/
│   └── test_driver.py    # A user-space Python script to test the driver.
│
├── bin/                  # Generated on build (contains .o and .ko files).
│
├── Makefile              # Build system for compiling the kernel module.
└── README.md             # This file.


---

## ⚙️ Build and Usage Instructions

Follow these steps to build the driver, insert it into the kernel, and test its basic file operations.

### 1. Clone the Repository

First, clone the repository and navigate into the directory:

```bash
git clone [https://github.com/](https://github.com/)<your-username>/char_driver_repo.git
cd char_driver_repo
```

2. Build the Driver

Use the provided Makefile to compile the module:
Bash

make

This command compiles the source code and generates the kernel object file, char_driver.ko, inside the bin/ folder.

3. Insert the Module

Load the compiled kernel module into the Linux kernel using insmod:
Bash

sudo insmod bin/char_driver.ko

Once loaded, the device file should be available at /dev/char_driver.

4. Basic File Operations

You can test the driver's core functionality directly using standard shell commands:
Operation	Command	Description
Write	echo "Hello" > /dev/char_driver	Writes a string to the device driver.
Read	cat /dev/char_driver	Reads the internal buffer content from the driver.

🧪 Testing

The included Python script provides a robust test of the driver's read and write capabilities.

Run the Test Script

Execute the script from the root of the repository:
Bash

python3 tests/test_driver.py

Expected Output

If the driver is loaded correctly and functioning, the output should match:

Opening the device...
Writing: This is John from userspace!
Read back: This is John from userspace!
Device test complete!

🧹 Clean Up

1. Remove the Module

To unload the driver from the kernel:
Bash

sudo rmmod char_driver

2. Remove Build Files

To remove all generated build files (.o, .ko, module information, etc.), use the clean target in the Makefile:
Bash

make clean
