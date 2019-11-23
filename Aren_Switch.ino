#include <Servo.h>
int ENABLE_LF = 5;   //LF = LEFT FORWARD
int ENABLE_LB = 6;   //LB = LEFT BACKWARD

int ENABLE_RF = 3;   //RF = RIGHT FORWARD
int ENABLE_RB = 11;  //RB = RIGHT BACKWARD

int VALUEleft = 0;
int VALUEright = 0;
int VALUEarm = 0;
int VALUEhand = 0;

Servo ArmServo1;
Servo ArmServo2;
Servo HandServo;

int posArm1 = 90;
int posArm2 = 180;
int posHand = 0;
int DelayArm = 0;
int DelayHand = 0;

int swMain = 0b00000000;
int swArm0 = 0b00;
int swArm1 = 0b00;
int swHand0 = 0b00;
int swHand1 = 0b00;

String BLUETOOTH;

void setup() {
  pinMode (ENABLE_LF, OUTPUT);
  pinMode (ENABLE_LB, OUTPUT);
  pinMode (ENABLE_RF, OUTPUT);
  pinMode (ENABLE_RB, OUTPUT);

  ArmServo1.attach(7);
  ArmServo2.attach(8);
  HandServo.attach(12);

  Serial.begin(9600);
}

void loop() {
  
  BLUETOOTH = Serial.readStringUntil (';');
  //BLUETOOTH = "0,0,0,0;";
  int commaIndex = BLUETOOTH.indexOf(',');
  int commaIndex2 = BLUETOOTH.indexOf(',', commaIndex + 1);
  int commaIndex3 = BLUETOOTH.indexOf(',', commaIndex2 + 1);
  String LmotorValue = BLUETOOTH.substring(0, commaIndex);
  String RmotorValue = BLUETOOTH.substring(commaIndex + 1, commaIndex2);
  String ArmValue = BLUETOOTH.substring(commaIndex2 + 1, commaIndex3);
  String HandValue = BLUETOOTH.substring(commaIndex3 + 1);
  int VALUEleft = LmotorValue.toInt();
  int VALUEright = RmotorValue.toInt();
  int VALUEarm = ArmValue.toInt();
  int VALUEhand = HandValue.toInt();


//update bits 1-3 of swMain for VALUEleft
  if (VALUEleft == 0) {
    swMain = swMain | 0b00000001;  // bit 1 is 1 if VALUEleft == 0
    swMain = swMain & 0b11111001; // bits 2 & 3 are 0 if VALUEleft > & < 0
  }
  else if (VALUEleft > 0) {
    swMain = swMain | 0b00000010; // bit 2 is 1 if VALUEleft > 0
    swMain = swMain & 0b11111010; // bits 1 & 3 are 0 if VALUEleft == & < 0
  }
  else if (VALUEleft < 0) {
    swMain = swMain | 0b00000100; // bit 3 is 1 if VALUEleft < 0
    swMain = swMain & 0b11111100; // bits 1 & 2 are 0 if VALUEleft == & > 0
  }
//update bits 4-6 of swMain for VALUEright
  if (VALUEright == 0) {
    swMain = swMain | 0b00001000;  // bit 4 is 1 if VALUEright == 0
    swMain = swMain & 0b11001111; // bits 5 & 6 are 0 if VALUEright > & < 0
  }
  else if (VALUEright > 0) {
    swMain = swMain | 0b00010000; // bit 5 is 1 if VALUEright > 0
    swMain = swMain & 0b11010111; // bits 4 & 6 are 0 if VALUEright == & < 0
  }
  else if (VALUEright < 0) {
    swMain = swMain | 0b00100000; // bit 6 is 1 if VALUEright < 0
    swMain = swMain & 0b11100111; // bits 4 & 5 are 0 if VALUEright == & > 0
  }
// update bit 7 of swMain for VALUEarm
  if (VALUEarm == 0) {
    swMain = swMain & 0b10111111; // bit 7 is 0 if VALUEarm == 0
  }
  else if (VALUEarm == 1) {
    swMain = swMain | 0b01000000; // bit 7 is 1 if VALUEarm == 1
  } 
// update bit 8 of swMain for VALUEhand
  if (VALUEhand == 0) {
    swMain = swMain & 0b01111111; // bit 8 is 0 if VALUEhand == 0
  }
  else if (VALUEhand == 1) {
    swMain = swMain | 0b10000000; // bit 8 is 1 if VALUEhand == 1
  }


//update bit 1 of swArm0 for posArm1
  if (posArm1 > 90) {
    swArm0 = swArm0 & 0b10; // bit 1 is 0 if posArm1 > 90
  }
  else if (posArm1 == 90) {
    swArm0 = swArm0 | 0b01; // bit 1 is 1 if posArm1 == 90
  }
//update bit 2 of swArm0 for DelayArm
  if (DelayArm == 3) {
    swArm0 = swArm0 & 0b01; // bit 2 is 0 if DelayArm == 3
  }
  else if (DelayArm < 3) {
    swArm0 = swArm0 | 0b10; // bit 2 is 1 if DelayArm < 3
  }


//update bit 1 of swArm1 for posArm1
  if (posArm1 < 180) {
    swArm1 = swArm1 & 0b10; // bit 1 is 0 if posArm1 < 180
  }
  else if (posArm1 == 180) {
    swArm1 = swArm1 | 0b01; // bit 1 is 1 if posArm1 == 180
  }
//update bit 2 of swArm1 for DelayArm
  if (DelayArm == 3) {
    swArm1 = swArm1 & 0b01; // bit 2 is 0 if DelayArm == 3
  }
  else if (DelayArm < 3) {
    swArm1 = swArm1 | 0b10; // bit 2 is 1 if DelayArm < 3
  }


//update bit 1 of swHand0 for posHand
  if (posHand > 0) {
    swHand0 = swHand0 & 0b10; // bit 1 is 0 if posHand > 0
  }
  else if (posHand == 0) {
    swHand0 = swHand0 | 0b01; // bit 1 is 1 if posHand == 0
  }
//update bit 2 of swHand0 for DelayHand
  if (DelayHand == 3) {
    swHand0 = swHand0 & 0b01; // bit 2 is 0 if DelayHand == 3
  }
  else if (DelayHand < 3) {
    swHand0 = swHand0 | 0b10; // bit 2 is 1 if DelayHand < 3
  }


//update bit 1 of swHand1 for posHand
  if (posHand < 120) {
    swHand1 = swHand1 & 0b10; // bit 1 is 0 if posHand < 120
  }
  else if (posHand == 120) {
    swHand1 = swHand1 | 0b01; // bit 1 is 1 if posHand == 120
  }
//update bit 2 of swHand1 for DelayHand
  if (DelayHand == 3) {
    swHand1 = swHand1 & 0b01; // bit 2 is 0 if DelayHand == 3
  }
  else if (DelayHand < 3) {
    swHand1 = swHand1 | 0b10; // bit 2 is 1 if DelayHand < 3
  }



  switch (swMain) {
//no arm and no hand
  case 0b00001001: //left = 0 , right = 0  , arm = 0 , hand = 0
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand0();
      break;
  case 0b00001010: //left > 0 , right = 0  , arm = 0 , hand = 0
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand0();
      break;
  case 0b00001100: //left < 0 , right = 0  , arm = 0 , hand = 0
      VALUEleft = VALUEleft * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand0();
      break;
  case 0b00010001: //left = 0 , right > 0  , arm = 0 , hand = 0
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand0();
      break;
  case 0b00010010: //left > 0 , right > 0  , arm = 0 , hand = 0
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand0();
      break;
  case 0b00010100: //left < 0 , right > 0  , arm = 0 , hand = 0
      VALUEleft = VALUEleft * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand0();
      break;
  case 0b00100001: //left = 0 , right < 0  , arm = 0 , hand = 0
      VALUEright = VALUEright * -1;
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm0Hand0();
      break;
  case 0b00100010: //left > 0 , right < 0  , arm = 0 , hand = 0
      VALUEright = VALUEright * -1;
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm0Hand0();
      break;
  case 0b00100100: //left < 0 , right < 0  , arm = 0 , hand = 0
      VALUEleft = VALUEleft * -1;
      VALUEright = VALUEright * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm0Hand0();
      break;
      


//yes arm and no hand
  case 0b01001001: //left = 0 , right = 0  , arm = 1 , hand = 0
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand0();
      break;
  case 0b01001010: //left > 0 , right = 0  , arm = 1 , hand = 0
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand0();
      break;
  case 0b01001100: //left < 0 , right = 0  , arm = 1 , hand = 0
      VALUEleft = VALUEleft * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand0();
      break;
  case 0b01010001: //left = 0 , right > 0  , arm = 1 , hand = 0
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand0();
      break;
  case 0b01010010: //left > 0 , right > 0  , arm = 1 , hand = 0
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand0();
      break;
  case 0b01010100: //left < 0 , right > 0  , arm = 1 , hand = 0
      VALUEleft = VALUEleft * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand0();
      break;
  case 0b01100001: //left = 0 , right < 0 , arm = 1 , hand = 0
      VALUEright = VALUEright * -1;
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm1Hand0();
      break;
  case 0b01100010: //left > 0 , right < 0 , arm = 1 , hand = 0
      VALUEright = VALUEright * -1;
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm1Hand0();
      break;
  case 0b01100100: //left < 0 , right < 0 , arm = 1 , hand = 0
      VALUEleft = VALUEleft * -1;
      VALUEright = VALUEright * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm1Hand0();
      break;


      
//no arm and yes hand
  case 0b10001001: //left = 0 , right = 0  , arm = 0 , hand = 1
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand1();
      break;
  case 0b10001010: //left > 0 , right = 0  , arm = 0 , hand = 1
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand1();
      break;
  case 0b10001100: //left < 0 , right = 0  , arm = 0 , hand = 1
      VALUEleft = VALUEleft * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand1();
      break;
  case 0b10010001: //left = 0 , right > 0  , arm = 0 , hand = 1
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand1();
      break;
  case 0b10010010: //left > 0 , right > 0  , arm = 0 , hand = 1
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand1();
      break;
  case 0b10010100: //left < 0 , right > 0  , arm = 0 , hand = 1
      VALUEleft = VALUEleft * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm0Hand1();
      break;
  case 0b10100001: //left = 0 , right < 0  , arm = 0 , hand = 1
      VALUEright = VALUEright * -1;
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm0Hand1();
      break;
  case 0b10100010: //left > 0 , right < 0  , arm = 0 , hand = 1
      VALUEright = VALUEright * -1;
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm0Hand1();
      break;
  case 0b10100100: //left < 0 , right < 0  , arm = 0 , hand = 1
      VALUEleft = VALUEleft * -1;
      VALUEright = VALUEright * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm0Hand1();
      break;


      
//yes arm and yes hand
  case 0b11001001: //left = 0 , right = 0  , arm = 1 , hand = 1
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand1();
      break;
  case 0b11001010: //left > 0 , right = 0  , arm = 1 , hand = 1
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand1();
      break;
  case 0b11001100: //left < 0 , right = 0  , arm = 1 , hand = 1
      VALUEleft = VALUEleft * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      digitalWrite (ENABLE_RF, LOW);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand1();
      break;
  case 0b11010001: //left = 0 , right > 0  , arm = 1 , hand = 1
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand1();
      break;
  case 0b11010010: //left > 0 , right > 0  , arm = 1 , hand = 1
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand1();
      break;
  case 0b11010100: //left < 0 , right > 0  , arm = 1 , hand = 1
      VALUEleft = VALUEleft * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      analogWrite (ENABLE_RF, VALUEright);
      digitalWrite (ENABLE_RB, LOW);
      Arm1Hand1();
      break;
  case 0b11100001: //left = 0 , right < 0  , arm = 1 , hand = 1
      VALUEright = VALUEright * -1;
      digitalWrite (ENABLE_LF, LOW);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm1Hand1();
      break;
  case 0b11100010: //left > 0 , right < 0  , arm = 1 , hand = 1
      VALUEright = VALUEright * -1;
      analogWrite (ENABLE_LF, VALUEleft);
      digitalWrite (ENABLE_LB, LOW);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm1Hand1();
      break;
  case 0b11100100: //left < 0 , right < 0  , arm = 1 , hand = 1
      VALUEleft = VALUEleft * -1;
      VALUEright = VALUEright * -1;
      digitalWrite (ENABLE_LF, LOW);
      analogWrite (ENABLE_LB, VALUEleft);
      digitalWrite (ENABLE_RF, LOW);
      analogWrite (ENABLE_RB, VALUEright);
      Arm1Hand1();
      break;
  }
}


