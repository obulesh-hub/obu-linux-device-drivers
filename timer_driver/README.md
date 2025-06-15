# Timer Driver Module

This Linux kernel module sets up a simple timer and prints jiffies during each callback.

## Build and Run

```bash
make
sudo insmod timer_driver.ko
dmesg | tail
sudo rmmod timer_driver

