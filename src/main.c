#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 50

// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif
#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec ledd = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

int main()
{
    int ret;
    int ret1;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led))
    {
        printk("Error: LED device %s is not ready\n", led.port->name);
        return;
    }
    if (!gpio_is_ready_dt(&ledd))
    {
        printk("Error: LED device %s is not ready\n", ledd.port->name);
        return;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0)
    {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }
    // Configura o pino como saída
    ret1 = gpio_pin_configure_dt(&ledd, GPIO_OUTPUT_ACTIVE);
    if (ret1 < 0)
    {
        printk("Error %d: failed to configure LED pin\n", ret1);
        return;
    }

    printk("LED blinking on %s pin %d\n", led.port->name, led.pin);
    int tick = 4;
    while (1)
    {
        if (tick % 7 == 0)
        {
            gpio_pin_toggle_dt(&led);
        }
        if (tick % 20 == 0)
        {
            gpio_pin_toggle_dt(&ledd);
        }
        tick++;
        k_msleep(SLEEP_TIME_MS/2);
    }
}