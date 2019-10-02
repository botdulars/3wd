//botdulars test program for levels 1 and 2 
#include <SoftwareSerial.h>
#include <math.h>
#include <Servo.h> 
const int thermistor_output = A7;
Servo myServo; 
SoftwareSerial BTSerial(0,1); // for the RX and TX connectivity with BLE 
int value = 0; 
int pos = 0; 
int buttonState = 0;         // variable for reading the pushbutton status
const int buttonPin =12;     // the number of the pushbutton pin
const int greenLED=  8;      // the number of the LED pin
const int trigPin = A4;
const int echoPin = A5;
//Motor A
const int motorPin1  = 10;  // Pin 14 of L293
const int motorPin2  = 9;  // Pin 10 of L293
//Motor B
const int motorPin3  = 6; // Pin  7 of L293
const int motorPin4  = 5;  // Pin  2 of L293


void setup() {
  // put your setup code here, to run once:
  //start with joystick 
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  digitalWrite(A2, HIGH);
  pinMode(A2, INPUT_PULLUP); 

  pinMode(greenLED, OUTPUT);      
  pinMode(7, INPUT);
  //potentiometer
  pinMode(A6, INPUT) ; 
  //trig and echo - ultrasound
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //LDR 
  pinMode(A3, INPUT); 
  //wheels
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  Serial.begin(9600) ; 
  Serial.println("Welcome to the botdulars final program for Levels 1&2") ; 
  
}

void loop() {
  // put your main code here, to run repeatedly:
  value = Serial.parseInt() ; 

  if (Serial.available() && (value>0) )
  {
    //value = (int)value ; 
    Serial.print("received input from BLE as:") ; 
    Serial.println(value) ; 
    if (value==1) showPotValue() ; 
    else if (value == 2) showJoystickReadings() ; 
    else if (value == 3) showUltrasonicValues() ; 
    else if (value == 4) showTemp() ; 
    else if (value == 5) showLuminance() ; 
    else if (value == 6) turnONGreenLED() ;  
    else if (value == 7) servoTest() ; 
    else if (value == 8) wheelSpin() ; 

    //while (Serial.available() && Serial.read()); // empty buffer 
  }
}
void showPotValue() 
{
  int potval = analogRead(A6);          //Read and save analog value from potentiometer
  //potval = map(value, 0, 1023, 0, 255); //Map value 0-1023 to 0-255 (PWM)
  Serial.print("Potentiometer value:"); 
  Serial.println(potval) ;   
}

void showJoystickReadings() 
{
  int xPosition = analogRead(A0);
  int yPosition = analogRead(A1);
  int SW_state = digitalRead(A2);
  int mapX = map(xPosition, 0, 1023, 512, -512);
  int mapY = map(yPosition, 0, 1023, -512, 512);
  
  Serial.print("X: ");Serial.print(mapX); 
  Serial.print(" | Y: "); Serial.print(mapY);
  Serial.print(" | Button: ");  Serial.println(SW_state);
   
}

void showUltrasonicValues()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000);
}

void showTemp() 
{
  int thermistor_adc_val;
  double output_voltage, thermistor_resistance, therm_res_ln, temperature; 
  thermistor_adc_val = analogRead(thermistor_output);
  output_voltage = ( (thermistor_adc_val * 5.0) / 1023.0 );
  thermistor_resistance = ( ( 5 * ( 10.0 / output_voltage ) ) - 10 ); /* Resistance in kilo ohms */
  thermistor_resistance = thermistor_resistance * 1000 ; /* Resistance in ohms   */
  therm_res_ln = log(thermistor_resistance);
  /*  Steinhart-Hart Thermistor Equation: */
  /*  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)   */
  /*  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
  temperature = ( 1 / ( 0.001129148 + ( 0.000234125 * therm_res_ln ) + ( 0.0000000876741 * therm_res_ln * therm_res_ln * therm_res_ln ) ) ); /* Temperature in Kelvin */
  temperature = temperature - 273.15; /* Temperature in degree Celsius */
  Serial.print("Temperature in degree Celsius = ");
  Serial.print(temperature);
  Serial.print("\t");
  Serial.print("Resistance in ohms = ");
  Serial.println(thermistor_resistance);
}

void showLuminance()
{
  int ldrStatus = analogRead(A3);
  Serial.print("Luminance value:") ; 
  Serial.println(ldrStatus);  
}

void pushButton()
{

}

void servoTest() 
{
  Serial.println("running servo sweep..") ;
  myServo.attach(11);  // attaches the servo on pin 9 to the servo object
  for (pos = 0; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
}

void wheelSpin()
{
    //This code  will turn Motor A clockwise for 2 sec.
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, HIGH);
    delay(300); 
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    digitalWrite(motorPin3, HIGH);
    digitalWrite(motorPin4, LOW);
    delay(300); 
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4, LOW);
    
  
}

void turnONGreenLED() 
{
    digitalWrite(greenLED, HIGH);  
    Serial.println("This instruction turns the green LED ON for 1 sec") ; 
    delay(1000); 
    digitalWrite(greenLED, LOW); 
  
}

