
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h> /* include wiringPi library */
#include <softPwm.h>  /* include header file for software PWM */

int main(){
        int PWM_pin = 7;                /* GPIO1 as per WiringPi,GPIO18 as per BCM */
        int intensity;
        wiringPiSetup();                /* initialize wiringPi setup */
        pinMode(PWM_pin,OUTPUT);        /* set GPIO as output */
        softPwmCreate(PWM_pin,1,100);   /* set PWM channel along with range*/
        while (1)
          {
                for (intensity = 0; intensity < 101; intensity++)
                {
                  softPwmWrite (PWM_pin, intensity); /* change the value of PWM */
                  delay (100) ;
                  printf("intensity = %d\n", intensity);
                }
                delay(100);

                for (intensity = 100; intensity >= 0; intensity--)
                {
                  softPwmWrite (PWM_pin, intensity);
                  delay (100) ;
                  printf("intensity = %d\n", intensity);
                }
                delay(100);

        }
}
