# Simple Linux Character Driver

This repository contains a simple Linux kernel character driver with a user-space test script.  
It demonstrates how to write, build, and test a basic Linux device driver.  

---

## 📂 Repository Structure

char_driver/
│
├── source/
│   └── char_driver.c
│
├── tests/
│   └── test_driver.py
│
├── bin/               # Generated on build (contains .o and .ko files)
│
├── Makefile
└── README.md

---

## ⚙️ Build Instructions

1. Clone the repo and enter the directory:
   ```bash
   git clone https://github.com/<your-username>/char_driver_repo.git
   cd char_driver_repo

    Build the driver:

make

This will generate char_driver.ko in the bin/ folder.

Insert the module:

sudo insmod bin/char_driver.ko

write operation : echo "Hello" > ./dev/char_driver
read operation : cat /dev/char_driver

## 🧪 Testing

Run the Python test script:

python3 tests/test_driver.py

Expected output:

Opening the device...
Writing: This is John from userspace!
Read back: This is John from userspace!
Device test complete!

## 🧹 Clean Up

To remove build files:
