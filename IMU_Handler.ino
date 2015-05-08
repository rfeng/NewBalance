
void IMU_setup()
{
  delay(10);
  pinMode (STATUS_LED,OUTPUT);  // Status LED

  I2C_Init();

  Serial.println("Pololu MinIMU-9 + Arduino AHRS");

  digitalWrite(STATUS_LED,LOW);
  delay(1500);

  Accel_Init();
  Compass_Init();
  Gyro_Init();

  delay(20);

  for(int i=0;i<32;i++)    // We take some readings...
  {
    Read_Gyro();
    Read_Accel();
    for(int y=0; y<6; y++)   // Cumulate values
      AN_OFFSET[y] += AN[y];
    delay(20);
  }
  
  for(int y=0; y<6; y++)
    AN_OFFSET[y] = AN_OFFSET[y]/32;

  AN_OFFSET[5]-=GRAVITY*SENSOR_SIGN[5];

  Serial.println("Offset:");
  for(int y=0; y<6; y++)
    Serial.println(AN_OFFSET[y]);

  delay(2000);
  digitalWrite(STATUS_LED,HIGH);

  timer=millis();
  delay(20);
  counter=0;
}

void IMU_compute_angles()
{
  counter++;
  timer_old = timer;
  timer=millis();
  if (timer>timer_old)
    G_Dt = (timer-timer_old)/1000.0;    // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
  else
    G_Dt = 0;

  // *** DCM algorithm
  // Data adquisition
  Read_Gyro();   // This read gyro data
  Read_Accel();     // Read I2C accelerometer

  if (counter > 5)  // Read compass data at 10Hz... (5 loop runs)
  {
    counter=0;
    Read_Compass();    // Read I2C magnetometer
    Compass_Heading(); // Calculate magnetic heading  
  }

  // Calculations...
  Matrix_update(); 
  Normalize();
  Drift_correction();
  Euler_angles();
}

float get_roll()
{
  return 100*roll;
}

float get_pitch()
{
  return -100*pitch;
}
