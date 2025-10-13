#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define PERIODO_LED0 1000
#define PERIODO_LED1 350
#define PULSO_TIME 100

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
#error "Unsupported board: led1 devicetree alias is not defined"
#endif

void blink_led_0(void)
{
    int ret;

    if (!gpio_is_ready_dt(&led0)) {
        printk("Error: LED device %s is not ready\n", led0.port->name);
        return;
    }

    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    printk("Thread iniciada: LED0 piscando no pino %d\n", led0.pin);

    // Pega o tempo inicial
    int64_t start_time = k_uptime_get();

    while (1) {
        int64_t now = k_uptime_get();
        int64_t elapsed = now - start_time;
        int64_t next_cycle = ((elapsed / PERIODO_LED0) + 1) * PERIODO_LED0;

        gpio_pin_set_dt(&led0, 1);
        k_msleep(PULSO_TIME);
        gpio_pin_set_dt(&led0, 0);

        // Espera até o próximo múltiplo exato do período
        k_msleep(next_cycle - (k_uptime_get() - start_time));
    }
}

void blink_led_1(void)
{
    int ret;

    if (!gpio_is_ready_dt(&led1)) {
        printk("Error: LED device %s is not ready\n", led1.port->name);
        return;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    printk("Thread iniciada: LED1 piscando no pino %d\n", led1.pin);

    int64_t start_time = k_uptime_get();

    while (1) {
        int64_t now = k_uptime_get();
        int64_t elapsed = now - start_time;
        int64_t next_cycle = ((elapsed / PERIODO_LED1) + 1) * PERIODO_LED1;

        gpio_pin_set_dt(&led1, 1);
        k_msleep(PULSO_TIME);
        gpio_pin_set_dt(&led1, 0);

        k_msleep(next_cycle - (k_uptime_get() - start_time));
    }
}

K_THREAD_DEFINE(blink_led0_id, 1024, blink_led_0, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(blink_led1_id, 1024, blink_led_1, NULL, NULL, NULL, 7, 0, 0);

void main(void)
{
    printk("Sistema iniciado.\n");
}
