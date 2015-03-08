/*declare the variables used for the problem statement*/

const int led = 3;
const int reedSwitch = 2; 
unsigned long time;
unsigned int boxState;
unsigned int flag =0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);   
  pinMode(reedSwitch,INPUT);
  time = millis();  
}

// the loop routine runs over and over again forever:
void loop()
{
  if(flag == 0)
  {
    if(millis() - time >=5000) // check for expiry of time and set a flag to indicate that its time to take a pill
    {
      flag = 1;
    }
  }
    
   if(flag == 1) 
   {
     // Time to take a pill. So tell the user about it by setting an LED.
     digitalWrite(led, HIGH);
     boxState = digitalRead(reedSwitch);
     if(boxState == HIGH) // if Pill box is opened, then reset the flag, switch off the led and restart the timer.
      {
         flag = 0;
         digitalWrite(led, LOW);
         time = millis();
      }
   }
         
    
}
