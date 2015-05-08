
void setup_serial(int baudrate)
{
  delay(10);
  
  Serial.begin(baudrate);
  
  Serial.println("Press Start");
  
  int test;
  while( test != 35 )
  {
    if( Serial.available() > 0 )
    {
      test = Serial.read();
    }
  }
  
  Serial.print("Serial setup at:");
  Serial.print(baudrate);
  Serial.print(" with message ");
  Serial.println(test);
}

void getCommand()
{
  if( Serial.available() > 0 )
  {
    int cmd = Serial.read();
    
    if( cmd == 119 )  // w
    {
      set_gyro_PID_setpoints(50, 0);
    }
    else if( cmd == 97 )  // a
    {
      set_gyro_PID_setpoints(0, -50);
    }
    else if( cmd == 115 )  // s
    {
      set_gyro_PID_setpoints(-50, 0);
    }
    else if( cmd == 100 )  // d
    {
      set_gyro_PID_setpoints(0, 50);
    }
  }
  else
  {
    set_gyro_PID_setpoints(0,0);
  }
}
