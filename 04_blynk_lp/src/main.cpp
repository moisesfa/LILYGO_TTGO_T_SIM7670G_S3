#include <Arduino.h>
//#include "../lib/t_sim767xg_s3.h"
#include "battery.h"
#include "bme280.h"
#include "gsm_manage.h"
#include "blynk_manage.h"

#define uS_TO_S_FACTOR      1000000ULL  /* Conversion factor for micro seconds to seconds */
//#define TIME_TO_SLEEP       30          /* Time ESP32 will go to sleep (in seconds) */
#define TIME_TO_SLEEP       900         /* Time ESP32 will go to sleep (in seconds) */
#define TPS_ON 1                        // GPIO 1 del ESP32-S3

void setup()
{
    pinMode(TPS_ON, OUTPUT);        // Configurar GPIO 1 como salida
    digitalWrite(TPS_ON, LOW);      // Asegurar que inicie apagado

    Serial.begin(115200);
    
    if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_TIMER) {
        Serial.println("Wakeup timer");
        int i = 10;
        while (i > 0) {
            Serial.printf("Modem will start in %d seconds\n", i);
            Serial.flush();
            delay(1000);
            i--;
        }
        Serial.println("TurnON Modem!");
    }
    
    digitalWrite(TPS_ON, HIGH);  // Encender sensores
    gsm_init();
    bme280_init();
    blynk_init();
    
    //? Leer los datoa para luego enviarlos
    uint32_t battery_voltage_mv = getBatteryVoltage();
    double bat_vol_double = (double)battery_voltage_mv / 1000;
    Serial.printf("Battery voltage is ,%u mv\n", battery_voltage_mv);
    Serial.printf("Battery voltage is ,%u v\n", bat_vol_double);
    float h = bme280_read_hum();
    float t = bme280_read_tem();
    Serial.printf("Hum = %f \t",h);
    Serial.printf("Tem = %f \n",t);

    blynk_send_data(bat_vol_double, h, t);
    
    digitalWrite(TPS_ON, LOW);   // Apagar sensores
    gsm_stop();

    Serial.println("Enter esp32 goto deepsleep!");
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    delay(200);
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
}

void loop()
{
}

