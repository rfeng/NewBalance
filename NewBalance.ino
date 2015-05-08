// Uncomment the below line to use this axis definition: 
// X axis pointing forward
// Y axis pointing to the right 
// and Z axis pointing down.
// Positive pitch : nose up
// Positive roll : right wing down
// Positive yaw : clockwise
int SENSOR_SIGN[9] = {
  1,1,1,-1,-1,-1,1,1,1}; //Correct directions x,y,z - gyro, accelerometer, magnetometer
// Uncomment the below line to use this axis definition: 
// X axis pointing forward
// Y axis pointing to the left 
// and Z axis pointing up.
// Positive pitch : nose down
// Positive roll : right wing down
// Positive yaw : counterclockwise
//int SENSOR_SIGN[9] = {1,-1,-1,-1,1,1,1,-1,-1}; //Correct directions x,y,z - gyro, accelerometer, magnetometer

// LSM303 accelerometer: 8 g sensitivity
// 3.9 mg/digit; 1 g = 256
#define GRAVITY 10  //this equivalent to 1G in the raw data coming from the accelerometer 

#define ToRad(x) ((x)*0.01745329252)  // *pi/180
#define ToDeg(x) ((x)*57.2957795131)  // *180/pi

// L3G4200D gyro: 2000 dps full scale
// 70 mdps/digit; 1 dps = 0.07
//#define Gyro_Gain_X 0.07 //X axis Gyro gain
//#define Gyro_Gain_Y 0.07 //Y axis Gyro gain
//#define Gyro_Gain_Z 0.07 //Z axis Gyro gain
//#define Gyro_Scaled_X(x) ((x)*ToRad(Gyro_Gain_X)) //Return the scaled ADC raw data of the gyro in radians for second
//#define Gyro_Scaled_Y(x) ((x)*ToRad(Gyro_Gain_Y)) //Return the scaled ADC raw data of the gyro in radians for second
//#define Gyro_Scaled_Z(x) ((x)*ToRad(Gyro_Gain_Z)) //Return the scaled ADC raw data of the gyro in radians for second

// LSM303 magnetometer calibration constants; use the Calibrate example from
// the Pololu LSM303 library to find the right values for your board
#define M_X_MIN -421
#define M_Y_MIN -639
#define M_Z_MIN -238
#define M_X_MAX 424
#define M_Y_MAX 295
#define M_Z_MAX 472

#define Kp_ROLLPITCH 0.5
#define Ki_ROLLPITCH 0.0005
#define Kp_YAW 1.2
#define Ki_YAW 0.00002

/*For debugging purposes*/
//OUTPUTMODE=1 will print the corrected data, 
//OUTPUTMODE=0 will print uncorrected data of the gyros (with drift)
#define OUTPUTMODE 1

//#define PRINT_DCM 0     //Will print the whole direction cosine matrix
#define PRINT_ANALOGS 0 //Will print the analog raw data
#define PRINT_EULER 1   //Will print the Euler angles Roll, Pitch and Yaw

#define STATUS_LED 13 

float G_Dt=0.02;    // Integration time (DCM algorithm)  We will run the integration loop at 50Hz if possible

long timer=0;   //general purpuse timer
long timer_old;
long timer24=0; //Second timer used to print values 
float AN[6]; //array that stores the gyro and accelerometer data
float AN_OFFSET[6]={
  0,0,0,0,0,0}; //Array that stores the Offset of the sensors

int gyro_x;
int gyro_y;
int gyro_z;
float accel_x;
float accel_y;
float accel_z;
int magnetom_x;
int magnetom_y;
int magnetom_z;
float c_magnetom_x;
float c_magnetom_y;
float c_magnetom_z;
float MAG_Heading;

float Accel_Vector[3]= {
  0,0,0}; //Store the acceleration in a vector
float Gyro_Vector[3]= {
  0,0,0};//Store the gyros turn rate in a vector
float Omega_Vector[3]= {
  0,0,0}; //Corrected Gyro_Vector data
float Omega_P[3]= {
  0,0,0};//Omega Proportional correction
float Omega_I[3]= {
  0,0,0};//Omega Integrator
float Omega[3]= {
  0,0,0};

// Euler angles
float roll;
float pitch;
float yaw;

float errorRollPitch[3]= {
  0,0,0}; 
float errorYaw[3]= {
  0,0,0};

unsigned int counter=0;
byte gyro_sat=0;

float DCM_Matrix[3][3]= {
  {
    1,0,0    }
  ,{
    0,1,0    }
  ,{
    0,0,1    }
}; 
float Update_Matrix[3][3]={
  {
    0,1,2  }
  ,{
    3,4,5  }
  ,{
    6,7,8  }
}; //Gyros here


