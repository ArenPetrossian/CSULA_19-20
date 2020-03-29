/* Robosub 2019-2020 Horizontal Thruster Testing
   
   Current Revision 11 14 19:
      Only Horizontal Thrusters React
   
   All values with "//****"  can be personalized
*/


//All librarys and IMU setup
#include <PID_v1.h>
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_BNO055.h>
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055();



//Start thrusters as servos and set Pins**
Servo left_thruster;
Servo right_thruster;
double final_left_thruster_value;
double final_right_thruster_value;
int left_thruster_pin = 11;         //****
int right_thruster_pin = 10;        //****



//Start all PIDs and set k values**
double distance_input, distance_output, distance_setpoint;
double angle_input, angle_output, angle_setpoint;

double distance_kP = 1;            //****
double distance_kI = 0;            //****
double distance_kD = 0;            //****
double angle_kP = 3.5;             //****
double angle_kI = 0.0005;          //****
double angle_kD = 4;               //****

PID distance_PID  (&distance_input, &distance_output, &distance_setpoint,
                   distance_kP, distance_kI, distance_kD, DIRECT);
PID angle_PID     (&angle_input, &angle_output, &angle_setpoint,
                   angle_kP, angle_kI, angle_kD, DIRECT);



//Basic setup steps
void setup(){
  Serial.begin(9600);
  InitializeIMU();
  left_thruster.attach(left_thruster_pin);
  right_thruster.attach(right_thruster_pin);
  distance_PID.SetMode(AUTOMATIC);
  angle_PID.SetMode(AUTOMATIC);
  distance_PID.SetOutputLimits(-300.00, 300.00);     //assuming max power is +-300
  angle_PID.SetOutputLimits(-100.00, 100.00);
  
  distance_input = 0;                      //The distance input will always be 0
  
  distance_setpoint = 0;                   //****
  angle_setpoint = 0;                      //****
  delay(6000);
}



//Plugs IMU angle into PID and moves Thrusters
void loop(){
  IMU_x_angle();
  Horizontal_Outputs();
}



//Turns IMU data collecting on
void InitializeIMU(){
  Wire.begin();
  if(!bno.begin()) {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  bno.setExtCrystalUse(true);
}



//Gets the X angle from the IMU
void IMU_x_angle(){
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    angle_input = euler.x();
}



//Calculates PIDs and sends Outputs
void Horizontal_Outputs(){
  Path_Optimization();
  
  distance_PID.Compute();
  angle_PID.Compute();
  mixer();
  
  Serial.print("Left: ");
  Serial.print(final_left_thruster_value);
  Serial.print("-------");
  Serial.print("Right: ");
  Serial.println(final_right_thruster_value);
  left_thruster.writeMicroseconds(final_left_thruster_value);
  right_thruster.writeMicroseconds(final_right_thruster_value);
}



//Takes Error and Chooses which Direction to turn
void Path_Optimization(){
  double half_circle_pos = 180.00;
  double half_circle_neg = -180.00;
  double angle_error = angle_setpoint - angle_input;
  if (angle_error > half_circle_pos){
    angle_error = angle_error - 360;  
  }
  else if (angle_error < half_circle_neg){
    angle_error = angle_error + 360;  
  }
    
  angle_setpoint = angle_error + angle_input;
}



//Takes PID outputs and makes pwm for Thrusters
void mixer(){
    final_left_thruster_value = 1500 + distance_output + angle_output;
    final_right_thruster_value = 1500 + distance_output - angle_output;
}
