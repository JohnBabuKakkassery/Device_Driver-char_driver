import time
import os

DEVICE_PATH = "/dev/char_driver"

def main():
    if not os.path.exists(DEVICE_PATH):
        print(f"Error: {DEVICE_PATH} not found. Did you load the module?")
        return

    try:
        print("Opening the device...")
        with open(DEVICE_PATH, "w") as f:
            msg = "This is John from userspace!\n"
            print(f"Writing: {msg.strip()}")
            f.write(msg)
            f.flush()

        time.sleep(1)

        with open(DEVICE_PATH, "r") as f:
            data = f.read()
            print(f"Read back: {data.strip()}")

        print("Device test complete!")

    except PermissionError:
        print(f"Error: Permission denied. Try running with sudo or adjust permissions (chmod 666 {DEVICE_PATH}).")

if __name__ == "__main__":
    main()

