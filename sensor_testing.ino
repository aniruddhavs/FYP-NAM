
// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Raja";
const char* password =  "gokurocks";
const char* mqtt_server = "broker.mqttdashboard.com";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_MPU6050 mpu;

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
}
//
//  Serial.println("");
//    WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) 
//  {
//    delay(500);
//    Serial.println("Connecting to WiFi..");
//  }
//  Serial.print("Connected to WiFi :");
//  Serial.println(WiFi.SSID());
//  client.setServer(mqtt_server, mqtt_port);
//  client.setCallback(MQTTcallback);
//  while (!client.connected()) 
//  {
//    Serial.println("Connecting to MQTT...");
//    if (client.connect("ESP8266"))
//    {
//      Serial.println("connected");
//    }
//    else
//    {
//      Serial.print("failed with state ");
//      Serial.println(client.state());
//      delay(2000);
//    }
//  }
//  client.subscribe("fypnam/test");
//}
//void reconnect() {
//  // Loop until we're reconnected
//  while (!client.connected()) {
//    Serial.print("Attempting MQTT connection...");
//    // Create a random client ID
//    String clientId = "ESP8266Client-";
//    clientId += String(random(0xffff), HEX);
//    // Attempt to connect
//    if (client.connect(clientId.c_str())) {
//      Serial.println("connected");
//      // Once connected, publish an announcement...
//      client.publish("outTopic", "hello world");
//      // ... and resubscribe
//      client.subscribe("inTopic");
//    } else {
//      Serial.print("failed, rc=");
//      Serial.print(client.state());
//      Serial.println(" try again in 5 seconds");
//      // Wait 5 seconds before retrying
//      delay(5000);
//    }
//  }
//}
//void MQTTcallback(char* topic, byte* payload, unsigned int length) 
//{
//  Serial.print("Message received in topic: ");
//  Serial.println(topic);
//  Serial.print("Message:");
//  String message;
//  for (int i = 0; i < length; i++) 
//  {
//    message = message + (char)payload[i];
//  }
//  Serial.print(message);
//  Serial.println();
//  Serial.println("-----------------------");
//}


void loop() {

  /* Get new sensor events with the readings */

    while(1)
{ 
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  /* Print out the values */
//  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(",");
//  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(",");
//  Serial.print(", Z: ");
  Serial.println(a.acceleration.z);
//  Serial.println(" m/s^2");
//  Serial.print("Rotation X: ");
//  Serial.print(g.gyro.x);
//  Serial.print(", Y: ");
//  Serial.print(g.gyro.y);
//  Serial.print(", Z: ");
//  Serial.print(g.gyro.z);
//  Serial.println(" rad/s");
//  Serial.println("");
//  Serial.println("Before publish"); 
//  char pub_msg[100];
//  sprintf(pub_msg,"ACC: X : %f,Y: %f,Z: %f \n GYP: X:%f,Y: %f,Z: %f",a.acceleration.x,a.acceleration.y,a.acceleration.z,g.gyro.x,g.gyro.y,g.gyro.z);
//  client.publish("fypnam/test",pub_msg);
//  Serial.println("Published");
//  Serial.println(client.connected());
//  delay(10000);
}
}
