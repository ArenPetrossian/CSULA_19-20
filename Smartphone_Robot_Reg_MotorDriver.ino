int RmotorF = 6;
int RmotorB = 7;
int Enable_Rmotor = 5;

int LmotorF = 8;
int LmotorB = 9;
int Enable_Lmotor = 10;

int ValueofRmotor = 0;
int ValueofLmotor = 0;
String myString;

void setup() {
  pinMode(RmotorF, OUTPUT);
  pinMode(RmotorB, OUTPUT);
  pinMode(LmotorF, OUTPUT);
  pinMode(LmotorB, OUTPUT);
  pinMode(Enable_Rmotor, OUTPUT);
  pinMode(Enable_Lmotor, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  myString = Serial.readStringUntil(';');

  int commaIndex = myString.indexOf(',');
  String RmotorValue = myString.substring(0, commaIndex);
  String LmotorValue = myString.substring(commaIndex + 1);
  int ValueofRmotor = RmotorValue.toInt();
  int ValueofLmotor = LmotorValue.toInt();


  if ((ValueofRmotor == 0) && (ValueofLmotor == 0)) {
    digitalWrite(RmotorF, LOW);
    digitalWrite(RmotorB, LOW);
    digitalWrite(LmotorF, LOW);
    digitalWrite(LmotorB, LOW);
    analogWrite(Enable_Rmotor, ValueofRmotor);
    analogWrite(Enable_Lmotor, ValueofLmotor);
  }

  else if ((ValueofRmotor == 0) && (ValueofLmotor > 0)) {
    digitalWrite(RmotorF, LOW);
    digitalWrite(RmotorB, LOW);
    digitalWrite(LmotorF, LOW);
    digitalWrite(LmotorB, HIGH);
    analogWrite(Enable_Rmotor, ValueofRmotor);
    analogWrite(Enable_Lmotor, ValueofLmotor);
  }

  else if ((ValueofRmotor == 0) && (ValueofLmotor < 0)) {
    digitalWrite(RmotorF, LOW);
    digitalWrite(RmotorB, LOW);
    digitalWrite(LmotorF, HIGH);
    digitalWrite(LmotorB, LOW);
    ValueofLmotor = ValueofLmotor * -1;
    analogWrite(Enable_Rmotor, ValueofRmotor);
    analogWrite(Enable_Lmotor, ValueofLmotor);
  }

  else if ((ValueofRmotor < 0) && (ValueofLmotor == 0)) {
    digitalWrite(RmotorF, LOW);
    digitalWrite(RmotorB, HIGH);
    digitalWrite(LmotorF, LOW);
    digitalWrite(LmotorB, LOW);
    ValueofRmotor = ValueofRmotor * -1;
    analogWrite(Enable_Rmotor, ValueofRmotor);
    analogWrite(Enable_Lmotor, ValueofLmotor);
  }

  else if ((ValueofRmotor < 0) && (ValueofLmotor > 0)) {
    digitalWrite(RmotorF, LOW);
    digitalWrite(RmotorB, HIGH);
    digitalWrite(LmotorF, LOW);
    digitalWrite(LmotorB, HIGH);
    ValueofRmotor = ValueofRmotor * -1;
    analogWrite(Enable_Rmotor, ValueofRmotor);
    analogWrite(Enable_Lmotor, ValueofLmotor);
  }

  else if ((ValueofRmotor < 0) && (ValueofLmotor < 0)) {
    digitalWrite(RmotorF, LOW);
    digitalWrite(RmotorB, HIGH);
    digitalWrite(LmotorF, HIGH);
    digitalWrite(LmotorB, LOW);
    ValueofRmotor = ValueofRmotor * -1;
    ValueofLmotor = ValueofLmotor * -1;
    analogWrite(Enable_Rmotor, ValueofRmotor);
    analogWrite(Enable_Lmotor, ValueofLmotor);
  }

  else if ((ValueofRmotor > 0) && (ValueofLmotor == 0)) {
    digitalWrite(RmotorF, HIGH);
    digitalWrite(RmotorB, LOW);
    digitalWrite(LmotorF, LOW);
    digitalWrite(LmotorB, LOW);
    analogWrite(Enable_Rmotor, ValueofRmotor);
    analogWrite(Enable_Lmotor, ValueofLmotor);
  }

  else if ((ValueofRmotor > 0) && (ValueofLmotor > 0)) {
    digitalWrite(RmotorF, HIGH);
    digitalWrite(RmotorB, LOW);
    digitalWrite(LmotorF, LOW);
    digitalWrite(LmotorB, HIGH);
    analogWrite(Enable_Rmotor, ValueofRmotor);
    analogWrite(Enable_Lmotor, ValueofLmotor);
  }

  else if ((ValueofRmotor > 0) && (ValueofLmotor < 0)) {
    digitalWrite(RmotorF, HIGH);
    digitalWrite(RmotorB, LOW);
    digitalWrite(LmotorF, HIGH);
    digitalWrite(LmotorB, LOW);
    ValueofLmotor = ValueofLmotor * -1;
    analogWrite(Enable_Rmotor, ValueofRmotor);
    analogWrite(Enable_Lmotor, ValueofLmotor);
  }
}
