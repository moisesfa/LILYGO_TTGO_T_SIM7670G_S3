#include "battery.h"
#include "../t_sim767xg_s3.h"
#include <vector>
#include <algorithm>
#include <numeric>

// Calculate the average power data
uint32_t getBatteryVoltage()
{
    std::vector<uint32_t> data;
    for (int i = 0; i < 30; ++i) {
        uint32_t val = analogReadMilliVolts(BOARD_BAT_ADC_PIN);
        // Serial.printf("analogReadMilliVolts : %u mv \n", val * 2);
        data.push_back(val);
        delay(30);
    }
    std::sort(data.begin(), data.end());
    data.erase(data.begin());
    data.pop_back();
    int sum = std::accumulate(data.begin(), data.end(), 0);
    double average = static_cast<double>(sum) / data.size();
    return  average * 2;
}
