#include <Wire.h> // Librairie pour la communication I2C
#include <Servo.h>
#include <Braccio.h>
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;
long Temps = 0 ; 
int x = 21 ;
int y = 23 ;

//***************************FONCTION DELAY************************************
void pause (int tmp)
{ 
  Temps = millis();
  while((millis() - Temps )  < tmp ) {}
}

//**************************FONCTION CALCUL BRAS ROBOT****************************
void Brasrobot( float x , float y )
{
//cas d'un bras motorisé a 3 segments
    int   r1 = 13;
    float r2 = 12.5;
    int   r3 = 19;
    float r4 = 0;
    float r = sqrt(pow(x,2)+pow(y,2));
    float alpha=0.0;
    float beta = 0.0;
    float beta1 = 0.0;
    float beta2 = 0.0;
    float gamma =0.0;
    float gamma1 = 0.0;

    // début calcul alpha
     if (x<20)
     {
      alpha = 90-(atan(x/20))*180/PI; // angle de rotation du moteur pour cadrant sup gauche
      alpha = alpha*0.75;
      r4 = sqrt(pow(r1,2)+ pow(r,2) - 2*r1*r2*cos(alpha));
      Serial.print("je suis r4");
      Serial.println(r4);
      
      }
     if (x>20)
     {
      alpha =90+( (atan(x/20))*180/PI); // angle de rotation du moteur pour cadrant sup droit
      alpha = alpha*0.75;
      r4 = sqrt(pow(r1,2)+ pow(r,2) - 2*r1*r2*cos(alpha));
      Serial.print("je suis r4");
      Serial.println(r4);      
     }
     if (x==0)
     {
      alpha = 90; 
     }
     // fin calcul de alpha
     // debut calcul beta1
     beta1=acos((pow(r1,2)+pow(r4,2)-pow(r,2))/(2*r1*r4))*180/PI;
     // fin calcul beta1
     // debut calcul beta2
     beta2=acos((pow(r4,2)+pow(r2,2)-pow(r3,2))/(2*r4*r2))*180/PI;
     // fin calcul beta2
     // debut calcul beta 
     beta = PI-beta1-beta2;
     // fin calcul beta
     // debut calcul gamma1
     gamma1=acos((pow(r2,2)+pow(r3,2)-pow(r4,2))/(2*r2*r3))*180/PI;
     // fin calcul gamma1
     // debut calcul gamma
     gamma=PI-gamma1;
     // fin calcul gamma
     Serial.print("je suis alpha :");
     Serial.println(alpha);
     Serial.print("je suis beta1");
     Serial.println(r4);
     Serial.print("je suis beta2");
     Serial.println(r4);
     Serial.print("je suis beta ");
     Serial.println(r4);
     Serial.print("je suis gamma1");
     Serial.println(r4);
     Serial.print("je suis gamma");
     Serial.println(r4);

  Braccio.ServoMovement(20, alpha, 90, beta, gamma, 90, 73);
  //Braccio.ServoMovement(20, alpha, 90, beta, gamma, 90, 75);  
}

// Fonction qui s execute si quelque chose est present sur l interface
void receiveEvent(int howMany)
{
int x = Wire.read(); // recevoir un chiffre
int y = Wire.read();
Serial.println(x); // afficher ce chiffre sur l'interface serie
Serial.println(y);
Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 73);
pause(5000);
Brasrobot(x,y);
pause(5000);
Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 73);
return
delay(1000);
}

void setup()
{
Wire.begin(4); // Rejoindre le bus à l'adresse #4
Wire.onReceive(receiveEvent); // Preparer une fonction spécifique a la reception de donnee
Serial.begin(9600); // Demarrer la liaison serie avec le PC
Braccio.begin();
}

void loop()
{
  delay(100);
}
