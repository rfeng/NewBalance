
#include <PID_v1.h>

double Velocity_0_Input, Velocity_0_Output, Velocity_0_Setpoint;
double Velocity_1_Input, Velocity_1_Output, Velocity_1_Setpoint;
double Velocity_2_Input, Velocity_2_Output, Velocity_2_Setpoint;

PID Velocity_0_PID(&Velocity_0_Input, &Velocity_0_Output, &Velocity_0_Setpoint, 0, 0, 0, DIRECT);
PID Velocity_1_PID(&Velocity_1_Input, &Velocity_1_Output, &Velocity_1_Setpoint, 0, 0, 0, DIRECT);
PID Velocity_2_PID(&Velocity_2_Input, &Velocity_2_Output, &Velocity_2_Setpoint, 0, 0, 0, DIRECT);

void Velocity_PID_setup()
{
  delay(10);
  
  //initialize the variables we're linked to
  Velocity_0_Input = 0;
  Velocity_0_Setpoint = 0;
  
  Velocity_1_Input = 0;
  Velocity_1_Setpoint = 0;
  
  Velocity_2_Input = 0;
  Velocity_2_Setpoint = 0;
  
  //turn the PID on
  Velocity_0_PID.SetOutputLimits(-255,255);
  Velocity_0_PID.SetSampleTime(20);
  Velocity_0_PID.SetMode(AUTOMATIC);
  
  Velocity_1_PID.SetOutputLimits(-255,255);
  Velocity_1_PID.SetSampleTime(20);
  Velocity_1_PID.SetMode(AUTOMATIC);
  
  Velocity_2_PID.SetOutputLimits(-255,255);
  Velocity_2_PID.SetSampleTime(20);
  Velocity_2_PID.SetMode(AUTOMATIC);

  motors_on();
  
  Serial.println("Velocity control setup finished");
}

void motors_on()
{
  Velocity_0_PID.SetTunings(10, 2, 0.00);
  Velocity_1_PID.SetTunings(10, 2, 0.00);
  Velocity_2_PID.SetTunings(10, 2, 0.00);
}

void motors_off()
{
  Velocity_0_PID.SetTunings(0.00, 0.00, 0.00);
  Velocity_1_PID.SetTunings(0.00, 0.00, 0.00);
  Velocity_2_PID.SetTunings(0.00, 0.00, 0.00);
}

void set_Velocity_PID_setpoints(double val0, double val1, double val2)
{
  Velocity_0_Setpoint = val0;
  Velocity_1_Setpoint = val1;
  Velocity_2_Setpoint = val2;
}

double get_Velocity_0_Output(double val)
{
  Velocity_0_Input = val;
  Velocity_0_PID.Compute();
  return Velocity_0_Output;
}

double get_Velocity_1_Output(double val)
{
  Velocity_1_Input = val;
  Velocity_1_PID.Compute();
  return Velocity_1_Output;
}

double get_Velocity_2_Output(double val)
{
  Velocity_2_Input = val;
  Velocity_2_PID.Compute();
  return Velocity_2_Output;
}
