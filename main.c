#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

volatile int  pulse ;
const uint led = 22;
const uint flow_sensor = 15;
double  Liter_per_hour;
void button_callback(uint gpio, uint32_t events)
{
  pulse++;
}


bool timer_callback( repeating_timer_t *rt )
{   gpio_set_irq_enabled(flow_sensor, 0x08, 0);
    Liter_per_hour = (pulse * 60 * 5 / 7.5);
    pulse= 0;
    gpio_set_irq_enabled(flow_sensor, 0x08, 1);
//    printf("Liter/hour:%f", Liter_per_hour);
    return (true);
}
int main() {
   


    // Initialize switch pin
    gpio_init(led);
    gpio_set_dir(led, GPIO_OUT);

    //intially set switch in OFF condition
    gpio_put(led, true);

    //set water level threshold
    float thl_flow =10;  
    stdio_init_all();
    //printf("ADC Example, measuring GPIO26\n");

    //adc_init();

    // Make sure GPIO is high-impedance, no pullups etc
    gpio_init(flow_sensor);
    // Select ADC input 0 (GPIO26)
    gpio_set_dir(flow_sensor, GPIO_IN);

    gpio_set_irq_enabled_with_callback(flow_sensor, 0x08, 1, button_callback);

    repeating_timer_t timer;
    add_repeating_timer_ms( 200, &timer_callback, NULL, &timer );
//    while (1) {
//        // 12-bit conversion, assume max value == ADC_VREF == 5 V
//        //const float conversion_factor = 5f / (1 << 12);
//        //uint16_t voltage = adc_read();
//
//
//
//        printf( "no. of pulses: %d \n", pulse);
//
//        // 5 pulse per min= 1 liter per min
//        float flow_rate = 0.2*pulse;
//        printf("flow rate: %f liter/min \n", flow_rate);
//
//        sleep_ms(500);
//
///*
//        if(voltage>threshold)
//        {
//
//            gpio_put(switch_ckt, false);
//            sleep_ms(1000);
//
//        }
//        else
//            gpio_put(switch_ckt, true);
//
//*/
//    }

    while (1)
    {
        printf("Liter/hour:%f\n", Liter_per_hour);
        sleep_ms(1000);
    }
} 