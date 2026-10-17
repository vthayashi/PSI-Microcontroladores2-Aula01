#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led1 devicetree alia
#endif

void timer0_handler(struct k_timer *timer_id) {
    printk("[%lld ms] Piscando LED (500ms)!\n", k_uptime_get());
    gpio_pin_toggle_dt(&led0);
}

void timer1_handler(struct k_timer *timer_id) {
    printk("[%lld ms] Piscando LED (1000ms)!\n", k_uptime_get());
    gpio_pin_toggle_dt(&led1);
}

K_TIMER_DEFINE(timer0, timer0_handler, NULL);
K_TIMER_DEFINE(timer1, timer1_handler, NULL);

void blink_led_500ms(void) {
    k_timer_start(&timer0, K_MSEC(0), K_MSEC(500));
}

void blink_led_1000ms(void) {
    k_timer_start(&timer1, K_MSEC(0), K_MSEC(1000));
}

void main(void)
{
    int ret;

    if (!gpio_is_ready_dt(&led0)) {
        printk("Error: LED device %s is not ready\n", led0.port->name);
        return;
    }

    if (!gpio_is_ready_dt(&led1)) {
        printk("Error: LED device %s is not ready\n", led1.port->name);
        return;
    }

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

    blink_led_500ms();
    blink_led_1000ms();
}