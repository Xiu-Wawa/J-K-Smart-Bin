// Necessary packages
#include <Servo.h>

int pos = 0;
int Index;


// object initialization
Servo myDropper;


// define variables
// ultrasonic sensor
const int trigPin = 10;
const int echoPin = 11;
float distance = 0;
float duration;

// capacitive sensor
int plastic_sensor = 13;

// stepper motor
int dirPin = 5;
int stepPin = 4;
int enablePin = 6;

int state = LOW;


// servo motor (dropper)
int dropperPin = 9;



void setup() {
  
    // setup for ultrasonic sensor
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // setup for servo motor
    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);


    // setup for capacitive sensor
    pinMode(plastic_sensor, INPUT_PULLUP);

    //setup for stepper motor
    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);
    pinMode(enablePin,OUTPUT);

    digitalWrite(enablePin,LOW);

    
    // setup for servo motor (dropper)
    myDropper.attach(dropperPin); 

    Serial.begin(9600);
}



void loop() {

 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);

 duration = pulseIn(echoPin, HIGH);
 distance = duration*0.034/2;

 //Serial.print("Distance");
 //Serial.println(distance);
 //delay(500);

 
    digitalWrite(dirPin,HIGH);
    int val = digitalRead(plastic_sensor);

    //======================================================================

    // Plastic section
    if (val != state) {
        state = val;
        Serial.print(" Sensor value = ");
        if (state == 0) {
           Serial.println("PLASTIC DETECTED");
           delay(1000);

        // Open the lid (servo motor)
           for (pos = 5; pos <= 65; pos=pos+1); {
            myDropper.write(pos);
            delay(25);
           }
        
           delay(3000);  //Wait 3 seconds
        
           for (pos = 65; pos >= 5; pos=pos-1); {
            myDropper.write(pos);
            delay(25);
           }
        }
        delay(1500);
    }

        

    //======================================================================

    
    // Not plastic section
    else if ((distance <= 9.5)) {
        Serial.print(" Sensor value = ");
        Serial.println("PAPER DETECTED");
        delay(1000);

        //rotate stepper motor
          for (Index = 0; Index <= 200; Index++) {

            digitalWrite(stepPin,HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPin,LOW);
            delayMicroseconds(500);
        }

          // Open the lid (servo motor)
        for (pos = 5; pos <= 65; pos=pos+1) {
            myDropper.write(pos);
            delay(25);
        }
        delay(3000);   //Wait 3 seconds
        

        digitalWrite(dirPin,LOW);

        for (Index = 0; Index <= 200; Index++) {

            digitalWrite(stepPin,HIGH);
            delayMicroseconds(500);
            digitalWrite(stepPin,LOW);
            delayMicroseconds(500);
        }
          

        for (pos = 65; pos >= 5; pos=pos-1); {
            myDropper.write(pos);
            delay(25);
        }

    }
    
    //======================================================================

    // DO NOTHING section
    else {
        Serial.print(" Sensor value = ");
        Serial.println("No Waste");
        delay(1000);
    }
    
    //======================================================================

    //digitalWrite(trigPin, LOW);
    //duration = pulseIn(echoPin, HIGH);
    //distance = (duration * .0343) / 2;

    //Serial.print("Distance: ");
    //Serial.println(distance);
    //delay(100);

    // Close the lid (servo motor)
    
    }
