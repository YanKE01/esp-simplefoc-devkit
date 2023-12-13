#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "VF.h"

void app_main(void)
{

    rtU.Freq = 6;
    rtU.ud = 0;
    rtU.uq = 4;
    rtU.v_bus = 12;

    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = (1ULL << GPIO_NUM_10),
        .pull_down_en = 0,
        .pull_up_en = 0,
    };

    gpio_config(&io_conf);

    gpio_set_level(GPIO_NUM_10, 1);

    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 10 * 1000, // Set output frequency at 20 kHz
        .clk_cfg = LEDC_USE_APB_CLK};
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    gpio_num_t pins[3] = {GPIO_NUM_4, GPIO_NUM_5, GPIO_NUM_6};
    ledc_channel_t channels[3] = {LEDC_CHANNEL_0, LEDC_CHANNEL_1, LEDC_CHANNEL_2};

    ledc_channel_config_t ledc_channel;
    for (int i = 0; i < 3; i++)
    {
        ledc_channel.speed_mode = LEDC_LOW_SPEED_MODE;
        ledc_channel.timer_sel = LEDC_TIMER_0;
        ledc_channel.duty = 0;
        ledc_channel.hpoint = 0;
        ledc_channel.intr_type = LEDC_INTR_DISABLE;
        ledc_channel.channel = channels[i];
        ledc_channel.gpio_num = pins[i];
        ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    }

    while (1)
    {
        VF_step();
        ledc_set_duty(LEDC_LOW_SPEED_MODE, channels[0], rtY.tABC[0]);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, channels[0]);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, channels[1], rtY.tABC[1]);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, channels[1]);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, channels[2], rtY.tABC[2]);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, channels[2]);
    }
}