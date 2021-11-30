#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#define DEVICE_ID 0x08
#define ADAPTER_ID 1
using namespace std;

int main (int argc, char **argv)
{
    // Setup I2C communication
    int received_char = 0;
    int recv_indx = 0;
    char data_to_send[] = "\0Hello Leanordo\n";
    char received_data[300] = "none";
    int file;
    char filename[20];

    // Initialise raspberry i2c
    snprintf(filename, 19, "/dev/i2c-%d", ADAPTER_ID);
    file = open(filename, O_RDWR);
    if (file < 0)
    {
        cout << "Failed to init I2C communication.\n";
        return -1;
    }

    // Connect to SLAVE
    if (ioctl(file, I2C_SLAVE, DEVICE_ID) < 0)
    {
        cout << "Failed to init I2C communication.\n";
        return -1;
    }

    cout << "I2C communication successfully setup.\n";

    // Send data to arduino
    data_to_send[0] = 0x10;
    if (write(file, data_to_send, sizeof(data_to_send)) != sizeof(data_to_send))
    {
        cout << "Failed to write I2C.\n";
        return -1;
    }
    cout << "Sent data: " << data_to_send << "\n";

    while (true)
    {
        /* Using I2C Read, equivalent of i2c_smbus_read_byte(file) */
        if (read(file, received_data, 30) != 30)
        {
            cout << "Failed to read I2C.\n";
            return -1;
        }
        cout << "Data received: " << received_data << "\n";
        if (sizeof(received_data) > 16) break;
    }

    if (file)
    {
        close(file);
    }

    // __s32 res;
    // res = i2c_smbus_read_word_data(file, reg);
    // if (res < 0)
    // {
    //     cout << "Failed to read I2C.\n";
    //     return -1;
    // }
    // else
    // {
    //     c
    // }

    return 0;
}