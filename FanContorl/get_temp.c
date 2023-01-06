// gcc -o fanctl get_temp.c -lwiringPi -lcrypt -lm -lrt

#include <stdio.h>
#include <stdlib.h>

// Import file control function library
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Import wiringPi/I2C library
#include <wiringPi.h>
// #include <wiringPiI2C.h>

#define TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"
#define MAX_SIZE 20
#define CTL_PIN 2
#define TEMP_FAN_RUN 55
#define TEMP_FAN_STOP 45
#define TEMP_MAX 80

int main(void)
{
    // Define CPU temperature related parameters
    int fd_temp;
    double temp = 0, level_temp = 0;
    char buf[MAX_SIZE];

    // Define I2C related parameters
    //  int fd_i2c;
    wiringPiSetup();
    pinMode(CTL_PIN, OUTPUT);
    // fd_i2c = wiringPiI2CSetup(0x0d);
    // if (fd_i2c < 0)
    // {
    //     fprintf(stderr, "fail to init I2C\n");
    //     return -1;
    // }

    while (1)
    {
        fd_temp = open(TEMP_PATH, O_RDONLY);
        // Determine if the file is open normally
        if (fd_temp < 0)
        {
            fprintf(stderr, "fail to open thermal_zone0/temp\n");
            return -1;
        }

        // Read temperature and judge
        if (read(fd_temp, buf, MAX_SIZE) < 0)
        {
            fprintf(stderr, "fail to read temp\n");
            return -1;
        }

        // Conversion format, the output retains 2 decimal places
        temp = atoi(buf) / 1000.0;
        printf("temp: %.1fC\n", temp);
        close(fd_temp); // turn off file

        if (temp <= TEMP_FAN_STOP)
        {
            // wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x00);
            digitalWrite(CTL_PIN, LOW);
        }
        else if (temp >= TEMP_FAN_RUN && temp < TEMP_MAX)
        {
            // wiringPiI2CWriteReg8(fd_i2c, 0x08, 0x01);
            digitalWrite(CTL_PIN, HIGH);
        }
        else if (temp >= TEMP_MAX)
        {
            // Running Linux OS command using system
            digitalWrite(CTL_PIN, LOW);
            system("shutdown -P now");
        }

        sleep(3);
        // delay(1000);
    }

    return 0;
}
