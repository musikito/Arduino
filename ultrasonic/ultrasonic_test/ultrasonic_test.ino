
#include <Servo.h> //servo library

Servo sonicServo;

int Echo = A4;
int Trig = A5;

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

int rightDistance = 0, leftDistance = 0, middleDistance = 0;

//Ultrasonic distance measurement

int DistanceTest()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}

void setup()
{
  sonicServo.attach(3);  // attach servo on pin 3 to servo object
  Serial.begin(9600);     
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop()
{
  sonicServo.write(90);  //setservo position according to scaled value
    delay(500); 
    middleDistance = DistanceTest();
    Serial.println(middleDistance);

    if(middleDistance <= 20) {     
      Serial.println("stop()");
      delay(500);                         
      sonicServo.write(10);          
      delay(1000);      
      rightDistance = DistanceTest();
      
      delay(500);
      sonicServo.write(90);              
      delay(1000);                                                  
      sonicServo.write(180);              
      delay(1000); 
      leftDistance = DistanceTest();
      
      delay(500);
      sonicServo.write(90);              
      delay(1000);
      if(rightDistance > leftDistance) {
        Serial.println("right()");
        delay(360);
      }
      else if(rightDistance < leftDistance) {
        Serial.println("left()");
        delay(360);
      }
      else if((rightDistance <= 20) || (leftDistance <= 20)) {
        Serial.println("back()");
        delay(180);
      }
      else {
        Serial.println("forward()");
      }
    }  
    else {
        Serial.println("forward()");
    }                     
}
