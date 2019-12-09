int ENABLE_LF = 5;  //LF = LEFT FORWARD
int ENABLE_LB = 6;  //LB = LEFT BACKWARD

int ENABLE_RF = 3;  //RF = RIGHT FORWARD
int ENABLE_RB = 11; //RB = RIGHT BACKWARD

int VALUEleft = 0; 
int VALUEright = 0;

String BLUETOOTH;

void setup() {
  pinMode (ENABLE_LF, OUTPUT);
  pinMode (ENABLE_LB, OUTPUT);
  pinMode (ENABLE_RF, OUTPUT);
  pinMode (ENABLE_RB, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  BLUETOOTH = Serial.readStringUntil (';');

  int commaIndex = BLUETOOTH.indexOf(',');
  String RmotorValue = BLUETOOTH.substring(0, commaIndex);
  String LmotorValue = BLUETOOTH.substring(commaIndex + 1);
  int VALUEright = RmotorValue.toInt();
  int VALUEleft = LmotorValue.toInt();
  
  if ((VALUEleft == 0) && (VALUEright == 0)) {
    digitalWrite (ENABLE_LF, LOW);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    digitalWrite (ENABLE_RB, LOW);
  }
  else if ((VALUEleft == 0) && (VALUEright > 0)) {
    digitalWrite (ENABLE_LF, LOW);
    digitalWrite (ENABLE_LB, LOW);
    analogWrite (ENABLE_RF, VALUEright);
    digitalWrite (ENABLE_RB, LOW);
  }
  else if ((VALUEleft == 0) && (VALUEright < 0)) {
    VALUEright = VALUEright * -1;
    digitalWrite (ENABLE_LF, LOW);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    analogWrite (ENABLE_RB, VALUEright);
  }
  else if ((VALUEleft > 0) && (VALUEright == 0)) {
    analogWrite (ENABLE_LF, VALUEleft);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    digitalWrite (ENABLE_RB, LOW);
  }
  else if ((VALUEleft > 0) && (VALUEright > 0)) {
    analogWrite (ENABLE_LF, VALUEleft);
    digitalWrite (ENABLE_LB, LOW);
    analogWrite (ENABLE_RF, VALUEright);
    digitalWrite (ENABLE_RB, LOW);
  }
  else if ((VALUEleft > 0) && (VALUEright < 0)) {
    VALUEright = VALUEright * -1;
    analogWrite (ENABLE_LF, VALUEleft);
    digitalWrite (ENABLE_LB, LOW);
    digitalWrite (ENABLE_RF, LOW);
    analogWrite (ENABLE_RB, VALUEright);
  }
  else if ((VALUEleft < 0) && (VALUEright == 0)) {
    VALUEleft = VALUEleft * -1;
    digitalWrite (ENABLE_LF, LOW);
    analogWrite (ENABLE_LB, VALUEleft);
    digitalWrite (ENABLE_RF, LOW);
    digitalWrite (ENABLE_RB, LOW);
  }
  else if ((VALUEleft < 0) && (VALUEright > 0)) {
    VALUEleft = VALUEleft * -1;
    digitalWrite (ENABLE_LF, LOW);
    analogWrite (ENABLE_LB, VALUEleft);
    analogWrite (ENABLE_RF, VALUEright);
    digitalWrite (ENABLE_RB, LOW);
  }
  else if ((VALUEleft < 0) && (VALUEright < 0)) {
    VALUEleft = VALUEleft * -1;
    VALUEright = VALUEright * -1;
    digitalWrite (ENABLE_LF, LOW);
    analogWrite (ENABLE_LB, VALUEleft);
    digitalWrite (ENABLE_RF, LOW);
    analogWrite (ENABLE_RB, VALUEright);
  }
}
