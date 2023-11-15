#include "include/adc.hpp"

#define IRLED_FR GPIO_NUM_33
#define IRLED_FL GPIO_NUM_17
#define IRLED_R GPIO_NUM_21
#define IRLED_L GPIO_NUM_18


adc_oneshot_unit_handle_t adc1;

void SetIRLED(uint8_t led){
    gpio_set_level(IRLED_FL,led&1);
    gpio_set_level(IRLED_L,(led>>1)&1);
    gpio_set_level(IRLED_R,(led>>2)&1);
    gpio_set_level(IRLED_FR,(led>>3)&1);
}

void initadc(){
    adc_oneshot_unit_init_cfg_t adc1_init = {};
    adc1_init.unit_id = ADC_UNIT_1;

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&adc1_init, &adc1));

    adc_oneshot_chan_cfg_t adc1_chan = {};
    adc1_chan.bitwidth = ADC_BITWIDTH_DEFAULT;
    adc1_chan.atten = ADC_ATTEN_DB_11;
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, ADC_CHANNEL_2, &adc1_chan));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, ADC_CHANNEL_3, &adc1_chan));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, ADC_CHANNEL_4, &adc1_chan));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, ADC_CHANNEL_7, &adc1_chan));
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, ADC_CHANNEL_9, &adc1_chan));

    gpio_config_t ir_conf = {};
    ir_conf.mode = GPIO_MODE_OUTPUT;
    ir_conf.pin_bit_mask = (1ULL<<IRLED_FR) | (1ULL<<IRLED_FL) | (1ULL<<IRLED_R) | (1ULL<<IRLED_L);
    ESP_ERROR_CHECK(gpio_config(&ir_conf));
    SetIRLED(0b0000);
}

int BatteryVoltage(){
    int _raw=0;
    ESP_ERROR_CHECK(adc_oneshot_read(adc1, ADC_CHANNEL_2, &_raw));
    return _raw;
}

void ReadSensor(int* sensors,uint8_t mask){
    if(mask & 1) ESP_ERROR_CHECK(adc_oneshot_read(adc1, ADC_CHANNEL_9, &sensors[0]));
    if((mask>>1) & 1) ESP_ERROR_CHECK(adc_oneshot_read(adc1, ADC_CHANNEL_7, &sensors[1]));
    if((mask>>2) & 1) ESP_ERROR_CHECK(adc_oneshot_read(adc1, ADC_CHANNEL_4, &sensors[2]));
    if((mask>>3) & 1) ESP_ERROR_CHECK(adc_oneshot_read(adc1, ADC_CHANNEL_3, &sensors[3]));
}

void WallSensor(){
    int before[4];
    int sensors[4];
    while(1){
        SetIRLED(0b0000);
        ReadSensor(before,0b1111);
        SetIRLED(0b1010);
        vTaskDelay(1);
        ReadSensor(sensors,0b1010);
        SetIRLED(0b0101);
        vTaskDelay(1);
        ReadSensor(sensors,0b0101);
        SetIRLED(0b0000);
        printf(">FL:%d\n",sensors[0]-before[0]);
        printf(">L:%d\n",sensors[1]-before[1]);
        printf(">R:%d\n",sensors[2]);
        printf(">FR:%d\n",sensors[3]-before[3]);
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}