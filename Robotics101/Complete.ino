int lefteye = A0;
int righteye = A1;

int lMotorPin1 = 6;
int lMotorPin2 = 9;
int rMotorPin1 = 3;
int rMotorPin2 = 5;

int tol = 35;

int trigPin = 10;
int echoPin = 11;

int microsecondsToCentimeters(signed long duration);

void goforward(int speed);
void turnright();
void turnleft();
void backwards();


void setup() {
  // put your setup code here, to run once:
  pinMode(lefteye, INPUT);
  pinMode(righteye, INPUT);

  pinMode(lMotorPin1, OUTPUT);
  pinMode(lMotorPin2, OUTPUT);
  pinMode(rMotorPin1, OUTPUT);
  pinMode(rMotorPin2, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  int lefteyeValue =analogRead(lefteye)-30;
  int righteyeValue =analogRead(righteye);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  signed long duration = pulseIn(echoPin, HIGH);
  int distance = microsecondsToCentimeters(duration);
  Serial.print("Distance: ");
  Serial.println(distance);
  

  if ((distance < 10) &&(distance != 0)) {
    backwards();
    delay(1000);
    turnright();
    delay(1000);
  }
  else {
    Serial.print("left: ");
    Serial.println(lefteyeValue);

    Serial.print("right: ");
    Serial.println(righteyeValue);

 

  if (int(righteyeValue - lefteyeValue) > tol) {
    Serial.println("Turn Right");
    turnright();
  } else if (int(righteyeValue - lefteyeValue) < -tol) {
    Serial.println("Turn Left");
    turnleft();
  } else{
    Serial.println("go forward");
    goforward(255);
  }

 

  
  }
}


void goforward(int speed){
   analogWrite(lMotorPin1, 0);
  analogWrite(lMotorPin2, speed);

   analogWrite(rMotorPin1, 0);
  analogWrite(rMotorPin2, speed);
}


void turnright(){
    analogWrite(lMotorPin1, 0);
  analogWrite(lMotorPin2, 255);

   analogWrite(rMotorPin1, 255);
  analogWrite(rMotorPin2, 0);
}

void turnleft() {
  analogWrite(lMotorPin1, 255);
  analogWrite(lMotorPin2, 0);

   analogWrite(rMotorPin1, 0);
  analogWrite(rMotorPin2, 255);
}

void backwards(){
   analogWrite(lMotorPin1, 255);
  analogWrite(lMotorPin2, 0);

   analogWrite(rMotorPin1, 255);
  analogWrite(rMotorPin2, 0);
}

int microsecondsToCentimeters(signed long duration){
  return (int) (340.29*(duration)/10000/2);
}

