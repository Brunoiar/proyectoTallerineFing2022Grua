#include <Servo.h>
#include <Arduino.h>
#include "BasicStepperDriver.h"

bool posicioninicial = false;
const int primerservo_PIN = 9;
const int segundoservo_PIN = 10;
Servo primerservo;
Servo segundoservo;
int i;
volatile int parar;
int interruptPin=2;
int posx = 0;
int posy = 0;ss
int movx = 0;
int movy = 0;
char letraentrante;
const int pinestado=3;

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPMX 300
#define RPMY 300

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

#define DIRX 4
#define STEPX 5


#define DIRY 6
#define STEPY 7


// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepperX(MOTOR_STEPS, DIRX, STEPY);
BasicStepperDriver stepperY(MOTOR_STEPS, DIRX, STEPY);




void setup() {
  
  digitalWrite(pinestado, LOW);
  delay(30000); //Demora 30s en arrancar, para evitar conflictos. Iniciar ambos arduino con menos de 30s de diferencia entre ellos.
  parar=0;

  Serial.begin(9600);
  pinMode(interruptPin, INPUT);
    for (i=4; i<12; i++) {
      pinMode(i, OUTPUT);
      }
  
  stepperX.begin(RPMX, MICROSTEPS);
  stepperY.begin(RPMY, MICROSTEPS);

  primerservo.attach(primerservo_PIN);
  segundoservo.attach(segundoservo_PIN);
  pinMode(pinestado, OUTPUT);
  primerservo.write(0);
  segundoservo.write(0);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), calibrar, LOW);
  while(parar==0){
     stepperX.move(1);
      }
  stepperX.move(-30);
  parar=0;
  delay(1500);

  attachInterrupt(digitalPinToInterrupt(interruptPin), calibrar, LOW);
  while(parar==0){
     stepperY.move(-1);
      }
  stepperY.move(300);
  parar=0;
  delay(1500);

  
  attachInterrupt(digitalPinToInterrupt(interruptPin), stop, LOW);   
  digitalWrite(pinestado, HIGH);                       
}

void loop() {
   
  //espera a recibir datos
  while(Serial.available()==0){  
    Serial.println("esperando");
    delay(1500);     
  }
  
  


  while(Serial.available()){

    letraentrante=Serial.read();   
    Serial.print(letraentrante);

    if(letraentrante == 'a'  && parar==0 ){
      digitalWrite(pinestado, LOW);
      movx= -posx;
      for (i=0 ; i<=movx && parar==0; i++ ){
        stepperX.move(1);
        posx = posx+1;
      }
      delay(500);
      digitalWrite(pinestado, HIGH);
    }


    if(letraentrante == 'b'  && parar==0 ){
      digitalWrite(pinestado, LOW);
      movx= -600 -posx;
      Serial.println(movx);
      for (i=0 ; i>=movx && parar==0; i-- ){
        stepperX.move(-1);
        posx = posx-1;
      }
      delay(500);
      digitalWrite(pinestado, HIGH);
    }

    if(letraentrante == 'h'  && parar==0 ){
      digitalWrite(pinestado, LOW);
      primerservo.write(140);
      delay(1000);
      primerservo.write(0);
      delay(1000);
      delay(500);
      digitalWrite(pinestado, HIGH);
    }

    if(letraentrante == 'y'  && parar==0 ){
      digitalWrite(pinestado, LOW);
      segundoservo.write(120);
      delay(1000);
      segundoservo.write(0);
      delay(1000);
      delay(500);
      digitalWrite(pinestado, HIGH);
    }

    if(letraentrante == 'q'  && parar==0 ){
      digitalWrite(pinestado, LOW);
      movy= -posy;
      for (i=0 ; i<=movy && parar==0; i++ ){
        stepperY.move(-1);
        posy = posy+1;  
      }
      delay(500);
      digitalWrite(pinestado, HIGH);
    }

    if(letraentrante == 'w'  && parar==0 ){
      digitalWrite(pinestado, LOW);
      movy= -2514 -posy;
      for (i=0 ; i>=movy && parar==0; i-- ){
        stepperY.move(+1);
        posy = posy-1;
      }
      delay(500);
      digitalWrite(pinestado, HIGH);
    }

    if(letraentrante == 'e'  && parar==0 ){
      digitalWrite(pinestado, LOW);
      movy= -5028 -posy;
      for (i=0 ; i>=movy && parar==0; i-- ){
        stepperY.move(+1);
        posy = posy-1;
      }
      delay(500);
      digitalWrite(pinestado, HIGH);
    }
    
    
  }
      
}
    
void stop(){
  parar=1;
  Serial.println("stop");
  delay(1000); 
}  

void calibrar(){
  parar=1;
  detachInterrupt(digitalPinToInterrupt(interruptPin));  
}

  
 
