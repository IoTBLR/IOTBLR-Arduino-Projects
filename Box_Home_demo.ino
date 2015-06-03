
#define TRUE 1
#define FALSE 0
#define DEBUG TRUE

#define LIGHT_LOW_THRESHOLD 400
int pirPin = 7;    //the digital pin connected to the PIR sensor's output
int ledPin = 2;
const int ldrpin=A0;

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 15;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  




/////////////////////////////
//SETUP
void setup(){
#if(DEBUG == TRUE)
  Serial.begin(9600);
#endif
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  //give the sensor some time to calibrate
#if(DEBUG == TRUE)
  Serial.print("calibrating sensor ");
#endif
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
  }
#if(DEBUG == TRUE)
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
#endif
  delay(50);
}
uint8_t motionFlag=0;
////////////////////////////
//LOOP
void loop(){

  int sensorValue = 0; 


  sensorValue = analogRead(ldrpin); 

  if(digitalRead(pirPin) == HIGH){

    if(lockLow){  
      //makes sure we wait for a transition to LOW before any further output is made:
      lockLow = false; 
      motionFlag = 1;  
#if(DEBUG == TRUE)      
      Serial.println("---");
      Serial.print("motion detected at ");
      Serial.print(millis()/1000);
      Serial.println(" sec"); 

#endif
      delay(50);
    }         
    takeLowTime = true;
  }

  if(digitalRead(pirPin) == LOW){       


    if(takeLowTime){
      lowIn = millis();          //save the time of the transition from high to LOW
      takeLowTime = false;       //make sure this is only done at the start of a LOW phase
    }
    //if the sensor is low for more than the given pause, 
    //we assume that no more motion is going to happen
    if(!lockLow && millis() - lowIn > pause){  
      //makes sure this block of code is only executed again after 
      //a new motion sequence has been detected
      lockLow = true;        
      motionFlag=0;
#if(DEBUG == TRUE)      
      Serial.print("motion ended at ");      //output
      Serial.print((millis() - pause)/1000);
      Serial.println(" sec");
#endif
      delay(50);
    }
  }

  //check to switch on the LED when light is low and there is motion
  if((sensorValue < LIGHT_LOW_THRESHOLD) && (motionFlag ==1))
  {
#if(DEBUG == TRUE)
    Serial.print("sensor = " );                       
    Serial.println(sensorValue);  
#endif

    digitalWrite(ledPin,250);
    //delay(pause);
  }
  else
  {
    digitalWrite(ledPin,LOW);
  }

}






