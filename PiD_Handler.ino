#include <PID_v1.h>

//Define Variables we'll be connecting to
double ThetaSetpoint, ThetaInput, ThetaOutput, PhiSetpoint, PhiInput, PhiOutput;

//Specify the links and initial tuning parameters
PID thetaPID(&ThetaInput, &ThetaOutput, &ThetaSetpoint,0,0,0, DIRECT);
PID phiPID(&PhiInput, &PhiOutput, &PhiSetpoint,0,0,0, DIRECT);

void gyro_PID_setup(float p, float i, float d)
{
  delay(10);
  
  //initialize the variables we're linked to
  ThetaInput = 0;
  ThetaSetpoint = 0;
  PhiInput = 0;
  PhiSetpoint = 0;
  
  //turn the PID on
  thetaPID.SetOutputLimits(-255,255);
  thetaPID.SetSampleTime(10);
  thetaPID.SetMode(AUTOMATIC);
  
  phiPID.SetOutputLimits(-255,255);
  phiPID.SetSampleTime(10);
  phiPID.SetMode(AUTOMATIC);
  
  set_gyro_PID_tunings(p,i,d, p,i,d);
  
  Serial.println("IMU PID setup finished");
}

void compute_gyro_PID(double thVal, double phVal) 
{
  ThetaInput = thVal;
  PhiInput = phVal;
  
  thetaPID.Compute();
  phiPID.Compute();
}

void set_gyro_PID_tunings(float tp, float ti, float td, float pp, float pi, float pd)
{
  thetaPID.SetTunings(tp, ti, td);
  phiPID.SetTunings(pp, pi, pd);
}

void set_gyro_PID_setpoints(double thVal, double phVal)
{
  ThetaSetpoint = thVal;
  PhiSetpoint = phVal;
}

double get_theta_output() 
{
  return ThetaOutput;
}

double get_phi_output()
{
  return PhiOutput;
}
