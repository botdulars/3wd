//botdulars buzzer program 

const int buzzer = 4; //buzzer to arduino pin 4
const int buttonPin =12;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status


void setup(){
 
  pinMode(buttonPin, INPUT); 
  Serial.begin(9600); 
  pinMode(buzzer, OUTPUT); 

}

void loop(){
  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState); 
  digitalWrite(buzzer, HIGH); 
  noTone(buzzer);     
   if (buttonState == LOW){
      digitalWrite(buzzer, LOW); 
      //tone(buzzer, 1000); // Send 1KHz sound signal...
      delay(1000);        // ...for 1 sec
   }
   else
   {
      digitalWrite(buzzer, HIGH) ; 
      delay(1000);        // ...for 1sec        
   }
  
}
