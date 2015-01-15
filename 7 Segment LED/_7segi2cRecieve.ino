#include <Wire.h>

int number = 0;
int state = 0;
int buttonval = 0;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);        
  Wire.begin(0x04);
  Wire.onReceive(receiveData);
  Wire.onRequest(requestEvent);
}

void loop() {
  buttonval = digitalRead(9);
  if(buttonval == LOW) {
   
    if (number == 1) {
      one();
      delay(1000);
    }
    
    if (number == 2) {
      two();
      delay(1000);
    }
    
    if (number == 3) {
      three();
      delay(1000);
    }
    
    if (number == 4) {
      four();
      delay(1000);
    }
    
    if (number == 5) {
      five();
      delay(1000);
    }
    
    if (number == 6) {
      six();
      delay(1000);
    }
    
    if (number == 7) {
      seven();
      delay(1000);
    }
    
    if (number == 8) {
      eight();
      delay(1000);
    }
    
    if (number == 9) {
      nine();
      delay(1000);
    }
    
    if (number == 0) {
      zero();
      delay(1000);
    }
    
    else {
      nothing();
    }
  }
  
  delay(5);
  
  if(buttonval == HIGH) {
    Serial.print("Done Picking: ");
    Serial.print(number);
    Serial.println(" items");
    while(1) {
      nothing();
    }
  }
  
  delay(5);
}

void receiveData(int byteCount) {

  while(Wire.available()) {

    number = Wire.read();
    Serial.print("data received: ");
    Serial.println(number);
  }
}

void requestEvent() {
  Wire.write(buttonval);                       
}

void one() {
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}

void two() {
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void three() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void four() {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}

void five() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void six() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void seven() {
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}

void eight() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void nine () {
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void zero() {
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

void nothing() {
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
}
