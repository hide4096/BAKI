#include "include/Motor.hpp"

#define BDC_MCPWM_TIMER_RESOLUTION_HZ 10000000 // 10MHz, 1 tick = 0.1us
#define BDC_MCPWM_FREQ_HZ             250000    // 250KHz PWM
#define BDC_MCPWM_DUTY_TICK_MAX       (BDC_MCPWM_TIMER_RESOLUTION_HZ / BDC_MCPWM_FREQ_HZ) // maximum value we can set for the duty cycle, in ticks
#define BDC_R_MCPWM_GPIO_A              45
#define BDC_R_MCPWM_GPIO_B              46
#define BDC_L_MCPWM_GPIO_A              GPIO_NUM_41
#define BDC_L_MCPWM_GPIO_B              GPIO_NUM_42
#define FAN_PIN                         GPIO_NUM_13

bdc_motor_handle_t motor_r = NULL;
bdc_motor_handle_t motor_l = NULL;

void initMotors(){
    //モタドラ
    //MODE GPIO40
    gpio_config_t mode_conf = {};
    mode_conf.intr_type = GPIO_INTR_DISABLE;
    mode_conf.mode = GPIO_MODE_OUTPUT;
    mode_conf.pin_bit_mask = (1ULL << 40) && (1ULL << 41) && (1ULL << 42);
    //mode_conf.pin_bit_mask = (1ULL << 40);
    mode_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    mode_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    gpio_config(&mode_conf);
    gpio_set_level(GPIO_NUM_40, 0);
    gpio_set_level(GPIO_NUM_41, 0);
    gpio_set_level(GPIO_NUM_42, 0);

    bdc_motor_config_t motor_r_config;
    motor_r_config.pwm_freq_hz = BDC_MCPWM_FREQ_HZ;
    motor_r_config.pwma_gpio_num = BDC_R_MCPWM_GPIO_A;
    motor_r_config.pwmb_gpio_num = BDC_R_MCPWM_GPIO_B;

    vTaskDelay(1000 / portTICK_PERIOD_MS);

    bdc_motor_config_t motor_l_config;
    motor_l_config.pwm_freq_hz = BDC_MCPWM_FREQ_HZ;
    motor_l_config.pwma_gpio_num = BDC_L_MCPWM_GPIO_A;
    motor_l_config.pwmb_gpio_num = BDC_L_MCPWM_GPIO_B;

    bdc_motor_mcpwm_config_t mcpwm_r_config;
    mcpwm_r_config.group_id = 0;
    mcpwm_r_config.resolution_hz = BDC_MCPWM_TIMER_RESOLUTION_HZ;

    bdc_motor_mcpwm_config_t mcpwm_l_config;
    mcpwm_l_config.group_id = 0;
    mcpwm_l_config.resolution_hz = BDC_MCPWM_TIMER_RESOLUTION_HZ;

    ESP_ERROR_CHECK(bdc_motor_new_mcpwm_device(&motor_r_config, &mcpwm_r_config, &motor_r));
    ESP_ERROR_CHECK(bdc_motor_new_mcpwm_device(&motor_l_config, &mcpwm_l_config, &motor_l));

    printf("motor init\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    bdc_motor_set_speed(motor_r, 0);
    bdc_motor_set_speed(motor_l, 0);

    printf("motor set speed\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    bdc_motor_enable(motor_r);
    bdc_motor_enable(motor_l);
    
    printf("motor enable\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    bdc_motor_forward(motor_r);
    bdc_motor_forward(motor_l);

    printf("motor enable\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    //吸引ファン
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_8_BIT,
        .timer_num        = LEDC_TIMER_1,
        .freq_hz          = 100*1000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = FAN_PIN,
        .speed_mode     = LEDC_LOW_SPEED_MODE,
        .channel        = LEDC_CHANNEL_0,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER_1,
        .duty           = 0,
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void setMotorSpeed(float spdR, float spdL,float fan){
    if(spdR > 0){
        bdc_motor_forward(motor_r);
    }else{
        bdc_motor_reverse(motor_r);
    }
    if(spdL > 0){
        bdc_motor_forward(motor_l);
    }else{
        bdc_motor_reverse(motor_l);
    }
    float dutyR = fabs(spdR);
    float dutyL = fabs(spdL);

    bdc_motor_set_speed(motor_l, dutyL * BDC_MCPWM_DUTY_TICK_MAX);
    bdc_motor_set_speed(motor_r, dutyR * BDC_MCPWM_DUTY_TICK_MAX);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, fan * 256);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

void sincurve(){
    float spdR,spdL;
    float fan;
    float t = 0;
    while(1){
        spdR = sin(t);
        spdL = sin(t);
        fan = 0.5 * sin(t) + 0.5;
        setMotorSpeed(spdR*0.5,spdL*0.5,0);
        //setMotorSpeed(0,0,fan);
        t += 0.01;
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}