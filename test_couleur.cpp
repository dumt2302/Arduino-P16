#include <Arduino.h>
#include <librobus.h>
#include "Wire.h"
#include "GroveColorSensor.h"
#include "ChainableLED.h"

#define MOTOR_REVERSED 1 // 1 = moteur inverse B, 0 = moteur correct A
#define CLK_PIN   7
#define DATA_PIN  8
#define NUM_LEDS  1            //Nombre de LEDS RGB

ChainableLED leds(CLK_PIN, DATA_PIN, NUM_LEDS);

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    BoardInit(); //pour librairie
    MOTOR_SetSpeed(0, 0); //Set les moteurs à 0
    MOTOR_SetSpeed(1, 0);
}

void loop()
{
    int rouge, vert, bleu;
    GroveColorSensor colorSensor;
    colorSensor.ledStatus = 1;            //Quand le détecteur est allumé, =1. Quand le détecteur est fermé, =0
    while(1)
    {
        colorSensor.readRGB(&rouge, &vert, &bleu);    //Assigner les couleurs lues aux variables
        delay(300);
        Serial.print("Les valeurs RGB: RGB( ");
        Serial.print(rouge,DEC);
        Serial.print(", ");
        Serial.print(vert,DEC);
        Serial.print(", ");
        Serial.print(bleu,DEC);
        Serial.println(" )");
        colorSensor.clearInterrupt();
        for(int i = 0; i<NUM_LEDS; i++)
        {
            leds.setColorRGB(i, rouge, vert, bleu);
        }
    }
}
