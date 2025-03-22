#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "bme280.h"

#define SDA_PIN 41
#define SCL_PIN 42

Adafruit_BME280 bme;  // Objeto para el sensor

void bme280_init()
{
    Wire.begin(SDA_PIN, SCL_PIN);  // Configura I²C con los pines personalizados

    if (!bme.begin(0x76)) {  // Dirección I²C común (cambia a 0x77 si es necesario)
        Serial.println("No se encontró el BME280. Revisa las conexiones.");
        while (1);
    }

    Serial.println("BME280 detectado");
}

float bme280_read_tem()
{
    float t = bme.readTemperature();
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" °C");
    return t;   
}

float bme280_read_hum()
{
    float h = bme.readHumidity();
    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.println(" %");
    return h;
}
