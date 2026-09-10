// 26/586041/TK/66823
// Alfonsus Liguori Bonfilio Valentino Bonagiunta

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <ESP32Servo.h>

Adafruit_MPU6050 mpu;

Servo servo1, servo2, servo3, servo4, servo5;

// Pin
#define SDA_PIN 32
#define SCL_PIN 33
#define PIR_PIN 2

#define SERVO1_PIN 22
#define SERVO2_PIN 13
#define SERVO3_PIN 17
#define SERVO4_PIN 16
#define SERVO5_PIN 23

// Pengaturan
#define INITIAL 90
#define PIR_POS 135

const float DEG = 57.2958;
const float THRESHOLD = 1.5;

float roll = 0;
float pitch = 0;
float yaw = 0;

float offsetX = 0;
float offsetY = 0;
float offsetZ = 0;

unsigned long lastTime;
unsigned long yawStopTime = 0;

bool yawMoving = false;


// Reset Servo

void resetServo() {
  servo1.write(INITIAL);
  servo2.write(INITIAL);
  servo3.write(INITIAL);
  servo4.write(INITIAL);
  servo5.write(INITIAL);

  roll = 0;
  pitch = 0;
  yaw = 0;
  yawMoving = false;
}


// Kalibrasi MPU6050

void calibrate() {
  for (int i = 0; i < 100; i++) {

    sensors_event_t accel, gyro, temp;
    mpu.getEvent(&accel, &gyro, &temp);

    offsetX += gyro.gyro.x * DEG;
    offsetY += gyro.gyro.y * DEG;
    offsetZ += gyro.gyro.z * DEG;

    delay(5);
  }

  offsetX /= 100;
  offsetY /= 100;
  offsetZ /= 100;
}


// Setup

void setup() {

  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  // MPU6050
  Wire.begin(SDA_PIN, SCL_PIN);

  if (!mpu.begin()) {
    Serial.println("MPU6050 tidak ditemukan!");
    while (1);
  }

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Servo
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
  servo4.attach(SERVO4_PIN);
  servo5.attach(SERVO5_PIN);

  resetServo();

  Serial.println("Kalibrasi MPU6050...");
  calibrate();

  lastTime = millis();

  Serial.println("Sistem siap!");
}


// Loop

void loop() {

  // -------- PIR --------

  if (digitalRead(PIR_PIN) == HIGH) {

    Serial.println("MOTION TERDETEKSI!");

    // Semua servo bergerak ke 135°
    servo1.write(PIR_POS);
    servo2.write(PIR_POS);
    servo3.write(PIR_POS);
    servo4.write(PIR_POS);
    servo5.write(PIR_POS);

    delay(500);

    // Kembali ke posisi awal
    resetServo();

    while (digitalRead(PIR_PIN) == HIGH) {
      delay(10);
    }
  }


  // Waktu

  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;
  lastTime = now;


  // Membaca MPU6050

  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  float rx = gyro.gyro.x * DEG - offsetX;
  float ry = gyro.gyro.y * DEG - offsetY;
  float rz = gyro.gyro.z * DEG - offsetZ;


  // Mengurangi noise
  if (abs(rx) < THRESHOLD) rx = 0;
  if (abs(ry) < THRESHOLD) ry = 0;
  if (abs(rz) < THRESHOLD) rz = 0;


  // Menghitung sudut

  roll += rx * dt;
  pitch += ry * dt;
  yaw += rz * dt;

  roll = constrain(roll, -90, 90);
  pitch = constrain(pitch, -90, 90);
  yaw = constrain(yaw, -90, 90);


  // Roll servo 1 dan 2 berlawanan arah

  servo1.write(constrain(INITIAL - roll, 0, 180));
  servo2.write(constrain(INITIAL + roll, 0, 180));


  // Pitch servo 3 dan 4 searah

  servo3.write(constrain(INITIAL + pitch, 0, 180));
  servo4.write(constrain(INITIAL + pitch, 0, 180));


  // Servo 5 mengikuti yaw

  if (rz != 0) {

    servo5.write(constrain(INITIAL + yaw, 0, 180));

    yawMoving = true;
    yawStopTime = millis();
  }


  // Jika yaw berhenti selama 1 detik
  if (yawMoving && rz == 0) {

    if (millis() - yawStopTime >= 1000) {

      servo5.write(INITIAL);

      yaw = 0;
      yawMoving = false;
    }
  }


  delay(20);
}