// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"

const char* ssid = "Raja";
const char* password =  "gokurocks";
const char* mqtt_server = "broker.mqttdashboard.com";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_MPU6050 mpu;
// Select a Timer Clock
#define USING_TIM_DIV1                true           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              false            // for longest timer but least accurate. Default

// Init ESP8266 only and only Timer 1
ESP8266Timer ITimer;
uint8_t GPIO_Pin = D3;
void ICACHE_RAM_ATTR SensorCallback(// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"

const char* ssid = "Raja";
const char* password =  "gokurocks";
const char* mqtt_server = "broker.mqttdashboard.com";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_MPU6050 mpu;
// Select a Timer Clock
#define USING_TIM_DIV1                true           // for shortest and most accurate timer
#define USING_TIM_DIV16               false           // for medium time and medium accurate timer
#define USING_TIM_DIV256              false            // for longest timer but least accurate. Default

// Init ESP8266 only and only Timer 1
ESP8266Timer ITimer;
uint8_t GPIO_Pin = D3;
void ICACHE_RAM_ATTR SensorCallback();
#define TIMER_FREQ_HZ        21.00000

float prev_vel_x = 0;
float prev_vel_y = 0;
float prev_vel_z = 0;
float prev_disp_x = 0;
float prev_disp_y = 0;
float prev_disp_z = 0;

float zero_x = 0;
float zero_y = 0;
float zero_z = 0;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }
  //attachInterrupt(digitalPinToInterrupt(GPIO_Pin), SensorCallback, RISING);
  // Frequency in float Hz
  if (ITimer.attachInterrupt(TIMER_FREQ_HZ, TimerHandler))
    Serial.println("Starting  ITimer OK, millis() = " + String(millis()));
  else
    Serial.println("Can't set ITimer. Select another freq. or timer");

  for(int i=0;i<5;i++)
  {
   sensors_event_t a, g, temp;
   mpu.getEvent(&a, &g, &temp);
   zero_x += a.acceleration.x;
   zero_y += a.acceleration.y;
   zero_z += a.acceleration.z;
   delay(100);
    }
  zero_x /= 5;
  zero_y /= 5;
  zero_z /= 5;
}

void loop() {
Serial.print(prev_disp_x);
Serial.print(",");
Serial.print(prev_disp_y);
Serial.print(",");
Serial.println(prev_disp_z);
delay(1000);
}

void TimerHandler()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  prev_disp_x = prev_disp_x + (prev_vel_x*0.0476109476);
  prev_vel_x = prev_vel_x + ((a.acceleration.x-zero_x)*0.0476109476);
  
  prev_disp_y = prev_disp_y + (prev_vel_y*0.0476109476);
  prev_vel_y = prev_vel_y + ((a.acceleration.y-zero_y)*0.0476109476);
  
  prev_disp_z = prev_disp_z + (prev_vel_z*0.0476109476);
  prev_vel_z = prev_vel_z + ((a.acceleration.z-zero_z)*0.0476109476);
  
}
