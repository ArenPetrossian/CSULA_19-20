/* Robosub 2019-2020 Reading Values from BNO055 IMU

   Current Revision 11 04 19
   Aren Petrossian
*/

#include <Wire.h>                               
#include <Adafruit_BNO055.h>
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055();
float x_angle, y_angle, z_angle;

void setup() {
  Initialize_IMU();
}


void loop() {
  IMU_Data_Values();
}


void Initialize_IMU(){
  Wire.begin();                //begin the wire communication
  //Wire.beginTransmission(0x28); //don't need for now but will need when we have > 1 sensor
  Serial.begin(9600);
  /* Initialise the IMU */
  if(!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  bno.setExtCrystalUse(true);
}


void IMU_Data_Values(){
   imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
   x_angle = euler.x();    // our X is yaw
   y_angle = euler.z();    // our Y is roll
   z_angle = euler.y();    // our Z is pitch
   Serial.print(x_angle);
   Serial.print(' ');
   Serial.print(y_angle);
   Serial.print(' ');
   Serial.println(z_angle);
}
