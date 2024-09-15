#include <ESP8266WiFi.h>

const char* ssid = "iPhone";
const char* password = "bk2z-IPmK-SMm3-pgnE";

WiFiServer server(80);

const int motorA1 = D8;
const int motorA2 = D7;
const int enableA = D5;  // PWM pin for Motor A speed control

// Motor B connections
const int motorB1 = D4;
const int motorB2 = D3;
const int enableB = D6;  // PWM pin for Motor B speed control

int speedA = 1000;
int speedB = 1023;

const int trigPin = D1;  // Change A0 to D1
const int echoPin = D2;  // Change A1 to D2
float duration, distance;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  server.begin();
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(enableB, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(D0, HIGH);
}

void moveForward() {
  analogWrite(enableA, speedA);
  analogWrite(enableB, speedB);
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void moveBackward() {
  analogWrite(enableA, speedA);
  analogWrite(enableB, speedB);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void turnLeft() {
  analogWrite(enableA, speedA);  // Reduce speed on Motor A to turn left
  analogWrite(enableB, speedB);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void turnRight() {
  analogWrite(enableA, speedA);  //left motor
  analogWrite(enableB, speedB);  // Reduce speed on Motor B to turn right
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void stopMotors() {
  analogWrite(enableA, 0);
  analogWrite(enableB, 0);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}

void object(){
       digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
      distance = (duration * 0.0343) / 2;
      // Serial.println(distance);
      // Serial.println(duration);
      delay(20);
      while (distance < 20) {
        delay(50);

        Serial.println("OK");
        Serial.print("New distance is: ");
        Serial.println(distance);
        turnRight();
        delay(100);
        stopMotors();
       digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
      distance = (duration * 0.0343) / 2;
        // moveForward();
      }

}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      object();
      if (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.println("Received: " + data);

        // digitalWrite(D0, HIGH);
        // digitalWrite(trigPin, LOW);
        // delayMicroseconds(2);
        // digitalWrite(trigPin, HIGH);
        // delayMicroseconds(10);
        // digitalWrite(trigPin, LOW);

        // duration = pulseIn(echoPin, HIGH);
        // distance = (duration * 0.0343) / 2;
        // Serial.println(distance);

                if (data == "f") {
          delay(50);
          moveForward();
          Serial.println("Forward");
          delay(500);
          stopMotors();
          data = "";
          continue;
          Serial.println("Forward");
        } else if (data == "b") {
          delay(50);

          moveBackward();
          Serial.println("Backward");
          delay(500);
          stopMotors();
          data = "";
          continue;

        } else if (data == "l") {
          delay(50);

          turnLeft();
          delay(200);
          moveForward();
          Serial.println("Left");
          delay(500);
          stopMotors();
          data = "";
          continue;
        } else if (data == "r") {
          delay(50);

          turnRight();
          delay(200);
          moveForward();
          Serial.println("Right");
          delay(500);
          stopMotors();
          data = "";
          continue;
        } else if (data == "s"){
          stopMotors();
          Serial.println("Stop");
        }

        else if (data == "w") {
          delay(50);
          moveForward();
          Serial.println("Forward");
          delay(1000);
          stopMotors();
          data = "";
          continue;

        } else if (data == "d") {
          delay(50);

          moveBackward();
          Serial.println("Backward");
          delay(1000);
          stopMotors();
          data = "";
          continue;


        } else if (data == "a") {
          delay(50);

          turnLeft();
          delay(200);
          moveForward();
          Serial.println("Left");
          delay(1000);
          stopMotors();
          data = "";
          continue;


        } else if (data == "d") {
          delay(50);

          turnRight();
          delay(200);
          moveForward();
          Serial.println("Right");
          delay(1000);
          stopMotors();
          data = "";
          continue;
        }


        //         else if (distance < 15) {
        //   Serial.println("OK");
        //   turnRight();
        //   delay(10);
        //   moveForward();
        // }
      }
      // digitalWrite(D0, HIGH);


      //     // Serial.println(distance);

      //     //Serial.print("Distance: ");
      //     //Serial.println(distance);
    }
    client.stop();
  }
}
