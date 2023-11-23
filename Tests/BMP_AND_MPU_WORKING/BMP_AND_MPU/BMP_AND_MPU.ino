#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <MPU6050.h>

Adafruit_BMP280 bmp; // I2C
MPU6050 mpu6050;

void setup() {
    Serial.begin(115200);

    // Iniciar BMP280
    if (!bmp.begin(0x77)) {   // Cambia a 0x77 si es necesario
        Serial.println("No se encontró un sensor BMP280 válido, verifica el cableado!");
        while (1);
    }

    // Configuración adicional para BMP280
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,    
                    Adafruit_BMP280::SAMPLING_X2,    
                    Adafruit_BMP280::SAMPLING_X16,   
                    Adafruit_BMP280::FILTER_X16,     
                    Adafruit_BMP280::STANDBY_MS_500);

    // Iniciar MPU6050
    Wire.begin();
    mpu6050.initialize();

    if (mpu6050.testConnection()) {
        Serial.println("Conexión con MPU6050 exitosa");
    } else {
        Serial.println("Fallo en la conexión con MPU6050");
        while (1);
    }
}

void loop() {
    // Leer y mostrar los datos del BMP280
    Serial.print("Temperatura = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print("Presion = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print("Altitud = ");
    Serial.println(bmp.readAltitude(1013.25)); // Ajusta este valor a tu presión local en hPa

    // Leer y mostrar los datos del MPU6050
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    mpu6050.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    Serial.print("Aceleracion: X=");
    Serial.print(ax); Serial.print(" Y=");
    Serial.print(ay); Serial.print(" Z=");
    Serial.println(az);

    Serial.print("Giroscopio: X=");
    Serial.print(gx); Serial.print(" Y=");
    Serial.print(gy); Serial.print(" Z=");
    Serial.println(gz);

    delay(2000);
}
