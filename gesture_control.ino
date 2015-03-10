
/*
 ADXL3xx
 
 Reads an Analog Devices ADXL3xx accelerometer and communicates the
 acceleration to the computer.  The pins used are designed to be easily
 compatible with the breakout boards from Sparkfun, available from:
 http://www.sparkfun.com/commerce/categories.php?c=80
 
 http://www.arduino.cc/en/Tutorial/ADXL3xx
 
 The circuit:
 analog 0: accelerometer self test
 analog 1: z-axis
 analog 2: y-axis
 analog 3: x-axis
 analog 4: ground
 analog 5: vcc
 
 created 2 Jul 2008
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe 
 
 This example code is in the public domain.
 
 */

// these constants describe the pins. They won't change:
const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)
void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);

  // Provide ground and power by using the analog inputs as normal
  // digital pins.  This makes it possible to directly connect the
  // breakout board to the Arduino.  If you use the normal 5V and
  // GND pins on the Arduino, you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW); 
  digitalWrite(powerpin, HIGH);
}
const float a = 0.5;
float x,y,z,Total;
#define ZEROBIAS 1.65
#define TOTAL_THRESHOLD 25
#define NEXT_THRESHOLD -10
#define PREVIOUS_THRESHOLD 10

void loop()
{

  x = analogRead(xpin);
  y = analogRead(ypin);
  z = analogRead(zpin);

  x = (x * 5)/1024;
  x = (x - ZEROBIAS)*1000/330;
  x = x* 9.8;

  y = (y * 5)/1024;
  y = (y - ZEROBIAS)*1000/330;
  y = y* 9.8;

  z = (z * 5)/1024;
  z = (z - ZEROBIAS)*1000/330;
  z = z* 9.8;
  Total = sqrt(x*x + y*y + z*z);
 // Serial.print("T :");  Serial.println(Total);
  //Serial.print("Y :");Serial.println(y);
  //Serial.print("z :");  Serial.println(z);


  if(Total > TOTAL_THRESHOLD)
  {
    if(z < NEXT_THRESHOLD)
    {

      Serial.println("next");//Serial.print("z :");Serial.println(z);

      delay(500);
      goto here;
    }
    if(z > PREVIOUS_THRESHOLD)
    {
      Serial.println("Previous");//Serial.print("z :");Serial.println(z);

      delay(250);
    }
  }
here:;


}





