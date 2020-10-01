
/*
Projet: Le nom du script
Equipe: 16
Auteurs: Tristan Dumas, Bastien Bernier-Rousseau,
Description: Breve description du script
Date: 17 septembre 2020
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
int VirageDegre = 0;

/* ****************************************************************************
Vos propres fonctions sont creees ici
**************************************************************************** */
void maFonction(){
  // code

}
//Par : Tristan et Félix 
//Date: 1 octobre
//Description: Convertir 
//
//
void virage(int VirageDegre)
{
  // code
  //la circonférence d'une roue est 23.93894cm
  //la circonférence d'un tour du robot est de 59.6902cm
  //1 degré est égal à 24.934 pulse, donc 25 pulse.

  //définition des variables
    int Arondir;
    float UnPulse = 0.0480;
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
      while (ENCODER_Read(0)<= Arondir)
      {
        MOTOR_SetSpeed(0,0.5);
        MOTOR_SetSpeed(1,-0.5);
      }
      
    }
    else if(VirageDegre<=0)
    {
      while (ENCODER_Read(1)<= Arondir)
      {
         MOTOR_SetSpeed(0,-0.5);
         MOTOR_SetSpeed(1,0.5);
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

  virage(-90);
  delay(3000);
  

  // String helloworld= "Hello World! :P";
    // digitalWrite(13, HIGH);
    // delay(1000);
    // digitalWrite(13, LOW);
    // Serial.print (helloworld);
}