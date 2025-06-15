# char Driver Module

This Linux kernel module sets up a simple char driver.

## Build and Run

```bash
make
sudo insmod char_dev.ko
sudo ./user_test
dmesg | tail
sudo rmmod char_dev

