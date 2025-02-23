#include <Arduino.h>
#include "../lib/t_sim767xg_s3.h"
#include "battery.h"

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME         "Device"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"

#define uS_TO_S_FACTOR      1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP       30          /* Time ESP32 will go to sleep (in seconds) */

// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
//#define BLYNK_HEARTBEAT 30

#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

//BlynkTimer timer;
TinyGsm modem(SerialAT);

// Your GPRS credentials
// Leave empty, if missing user or pass
char apn[]  = "orangeworld";
char user[] = "";
char pass[] = "";


void sendRandomData(double bat)
{
    //Send randomly generated fake data
    float h = random(0, 100);
    float t = random(0, 50);
    Serial.printf("Hum = %f \t",h);
    Serial.printf("Tem = %f \n",t);
    Blynk.virtualWrite(V1, h);
    Blynk.virtualWrite(V2, t);
    Blynk.virtualWrite(V3, bat);
}

void initModen()
{
// Turn on DC boost to power on the modem
// There is no modem power control, the LED Pin is used as a power indicator here.
#ifdef BOARD_POWERON_PIN
    pinMode(BOARD_POWERON_PIN, OUTPUT);
    //digitalWrite(BOARD_POWERON_PIN, HIGH);
    digitalWrite(BOARD_POWERON_PIN, LOW);
#endif

    // Set modem reset pin ,reset modem
    pinMode(MODEM_RESET_PIN, OUTPUT);
    digitalWrite(MODEM_RESET_PIN, !MODEM_RESET_LEVEL); delay(100);
    digitalWrite(MODEM_RESET_PIN, MODEM_RESET_LEVEL); delay(2600);
    digitalWrite(MODEM_RESET_PIN, !MODEM_RESET_LEVEL);
    // Turn on modem
    pinMode(BOARD_PWRKEY_PIN, OUTPUT);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);
    delay(100);
    digitalWrite(BOARD_PWRKEY_PIN, HIGH);
    delay(1000);
    digitalWrite(BOARD_PWRKEY_PIN, LOW);

    // Set modem baud
    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);

    Serial.println("Start modem...");
    delay(3000);

    // Restart takes quite some time
    // To skip it, call init() instead of restart()
    Serial.println("Initializing modem...");
    if (!modem.init()) {
        Serial.println("Failed to restart modem, delaying 10s and retrying");
        return;
    }

    String name = modem.getModemName();
    Serial.println("Modem Name: " + name);
}

void offModen()
{
    Serial.println("Enter modem power off!");

    if (modem.poweroff()) {
        Serial.println("Modem enter power off modem!");
    } else {
        Serial.println("modem power off failed!");
    }

    delay(5000);

    Serial.println("Check modem response .");
    while (modem.testAT()) {
        Serial.print("."); delay(500);
    }
    Serial.println("Modem is not respone ,modem has power off !");

    delay(5000);

#ifdef BOARD_POWERON_PIN
    // Turn on DC boost to power off the modem
    digitalWrite(BOARD_POWERON_PIN, LOW);
#endif

#ifdef MODEM_RESET_PIN
    // Keep it low during the sleep period. If the module uses GPIO5 as reset, 
    // there will be a pulse when waking up from sleep that will cause the module to start directly.
    // https://github.com/Xinyuan-LilyGO/LilyGO-T-A76XX/issues/85
    digitalWrite(MODEM_RESET_PIN, !MODEM_RESET_LEVEL);
    gpio_hold_en((gpio_num_t)MODEM_RESET_PIN);
    gpio_deep_sleep_hold_en();
#endif
}


void setup()
{
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
    
    initModen();
    
    Blynk.begin(BLYNK_AUTH_TOKEN, modem, apn, user, pass);
    
    // Setup a function to be called every two second
    //timer.setInterval(2000L, sendRandomData);

    uint32_t battery_voltage_mv = getBatteryVoltage();
    double bat_vol_double = (double)battery_voltage_mv / 1000;
    Serial.printf("Battery voltage is ,%u mv\n", battery_voltage_mv);
    Serial.printf("Battery voltage is ,%u v\n", bat_vol_double);

    sendRandomData(bat_vol_double);

    offModen();

    Serial.println("Enter esp32 goto deepsleep!");
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    delay(200);
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
}

void loop()
{
}

