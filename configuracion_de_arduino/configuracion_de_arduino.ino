 
#include <SoftwareSerial.h> 
 
SoftwareSerial ModBluetooth(2, 3); // RX | TX 
#define pecho 6
#define ptrig 7
long duracion,distancia,porcentaje;
int atm=0;
 
void setup()  
{ 
    pinMode(10, OUTPUT); 
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    digitalWrite(13, LOW);  
    pinMode(pecho,INPUT);
    pinMode (ptrig,OUTPUT);
    ModBluetooth.begin(9600); 
    Serial.begin(9600);  
    ModBluetooth.println("MODULO CONECTADO");  
    ModBluetooth.print("#");  
} 
 
void loop()  
{  //BLUCLE ULTRASONICO
  digitalWrite(ptrig, LOW);
    delayMicroseconds(2);
    digitalWrite(ptrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(ptrig, LOW);
    duracion = pulseIn(pecho, HIGH);
    distancia =(duracion/2)/29; //distancia en centrimetros
    porcentaje=((distancia*100/19)-100)*-1;
    ModBluetooth.print(porcentaje); 
    ModBluetooth.print("#");
    Serial.print(distancia);
    Serial.println(" cm");
    delay(400);
    if ((atm==1) && (distancia>=5)) {
       digitalWrite(11, HIGH);
    }
    if (distancia<=5){
      digitalWrite(11, LOW);
      }
    
     if (ModBluetooth.available())  
    {   
        char VarChar;
         
       VarChar = ModBluetooth.read();
      
        
       if(VarChar == '0') {
        digitalWrite(10, LOW); 
        delay(100);
       }   
        if(VarChar == '1') {
        digitalWrite(10, HIGH); 
        delay(100);
        }
   
        if(VarChar == '2') 
        { 
        digitalWrite(12, LOW); 
        delay(100); 
        } 
        
        if(VarChar == '3') 
        { 
        digitalWrite(12, HIGH); 
        delay(100); 
        } 

        if(VarChar == '4') 
        { 
        atm=1; 
        } 
        
        if(VarChar == '5') 
        { 
        atm=0;  
        } 
        if(VarChar == '6'  &&  atm == 0) 
        { 
        digitalWrite(11, HIGH); 
        delay(100); 
        } 
        
        if(VarChar == '7'  &&  atm == 0) 
        { 
        digitalWrite(11, LOW); 
        delay(100); 
        } 
    } 
} 
