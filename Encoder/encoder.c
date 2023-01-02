// 检测旋转编码器状态，并且输出到屏幕
// +----------------------------+
// | ENCODER_A = 1              |
// | ENCODER_B = 0              |
// | ENCODER_S = 1              |
// |                            |
// +----------------------------+

#include <stdio.h>

#include <wiringPi.h>
// #include <wiringPiI2C.h>

#include "../OLED/ssd1306_i2c.h"

#define ENCODER_A 3
#define ENCODER_B 4
#define ENCODER_S 6

#define MAX_SIZE 32

int counter = 0;
// int currentState_ENCODER_A;
// int lastState_ENCODER_A;
char currentDir = 0;
// unsigned long lastButtonPress = 0;

// char A_stat[MAX_SIZE];
// char B_stat[MAX_SIZE];
// char S_stat[MAX_SIZE];
char R_stat[MAX_SIZE];
int A_stat = 0;
int B_stat = 0;

void A(void)
{
    // A_stat = digitalRead(ENCODER_A);
    B_stat = digitalRead(ENCODER_B);

    if (A_stat = B_stat)
    {
        counter++;
        currentDir = 'S';
    }
    else
    {
        counter--;
        currentDir = 'I';
    }
    return;
}


void S(void)
{
    counter = 0;
    return;
}

void main(void)
{
    wiringPiSetup();

    pinMode(ENCODER_A, INPUT);
    pinMode(ENCODER_B, INPUT);
    pinMode(ENCODER_S, INPUT);

    wiringPiISR(ENCODER_A, INT_EDGE_RISING, &A);
    // wiringPiISR(ENCODER_B, INT_EDGE_RISING, &B);
    wiringPiISR(ENCODER_S, INT_EDGE_FALLING, &S);

    ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);

    printf("init ok!\n");
    // lastState_ENCODER_A = digitalRead(ENCODER_A);

    while (1)
    {
        // currentState_ENCODER_A = digitalRead(ENCODER_A);

        // sprintf(A_stat, "ENCODER_A = %d", digitalRead(ENCODER_A));
        // sprintf(B_stat, "ENCODER_B = %d", digitalRead(ENCODER_B));
        // sprintf(S_stat, "ENCODER_S = %d", digitalRead(ENCODER_S));
        sprintf(R_stat, "counter= %d, Dir= %c", counter, currentDir);

        ssd1306_clearDisplay();
        // ssd1306_drawText(0, 0, A_stat);
        // ssd1306_drawText(0, 8, B_stat);
        // ssd1306_drawText(0, 16, S_stat);
        ssd1306_drawText(0, 24, R_stat);
        ssd1306_display();

        // lastState_ENCODER_A = currentState_ENCODER_A;

        delay(1);
    }
}
