// 检测旋转编码器状态，并且输出到屏幕
// +----------------------------+
// | ENCODER_A = 1              |
// | ENCODER_B = 0              |
// | ENCODER_S = 1              |
// |                            |
// +----------------------------+


#include <stdio.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "../OLED/ssd1306_i2c.h"

#define ENCODER_A 3
#define ENCODER_B 4
#define ENCODER_S 6

#define MAX_SIZE 32

int counter = 0;
int currentState_ENCODER_A;
int lastState_ENCODER_A;
char currentDir = 'A';
unsigned long lastButtonPress = 0;

char A_stat[MAX_SIZE];
char B_stat[MAX_SIZE];
char S_stat[MAX_SIZE];

void main(void)
{
    wiringPiSetup();

    pinMode(ENCODER_A, INPUT);
    pinMode(ENCODER_B, INPUT);
    pinMode(ENCODER_S, INPUT);

    ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);

    printf("init ok!\n");

    while (1)
    {
        sprintf(A_stat, "ENCODER_A = %d", digitalRead(ENCODER_A));
        sprintf(B_stat, "ENCODER_B = %d", digitalRead(ENCODER_B));
        sprintf(S_stat, "ENCODER_S = %d", digitalRead(ENCODER_S));

        ssd1306_clearDisplay();
        ssd1306_drawText(0, 0, A_stat);
        ssd1306_drawText(0, 10, B_stat);
        ssd1306_drawText(0, 20, S_stat);

        ssd1306_display();
        delay(10);
    }
}