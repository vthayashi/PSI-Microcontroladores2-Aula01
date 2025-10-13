#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define PERIODO_LED 1000
#define PULSO_TIME 100

#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

void blink_led(void)
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
        int64_t next_cycle = ((elapsed / PERIODO_LED) + 1) * PERIODO_LED;

        gpio_pin_set_dt(&led0, 1);
        k_msleep(PULSO_TIME);
        gpio_pin_set_dt(&led0, 0);

        // Espera até o próximo múltiplo exato do período
        k_msleep(next_cycle - (k_uptime_get() - start_time));
    }
}

K_THREAD_DEFINE(blink_led_id, 1024, blink_led, NULL, NULL, NULL, 7, 0, 0);

void main(void)
{
    printk("Sistema iniciado.\n");
}