void Arm0Hand0() {
  switch (swArm0) {
   case 0b00: // posArm1 > 90 and DelayArm = 3
    ArmServo1.write(posArm1);
    ArmServo2.write(posArm2);
    posArm1 --;
    posArm2 ++;
    DelayArm = 0;
    break;
   case 0b01: // posArm1 = 90 and DelayArm = 3
    DelayArm = 0;
    break;
   case 0b10: // DelayArm < 3
    DelayArm ++;
    break;
   case 0b11: // DelayArm < 3
    DelayArm ++;
    break;
  }
  switch (swHand0) {
   case 0b00: // posHand > 0 and DelayHand = 3
    HandServo.write(posHand);
    posHand --;
    DelayHand = 0;
    break;
   case 0b01: // posHand = 0 and DelayHand = 3
    DelayHand = 0;
    break;
   case 0b10: // DelayHand < 3
    DelayHand ++;
    break;
   case 0b11: // DelayHand < 3
    DelayHand ++;
    break;
  }
  return 0;
}


void Arm1Hand0() {
  switch (swArm1) {
   case 0b00: // posArm1 < 180 and DelayArm = 3
    ArmServo1.write(posArm1);
    ArmServo2.write(posArm2);
    posArm1 ++;
    posArm2 --;
    DelayArm = 0;
    break;
   case 0b01: // posArm1 = 180 and DelayArm = 3
    DelayArm = 0;
    break;
   case 0b10: // DelayArm < 3
    DelayArm ++;
    break;
   case 0b11: // DelayArm < 3
    DelayArm ++;
    break;
  }
  switch (swHand0) {
   case 0b00: // posHand > 0 and DelayHand = 3
    HandServo.write(posHand);
    posHand --;
    DelayHand = 0;
    break;
   case 0b01: // posHand = 0 and DelayHand = 3
    DelayHand = 0;
    break;
   case 0b10: // DelayHand < 3
    DelayHand ++;
    break;
   case 0b11: // DelayHand < 3
    DelayHand ++;
    break;
  }
  return 0;
}


