//////////////////////////////////////////////////////////////////////////////////

#define FWD_BCK 4
#define LFT_RGHT 3

#define StopMotor 0
#define FwdMotor 1
#define BackMotor 2
#define LeftMotor 3
#define RightMotor 4

char INBYTE;
int  LED = 13; // LED on pin 13

// --------------------------------------------------------------------------- Motors
int motor1 = 23;
int motor2 = 22;
int motorLeft = 24;
int motorRight = 25;

// --------------------------------------------------------------------------- Setup
void setup() {
  Serial2.begin(9600); 
    Serial.begin(9600); 
  pinMode(LED, OUTPUT);
pinMode(FWD_BCK,OUTPUT);
pinMode(LFT_RGHT,OUTPUT);
pinMode(motor2, OUTPUT);
pinMode(motor1, OUTPUT);
pinMode(motorLeft,OUTPUT);
pinMode(motorRight,OUTPUT);

digitalWrite(LFT_RGHT,LOW);
digitalWrite(motor2, LOW);
digitalWrite(motor1, LOW);
digitalWrite(motorLeft,LOW);
digitalWrite(motorRight,LOW);

}
void loop() 
{
//  delay(2000);
//  digitalWrite(LED,HIGH);
//  digitalWrite( motor1,HIGH);
//  digitalWrite( motor2,LOW);
//  for (int fwdInt = 70; fwdInt<200 ;fwdInt++)
//  {
//      analogWrite(FWD_BCK,fwdInt);
//      delay(15);
//  }
//  digitalWrite(LFT_RGHT,HIGH);
//  digitalWrite(motorLeft,HIGH);
//  digitalWrite(LED,LOW);
//  delay(1000);
//  digitalWrite(LED,HIGH);
//  digitalWrite(motorLeft,LOW);
//  delay(1000);
//  
//  digitalWrite(motorRight,HIGH);
//  for (int fwdInt = 200;fwdInt >70;fwdInt--)
//  {
//      analogWrite(FWD_BCK,fwdInt);
//      delay(15);
//  }
//  digitalWrite(LED,LOW);
//  digitalWrite(motorRight,LOW);  
//  digitalWrite(LFT_RGHT,LOW);
//  digitalWrite( motor1,LOW);
//  delay(1000);
//  digitalWrite(LED,HIGH);
//  digitalWrite( motor2,HIGH);
// for (int fwdInt = 70; fwdInt<200 ;fwdInt++)
//  {
//      analogWrite(FWD_BCK,fwdInt);
//      delay(15);
//  }
//  digitalWrite(LED,LOW);
//delay(1000);
//digitalWrite(LED,HIGH);
//  for (int fwdInt = 200;fwdInt >70;fwdInt--)
//  {
//      analogWrite(FWD_BCK,fwdInt);
//      delay(15);
//  }
//    digitalWrite( motor2,LOW);
//    digitalWrite(LED,LOW);
//delay(2000);
//Serial2.println("Press 1 to turn Arduino pin 13 LED ON or 0 to turn it OFF:");
  Serial.println("wait");
  while (!Serial2.available());   // stay here so long as COM port is empty   
    Serial.println("done");
  INBYTE = Serial2.read();        // read next available byte
   
    
  if( INBYTE == '0' ) 
  {
    Serial.println("0");
    digitalWrite(LED,HIGH);
    delay(1000);
    digitalWrite(LED,LOW);
    motor_move(StopMotor);
  
  }  
   
  if( INBYTE == '1' )
 {
    Serial.println("1");
   digitalWrite(LED,HIGH);
    delay(1000);
    digitalWrite(LED,LOW);
  delay(1000);
    digitalWrite(LED,HIGH);
    delay(1000);
    digitalWrite(LED,LOW);

   motor_move(BackMotor);

 }  
if (INBYTE =='2' ) 
{
      Serial.println("2");
    digitalWrite(LED,HIGH);
    delay(1000);
    digitalWrite(LED,LOW);
  delay(1000);
    digitalWrite(LED,HIGH);
    delay(1000);
    digitalWrite(LED,LOW);
  motor_move(FwdMotor); 
}
  delay(50);
}

void motor_move(int dir)
{
  switch (dir)
  {
    case StopMotor:
//            Serial.println("Stop");
      digitalWrite(FWD_BCK,LOW);
//      analogWrite(FWD_BCK,0);
      digitalWrite( motor1,LOW);
      digitalWrite( motor2,LOW);
      break;
    case FwdMotor:
//    Serial.println("Forward");
     digitalWrite( motor1,HIGH);
     digitalWrite( motor2,LOW);
      for (int y=0;y<255;y++)
      {
        analogWrite(LED,y);
        analogWrite(FWD_BCK,y);
        delay(10);
      }
      delay(500);
      for (int y=255;y>0;y--)
      {
        analogWrite(LED,y);
        analogWrite(FWD_BCK,y);
        delay(10);
      }
      analogWrite(FWD_BCK,0);
      digitalWrite( motor1,LOW);
      digitalWrite( motor2,LOW);
      break;
    case BackMotor:
//        Serial.println("Backwards");
      digitalWrite( motor1,LOW);
      digitalWrite( motor2,HIGH);
      for (int y=0;y<255;y++)
      {
        analogWrite(LED,y);
        analogWrite(FWD_BCK,y);
        delay(10);
      }
      delay(500);
      for (int y=255;y>0;y--)
      {
        analogWrite(LED,y);
        analogWrite(FWD_BCK,y);
        delay(10);
      }
      analogWrite(FWD_BCK,0);
      digitalWrite( motor1,LOW);
      digitalWrite( motor2,LOW);
      break;
   default:
      analogWrite(FWD_BCK,0);
      digitalWrite( motor1,LOW);
      digitalWrite( motor2,LOW);
      break;
  }      
}


