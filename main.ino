/*
Projet: Fast & Furius - The Sherbie death race ft. Flash Mcqueen
Equipe: 16
Auteurs: Équipe 16 - Cracking a code with da boiiiiz
Description: Permet de parcourir un trajet entré manuelement
Date: 8 octobre
*/

/* ****************************************************************************
Inclure les librairies de functions que vous voulez utiliser
**************************************************************************** */

#include <LibRobus.h> // Essentielle pour utiliser RobUS
#include <Arduino.h> // Essentielle pour l'utilisation



/* ****************************************************************************
Variables globales et defines
**************************************************************************** */
// -> defines...
// L'ensemble des fonctions y ont acces
//identifie le robot A et B
bool A = 0;
bool B = 1;
//indique l.amplitude du virage en degré
int VirageDegre;

//encodeur gauche et droite 
int32_t EncodeurDroite = 0;
int32_t EncodeurGauche = 0;

//sommation de la différence des erreurs
int32_t sumDiff = 0;
/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */


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

//Par : Tristan et Félix 
//Date de dernière modification: 8 octobre 
//Description: permet de faire des virages en degrés
//
//
void virage(int VirageDegre,bool robot)
{
  // code
  //la circonférence d'une roue est 23.93894cm
  //la circonférence d'un tour du robot est de 59.6902cm
  //1 degré est égal à 24.934 pulse, donc 25 pulse.

  //définition des variables
    
    int Arondir;
    float UnPulse;
    if (robot==0){
     UnPulse= 0.0457;
      }
   else{
     UnPulse = 0.0447;
     }

    float ValeurPulse;
    //trouve le nombre de pulse nécessaire au virage
    ValeurPulse = abs(VirageDegre/UnPulse);
    Arondir = round(ValeurPulse);
    
   //réinitialise le compteur de pule de l'encodeur
   ENCODER_Reset(0);
   ENCODER_Reset(1);
  //Permet d'arrêter le virage à la bonne direction. 
  
    //Défini si le virage sera vers la gauche ou vers la droite. Positif est en sense horaire et négatif est anti-horaire. 
      if (VirageDegre>=0)
      {
        ENCODER_Reset(0);
        ENCODER_Reset(1);
        while (ENCODER_Read(0)<= Arondir)
        {
          if (ENCODER_Read(0) <= (Arondir/4)) 
          {
            MOTOR_SetSpeed(0,0.4);
            MOTOR_SetSpeed(1,-0.4);
          }
          else if (ENCODER_Read(0) <= (2*Arondir/4) )
          {
            MOTOR_SetSpeed(0,0.3);
            MOTOR_SetSpeed(1,-0.3);
          }
          else if (ENCODER_Read(0) <= (3*Arondir/4) )
          {
            MOTOR_SetSpeed(0,0.25);
            MOTOR_SetSpeed(1,-0.25);
          }
          else
          {
            MOTOR_SetSpeed(0,0.2);
            MOTOR_SetSpeed(1,-0.2);
          }
          
          
        }
        
      }
      else if(VirageDegre<=0)
      {
        while (ENCODER_Read(1)<= Arondir)
        {
          if (ENCODER_Read(1)<= (Arondir/4))
          {
            MOTOR_SetSpeed(0,-0.4);
            MOTOR_SetSpeed(1,0.4);
          }
          
          else if (ENCODER_Read(1) <= (2*Arondir/4))
          {
            MOTOR_SetSpeed(0,-0.3);
            MOTOR_SetSpeed(1,0.3);
          }
          else if (ENCODER_Read(1) <= (3*Arondir/4))
          {
            MOTOR_SetSpeed(0,-0.25);
            MOTOR_SetSpeed(1,0.25);
          }
          else
          {
            MOTOR_SetSpeed(0,-0.2);
            MOTOR_SetSpeed(1,0.2);
          }
          
        }
        
        
      }
  
  //Arrête la rotation
  MOTOR_SetSpeed(0,0);
  MOTOR_SetSpeed(1,0);
  //réinitialise le compteur de pule de l'encodeur
   ENCODER_Reset(0);
   ENCODER_Reset(1);

}
  

/* ****************************************************************************
Fonctions d'initialisation (setup)
**************************************************************************** */
// -> Se fait appeler au debut du programme
// -> Se fait appeler seulement un fois
// -> Generalement on y initilise les varibbles globales

void setup(){
  BoardInit();

}



/* ****************************************************************************
Fonctions de boucle infini (loop())
**************************************************************************** */
// -> Se fait appeler perpetuellement suite au "setup"

void loop() {
  // SOFT_TIMER_Update(); // A decommenter pour utiliser des compteurs logiciels
  delay(100);// Delais pour décharger le CPU

  virage(720,A);
  delay(1333);
  delay(1333);
}