float Temporary_Matrix[3][3]={
  {
    0,0,0    }
  ,{
    0,0,0    }
  ,{
    0,0,0    }
};

/*----------------------------------------------------------------------------------*/

float kp=7.75;
float ki=0.25;
float kd=0.07;

float scalefactor = 2.0/(2.0+sqrt(3.0)/2);

/*----------------------------------------------------------------------------------*/

//long encTimer = 0;
//long velTimer = 0;

//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_LSM303_U.h>
//#include <Adafruit_9DOF.h>
//#include <Adafruit_L3GD20_U.h>

/* Assign a unique ID to the sensors */
//Adafruit_9DOF                 dof   = Adafruit_9DOF();
//Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
//Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
//Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);


void setup()
{
  setup_serial(9600);

  IMU_setup();
  
//  if(!accel.begin())
//  {
//    /* There was a problem detecting the ADXL345 ... check your connections */
//    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
//    while(1);
//  }
//  if(!mag.begin())
//  {
//    /* There was a problem detecting the LSM303 ... check your connections */
//    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
//    while(1);
//  }
//  if(!gyro.begin())
//  {
//    /* There was a problem detecting the L3GD20 ... check your connections */
//    Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
//    while(1);
//  }
  
  delay(2000);
  digitalWrite(STATUS_LED,HIGH);

  timer=millis();
  delay(20);
  counter=0;
  
  delay(100);
  
  gyro_PID_setup(kp, ki, kd);
  Velocity_PID_setup();
  motor_init();
  //start_encoder_timing();
  Serial.print("hi");
}

void loop()
{
  getCommand();
  
//  if( (millis()-encTimer) >= 5 )  // Encoders update at 200 Hz
//  {
//    update_encoders();
//    encTimer = millis();
//  }
  
//  if( (millis()-velTimer) >= 10 )  // Motors run at 100 Hz
//  {
//    float m0speed = get_Velocity_0_Output( get_velocity_0() );
//    float m1speed = get_Velocity_1_Output( get_velocity_1() );
//    float m2speed = get_Velocity_2_Output( get_velocity_2() );
//    
//    setMotorSpeed(0, m0speed );
//    setMotorSpeed(1, m1speed );
//    setMotorSpeed(2, m2speed );
//    velTimer = millis();
//  }
  
  if( (millis()-timer) >= 20 )  // Main loop runs at 50Hz
  {
//    counter++;
//    timer_old = timer;
//    timer=millis();
//    if (timer>timer_old)
//      G_Dt = (timer-timer_old)/1000.0;    // Real time of loop run. We use this on the DCM algorithm (gyro integration time)
//    else
//      G_Dt = 0;
      
//    sensors_event_t event;
//    
//    accel.getEvent(&event);
//    
//    float accelx=event.acceleration.x;
//    float accely=event.acceleration.y;
//    float accelz=event.accelerlation.z;
//    
//    gyro.getEvent(&event);
//    
//    float gyrox=event.gyro.x*G_Dt;
//    float gyroy=event.gyro.y*G_Dt;
//    float gyroz=event.gyro.z*G_Dt;
//    
//  

//    sensors_event_t accel_event;
//    sensors_event_t mag_event;
//    sensors_vec_t   orientation;
//  
//    /* Read the accelerometer and magnetometer */
//    accel.getEvent(&accel_event);
//    mag.getEvent(&mag_event);
//  
//    /* Use the new fusionGetOrientation function to merge accel/mag data */  
//    if (dof.fusionGetOrientation(&accel_event, &mag_event, &orientation))
//    {
//      compute_gyro_PID(orientation.roll, orientation.pitch);
//    }
    
    IMU_compute_angles();
    
//    Serial.print(c_magnetom_x);
//    Serial.print(",");
//    Serial.print(c_magnetom_y);
//    Serial.print(",");
//    Serial.print(c_magnetom_z);
//    Serial.println();
//    
    compute_gyro_PID(get_roll(), get_pitch());
    float theta_out = get_theta_output();
    float phi_out = get_phi_output();

    float m0set = scalefactor*(theta_out+((sqrt(3.0)/4)*phi_out));    
    float m1set = scalefactor*(sqrt(3.0)/4*phi_out-theta_out);    
    float m2set = scalefactor*phi_out;

    setMotorSpeed(0,m0set);
    setMotorSpeed(1,m1set);
    setMotorSpeed(2,m2set);

    Serial.print(get_roll());
    Serial.print(",");
    Serial.print(get_pitch());
    Serial.print(", ");
    Serial.print(theta_out);
    Serial.print(",");
    Serial.print(phi_out);
    Serial.print(", ");
    Serial.print(m0set);
    Serial.print(",");
    Serial.print(m1set);
    Serial.print(",");
    Serial.print(m2set);
    Serial.println();
  }
}


