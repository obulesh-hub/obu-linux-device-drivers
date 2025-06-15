#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "obu_char"
#define CLASS_NAME  "obu_class"
#define BUF_LEN     1024

static dev_t dev_num;
static struct class *obu_class;
static struct cdev obu_cdev;
static char kernel_buffer[BUF_LEN] = "Hello from kernel space!\n";

// ------------------------ File Operation Functions ------------------------

static int obu_open(struct inode *inode, struct file *file) {
    pr_info("obu_char: Device opened\n");
    return 0;
}

static int obu_release(struct inode *inode, struct file *file) {
    pr_info("obu_char: Device closed\n");
    return 0;
}

static ssize_t obu_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    ssize_t bytes_read;

    if (*offset >= BUF_LEN)
        return 0;

    if (*offset + len > BUF_LEN)
        len = BUF_LEN - *offset;

    bytes_read = len - copy_to_user(buf, kernel_buffer + *offset, len);

    *offset += bytes_read;
    pr_info("obu_char: Sent %zd bytes to user\n", bytes_read);
    return bytes_read;
}

static ssize_t obu_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    ssize_t bytes_written;

    if (len > BUF_LEN)
        len = BUF_LEN;

    memset(kernel_buffer, 0, BUF_LEN);
    bytes_written = len - copy_from_user(kernel_buffer, buf, len);

    pr_info("obu_char: Received %zd bytes from user\n", bytes_written);
    return bytes_written;
}

// ------------------------ File Operations Structure ------------------------

static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = obu_open,
    .release = obu_release,
    .read    = obu_read,
    .write   = obu_write,
};

// ------------------------ Module Init/Exit ------------------------

static int __init obu_init(void) {
    int ret;

    // 1. Allocate device number
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        pr_err("obu_char: Failed to allocate device number\n");
        return ret;
    }

    // 2. Create device class
    obu_class = class_create(CLASS_NAME);
    if (IS_ERR(obu_class)) {
        unregister_chrdev_region(dev_num, 1);
        pr_err("obu_char: Failed to create class\n");
        return PTR_ERR(obu_class);
    }

    // 3. Create device
    if (IS_ERR(device_create(obu_class, NULL, dev_num, NULL, DEVICE_NAME))) {
        class_destroy(obu_class);
        unregister_chrdev_region(dev_num, 1);
        pr_err("obu_char: Failed to create device\n");
        return -1;
    }

    // 4. Init and add cdev
    cdev_init(&obu_cdev, &fops);
    obu_cdev.owner = THIS_MODULE;
    ret = cdev_add(&obu_cdev, dev_num, 1);
    if (ret < 0) {
        device_destroy(obu_class, dev_num);
        class_destroy(obu_class);
        unregister_chrdev_region(dev_num, 1);
        pr_err("obu_char: Failed to add cdev\n");
        return ret;
    }

    pr_info("obu_char: Module loaded successfully. Major: %d Minor: %d\n",
            MAJOR(dev_num), MINOR(dev_num));
    return 0;
}

static void __exit obu_exit(void) {
    cdev_del(&obu_cdev);
    device_destroy(obu_class, dev_num);
    class_destroy(obu_class);
    unregister_chrdev_region(dev_num, 1);
    pr_info("obu_char: Module unloaded\n");
}

module_init(obu_init);
module_exit(obu_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Obu");
MODULE_DESCRIPTION("Character device driver for kernel 6.12.0");
MODULE_VERSION("1.0");

