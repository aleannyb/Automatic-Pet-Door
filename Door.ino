#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

//Assigns the pins for the servo, red led, green led anf ulltrasonic sensor.
const int trigPin = 10;
const int echoPin = 11;
const int redPin = 2;
const int greenPin = 4;

//Assigns a servo and the starting angle will be 0.
Servo servo;
int angle = 10;

float duration, distance;


void setup() {
  servo.attach(8);
  servo.write(angle);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin();
  Serial.begin(9600);

  lcd.backlight();
}

void loop() {


//Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);



//Calculates the distance
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*0.0343)/2;


//Turns on green LED
  if (distance <= 20){       //Adjust distance if needed
    pinMode(greenPin,HIGH);
    pinMode(redPin, LOW);



    lcd.clear();
    lcd.print("Hello pet name!");  //Make sure to edit the pet name here

    //opens door
    for(angle = 10; angle < 180; angle++){
    servo.write(angle);
    delay(15);
    }

    delay(10000);

    //closes door
    for(angle = 180; angle > 10; angle--){
      servo.write(angle);
      delay(15);
    }

    lcd.clear();
  }
  
//Red LED on 
  else {
    pinMode(greenPin, LOW);
    pinMode(redPin, HIGH);
  }



  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);

}
