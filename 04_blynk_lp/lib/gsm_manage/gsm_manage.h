#pragma once 

#include "../t_sim767xg_s3.h"
#include <TinyGsmClient.h>
extern TinyGsm my_gsm;

void gsm_init(void);
void gsm_stop(void);