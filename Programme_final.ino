                                                                /**********************PROGRAMME DU DoEet - ROB**********************/

/*
Créateurs : DIA Yéro H., ESER Can, SABBADINI Maxime 
Il manque toute la phase d'initialisation qui permettrait d'intégrer la hauteur de la bouche, le nombre de tour que doivent effectuer les moteurs x et z... Il faudrait changer ces moteurs pour avoir 
la position intégrée ce qui faciliterait énormément la tâche. 


Si vous rencontrez des problèmes dans l'écriture de la suite du programme/compréhension de ce dernier, contactez diayeroharouna@hotmail.fr

Un schéma de câblage sera ajouté au fichier.

                                                                
*/

/* LIBRAIRIE UTILISÉE */

//Bibliothèque pour utiliser les servomoteurs
#include <Servo.h> 

//Bibliothèque pour utiliser les moteurs sur Adafruit (Moteurs X et Z)
#include <Wire.h>
#include <Adafruit_MotorShield.h>



/* DÉCLARATION DES CONSTANTES */

//Constante pour le bouton
#define Bouton 3
#define Led_Rouge 5
#define Led_Bleue 7

//Constante pour le servomoteur
#define ServoBranchement 11

//Constante pour les moteurs XZ
#define Nbre_Etapes_Tour 200
#define Vitesse 50
#define Nbr_Step 700




/* DÉCLARATION DES MOTEURS UTILISÉS */

//Servomoteur pour la rotation de l'assiette
Servo Servo_assiette;

//Moteurs X et Z
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_StepperMotor *Motor_x = AFMS.getStepper(Nbre_Etapes_Tour, 2); //Moteur x
Adafruit_StepperMotor *Motor_z = AFMS.getStepper(Nbre_Etapes_Tour, 1); //Moteur z


/* DECLARATION DES FONCTIONS DE MISE, LEVER ET ARRET D'URGENCE DU BOUCLIR */

                /**UTILISÉE UN BOUTON**/

void AppuiBouton(int appuye){
  int duree_appui=0;
  
   // Serial.println("Pas appuyé");

  if (appuye==LOW) { //Logique inverse : LOW = bouton appuyé
   // Serial.println("Say hi"); //ligne de commande de vérification
      while(appuye==LOW && duree_appui <= 1600){
        appuye = digitalRead(Bouton);
        duree_appui = duree_appui + 5;
        Serial.println(duree_appui);
        delay(5);
      }

      if(duree_appui >= 200 && duree_appui <= 700){
        Serial.println("Fonction amener la nourriture");
        digitalWrite(Led_Rouge, HIGH);
        delay(1000);
        SeNourrir();
        digitalWrite(Led_Rouge, LOW);
      }else{
        if(duree_appui >= 1000 && duree_appui <= 1500){
          Serial.println("Fonction tourner l'assiette");
          digitalWrite(Led_Bleue, HIGH);
          delay(1000);
          Rotation_Assiette();
          digitalWrite(Led_Bleue, LOW);
        }
      }
  }  
}

                /**L'assiette tourne d'une 20taine de degré (le servomoteur)**/

void Rotation_Assiette()
{
  Servo_assiette.write(80);
  delay(400);               //Effectue une rotation de l'assiette d'environ 20° (1°<=>0,03s)
  Servo_assiette.write(90); 
  delay(1000);         // A remplacer !!!
}

                

                /**L'action de se nourrir**/

void SeNourrir()
{
  Moteur(3,1);
  Moteur(1,0);
  Moteur(3,0);
  delay(5000);   //Délai pour manger (~5sec). À augmenter ou réduire selon les capacités de l'utilisateur
  Moteur(1,1);
}

                /**Programme pour lancer les moteurs x et z**/

void Moteur(int E, int O) {   //E étant pour le choix du moteur (1 celui de x, 3 de z) ; O le choix de l'orientation (0 pour l'avant, et 2 pour l'arrière).

  switch (E) {
    case 1:   //Action sur le moteur d'axe x
      Serial.println("Translation sur x");
      Motor_x->setSpeed(Vitesse);    //Vitesse de rotation du moteur (Rpm)
      if(O == 0){
        Motor_x->step(Nbr_Step, FORWARD, SINGLE); // Le moteur fait Nbr_Step pas vers l'avant, en mode single
      } else {
        Motor_x->step(Nbr_Step, BACKWARD, SINGLE); // Le moteur fait Nbr_Step pas vers l'arrière, en mode single
      }
      delay(10);
      break;
    case 3:   //Action sur le moteur d'axe z
      Serial.println("Translation sur z");
      Motor_z->setSpeed(Vitesse);    //Vitesse de rotation du moteur (Rpm)
      if(O == 0){
        Motor_z->step(Nbr_Step, FORWARD, SINGLE); // Le moteur fait Nbr_Step pas vers l'avant, en mode single
      } else {
        Motor_z->step(Nbr_Step, BACKWARD, SINGLE); // Le moteur fait Nbr_Step pas vers l'arrière, en mode single
      }
      delay(10);
      break;
  }
  
}                                                                            /********PROGRAMME********/
                                                                            
                /**INITIALISATION DES VARIABLES ET DES PARAMETRES DU PROGRAMME**/
void setup() { // fonction d'initialisation de la carte

  //Vitesse de transfer de données (en bits par seconde)
  Serial.begin(9600);
  
  //Définition du rôle des différents pins utilisés
  pinMode(Bouton, INPUT_PULLUP);
  pinMode(Led_Rouge, OUTPUT);
  pinMode(Led_Bleue, OUTPUT);

  //Branchement du servomoteur pour l'assiette
  Servo_assiette.attach(ServoBranchement);

  //Initialisation des moteurs X et Z
    AFMS.begin();
    
}



                /**LES INSTRUCTIONS DU PROGRAMME**/
void loop() { 

  int appuye = digitalRead(Bouton);
  AppuiBouton(appuye);

}