void Arm0Hand1() {
  switch (swArm0) {
   case 0b00: // posArm1 > 90 and DelayArm = 3
    ArmServo1.write(posArm1);
    ArmServo2.write(posArm2);
    posArm1 --;
    posArm2 ++;
    DelayArm = 0;
    break;
   case 0b01: // posArm1 = 90 and DelayArm = 3
    DelayArm = 0;
    break;
   case 0b10: // DelayArm < 3
    DelayArm ++;
    break;
   case 0b11: // DelayArm < 3
    DelayArm ++;
    break;
  }
  switch (swHand1) {
   case 0b00: // posHand < 120 and Delayhand = 3
    HandServo.write(posHand);
    posHand ++;
    DelayHand = 0;
    break;
   case 0b01: // posHand = 120 and DelayHand = 3
    DelayHand = 0;
    break;
   case 0b10: // DelayHand < 3
    DelayHand ++;
    break;
   case 0b11: // DelayHand < 3
    DelayHand ++;
    break;
  }
  return 0;
}


void Arm1Hand1() {
  switch (swArm1) {
   case 0b00: // posArm1 < 180 and DelayArm = 3
    ArmServo1.write(posArm1);
    ArmServo2.write(posArm2);
    posArm1 ++;
    posArm2 --;
    DelayArm = 0;
    break;
   case 0b01: // posArm1 = 180 and DelayArm = 3
    DelayArm = 0;
    break;
   case 0b10: // DelayArm < 3
    DelayArm ++;
    break;
   case 0b11: // DelayArm < 3
    DelayArm ++;
    break;
  }
  switch (swHand1) {
   case 0b00: // posHand < 120 and Delayhand = 3
    HandServo.write(posHand);
    posHand ++;
    DelayHand = 0;
    break;
   case 0b01: // posHand = 120 and DelayHand = 3
    DelayHand = 0;
    break;
   case 0b10: // DelayHand < 3
    DelayHand ++;
    break;
   case 0b11: // DelayHand < 3
    DelayHand ++;
    break;
  }
  return 0;
}
