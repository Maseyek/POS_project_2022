#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX

#define trigPin 6  
#define echoPin 5
#define buzzer 4
float new_delay; 
int counter = 0;
int bufindex = 0;


void setup() 
{
  Serial.begin (9600); 
  BTserial.begin(9600);
  pinMode(trigPin, OUTPUT); //TrigPin ustawiony jako output
  pinMode(echoPin, INPUT); //EchoPin ustawiony jako input
  pinMode(buzzer,OUTPUT); //Buzzer jako output
}


void loop() 
{
  float buff[100];
  long duration, distance;

  //ustawienie stanu wysokiego na 2 uS - impuls inicjalizujacy
  digitalWrite(trigPin, LOW);     //trigpin na LOW -> 0   
  delayMicroseconds(2);          

  //ustawienie stanu wysokiego na 10 uS - impuls inicjalizujacy
  digitalWrite(trigPin, HIGH); //trigpin jako high -->1
  delayMicroseconds(10);          
   
  digitalWrite(trigPin, LOW); ////trigpin na LOW -> 0  
  
  duration = pulseIn(echoPin, HIGH); //pulseIn odczytuje gdy wartosc na echoPin jest '1'
  distance = duration/58; //szerokość odbitego impulsu w uS podzielone przez 58 to odleglosc w cm
  
  new_delay= (distance *3) +30; //przyspieszenie działania buzzera wraz ze zmniejszeniem się dystansu

  if(bufindex<100)
  {
    buff[bufindex] = distance;
  
    if (bufindex >= 25) //gdy dojdzie do 1/4 zawatosci bufora
    {
      if (bufindex < 75) 
      {
          buff[bufindex] = buff[bufindex + 25]; //przesun okno bufora
      }
      else
      {
          buff[bufindex] = distance; //zapisuj dalej dane
      }
    }
      
    if((distance > 2) && (distance<50)) //jeśli miesci sie w zakresie
    {
      digitalWrite(buzzer,HIGH); //wlacz buzzer
      delay(new_delay);
      digitalWrite(buzzer,LOW); //wylacz buzzer
      
      counter += 1;
      
      if (counter >= 2)
      {
        //wysylanie po porcie szeregowym
        Serial.print("Detekcja: ");
        Serial.print(counter);
        Serial.print(",");
        Serial.println("ALARM");
        Serial.println(distance);
        //wysylanie po Bluetoothie
        BTserial.println("alarm");
      }
         
      bufindex+=1;
    }  
    else
    {
      digitalWrite(buzzer,LOW);//wylacz buzzer
      //wysylanie po porcie szeregowym
      Serial.println("bezpieczny");
      //wysylanie po Bluetoothie
      BTserial.println("bezpieczny"); 
     } 
  }
  else 
  {
    bufindex = 0;
    counter = 0;
  }
 delay(200);
}
