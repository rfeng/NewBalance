// Motor Pins

const unsigned char M0A = 9;
const unsigned char M0B = 8;
const unsigned char M0C = 7;

const unsigned char M1A = 3;
const unsigned char M1B = 4;
const unsigned char M1C = 5;

const unsigned char M2A = 10;
const unsigned char M2B = 11;
const unsigned char M2C = 12;



void motor_init() {
  
  delay(10);
  
  // put your setup code here, to run once:
  pinMode(M0A, OUTPUT);
  pinMode(M0B, OUTPUT);
  pinMode(M0C, OUTPUT);
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M1C, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  pinMode(M2C, OUTPUT);
  
  digitalWrite(M0A, LOW);
  digitalWrite(M0B, LOW);
  digitalWrite(M0C, LOW);
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M1C, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);
  digitalWrite(M2C, LOW);
  
  Serial.println("Motor setup finished"); 
}

void setMotorSpeed(int motor, double motorSpeed)
{
  int pwmPin;
  int dirPin1;
  int dirPin2;
  switch(motor)
  {
    case 0:
      pwmPin = M0A;
      dirPin1 = M0B;
      dirPin2 = M0C;
      break;
    case 1:
      pwmPin = M1A;
      dirPin1 = M1B;
      dirPin2 = M1C;
      break;
    case 2:
      pwmPin = M2A;
      dirPin1 = M2B;
      dirPin2 = M2C;
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
