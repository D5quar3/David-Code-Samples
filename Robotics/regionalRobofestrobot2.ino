#include <Servo.h>
#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 3
#define TxD 2

#define DEBUG_ENABLED  1

SoftwareSerial blueToothSerial(RxD,TxD);


#define ENCA 7
#define ENCB 6
#define ENCC 5

Servo a;
Servo b;
Servo c;

void driveX(int time) {
 int startA;
 int startB;
 int startC;
 int encA;
 int encB;
 int encC;
 int errB;
 int errC;
 float cmdB;
 float cmdC;
 float G = 2;
 unsigned long startTime = millis();
 a.write(180);
 b.write(85);
 c.write(88);
 encoder(startA, startB, startC);   
 while(1) {
   delay(10);
   encoder(encA, encB, encC);
   encA -= startA;
   encB -= startB;
   encC -= startC;
   errB = encB - (encA/2);
   errC = encC - (encA/2);
   cmdB = 85 + (G*errB);
   cmdC = 88 + (G*errC);
   b.write(cmdB);
   c.write(cmdC);
   if(millis() - startTime >= time) {
     break;
   }
 }
 Stop();
}

void driveY(int time) {
 int startA;
 int startB;
 int startC;
 int encA;
 int encB;
 int encC;
 int errA;
 int errC;
 float cmdA;
 float cmdC;
 float G = 2;
 unsigned long startTime = millis();
 a.write(90);
 b.write(0);
 c.write(180);
 encoder(startA, startB, startC);   
 while(1) {
   delay(10);
   encoder(encA, encB, encC);
   encA -= startA;
   encB -= startB;
   encC -= startC;
   errC = encC - (encB);
   cmdC = 180 + (G*errC);
   c.write(cmdC);
   if(millis() - startTime >= time) {
     break;
   }
 }
 Stop();
}


void driveXOpp(int time) {
 int startA;
 int startB;
 int startC;
 int encA;
 int encB;
 int encC;
 int errB;
 int errC;
 float cmdB;
 float cmdC;
 float G = 1;
 unsigned long startTime = millis();
 a.write(0);
 c.write(105);
 b.write(89.6);
 encoder(startA, startB, startC);   
 while(1) {
   delay(10);
   encoder(encA, encB, encC);
   encA -= startA;
   encB -= startB;
   encC -= startC;
   errB = encB - (encA/2);
   errC = encC - (encA/2);
   cmdB = 105 - (G*errB);
   cmdC = 89.6 - (G*errC);
   if(cmdB <= 90) cmdB = 92 ;
   c.write(cmdB);
   b.write(cmdC);
   if(millis() - startTime >= time) {
     break;
   }
 }
 Stop();
}

void driveYOpp(int time) {
  int startA;
 int startB;
 int startC;
 int encA;
 int encB;
 int encC;
 int errA;
 int errC;
 float cmdA;
 float cmdC;
 float G = 2;
 unsigned long startTime = millis();
 a.write(90);
 b.write(180);
 c.write(0);
 encoder(startA, startB, startC);   
 while(1) {
   delay(10);
   encoder(encA, encB, encC);
   encA -= startA;
   encB -= startB;
   encC -= startC;
   errC = encC - (encB);
   cmdC = 0 + (G*errC);
   c.write(cmdC);
   if(millis() - startTime >= time) {
     break;
   }
 }
 Stop();
  
}

void Stop() {
  a.write(90);
  b.write(90);
  c.write(90);
}

void encoder(int &outA, int &outB, int &outC) {
  static int aCount = 0;
  static int bCount = 0;
  static int cCount = 0;
  int valA = digitalRead(ENCA);
  int valB = digitalRead(ENCB);
  int valC = digitalRead(ENCC);
  static int lastPosA = 0; 
  static int lastPosB = 0;
  static int lastPosC = 0;
  if(valA != lastPosA) {
    aCount++;
    lastPosA = valA;
  }
  if(valB != lastPosB) {
    bCount++;
    lastPosB = valB;
  }
  if(valC != lastPosC) {
    cCount++;
    lastPosC = valC;
  }
  
  outA = aCount;
  outB = bCount;
  outC = cCount;
}

void setupBlueToothConnection()
{
    blueToothSerial.begin(38400);                           // Set BluetoothBee BaudRate to default baud rate 38400
    blueToothSerial.print("\r\n+STWMOD=0\r\n");             // set the bluetooth work in slave mode
    blueToothSerial.print("\r\n+STNA=SeeedBTSlave\r\n");    // set the bluetooth name as "SeeedBTSlave"
    blueToothSerial.print("\r\n+STOAUT=1\r\n");             // Permit Paired device to connect me
    blueToothSerial.print("\r\n+STAUTO=0\r\n");             // Auto-connection should be forbidden here
    delay(2000);                                            // This delay is required.
    blueToothSerial.print("\r\n+INQ=1\r\n");                // make the slave bluetooth inquirable
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);                                            // This delay is required.
    blueToothSerial.flush();
}

void setup() {
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(ENCC, INPUT);
  a.attach(11);
  b.attach(10);
  c.attach(9);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  Stop();
  setupBlueToothConnection();
}

void loop() {
  char recvChar;
  recvChar = blueToothSerial.read();
  if (recvChar == '1') {
    driveX(2000);
    Stop();
    delay(100);
    
    driveY(2000);
    Stop();
    delay(100);
    
    driveYOpp(2000);
    Stop();
    delay(100);
   
    while(1) Stop();
  }
  else {
   Stop();
  } 
 }

