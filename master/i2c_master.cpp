#include <iostream>
#include <wiringPiI2C.h>

#define DEVICE_ID 0x08

using namespace std;

int main (int argc, char **argv)
{
    // Setup I2C communication
    int received_char = 0;
    int recv_indx = 0;
    char data_to_send[] = "Hello Leanordo\n";
    char received_data[300] = "none";
    int fd = wiringPiI2CSetup(DEVICE_ID);
    if (fd == -1) {
        cout << "Failed to init I2C communication.\n";
        return -1;
    }
    cout << "I2C communication successfully setup.\n";
    // Send data to arduino
    while(true) {
        for (int i = 0; i < sizeof(data_to_send); i++)
        {
            wiringPiI2CWrite(fd, data_to_send[i]);
        }
        cout << "Sent data: " << data_to_send << "\n";

        recv_indx = 0;
        while(true) {
            received_char = wiringPiI2CRead(fd);
            cout << "\r" << "Char received: " << received_char << flush;
            if (received_char > 0)
            {
                received_data[recv_indx] = received_char;
                received_char = 0;
                recv_indx++;
                break;
            }
            if (received_char == 32)
            {
                break;
            }
        }
        cout << "Data received: " << received_data << "\n";
    }
    return 0;
}
