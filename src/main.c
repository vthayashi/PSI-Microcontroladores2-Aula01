#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define STACK_SIZE 1024
#define PRIORITY_1 5
#define PRIORITY_2 6

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led1 devicetree alias is not defined"
#endif


void blink_led_1000ms(void *arg1, void *arg2, void *arg3) {
    while (1) {
        printk("[%lld ms] Piscando LED (1000ms)!\n", k_uptime_get());
        gpio_pin_toggle_dt(&led0);
        k_msleep(1000);
    }
}

K_THREAD_DEFINE(thread_blink_led_1000ms, STACK_SIZE, blink_led_1000ms,
                NULL, NULL, NULL,
                PRIORITY_1, 0, 0);


void blink_led_500ms(void *arg1, void *arg2, void *arg3) {
    while (1) {
        printk("[%lld ms] Piscando LED (500ms)!\n", k_uptime_get());
        gpio_pin_toggle_dt(&led1);
        k_msleep(500);
    }
}

K_THREAD_DEFINE(thread_blink_led_500ms, STACK_SIZE, blink_led_500ms,
                NULL, NULL, NULL,
                PRIORITY_2, 0, 0);

void main(void) {
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
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    return;
}