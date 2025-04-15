#include <Arduino.h>
#include "gsm_manage.h"

TinyGsm my_gsm(SerialAT);

void gsm_init(void)
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
    if (!my_gsm.init()) {
        Serial.println("Failed to restart modem, delaying 10s and retrying");
        return;
    }

    String name = my_gsm.getModemName();
    Serial.println("Modem Name: " + name);
}

void gsm_stop(void)
{

    Serial.println("Enter modem power off!");

    if (my_gsm.poweroff()) {
        Serial.println("Modem enter power off modem!");
    } else {
        Serial.println("modem power off failed!");
    }

    delay(1000);

    Serial.println("Check modem response .");
    while (my_gsm.testAT()) {
        Serial.print("."); delay(500);
    }
    Serial.println("Modem is not respone ,modem has power off !");

    delay(1000);

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
