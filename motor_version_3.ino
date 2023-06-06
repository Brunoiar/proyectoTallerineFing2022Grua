#include <Stepper.h>
#include <Servo.h>

bool posicioninicial = false;
const int primerservo_PIN = 12;
const int segundoservo_PIN = 13;
Servo primerservo;
Servo segundoservo;
const int pasosxrev =200;
Stepper motorX (pasosxrev, 8, 9, 10, 11);
Stepper motorZ (pasosxrev, 4, 5, 6, 7);
int i;
volatile int parar;
int interruptPin=2;
int movz = 0;
int movx = 0;
int posx = 0;
int posz = 0;
char letraentrante;
const int pinestado=3;



void setup() {
  
  Serial.begin(9600);
  pinMode(interruptPin, INPUT);
    for (i=4; i<12; i++) {
      pinMode(i, OUTPUT);
      }
  motorX.setSpeed(90);
  motorZ.setSpeed(90);
  primerservo.attach(primerservo_PIN);
  segundoservo.attach(segundoservo_PIN);
  pinMode(pinestado, OUTPUT);
  primerservo.write(0);
  segundoservo.write(0);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), calibrar, LOW);
  while(parar==0){
     motorX.step(1);
      }
  motorX.step(-30);
  parar=0;
  delay(1500);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), calibrar, LOW);
  while(parar==0){
     motorZ.step(-1);
      }
  motorZ.step(300);
  parar=0;
  delay(1500);
    motorX.setSpeed(90);
  motorZ.setSpeed(90);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), stop, LOW);                          
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
      digitalWrite(pinestado, HIGH);
      movx= -posx;
      for (i=0 ; i<=movx && parar==0; i++ ){
        motorX.step(1);
        posx = posx+1;
      }
      delay(500);
      digitalWrite(pinestado, LOW);
    }


    if(letraentrante == 'b'  && parar==0 ){
      digitalWrite(pinestado, HIGH);
      movx= -600 -posx;
      Serial.println(movx);
      for (i=0 ; i>=movx && parar==0; i-- ){
        motorX.step(-1);
        posx = posx-1;
      }
      delay(500);
      digitalWrite(pinestado, LOW);
    }

    if(letraentrante == 'h'  && parar==0 ){
      digitalWrite(pinestado, HIGH);
      primerservo.write(140);
      delay(1000);
      primerservo.write(0);
      delay(1000);
      delay(500);
      digitalWrite(pinestado, LOW);
    }

    if(letraentrante == 'y'  && parar==0 ){
      digitalWrite(pinestado, HIGH);
      segundoservo.write(120);
      delay(1000);
      segundoservo.write(0);
      delay(1000);
      delay(500);
      digitalWrite(pinestado, LOW);
    }

    if(letraentrante == 'q'  && parar==0 ){
      digitalWrite(pinestado, HIGH);
      movz= -posz;
      for (i=0 ; i<=movz && parar==0; i++ ){
        motorZ.step(-1);
        posz = posz+1;
      }
      delay(500);
      digitalWrite(pinestado, LOW);
    }

    if(letraentrante == 'w'  && parar==0 ){
      digitalWrite(pinestado, HIGH);
      movz= -2514 -posz;
      for (i=0 ; i>=movz && parar==0; i-- ){
        motorZ.step(+1);
        posz = posz-1;
      }
      delay(500);
      digitalWrite(pinestado, LOW);
    }

    if(letraentrante == 'e'  && parar==0 ){
      digitalWrite(pinestado, HIGH);
      movz= -5028 -posz;
      for (i=0 ; i>=movz && parar==0; i-- ){
        motorZ.step(+1);
        posz = posz-1;
      }
      delay(500);
      digitalWrite(pinestado, LOW);
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

  
 
