#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // Espera a que el puerto serial esté listo

  Serial.println("Iniciando MPU6050 prueba de conexión...");

  // Intenta inicializar el MPU6050
  if (!mpu.begin()) {
    Serial.println("No se encontró un sensor MPU6050, ¡revisa tus conexiones!");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 encontrado!");

  // Establecer rango de acelerómetro
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Rango de acelerometro establecido a: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("±2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("±4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("±8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("±16G");
    break;
  }
  Serial.println("");
  delay(1000);
}

void loop() {
  /* Lea los sensores */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Imprime los valores del acelerómetro */
  Serial.print("Acelerometro - X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.println(a.acceleration.z);

  /* Imprime los valores del giroscopio */
  Serial.print("Giroscopio - X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.println(g.gyro.z);

  delay(100); // Retardo de 100ms entre lecturas
}
