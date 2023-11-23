#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

SoftwareSerial GPS_SoftSerial(5, 4); // Crear un objeto llamado GPS_SoftSerial de la clase SoftwareSerial (Rx, Tx)
TinyGPSPlus gps;

volatile float minutos, segundos;
volatile int grados, secs, mins; // Cambié el nombre de la variable "segundos" para evitar conflicto

void setup() {
  Serial.begin(9600); // Definir la velocidad de comunicación serial
  GPS_SoftSerial.begin(9600); // Definir la velocidad de comunicación serial por software
}

void loop() {
  obtenerDatosGPS();
}

void obtenerDatosGPS() {
  retardoInteligente(1000); // Generar un retardo preciso de 1ms
  unsigned long inicio;
  double latitud, longitud, altitud_m;
  uint8_t hr, min, sec;
  bool loc_valida, alt_valida, hora_valida;

  latitud = gps.location.lat(); // Obtener datos de latitud
  loc_valida = gps.location.isValid(); // Verificar si hay datos de ubicación válidos
  longitud = gps.location.lng(); // Obtener datos de longitud
  altitud_m = gps.altitude.meters(); // Obtener datos de altitud en metros
  alt_valida = gps.altitude.isValid(); // Verificar si hay datos de altitud válidos
  hr = gps.time.hour(); // Obtener hora
  min = gps.time.minute(); // Obtener minutos
  sec = gps.time.second(); // Obtener segundos
  hora_valida = gps.time.isValid(); // Verificar si hay datos de hora válidos

  // Ajustar la hora a la zona horaria de Colombia (UTC-5)
  hr = (hr + 19) % 24; // Agregar 19 horas y obtener el módulo para asegurarse de que esté en el rango de 0 a 23

  if (!loc_valida) {
    Serial.print("Latitud : ");
    Serial.println("***");
    Serial.print("Longitud : ");
    Serial.println("***");
  } else {
    DegMinSec(latitud);
    Serial.print("Latitud en Grados Decimales : ");
    Serial.println(latitud, 6);
    Serial.print("Latitud en Grados Minutos Segundos : ");
    Serial.print(grados);
    Serial.print("\t");
    Serial.print(mins);
    Serial.print("\t");
    Serial.println(secs);

    DegMinSec(longitud);
    Serial.print("Longitud en Grados Decimales : ");
    Serial.println(longitud, 6);
    Serial.print("Longitud en Grados Minutos Segundos : ");
    Serial.print(grados);
    Serial.print("\t");
    Serial.print(mins);
    Serial.print("\t");
    Serial.println(secs);
  }

  if (!alt_valida) {
    Serial.print("Altitud : ");
    Serial.println("***");
  } else {
    Serial.print("Altitud : ");
    Serial.println(altitud_m, 6);
  }

  if (!hora_valida) {
    Serial.print("Hora : ");
    Serial.println("***");
  } else {
    char cadena_tiempo[32];
    sprintf(cadena_tiempo, "Hora : %02d/%02d/%02d \n", hr, min, sec);
    Serial.print(cadena_tiempo);
  }
}

static void retardoInteligente(unsigned long ms) {
  unsigned long inicio = millis();
  do {
    while (GPS_SoftSerial.available()) // Codificar datos leídos del GPS mientras haya datos disponibles en el puerto serial
      gps.encode(GPS_SoftSerial.read());
  } while (millis() - inicio < ms);
}

void DegMinSec(double tot_val) {
  grados = (int)tot_val;
  minutos = tot_val - grados;
  segundos = 60 * minutos;
  mins = (int)minutos;
  minutos = minutos - mins;
  minutos = 60 * minutos;
  secs = (int)minutos;
}

