#include <Arduino.h>
#include <librobus.h>

int conteur = 0;
int32_t EncodeurDroite = 0;
int32_t EncodeurGauche = 0;
int32_t sumDiff = 0;
float vitesse = 0.5;

void MasterSlave(float MasterMOTOR, int32_t MasterENCODEUR, int32_t SlaveENCODEUR);
void ArretAvancer(float []);

void setup(){
  BoardInit();
}

void ArretAvancer(float tablpulses[])
{
  do
  {
    MOTOR_SetSpeed(0,0.5);
    MasterSlave(vitesse, ENCODER_Read(0), ENCODER_Read(1));
  } 
  while (ENCODER_Read(0) < tablpulses[conteur]);

  MOTOR_SetSpeed(0,0);
  MasterSlave(vitesse, ENCODER_Read(0), ENCODER_Read(1));

  ENCODER_ReadReset(0);
  ENCODER_ReadReset(1);
  conteur++;
}

void MasterSlave(float MasterMOTOR, int32_t MasterENCODEUR, int32_t SlaveENCODEUR)  //Prends en entrée la valeur du moteur maitre et les valeurs d'encodeur
  {
    float SlaveMOTOR = 0;   //valeur du moteur slave
    int32_t Diff_ENCODEUR = MasterENCODEUR - SlaveENCODEUR; //différence de pas entre les deux moteurs
    sumDiff += Diff_ENCODEUR;
    float kp = 0.0010;  //valeur de la constante P
    float ki = 0.00003;  //valeur de la constante I
    SlaveMOTOR = MasterMOTOR + kp * Diff_ENCODEUR + ki * sumDiff ;  //équation de la valeur du moteur slave
    MOTOR_SetSpeed(1, SlaveMOTOR);

  }


void loop() {

  float tablpulse[] = {13367};
  ArretAvancer(tablpulse);
}