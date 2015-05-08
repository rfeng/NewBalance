

const unsigned char M1A = 9;
const unsigned char M1B = 8;
const unsigned char M1C = 7;

const unsigned char M0PWM = 9;
const unsigned char M1PWM = 10;
const unsigned char M2PWM = 11;

const unsigned char M0DIR = 8;
const unsigned char M1DIR = 12;
const unsigned char M2DIR = A0;




void setup() {
  // put your setup code here, to run once:
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1C, OUTPUT);
  
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M1C, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:


  for (int speed = -200; speed <= 0; speed++)
  {
    setMotorSpeed(0, speed); //analogWrite(M1A, speed);
    delay(5);
  }
  
//    digitalWrite(M1B, HIGH);

  for (int speed = 0; speed <= 200; speed++)
  {
    setMotorSpeed(0, speed); //analogWrite(M1A, speed);
    delay(5);
  }

  for (int speed = 200; speed >= 0; speed--)
  {
    setMotorSpeed(0, speed); //analogWrite(M1A, speed);
    delay(5);
  }
//    digitalWrite(M1B, LOW);
  for (int speed = 0; speed >= -200; speed--)
  {
    setMotorSpeed(0, speed); //analogWrite(M1A, speed);
    delay(5);
  }


}

void setMotorSpeed(int motor, double motorSpeed)
{
  int pwmPin;
  int dirPin1;
  int dirPin2;
  switch(motor)
  {
    case 0:
      pwmPin = M1A;
      dirPin1 = M1B;
      dirPin2 = M1C;
      break;
    case 1:
      pwmPin = M1PWM;
      dirPin1 = M1DIR;
      dirPin2 = M1C;
      break;
    case 2:
      pwmPin = M2PWM;
      dirPin1 = M2DIR;
      dirPin2 = M1C;
      break;
    default:
      break;
  }
  
  if(motorSpeed < 0)
  {
    digitalWrite(dirPin1, LOW);
    digitalWrite(dirPin2, HIGH);
    analogWrite(pwmPin, -motorSpeed);
  }
  else
  {
    digitalWrite(dirPin1, HIGH);
    digitalWrite(dirPin2, LOW);
    analogWrite(pwmPin, motorSpeed);
  }
}
