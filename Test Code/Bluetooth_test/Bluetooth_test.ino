#include <SoftwareSerial.h>

#define rxd 0
#define txd 1

SoftwareSerial bt(rxd, txd);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bt.begin(38400);
  delay(1000);
  bt.print("AT\r\n");
  bt.flush();
  while(bt.available() > 0)
  {
    char out = (char)bt.read();
    Serial.println(out);
  }
  Serial.println("Done");
}

void loop() {
  // put your main code here, to run repeatedly:

  
}
