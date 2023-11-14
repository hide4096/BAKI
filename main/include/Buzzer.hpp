#ifndef BUZZER_HPP
#define BUZZER_HPP

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"


#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits


class BUZZER{
    public:
        
        enum melody{
            A = 538,
            B = 604,
            C = 678,
            D = 718,
            E = 806,
            F = 905,
            G = 1016,
        };
        BUZZER();
        ~BUZZER();

        void init(ledc_channel_t channel, ledc_timer_t timer, gpio_num_t pin);
        void freq(uint32_t freq);
        void volume(uint32_t duty);
        void stop();
        void play();
        void music(enum melody m);

    private:
        ledc_channel_t _channel;
        ledc_timer_t _timer;
};

#endif
