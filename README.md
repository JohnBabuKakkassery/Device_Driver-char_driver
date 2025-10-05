# Simple Linux Character Driver

This repository contains a simple Linux kernel character driver with a user-space test script.  
It demonstrates how to write, build, and test a basic Linux device driver.

---

## 📂 Repository Structure

- **source/** → Driver source code (`char_driver.c`)  
- **tests/** → User-space test script (`Python`)  
- **bin/** → Build output (`.o` and `.ko` files, created after `make`)  
- **Makefile** → Build rules  
- **README.md** → Documentation  

---

## ⚙️ Build Instructions

1. Clone the repository and enter the directory:

```bash
git clone https://github.com/<your-username>/char_driver_repo.git
cd char_driver_repo

    Build the driver:

make

This will generate char_driver.ko in the bin/ folder.

    Insert the module:

sudo insmod bin/char_driver.ko

    Perform read and write operations:

# Write operation
echo "Hello" > /dev/char_driver

# Read operation
cat /dev/char_driver

🧪 Testing

Run the Python test script:

python3 tests/test_driver.py

Expected output:

Opening the device...
Writing: This is John from userspace!
Read back: This is John from userspace!
Device test complete!

🧹 Clean Up

To remove build files:

make clean
