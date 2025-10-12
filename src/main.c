#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

#define PERIODO_LED0 1000   // 1 segundo
#define PERIODO_LED1 350    // 350 ms
#define PULSO_TIME 100      // 100 ms 

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led1 devicetree alias is not defined"
#endif

void main(void){
    int ret;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led0)) {
        printk("Error: LED device %s is not ready\n", led0.port->name);
        return;
    }
    if (!gpio_is_ready_dt(&led1)) {
        printk("Error: LED device %s is not ready\n", led1.port->name);
        return;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED0 pin\n", ret);
        return;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED1 pin\n", ret);
        return;
    }

    int64_t last_toggle_led0 = 0;
    int64_t last_toggle_led1 = 0;
    int64_t pulse_end_led0 = 0;
    int64_t pulse_end_led1 = 0;

    while (1) {
        int64_t agora = k_uptime_get();

        // LED 0
        if(agora - last_toggle_led0 >= PERIODO_LED0){
            gpio_pin_set_dt(&led0, 1);
            last_toggle_led0 = agora;
            pulse_end_led0 = agora + PULSO_TIME;
            printk("LED0 piscou em %lld ms\n", agora);
        }

        if(gpio_pin_get_dt(&led0) && agora >= pulse_end_led0){
            gpio_pin_set_dt(&led0, 0);
        }

        // LED 1
        if(agora - last_toggle_led1 >= PERIODO_LED1){
            gpio_pin_set_dt(&led1, 1);
            last_toggle_led1 = agora;
            pulse_end_led1 = agora + PULSO_TIME;
            printk("LED1 piscou em %lld ms\n", agora);
        }

        if(gpio_pin_get_dt(&led1) && agora >= pulse_end_led1){
            gpio_pin_set_dt(&led1, 0);
        }
    }
}