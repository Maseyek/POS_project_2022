#define trigPin 6  
#define echoPin 5
#define buzzer 2
float new_delay; 


void setup() 
{
  Serial.begin (9600); 
  pinMode(trigPin, OUTPUT); //TrigPin ustawiony jako output
  pinMode(echoPin, INPUT); //EchoPin ustawiony jako input
  pinMode(buzzer,OUTPUT); //Buzzer jako output
}


void loop() 
{
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
  
  new_delay= (distance *3) +30;

  //wyswietlenie na monitorze portu szeregowego
  Serial.print(distance);
  Serial.println("  cm");
  if (distance < 50)
  {
   digitalWrite(buzzer,HIGH);
   delay(new_delay);
   digitalWrite(buzzer,LOW);
  }
  else
  {
    digitalWrite(buzzer,LOW);
  }
  
 delay(200);
}
