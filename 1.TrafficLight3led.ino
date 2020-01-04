//botdulars traffic lights program for beginners 

int red = 7;
int green = 8;
int yellow = 3;

void setup(){
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(yellow, OUTPUT);
    changeLights(); 
    Serial.begin(9600); 
    Serial.println("This program should have demonstrated the LED lights turning ON for 1 second each"); 
}
void loop(){
    //changeLights();
    //delay(2000);
}

void changeLights(){
    // green on, yellow on for 1 second
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW); 
    delay(1000);

    // turn off yellow, then turn red on for 3 seconds
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW) ; 
    delay(1000);

    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH) ; 
    delay(1000);
}
