//botdulars traffic lights program for beginners 

int red = 7;
int green = 8;
int yellow = 3;

void setup(){
    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(yellow, OUTPUT);
    changeLights(); 
}
void loop(){
    //changeLights();
    //delay(2000);
}

void changeLights(){
    // green on, yellow on for 3 seconds
    
    digitalWrite(red, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW); 
    delay(1000);

    // turn off yellow, then turn red on for 3 seconds
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH) ; 
    delay(3000);

    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW) ; 
    delay(3000);

}
