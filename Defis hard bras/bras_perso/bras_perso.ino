#include <Wire.h>
#include <Braccio.h>
#include <Servo.h>
Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_ver;
Servo wrist_rot;
Servo gripper;
long Temps = 0 ;
float x= 21;  //************************** ENTRE LES VALEURS ICI *************************************************
float y = 20;//************************** ENTRE LES VALEURS ICI *************************************************
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
    x = x-20;
    float   r1 = 12.5;
    float r2 = 12.5;
    float   r3 = 12.5;
    
    float r = sqrt(pow(x,2)+pow(y,2));
    float alpha=0.0;
    float r4=0.0;
    float beta = 0.0;
    float beta1 = 0.0;
    float beta2 = 0.0;
    float gamma =0.0;
    float gamma1 = 0.0;

    // début calcul alpha
     if (x<0)
     {
      alpha = 90-(atan(x/20))*180/PI; // angle de rotation du moteur pour cadrant sup gauche
      alpha= alpha*0.75;
      r4= sqrt(569-520*cos(alpha));
      }
     if (x>0)
     {
      alpha =90+( (atan(x/20))*180/PI); // angle de rotation du moteur pour cadrant sup droit
      alpha= alpha*0.75;
      r4= sqrt(569-520*cos(alpha));
      
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
     beta =180-beta1-beta2;
     // fin calcul beta
     // debut calcul gamma1
     gamma1=acos((pow(r2,2)+pow(r3,2)-pow(r4,2))/(2*r2*r3))*180/PI;
     // fin calcul gamma1
     // debut calcul gamma
     gamma=90-gamma1;
     // fin calcul gamma

     Serial.print("je suis r ");
     Serial.println(r);
     Serial.print("je suis r1 ");
     Serial.println(r1);
     Serial.print("je suis r2 ");
     Serial.println(r2);
     Serial.print("je suis r3 ");
     Serial.println(r3);
     Serial.print("je suis r4 ");
     Serial.println(r4);
     
     
     Serial.println("debut listing");
     Serial.print("je suis alpha ");
     Serial.println(alpha);
     Serial.print("je suis beta1 ");
     Serial.println(beta1);
     Serial.print("je suis beta2 ");
     Serial.println(beta2);
     Serial.print("je suis beta ");
     Serial.println(beta);
     Serial.print("je suis gamma1 ");
     Serial.println(gamma1);
     Serial.print("je suis gamma ");
     Serial.println(gamma);
  Braccio.ServoMovement(20, alpha, 90, beta, gamma, 90, 12);
  //Braccio.ServoMovement(20, alpha, beta, gamma, 90, 90, 75);
  
}

void setup()
{
  Serial.begin(9600);
  Braccio.begin();
}


void loop()
{
  //Brasrobot(x,y); //*************** Go au coordonées ****************************************
  //pause(1000);
  Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 73);  //*************** teste rotation droite bras****************************************
  pause(2000);
  Braccio.ServoMovement(20, 75, 70, 20, 20, 135, 10);  //*************** teste rotation droite bras****************************************
  pause(1000);
  Braccio.ServoMovement(20, 75, 70, 20, 20, 135, 73);  //*************** teste rotation droite bras****************************************
  pause(1000);
  Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 73);  //*************** teste rotation droite bras****************************************
  pause(1000);
  Braccio.ServoMovement(20, 75, 70, 20, 20, 135, 73);  //*************** teste rotation droite bras****************************************
  pause(1000);
  Braccio.ServoMovement(20, 75, 70, 20, 20, 135, 10);  //*************** teste rotation droite bras****************************************
  pause(1000);
  //Braccio.ServoMovement(10, 45, 90, 90, 90, 90, 10);  //*************** teste rotation droite gauche****************************************
  //pause(2500);
  Braccio.ServoMovement(20, 90, 90, 90, 90, 90, 73);//*************** retour pos initiale ****************************************
 
}
