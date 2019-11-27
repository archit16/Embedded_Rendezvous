#include<Servo.h>
#include <ESP8266WiFi.h>
Servo motor1;
Servo motor2;
//
const char *ssid = "RTES-2019";
const char *pass = "rtes2019";


// defining pins for motors
#define STBY 0
#define AIN1 1 // Motor A is Left side motor_slow dowm to turn left
#define AIN2 2
#define PWMA 3
#define BIN1 4 // Motor B is Right side motor_slow dowm to turn Right
#define BIN2 4
#define PWMB 5

// PWM POSISTION FOR--
int posA=0;
int posB=0;


void setup()
{
  Serial.begin(115200);
  wificonnect();
  
  // motor controls
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  motor1.attach(PWMA);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  motor1.attach(PWMB);
  delay(100);
  pinMode(STBY,HIGH); // Making standby high to drive the motor

}

void loop()
{
  forward();
  backward();
}

void wificonnect()
{
  //WiFi connection ---
  WiFi.begin(ssid,pass);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

/*void wifistrenght(long rssi)
{
  long rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi);
}*/

void forward() // * MOTOR IS GIVEN PWM -- 0
{
  pinMode(AIN1,HIGH);
  pinMode(BIN1,HIGH);
  pinMode(PWMA,HIGH);
  motor1.write(0);
  motor2.write(0);
  delay(50);
}
void backward() // * MOTOR IS GIVEN PWM -- 180
{
  pinMode(AIN1,HIGH);
  pinMode(BIN1,HIGH);
  pinMode(PWMA,HIGH);
  motor1.write(180);
  motor2.write(180);
  delay(50);
}
