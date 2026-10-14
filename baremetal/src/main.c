#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 1000
#define SLEEP_TIME_MS1 500
#define SLEEP_TIME_MS2 350


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
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led1 devicetree alias is not defined"
#endif

int main(void)
{
    int ret;
    int ret1;

    /* Led 1 ===================================================== */

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led)) {
        printk("Error: LED device %s is not ready\n", led.port->name);
        return -1;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return ret;
    }

    printk("LED blinking on %s pin %d\n", led.port->name, led.pin);

    /* Led 2 ===================================================== */

    if (!gpio_is_ready_dt(&led1)) {
        printk("Error: LED device %s is not ready\n", led1.port->name);
        return -1;
    }

    // Configura o pino como saída
    ret1 = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret1 < 0) {
        printk("Error %d: failed to configure LED pin\n", ret1);
        return ret1;
    }   

    printk("LED blinking on %s pin %d\n", led1.port->name, led1.pin);

    while (1) {
        // Primeiro exercicio
        /* gpio_pin_set_dt(&led, 1);
        k_msleep(SLEEP_TIME_MS1);
        gpio_pin_set_dt(&led, 0);
		k_msleep(SLEEP_TIME_MS1);
        gpio_pin_set_dt(&led1, 1);
        k_msleep(SLEEP_TIME_MS);
		gpio_pin_set_dt(&led1, 0);
		k_msleep(SLEEP_TIME_MS); */


        // Desafio
        gpio_pin_toggle_dt(&led);
        k_msleep(SLEEP_TIME_MS);

        gpio_pin_toggle_dt(&led1);
        k_msleep(SLEEP_TIME_MS2);


	}
    return 0;
}
