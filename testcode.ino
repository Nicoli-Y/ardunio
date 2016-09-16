// include the library
#include <MotorLibrary.h>
#include <UltraSonic.h>
#include <IRremote.h>


//MotorLibrary
MotorLibrary motorLibrary;
//UltraSonic
UltraSonic ultraSonic;
//IR
int RECV_PIN = 2;
IRrecv irrecv(RECV_PIN);
decode_results results;



//counter for modes
int counter = 1;
//testing sounds
int Playsounds = 1;
void setup() {
  pinMode(8, OUTPUT); //Piezo
  Serial.begin(9600);
  irrecv.enableIRIn();
 

  // turn on debugging
  motorLibrary.debugMotors(true);
}


void loop() {
   //Test sounds
  if (Playsounds == 1) {
    
    tone(8, 262, 150); //c
    delay(250);
    tone(8, 294, 150); //d
    delay(250);
    tone(8, 330, 150); //e
    delay(250);
    tone(8, 349, 150); //f
    delay(250);
    tone(8, 392, 150); //g
    delay(500);
    Playsounds = 0;
}
  //Distance for Ultrasonic
  long distance = ultraSonic.testUltraSonic();

  // check the serial monitor to see the output
  Serial.print("Object distance (in cm's) = ");
  Serial.println(distance);

// note pin 2 does not work
// changing Modes 
  if (irrecv.decode(&results)) {
    Serial.println(results.actualKey);
     
  
    
    if (results.actualKey == "Power") {
      Serial.println("Power");
      tone(8, 330, 150);
      counter = 1 ; 
     
    }
     if (results.actualKey == "Repeat"){
      tone(8, 294, 150);
      counter = 2;
    }
  irrecv.resume();}
  
//Mode 1  
  if (counter == 1){
 
    Serial.println("mode1");
    //Forward
    if (results.actualKey == "num2"){
       Serial.println(results.actualKey);
       motorLibrary.forward(255);
       tone(8, 262, 150);
    
    } 
    //BackWards
    else if (results.actualKey == "num8"){
         Serial.println(results.actualKey);
         motorLibrary.reverse(255);
         tone(8, 262, 150);  
    } 
    //Right
    else if (results.actualKey == "num6"){
         Serial.println(results.actualKey);
         motorLibrary.hardRight(255);
         tone(8, 262, 150);
    
    }
    //Left
    else if (results.actualKey == "num4"){
         Serial.println(results.actualKey);
         motorLibrary.hardLeft(255);
         tone(8, 262, 150);
    
    }
    //Stop
    else if (results.actualKey == "num5"){
         Serial.println(results.actualKey);
         motorLibrary.stopMotors();
         tone(8, 262, 150);
  }

     }
     //Mode 2
     if (counter == 2){
     Serial.println("mode 2");
 
      //Automatic
      if (distance <= 15) {
        motorLibrary.reverse(255);
        tone(8, 392, 150); 
        delay(200);
        motorLibrary.hardRight(255);
        tone(8, 349, 150); 
        delay(500);
     }
      else if (distance >= 15){
        motorLibrary.forward(255);
    }
  }

     
}



