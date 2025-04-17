#include "blynk_manage.h"
#include "gsm_manage.h"
#include <BlynkSimpleTinyGSM.h>

// Your GPRS credentials
// Leave empty, if missing user or pass
char apn[]  = "orangeworld";
char user[] = "";
char pass[] = "";

void blynk_init(void)
{
    Blynk.begin(BLYNK_AUTH_TOKEN, my_gsm, apn, user, pass);
}

void blynk_send_data(double bat, float h, float t)
{
    Blynk.virtualWrite(V1, h);
    Blynk.virtualWrite(V2, t);
    Blynk.virtualWrite(V3, bat);
}
