/* Robosub 2019-2020 Vertical Thruster Testing
   
   Current Revision 11 14 19:
      Only Vertical Thrusters React
      Barometer kP updated to 400
      
   All values with "//****"  can be personalized
*/


//All librarys and IMU setup
#include <PID_v1.h>
#include <Wire.h>
#include <Servo.h>
#include "MS5837.h"
#include <Adafruit_BNO055.h>
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055();
MS5837 sensor;



//Start thrusters as servos and set Pins**
Servo front_right_thruster;
Servo front_left_thruster;
Servo back_left_thruster;
Servo back_right_thruster;

double final_front_right_thruster_value;
double final_front_left_thruster_value;
double final_back_left_thruster_value;
double final_back_right_thruster_value;

int front_right_thruster_pin = 5;           //****
int front_left_thruster_pin = 6;            //****
int back_left_thruster_pin = 9;             //****
int back_right_thruster_pin = 7;            //****



//Start all PIDs and set k values**
double barometer_input, barometer_output, barometer_setpoint;
double Y_angle_input, Y_angle_output, Y_angle_setpoint;
double Z_angle_input, Z_angle_output, Z_angle_setpoint;

double barometer_kP = 400;             //****
double barometer_kI = 0;              //****
double barometer_kD = 0;              //****
double Y_angle_kP = 3.5;              //****
double Y_angle_kI = 0.0005;           //****
double Y_angle_kD = 4;                //****
double Z_angle_kP = 3.5;              //****
double Z_angle_kI = 0.0005;           //****
double Z_angle_kD = 3.5;              //****

PID barometer_PID  (&barometer_input, &barometer_output, &barometer_setpoint,
                   barometer_kP, barometer_kI, barometer_kD, DIRECT);
PID Y_angle_PID    (&Y_angle_input, &Y_angle_output, &Y_angle_setpoint,
                   Y_angle_kP, Y_angle_kI, Y_angle_kD, DIRECT);
PID Z_angle_PID    (&Z_angle_input, &Z_angle_output, &Z_angle_setpoint,
                   Z_angle_kP, Z_angle_kI, Z_angle_kD, DIRECT);



//Basic setup steps
void setup(){
  Serial.begin(9600);
  InitializeIMU();
  InitializeBarometer();
  front_right_thruster.attach(front_right_thruster_pin);
  front_left_thruster.attach(front_left_thruster_pin);
  back_left_thruster.attach(back_left_thruster_pin);
  back_right_thruster.attach(back_right_thruster_pin);
  
  barometer_PID.SetMode(AUTOMATIC);
  Y_angle_PID.SetMode(AUTOMATIC);
  Z_angle_PID.SetMode(AUTOMATIC);
  
  Y_angle_PID.SetOutputLimits(-100.00, 100.00);
  Z_angle_PID.SetOutputLimits(-100.00, 100.00);
  barometer_PID.SetOutputLimits(-300.00, 300.00);     //assuming max power is +-300
  
  barometer_setpoint = 0.15;          //****
  Y_angle_setpoint = 0;               //****
  Z_angle_setpoint = 0;               //****
  delay(6000);                        //Thrusters need time to turn on or they dont spin
}



//Plugs IMU angle into PID and moves Thrusters
void loop(){
  IMU_YZ_angles();
  Barometer_Reading();
  Vertical_Outputs();
}



//Turns IMU data collecting on
void InitializeIMU(){
  Wire.beginTransmission(0x28);
  if(!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  bno.setExtCrystalUse(true);
}



//Turns Barometer data collecting on
void InitializeBarometer(){
  Wire.beginTransmission(0x76);
  while (!sensor.init()) {
    Serial.println("Initilization failed");
    delay(2000);
  }
  sensor.setModel(MS5837::MS5837_30BA);
  sensor.setFluidDensity(997);      //(air ~ 1.23, freshwater ~ 997, seawater ~1029)
}                                   //air is not accurate



//Gets the Y and Z angles from the IMU
void IMU_YZ_angles(){
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    Y_angle_input = euler.z();  // our Y is roll
    Z_angle_input = euler.y();  // our Z is pitch
}



//Gets the Depth from the Barometer
void Barometer_Reading(){
  sensor.read();
  barometer_input = sensor.depth();

//Don't need any of these for sub to run
/* 
   Serial.print("Depth: ");             //Use Depth in incompressible liquid only
   Serial.print(sensor.depth()); 
   Serial.println(" m");

   Serial.print("Pressure: "); 
   Serial.print(sensor.pressure()); 
   Serial.println(" mbar");

   Serial.print("Temperature: "); 
   Serial.print(sensor.temperature()); 
   Serial.println(" deg C");
  
   Serial.print("Altitude: ");         //Use Altitude in air only (not very good data)
   Serial.print(sensor.altitude()); 
   Serial.println(" m above mean sea level");
*/
}



//Calculates PIDs and sends Outputs
void Vertical_Outputs(){
  Path_Optimization();
  barometer_PID.Compute();
  Y_angle_PID.Compute();
  Z_angle_PID.Compute();
  Mixer();
  Serial_Print_Thruster_Values();
  
  front_right_thruster.writeMicroseconds(final_front_right_thruster_value);
  front_left_thruster.writeMicroseconds(final_front_left_thruster_value);
  back_left_thruster.writeMicroseconds(final_back_left_thruster_value);
  back_right_thruster.writeMicroseconds(final_back_right_thruster_value);
}



//Takes Error and Chooses which Direction to turn
void Path_Optimization(){
  double half_circle_pos = 180.00;
  double half_circle_neg = -180.00;
  double Y_angle_error = Y_angle_setpoint - Y_angle_input;
  double Z_angle_error = Z_angle_setpoint - Z_angle_input;
  
  if (Y_angle_error > half_circle_pos){
    Y_angle_error = Y_angle_error - 360;  
  }
  else if (Y_angle_error < half_circle_neg){
    Y_angle_error = Y_angle_error + 360;  
  }
  
  if (Z_angle_error > half_circle_pos){
    Z_angle_error = Z_angle_error - 360;  
  }
  else if (Z_angle_error < half_circle_neg){
    Z_angle_error = Z_angle_error + 360;  
  }
  
  Y_angle_setpoint = Y_angle_error + Y_angle_input;
  Z_angle_setpoint = Z_angle_error + Z_angle_input;
}



//Takes PID outputs and makes pwm for Thrusters
void Mixer(){
    final_front_right_thruster_value = 1500 + barometer_output + Y_angle_output + Z_angle_output;
    final_front_left_thruster_value = 1500 + barometer_output - Y_angle_output + Z_angle_output;
    final_back_left_thruster_value = 1500 + barometer_output - Y_angle_output - Z_angle_output;
    final_back_right_thruster_value = 1500 + barometer_output + Y_angle_output - Z_angle_output;
}



//Print All Thrusters Values
void Serial_Print_Thruster_Values(){
  Serial.print("FrontRight: ");
  Serial.print(final_front_right_thruster_value);
  Serial.print("----");
  Serial.print("FrontLeft: ");
  Serial.print(final_front_left_thruster_value);
  Serial.print("----");
  Serial.print("BackLeft: ");
  Serial.print(final_back_left_thruster_value);
  Serial.print("----");
  Serial.print("BackRight: ");
  Serial.println(final_back_right_thruster_value);
}
