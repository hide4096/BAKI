#include "include/adc.hpp"
#include "peripheral.hpp"
#include <rom/ets_sys.h>


adc_oneshot_unit_handle_t adc1;

void SetIRLED(uint8_t led){
    gpio_set_level(IRLED_FR,led&1);
    gpio_set_level(IRLED_R,(led>>1)&1);
    gpio_set_level(IRLED_L,(led>>2)&1);
    gpio_set_level(IRLED_FL,(led>>3)&1);
}

void initADC(){
    adc_oneshot_unit_init_cfg_t adc1_init = {};
    adc1_init.unit_id = ADC_UNIT_1;

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&adc1_init, &adc1));

    adc_oneshot_chan_cfg_t adc1_chan = {};
    adc1_chan.bitwidth = ADC_BITWIDTH_DEFAULT;
    adc1_chan.atten = ADC_ATTEN_DB_6;
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, ADC_CHANNEL_2, &adc1_chan)); //バッテリー電圧
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, ADC_CHANNEL_3, &adc1_chan)); // FR  
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, ADC_CHANNEL_4, &adc1_chan)); // R
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, ADC_CHANNEL_7, &adc1_chan)); // L
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1, ADC_CHANNEL_9, &adc1_chan)); // FL

    gpio_config_t ir_conf = {};
    ir_conf.mode = GPIO_MODE_OUTPUT;
    ir_conf.pin_bit_mask = (1ULL<<IRLED_FR) | (1ULL<<IRLED_FL) | (1ULL<<IRLED_R) | (1ULL<<IRLED_L);
    ESP_ERROR_CHECK(gpio_config(&ir_conf));
    SetIRLED(0b0000);
}

float BatteryVoltage(){
    int _raw=0;
    ESP_ERROR_CHECK(adc_oneshot_read(adc1, ADC_CHANNEL_2, &_raw));
    return (float)((float)(_raw)*(4.2 / 1000.0));
}

void ReadSensor(int* sensors,uint8_t mask){
    if(mask & 1) ESP_ERROR_CHECK(adc_oneshot_read(adc1, ADC_CHANNEL_9, &sensors[0]));
    if((mask>>1) & 1) ESP_ERROR_CHECK(adc_oneshot_read(adc1, ADC_CHANNEL_7, &sensors[1]));
    if((mask>>2) & 1) ESP_ERROR_CHECK(adc_oneshot_read(adc1, ADC_CHANNEL_4, &sensors[2]));
    if((mask>>3) & 1) ESP_ERROR_CHECK(adc_oneshot_read(adc1, ADC_CHANNEL_3, &sensors[3]));
}

void WallSensor(void* pvparam){
    int before[4];
    int sensors[4];
    while(1){
        //SetIRLED(0b0000);   // 全消灯
        //vTaskDelay(10/portTICK_PERIOD_MS);   // 1ms待つ
        //ets_delay_us(10);   // 10us待つ
        ReadSensor(before,0b1111);  // 全消灯での値を取得 
        
        SetIRLED(0b1001);   // fl,r点灯
        //vTaskDelay(1);    // 1ms待つ
        ets_delay_us(100);   // 10us待つ
        ReadSensor(sensors,0b1001); // fl,r点灯での値を取得
        //SetIRLED(0b0000);   // 全消灯

        //vTaskDelay(1);   // 1ms待つ
        //ets_delay_us(30);   // 10us待つ
        //ReadSensor(before,0b0101);  // 全消灯での値を取得
        
        SetIRLED(0b0110);   // l,fr点灯
        //vTaskDelay(1);  // 1ms待つ
        ets_delay_us(100);   // 10us待つ
        ReadSensor(sensors,0b0110); // l,fr点灯での値を取得
        SetIRLED(0b0000);   // 全消灯
        vTaskDelay(1/portTICK_PERIOD_MS);   // 1ms待つ
        

        w_sens.val.fl = sensors[0] - before[0];
        w_sens.val.l = sensors[1] - before[1];
        w_sens.val.r = sensors[2] - before[2];
        w_sens.val.fr = sensors[3] - before[3];
        ct.Vatt = BatteryVoltage(); // 他のタスクやループ内で呼ぼうとするとADCが上手く読めないのでここで呼ぶ

        //printf(">ct.Vatt:%f\n",ct.Vatt);
        //printf(">FL : %d,  >L : %d,  >R : %d,  >FR : %d\n",w_sens.val.fl, w_sens.val.l, w_sens.val.r, w_sens.val.fr);
        //vTaskDelay(10/portTICK_PERIOD_MS);   // 10ms待つ
    }
}