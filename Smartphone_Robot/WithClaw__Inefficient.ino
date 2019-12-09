#include <Servo.h>
int ENABLE_LF = 5;   //LF = LEFT FORWARD
int ENABLE_LB = 6;   //LB = LEFT BACKWARD

int ENABLE_RF = 3;   //RF = RIGHT FORWARD
int ENABLE_RB = 11;  //RB = RIGHT BACKWARD

int VALUEleft = 0;
int VALUEright = 0;
int VALUEclaw = 0;

Servo BaseServo1;
Servo BaseServo2;
Servo ClawServo;

int delays = 0;
int pos1 = 90;
int pos2 = 180;
int pos3 = 0;

String BLUETOOTH;

void setup() {
  pinMode (ENABLE_LF, OUTPUT);
  pinMode (ENABLE_LB, OUTPUT);
  pinMode (ENABLE_RF, OUTPUT);
  pinMode (ENABLE_RB, OUTPUT);

  BaseServo1.attach(7);
  BaseServo2.attach(8);
  ClawServo.attach(12);

  Serial.begin(9600);
}

void loop() {
  //BLUETOOTH = Serial.readStringUntil (';');
  BLUETOOTH = "0,0,1;";
  int commaIndex = BLUETOOTH.indexOf(',');
  int commaIndex2 = BLUETOOTH.indexOf(',', commaIndex + 1);
  String RmotorValue = BLUETOOTH.substring(0, commaIndex);
  String LmotorValue = BLUETOOTH.substring(commaIndex + 1, commaIndex2);
  String ClawValue = BLUETOOTH.substring(commaIndex2 + 1);
  int VALUEright = RmotorValue.toInt();
  int VALUEleft = LmotorValue.toInt();
  int VALUEclaw = ClawValue.toInt();

  if ((VALUEleft == 0) && (VALUEright == 0) && (VALUEclaw == 0)) {
    digitalWrite (ENABLE_LF, LOW);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 > 90) && (pos3 > 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 --;
      pos2 ++;
      pos3 --;
      delays = 0;
    }
    else if ((pos1 > 90) && (pos3 == 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 --;
      pos2 ++;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 > 0) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 --;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 == 0) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft == 0) && (VALUEright > 0) && (VALUEclaw == 0)) {
    digitalWrite (ENABLE_LF, LOW);
    digitalWrite (ENABLE_LB, LOW);
    analogWrite (ENABLE_RF, VALUEright);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 > 90) && (pos3 > 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 --;
      pos2 ++;
      pos3 --;
      delays = 0;
    }
    else if ((pos1 > 90) && (pos3 == 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 --;
      pos2 ++;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 > 0) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 --;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 == 0) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft == 0) && (VALUEright < 0) && (VALUEclaw == 0)) {
    VALUEright = VALUEright * -1;
    digitalWrite (ENABLE_LF, LOW);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    analogWrite (ENABLE_RB, VALUEright);
    if ((pos1 > 90) && (pos3 > 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 --;
      pos2 ++;
      pos3 --;
      delays = 0;
    }
    else if ((pos1 > 90) && (pos3 == 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 --;
      pos2 ++;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 > 0) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 --;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 == 0) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft > 0) && (VALUEright == 0) && (VALUEclaw == 0)) {
    analogWrite (ENABLE_LF, VALUEleft);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 > 90) && (pos3 > 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 --;
      pos2 ++;
      pos3 --;
      delays = 0;
    }
    else if ((pos1 > 90) && (pos3 == 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 --;
      pos2 ++;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 > 0) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 --;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 == 0) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft > 0) && (VALUEright > 0) && (VALUEclaw == 0)) {
    analogWrite (ENABLE_LF, VALUEleft);
    digitalWrite (ENABLE_LB, LOW);
    analogWrite (ENABLE_RF, VALUEright);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 > 90) && (pos3 > 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 --;
      pos2 ++;
      pos3 --;
      delays = 0;
    }
    else if ((pos1 > 90) && (pos3 == 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 --;
      pos2 ++;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 > 0) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 --;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 == 0) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft > 0) && (VALUEright < 0) && (VALUEclaw == 0)) {
    VALUEright = VALUEright * -1;
    analogWrite (ENABLE_LF, VALUEleft);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    analogWrite (ENABLE_RB, VALUEright);
    if ((pos1 > 90) && (pos3 > 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 --;
      pos2 ++;
      pos3 --;
      delays = 0;
    }
    else if ((pos1 > 90) && (pos3 == 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 --;
      pos2 ++;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 > 0) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 --;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 == 0) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft < 0) && (VALUEright == 0) && (VALUEclaw == 0)) {
    VALUEleft = VALUEleft * -1;
    digitalWrite (ENABLE_LF, LOW);
    analogWrite (ENABLE_LB, VALUEleft);
    digitalWrite (ENABLE_RF, LOW);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 > 90) && (pos3 > 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 --;
      pos2 ++;
      pos3 --;
      delays = 0;
    }
    else if ((pos1 > 90) && (pos3 == 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 --;
      pos2 ++;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 > 0) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 --;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 == 0) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft < 0) && (VALUEright > 0) && (VALUEclaw == 0)) {
    VALUEleft = VALUEleft * -1;
    digitalWrite (ENABLE_LF, LOW);
    analogWrite (ENABLE_LB, VALUEleft);
    analogWrite (ENABLE_RF, VALUEright);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 > 90) && (pos3 > 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 --;
      pos2 ++;
      pos3 --;
      delays = 0;
    }
    else if ((pos1 > 90) && (pos3 == 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 --;
      pos2 ++;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 > 0) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 --;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 == 0) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft < 0) && (VALUEright < 0) && (VALUEclaw == 0)) {
    VALUEleft = VALUEleft * -1;
    VALUEright = VALUEright * -1;
    digitalWrite (ENABLE_LF, LOW);
    analogWrite (ENABLE_LB, VALUEleft);
    digitalWrite (ENABLE_RF, LOW);
    analogWrite (ENABLE_RB, VALUEright);
    if ((pos1 > 90) && (pos3 > 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 --;
      pos2 ++;
      pos3 --;
      delays = 0;
    }
    else if ((pos1 > 90) && (pos3 == 0) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 --;
      pos2 ++;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 > 0) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 --;
      delays = 0;
    }
    else if ((pos1 == 90) && (pos3 == 0) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }



  else if ((VALUEleft == 0) && (VALUEright == 0) && (VALUEclaw == 1)) {
    digitalWrite (ENABLE_LF, LOW);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 < 160) && (pos3 < 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 ++;
      pos2 --;
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 < 160) && (pos3 == 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 ++;
      pos2 --;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 < 120) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 == 120) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft == 0) && (VALUEright > 0) && (VALUEclaw == 1)) {
    digitalWrite (ENABLE_LF, LOW);
    digitalWrite (ENABLE_LB, LOW);
    analogWrite (ENABLE_RF, VALUEright);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 < 160) && (pos3 < 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 ++;
      pos2 --;
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 < 160) && (pos3 == 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 ++;
      pos2 --;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 < 120) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 == 120) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft == 0) && (VALUEright < 0) && (VALUEclaw == 1)) {
    VALUEright = VALUEright * -1;
    digitalWrite (ENABLE_LF, LOW);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    analogWrite (ENABLE_RB, VALUEright);
    if ((pos1 < 160) && (pos3 < 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 ++;
      pos2 --;
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 < 160) && (pos3 == 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 ++;
      pos2 --;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 < 120) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 == 120) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft > 0) && (VALUEright == 0) && (VALUEclaw == 1)) {
    analogWrite (ENABLE_LF, VALUEleft);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 < 160) && (pos3 < 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 ++;
      pos2 --;
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 < 160) && (pos3 == 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 ++;
      pos2 --;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 < 120) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 == 120) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft > 0) && (VALUEright > 0) && (VALUEclaw == 1)) {
    analogWrite (ENABLE_LF, VALUEleft);
    digitalWrite (ENABLE_LB, LOW);
    analogWrite (ENABLE_RF, VALUEright);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 < 160) && (pos3 < 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 ++;
      pos2 --;
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 < 160) && (pos3 == 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 ++;
      pos2 --;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 < 120) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 == 120) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft > 0) && (VALUEright < 0) && (VALUEclaw == 1)) {
    VALUEright = VALUEright * -1;
    analogWrite (ENABLE_LF, VALUEleft);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    analogWrite (ENABLE_RB, VALUEright);
    if ((pos1 < 160) && (pos3 < 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 ++;
      pos2 --;
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 < 160) && (pos3 == 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 ++;
      pos2 --;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 < 120) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 == 120) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft < 0) && (VALUEright == 0) && (VALUEclaw == 1)) {
    VALUEleft = VALUEleft * -1;
    digitalWrite (ENABLE_LF, LOW);
    analogWrite (ENABLE_LB, VALUEleft);
    digitalWrite (ENABLE_RF, LOW);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 < 160) && (pos3 < 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 ++;
      pos2 --;
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 < 160) && (pos3 == 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 ++;
      pos2 --;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 < 120) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 == 120) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft < 0) && (VALUEright > 0) && (VALUEclaw == 1)) {
    VALUEleft = VALUEleft * -1;
    digitalWrite (ENABLE_LF, LOW);
    analogWrite (ENABLE_LB, VALUEleft);
    analogWrite (ENABLE_RF, VALUEright);
    digitalWrite (ENABLE_RB, LOW);
    if ((pos1 < 160) && (pos3 < 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 ++;
      pos2 --;
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 < 160) && (pos3 == 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 ++;
      pos2 --;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 < 120) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 == 120) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
  else if ((VALUEleft < 0) && (VALUEright < 0) && (VALUEclaw == 1)) {
    VALUEleft = VALUEleft * -1;
    VALUEright = VALUEright * -1;
    digitalWrite (ENABLE_LF, LOW);
    analogWrite (ENABLE_LB, VALUEleft);
    digitalWrite (ENABLE_RF, LOW);
    analogWrite (ENABLE_RB, VALUEright);
    if ((pos1 < 160) && (pos3 < 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      ClawServo.write(pos3);
      pos1 ++;
      pos2 --;
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 < 160) && (pos3 == 120) && (delays == 20)) {
      BaseServo1.write(pos1);
      BaseServo2.write(pos2);
      pos1 ++;
      pos2 --;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 < 120) && (delays == 20)) {
      ClawServo.write(pos3);
      pos3 ++;
      delays = 0;
    }
    else if ((pos1 == 160) && (pos3 == 120) && (delays == 20)) {
      delays = 0;
    }
    else if (delays < 20) {
      delays ++;
    }
  }
}
