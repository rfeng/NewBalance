#include <Encoder.h>
#include <RunningAverage.h>

RunningAverage spd_avg0(5); //over 3 datapoints, should be ok for speed control
RunningAverage spd_avg1(5);
RunningAverage spd_avg2(5);

Encoder e0(3,4);
Encoder e1(2,5);
Encoder e2(6,7);

long old0, old1, old2;

unsigned long time0, time1, time2;

void start_encoder_timing()
{
  delay(10);
  
  old0 = 0;
  old1 = 0;
  old2 = 0;
  
  time0 = micros();
  time1 = micros();
  time2 = micros();
  
  update_encoders();
  
  Serial.println("Encoder setup finished");
}

void update_encoders()
{
  long new0 = e0.read();
  long new1 = e1.read();
  long new2 = e2.read();
  
  spd_avg0.addValue( ((float) (new0-old0))*100000/(micros() -time0) );  //dx/t = speed.  Times 1mil to put into units
  spd_avg1.addValue( ((float) (new1-old1))*100000/(micros() -time1) );
  spd_avg2.addValue( ((float) (new2-old2))*100000/(micros() -time2) );
  
  old0 = new0;
  old1 = new1;
  old2 = new2;
  
  time0 = micros();
  time1 = micros();
  time2 = micros();
}

float get_velocity_0()
{
  return spd_avg0.getAverage();
}

float get_velocity_1()
{
  return spd_avg1.getAverage();
}

float get_velocity_2()
{
  return spd_avg2.getAverage();
}
