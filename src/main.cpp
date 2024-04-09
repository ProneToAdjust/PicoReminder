#include <Arduino.h>
#include <pico/cyw43_arch.h>
#include "boards/pico_w.h"
#include <stdio.h>
#include "hardware/rtc.h"
#include "pico/stdlib.h"
#include "pico/util/datetime.h"

#define BUTTON_PIN 16

char datetime_buf[256];
char *datetime_str = &datetime_buf[0];

// Set the current date and time
datetime_t current_datetime = {
    .year = 2024,
    .month = 04,
    .day = 19,
    .dotw = 2, // 0 is Sunday, so 5 is Friday
    .hour = 15,
    .min = 45,
    .sec = 50};

// Set an alarm for 4am everyday
datetime_t alarm_datetime = {
    .year = -1,
    .month = -1,
    .day = -1,
    .dotw = -1,
    .hour = 4,
    .min = -1,
    .sec = -1};

void alarm_callback();
void button_release_callback(uint gpio, uint32_t events);

void setup()
{
    // Set button pin as input
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    // Set button pin as pull up
    gpio_pull_up(BUTTON_PIN);

    // Start the RTC
    rtc_init();
    rtc_set_datetime(&current_datetime);

    // clk_sys is >2000x faster than clk_rtc, so datetime is not updated immediately when rtc_get_datetime() is called.
    // tbe delay is up to 3 RTC clock cycles (which is 64us with the default clock settings)
    sleep_us(64);

    // Set the alarm
    rtc_set_alarm(&alarm_datetime, &alarm_callback);
}

void loop()
{
    rtc_get_datetime(&current_datetime);
    datetime_to_str(datetime_str, sizeof(datetime_buf), &current_datetime);
    Serial.printf("\r%s      ", datetime_str);
}

void alarm_callback()
{
    // Turn on the onboard LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    // Enable the button interrupt
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_release_callback);
}

void button_release_callback(uint gpio, uint32_t events)
{
    // Turn off the onboard LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);

    // Disable the button interrupt
    gpio_set_irq_enabled(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, false);
}
