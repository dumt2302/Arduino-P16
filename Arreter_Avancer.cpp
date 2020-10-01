#include <Arduino.h>
#include <LibRobus.h>

int conteur = 0;
void ArretAvancer(float []);

int main()
{
  float tablpulse[] = {10};
  ArretAvancer(tablpulse);
}

void ArretAvancer(float tablpulses[])
{
  do
  {
    MOTOR_SetSpeed(0,0.5);
    MOTOR_SetSpeed(1,0.5);
  } while (ENCODER_Read(0) <= tablpulses[conteur]);

  MOTOR_SetSpeed(0,0.5);
  MOTOR_SetSpeed(1,0.5);

  ENCODER_ReadReset(0);
  conteur++;
}
