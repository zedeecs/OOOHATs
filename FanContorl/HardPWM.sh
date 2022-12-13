#!/bin/bash

iPeriod=$((1000000000/$1))
iDuty_cycle=$(($iPeriod*$2/100))

dev_path="/sys/class/pwm/pwmchip0"
# echo 0 > $dev_path"/export"

pwm_path=$dev_path"/pwm0"

echo "normal" > $pwm_path"/polarity"

echo 1 > $pwm_path"/enable"

echo 0 > $pwm_path"/duty_cycle"

echo $iPeriod > $pwm_path"/period"
echo $iDuty_cycle > $pwm_path"/duty_cycle"