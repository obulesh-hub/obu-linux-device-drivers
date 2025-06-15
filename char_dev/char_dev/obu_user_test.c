#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_PATH "/dev/obu_char"

int main() {
    int fd;
    char write_data[] = "Hello from User Space!";
    char read_data[100] = {0};

    // Open the device
    fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return 1;
    }

    printf("Device opened successfully.\n");

    // Write data to the device
    if (write(fd, write_data, strlen(write_data)) < 0) {
        perror("Write failed");
        close(fd);
        return 1;
    }
    printf("Data written to device: %s\n", write_data);

    // Read data from the device
    if (read(fd, read_data, sizeof(read_data)) < 0) {
        perror("Read failed");
        close(fd);
        return 1;
    }
    printf("Data read from device: %s\n", read_data);

    // Close the device
    close(fd);
    printf("Device closed.\n");

    return 0;
}

