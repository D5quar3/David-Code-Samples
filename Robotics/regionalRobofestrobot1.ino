#include <Servo.h>

#define ENCA 7
#define ENCB 6
#define ENCC 5

Servo a;
Servo b;
Servo c;

#include <SoftwareSerial.h>                     // Software Serial Port

#define RxD 3
#define TxD 2


#define DEBUG_ENABLED  1

String retSymb = "+RTINQ=";                     // start symble when there's any return
String slaveName = ";SeeedBTSlave";             // caution that ';'must be included, and make sure the slave name is right.
int nameIndex = 0;
int addrIndex = 0;

String recvBuf;
String slaveAddr;

String connectCmd = "\r\n+CONN=";

SoftwareSerial blueToothSerial(RxD,TxD);

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
 float G = 1;
 unsigned long startTime = millis();
 a.write(180);
 b.write(82);
 c.write(88.3);
 encoder(startA, startB, startC);   
 while(1) {
   delay(10);
   encoder(encA, encB, encC);
   encA -= startA;
   encB -= startB;
   encC -= startC;
   errB = encB - (encA/2);
   errC = encC - (encA/2);
   cmdB = 82 + (G*errB);
   cmdC = 88.3 + (G*errC);
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
    blueToothSerial.begin(38400);                               
    blueToothSerial.print("\r\n+STWMOD=1\r\n");                 
    blueToothSerial.print("\r\n+STNA=SeeedBTMaster\r\n");       
    blueToothSerial.print("\r\n+STAUTO=0\r\n");                 
    delay(2000);                                                
    blueToothSerial.flush();
    blueToothSerial.print("\r\n+INQ=1\r\n");                    
    Serial.println("Master is inquiring!");
    delay(2000); // This delay is required.

    //find the target slave
    char recvChar;
    while(1)
    {
        if(blueToothSerial.available())
        {
            recvChar = blueToothSerial.read();
            recvBuf += recvChar;
            nameIndex = recvBuf.indexOf(slaveName);             //get the position of slave name
            
                                                                //nameIndex -= 1;
                                                                //decrease the ';' in front of the slave name, to get the position of the end of the slave address
            if ( nameIndex != -1 )
            {
                //Serial.print(recvBuf);
                addrIndex = (recvBuf.indexOf(retSymb,(nameIndex - retSymb.length()- 18) ) + retSymb.length());//get the start position of slave address
                slaveAddr = recvBuf.substring(addrIndex, nameIndex);//get the string of slave address
                break;
            }
        }
    }
    
    //form the full connection command
    connectCmd += slaveAddr;
    connectCmd += "\r\n";
    int connectOK = 0;
    Serial.print("Connecting to slave:");
    Serial.print(slaveAddr);
    Serial.println(slaveName);
    //connecting the slave till they are connected
    do
    {
        blueToothSerial.print(connectCmd);//send connection command
        recvBuf = "";
        while(1)
        {
            if(blueToothSerial.available()){
                recvChar = blueToothSerial.read();
                recvBuf += recvChar;
                if(recvBuf.indexOf("CONNECT:OK") != -1)
                {
                    connectOK = 1;
                    Serial.println("Connected!");
                    blueToothSerial.print("Connected!");
                    break;
                }
                else if(recvBuf.indexOf("CONNECT:FAIL") != -1)
                {
                    Serial.println("Connect again!");
                    break;
                }
            }
        }
    }while(0 == connectOK);
}

void setup() {
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  pinMode(ENCC, INPUT);
  a.attach(11);
  b.attach(10);
  c.attach(9);
  Stop();
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBlueToothConnection();
  delay(1000);
  blueToothSerial.flush();
}

void loop() {
  blueToothSerial.print('1');
  driveX(2000);
  Stop();
  delay(100);
 
  driveY(2000);
  Stop();
  delay(100);
  
  driveYOpp(2000);
  Stop();
  delay(100);
  
 
  //driveXOpp(2000);
  while(1) Stop(); 
 }

