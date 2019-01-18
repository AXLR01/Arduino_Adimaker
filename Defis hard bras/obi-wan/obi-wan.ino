#include <Wire.h>
#include "rgb_lcd.h"
#include<SoftwareSerial.h>
rgb_lcd lcd ;
//******BRACCIO
#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;

//*******
const int potentiometre = A0 ; // Pin du Potentiometre
long Temps = 0 ; 
const int PIN_ULTRASONIC = 4 ; // ultrason gauche 
const int PIN_ULTRASONIC2 = 8 ; // ultrason droit
float surface ;
float p ;
float hauteur ;
float pythagore ;
#define DISTANCE 40 // Distance entre les deux capteurs 
long d1 = 0 ; 
long d2 = 0 ; 
float x=10;
float y=27;

int lastBoutonState = 1 ;
//***************************FONCTION LCD******************************************

void afficheurEcranLcd(float x, float y) 
{
  lcd.clear() ; 
  lcd.setCursor(0, 0) ;
  lcd.print("D1=") ;
  lcd.setCursor(8, 0) ;
  lcd.print("D2=") ;
  lcd.setCursor(0, 1) ;
  lcd.print("X=") ;
  lcd.setCursor(8, 1) ;
  lcd.print("Y=") ;
  lcd.setCursor(2, 1) ;
  lcd.print(x) ;
  lcd.setCursor(10, 1) ;
  lcd.print(y) ;
  lcd.setCursor(3, 0) ;
  lcd.print(d1) ;
  lcd.setCursor(11, 0) ;
  lcd.print(d2) ;
}

//***************************FONCTION CALCUL**************************************
void calculXY()
{
  Serial.print("distance capteur 1 =") ;
  Serial.println( readUltrasonic(PIN_ULTRASONIC) ) ;
  Serial.print("distance capteur 2  =") ;
  Serial.println( readUltrasonic(PIN_ULTRASONIC2) ) ;
  d1 = readUltrasonic(PIN_ULTRASONIC) + 1 ;
  d2 = readUltrasonic(PIN_ULTRASONIC2) + 1 ;
  if((d1 < 50) || (d2 < 50))
  {  
    p = (( DISTANCE + d1 + d2 ) /2 ) ;
    surface = sqrt( p* ( p - DISTANCE ) * ( p - d1 ) * ( p - d2 )) ;
    hauteur = (( 2 * surface ) / DISTANCE ) ;
    pythagore = sqrt( pow(d1,2) - ( pow(hauteur,2) )) ;
  }
  else 
  {
    lcd.clear() ;
    lcd.setRGB(255, 0, 0) ;
    lcd.setCursor(3, 0) ;
    lcd.print("OBJET NON") ;  
    lcd.setCursor(4, 1) ;
    lcd.print("DETECTE") ;
    //pause(2000) ;
  }
}

//***************************FONCTION CAPTEUR ULTRASON***************************
long readUltrasonic(int numeroPin) // définition de la fonction du capteur ultrasonique 1
{
  //émission d'une onde
  pinMode(numeroPin, OUTPUT) ;
  digitalWrite(numeroPin, LOW) ;
  delayMicroseconds(2) ;
  digitalWrite(numeroPin, HIGH) ;
  delayMicroseconds(5) ;
  digitalWrite(numeroPin, LOW) ;
  //réception de l'écho
  pinMode(numeroPin, INPUT) ;
  long duration = pulseIn(numeroPin, HIGH) ;
  //transformation du délai en centimètres
  return duration /29 / 2 ;
}

//***************************FONCTION DELAY************************************
void pause (int tmp)
{ 
  Temps = millis() ;
  while((millis() - Temps )  < tmp ) {}
}

//***************************SETUP*********************************************
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  lcd.begin(16, 2) ;
  lcd.setRGB(66, 66, 255) ; //la couleur est bleu 
  pinMode(potentiometre, INPUT) ; 
}

//***************************LOOP**********************************************
void loop()
{ 
 // int state = analogRead(potentiometre) ;
 int state = digitalRead(potentiometre) ;
  if ( state != lastBoutonState ) // Utilisation du potentiomètre comme un bouton ( Dépassement du seuil => Activation ) 
  {
    Serial.println("Debut");
    pause(1000);
    calculXY() ; 
    Serial.println(hauteur);
    Serial.println(pythagore);
    //pause(1000) ; 
    lcd.setRGB(66, 66, 255) ;
    //pause(1000);
    Wire.beginTransmission(4); // Envoyer vers device #4
    Serial.println(x);
    Wire.write(int(x));
    Serial.println(y);
    Wire.write(int(y));// Envoi le contenu de x
    Wire.endTransmission(); // Arreter la transmission   
    pause(1000);
    //afficheurEcranLcd(pythagore, hauteur) ;  
  } 
  else 
  {
    lcd.clear() ;
    lcd.setRGB(0, 255, 255) ;
    lcd.setCursor(2, 0) ;
    lcd.print("BIENVENUE A") ;  
    lcd.setCursor(1, 1) ;
    lcd.print("LA MAKERFAIRE") ;
    //pause(3000) ; 
    lcd.clear() ;
    lcd.setRGB(255, 255, 0) ;
    lcd.setCursor(3, 0) ;
    lcd.print("TOURNEZ LE") ;  
    lcd.setCursor(1, 1) ;
    lcd.print("POTENTIOMETRE") ;
    //pause(3000) ;
  }
  state = lastBoutonState ; 
}
