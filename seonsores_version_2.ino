
bool columnaA [3]={0,0,0};
bool columnaB [3]={0,0,0};
int espaciovacioA; 
int espaciovacioB;
int i;
int cambio=1;
const int interruptPin = 2; 
int tipodecaja=1;
const int pinestado=8;

void setup() {
  Serial.begin(9600);
  for (i=4; i<8; i++) {
    pinMode(i, INPUT);
  }
 pinMode(9, INPUT);
 pinMode(interruptPin, OUTPUT);
 digitalWrite(interruptPin, HIGH);
 pinMode(pinestado, INPUT);
 
}

void loop() {

    if (digitalRead(3)==0 && digitalRead(pinestado)==0){
        tipodecaja=cambio;
      
      
      if(tipodecaja==1){
        encontrarA();
        Serial.print('h');
        delay(3000);
                
        if(espaciovacioA==0){
          Serial.print('y');
          columnaA [espaciovacioA]=1;
          cambio=2;
        }
        if(espaciovacioA==1){
          Serial.print('w');
          Serial.print('y');
          columnaA [espaciovacioA]=1;
          Serial.println('q');
          cambio=2;
          
        }
        if(espaciovacioA==2){
          Serial.print('e');
          Serial.print('y');
          columnaA [espaciovacioA]=1;
          Serial.println('q');
          cambio=2;
          
        }

        delay(3000);

      }


      if(tipodecaja==2){
        encontrarB();
        Serial.print('h');
        delay(3000);
        Serial.print('b');
                
        if(espaciovacioB==0){
          Serial.print('y');
          columnaB [espaciovacioB]=1;
          cambio=1;
          
        }
        if(espaciovacioB==1){
          Serial.print('w');
          Serial.print('y');
          columnaB [espaciovacioB]=1;
          Serial.print('q');
          cambio=1;
          
        }
        if(espaciovacioB==2){
          Serial.print('e');
          Serial.print('y');
          columnaB [espaciovacioB]=1;
          Serial.print('q');
          cambio=1;
          
        } 
        Serial.println('a');
         
      }
    }
      
    if (finalesdecarrera()==true){
    
    digitalWrite(interruptPin, LOW);
    delay(1000);
    digitalWrite(interruptPin, HIGH);
  }
}
  
//FUNCIONES


void encontrarA(){
  for(int i=2; i>=0; i--){
        
    if(columnaA [i]==0){      
      espaciovacioA=i;      
    }

    if(columnaA [0]==1 && columnaA [1]==1 &&  columnaA [2]==1){
      espaciovacioA=987; //si estan todos lo espacios ocupados se almacena 987
    }
        
  } 
}

void encontrarB(){
  for(int i=2; i>=0; i--){
        
    if(columnaB [i]==0){      
      espaciovacioB=i;      
    }

    if(columnaB [0]==1 && columnaB [1]==1 &&  columnaB [2]==1){
      espaciovacioB=987; //si estan todos lo espacios ocupados se almacena 987
    }
        
  } 
}

bool finalesdecarrera(){
  if (digitalRead(4)== LOW || digitalRead(5)== LOW || digitalRead(6)== LOW || digitalRead(7)== LOW  ){
    return true;
  }
  else{
    return false;
  }
}

  
