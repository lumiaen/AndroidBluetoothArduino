//////////////////////////////////////////////////////////////////////////////////

#define FWD_BCK 4
#define LFT_RGHT 3

#define StraightMotor 0
#define FwdMotor 1
#define BackMotor 2
#define LeftMotor 3
#define RightMotor 4

int  LED = 13; // LED on pin 13
int byteCount = 0;
int digitCount = 0;
char newByte;

// --------------------------------------------------------------------------- Motors
int motor1 = 23;
int motor2 = 22;
int motorLeft = 24;
int motorRight = 25;
String myString = "";
int mov =0;
int INC=0;
int cnt = 0;
struct
{
  int inc;
  boolean ret;
} chkValRet;
struct
{
  int  mov;
  int  val;
} movement;
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
  Serial.flush();
  Serial2.flush();
  while (!Serial2.available());   // stay here so long as COM port is empty   
   if (getCommand())
  {
    Serial.print("[");
    Serial.print(movement.mov);
    Serial.print(",");
    Serial.print(movement.val);
    Serial.println("]");
    motor_move(movement.mov);
}

}

boolean getCommand ()
{
     
    // handle serial data begin
    if (Serial2.available() > 0)
    {
      // read the incoming byte:
      newByte = Serial2.read();
      switch (INC)
      {
        case 0:
            if (newByte == '*')
            {
              INC = 1;
            }
            break;
            return false;
        case 1:
            switch (newByte)
            {
              case 'f':
                  movement.mov = FwdMotor;
                  INC=2;
                  break;
              case 'b':
                  movement.mov = BackMotor;
                  INC=2;
                  break;
              case 'l':
                  movement.mov = LeftMotor;
                  movement.val=1;
                  INC=0;
                  return true;
                  break;
              case 'r':
                  movement.mov = RightMotor;
                  movement.val=1;
                  INC=0;
                  return true;
                  break;
              case 's':
                  movement.mov = StraightMotor;
                  movement.val=1;
                  INC=0;
                  return true;
                  break;
              default:
                  INC = 0;
            }
            break;
            return false;
        case 2:
            getVal();
            INC = chkValRet.inc;
            return chkValRet.ret;
            break;
        default:
            INC=0;
            break;
      }
      return false;
}
}

void getVal()
{
  int curVal=0;
  if (isDigit(newByte))
  {
    if (cnt<3)
    {
      myString += String(newByte);
      curVal = myString.toInt();
      if (curVal >255)
      {
        cnt=0;
        chkValRet.inc=0;
        chkValRet.ret=false;
        movement.val = 0;
        movement.mov = 9999;
        myString = "";
      }
      else
      {
        cnt++;
        chkValRet.inc=2;
        chkValRet.ret=false;
      }
    }
    if (cnt==3)
    {
      curVal = myString.toInt();
      if (curVal >255)
      {
        cnt=0;
        chkValRet.inc=0;
        chkValRet.ret=false;
        movement.val = 0;
        movement.mov = 9999;
        myString = "";
      }
       else
      {
        cnt=0;
        chkValRet.inc=0;
        chkValRet.ret=true;
        movement.val = myString.toInt();
        myString = "";
      }
    }
    else if (cnt > 3)
    {
      cnt=0;
      chkValRet.inc=0;
      chkValRet.ret=false;
      movement.val = 9999;
      myString = "";
    }
  }
  else if (newByte == '*'&& cnt!=0)
  {
        cnt=0;
        chkValRet.inc=0;
        chkValRet.ret=true;
        movement.val = myString.toInt();
        myString = "";
  }
  else
  {
      chkValRet.inc=0;
      chkValRet.ret=true;
      myString="";
      movement.mov=9999;
      movement.val=0;
  }
}

void motor_move(int dir)
{
  switch (dir)
  {
    case StraightMotor:
      Serial.println("Straight");
      digitalWrite(LFT_RGHT,LOW);
      digitalWrite( motorLeft,LOW);
      digitalWrite( motorRight,LOW);
      break;
    case LeftMotor:
      Serial.println("Left");
      digitalWrite(LFT_RGHT,HIGH);
      digitalWrite( motorLeft,HIGH);
      digitalWrite( motorRight,LOW);
      break;
    case RightMotor:
      Serial.println("Right");
      digitalWrite(LFT_RGHT,HIGH);
      digitalWrite( motorLeft,LOW);
      digitalWrite( motorRight,HIGH);
      break;
    case FwdMotor:
     Serial.println("Forward");
     digitalWrite( motor1,HIGH);
     digitalWrite( motor2,LOW);
     analogWrite(FWD_BCK,movement.val);
     break;
    case BackMotor:
      Serial.println("Back");
      digitalWrite( motor1,LOW);
      digitalWrite( motor2,HIGH);
      analogWrite(FWD_BCK,movement.val);
      break;
   default:
      analogWrite(FWD_BCK,LOW);
      digitalWrite( motor1,LOW);
      digitalWrite( motor2,LOW);
      digitalWrite(LFT_RGHT,LOW);
      digitalWrite( motorLeft,LOW);
      digitalWrite( motorRight,LOW);
      break;
  }      
}


