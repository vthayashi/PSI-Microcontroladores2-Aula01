#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 500

// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED2_NODE, okay)
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

void main(void)
{
    int ret, ret1, ret2;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led)) {
        printk("Error: LED device %s is not ready\n", led.port->name);
        return;
    }

    if (!gpio_is_ready_dt(&led1)) {
        printk("Error: LED device %s is not ready\n", led.port->name);
        return;
    }

    if (!gpio_is_ready_dt(&led2)) {
        printk("Error: LED device %s is not ready\n", led.port->name);
        return;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    ret1 = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret1 < 0) {
        printk("Error %d: failed to configure LED pin\n", ret1);
        return;
    }

    ret2 = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
    if (ret2 < 0) {
        printk("Error %d: failed to configure LED pin\n", ret2);
        return;
    }

    printk("LED blinking on %s pin %d\n", led.port->name, led.pin);
    printk("LED blinking on %s pin %d\n", led1.port->name, led1.pin);
    printk("LED blinking on %s pin %d\n", led2.port->name, led2.pin);

    int timer = 0;
    int timer1 = 0;

    while (1) {
        // Toggle do LED usando a nova API
        if (timer == 350) {
            gpio_pin_toggle_dt(&led);
            printk("LED blinking on %s pin %d\n", led1.port->name, led1.pin);
            timer = 0;
        }
        
        if (timer1 == 1000) {
            gpio_pin_toggle_dt(&led);
            printk("LED blinking on %s pin %d\n", led.port->name, led.pin);
            timer1 = 0;
        }
        
        timer++;
        timer1++;
        k_msleep(1);
    }