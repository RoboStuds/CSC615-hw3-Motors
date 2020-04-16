/*
There are delays in this one that would allow it to stop it is to let anyone who wants to try my code. I am not 
sure if it works but I made sure of it. 

*/

#include <wiringPi.h>
#include <softPwm.h>
const int MOTORCOUNT = 2;

// enable fwd reverse
const int MOTORS[2][3] = {11, 15, 13,
                          22, 16, 18}; // for the pins 

int moveMotors(int fwd, int reverse, int speed, int range)
{
    if (softPwmCreate(MOTORS[0][0], 0, range) != 0 && softPwmCreate(MOTORS[1][0], 0, range) != 0)
    {
        return -1;
    }
    for (int motorNum = 0; motorNum < MOTORCOUNT; motorNum++)
    {
      // depending on moving fwd and reverse if fwd 1 is 1 then it is moving forward. 
        digitalWrite(MOTORS[motorNum][0], 1); // e
        digitalWrite(MOTORS[motorNum][1], fwd); // fwd
        digitalWrite(MOTORS[motorNum][2], reverse); // reverse
    }
    // determine the speed
    softPwmWrite(MOTORS[0][0], speed);
    softPwmWrite(MOTORS[1][0], speed);
    delay(2000); // 2 seconds of spinning
    for (int off = 0; off < MOTORCOUNT; off++)
    {
        digitalWrite(MOTORS[off][0], 0); // e
        digitalWrite(MOTORS[off][1], 0); // fwd
        digitalWrite(MOTORS[off][2], 0); // reverse
    }
    delay(3000); // 3 seconds of letting cool then again
    return 0;
}
int main (void)
{
    if (wiringPiSetup() == -1)
    {
        return 0;
    }
    for (int i = 0; i < MOTORCOUNT; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            
            pinMode (MOTORS[i][j], OUTPUT);
            digitalWrite(MOTORS[i][j], LOW);
        }
    }
    if (moveMotors(1, 0, 20, 100) == -1 || moveMotors(1, 0, 10, 100) == -1)
    {
        return 0;
    }
    if (moveMotors(0, 1, 20, 100) == -1 || moveMotors(0, 1, 10, 100) == -1)
    {
        return 0;
    }
    
        
    return 0 ;
}
