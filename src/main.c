#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led_green = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec led_blue = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif


void main(void)
{
    int ret_green, ret_blue;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led_green)) {
        printk("Error: LED device %s is not ready\n", led_green.port->name);
        return;
    }

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led_blue)) {
        printk("Error: LED device %s is not ready\n", led_blue.port->name);
        return;
    }

    // Configura o pino como saída
    ret_green = gpio_pin_configure_dt(&led_green, GPIO_OUTPUT_INACTIVE);
    if (ret_green < 0) {
        printk("Error %d: failed to configure LED pin\n", ret_green);
        return;
    }

    printk("LED blinking on %s pin %d\n", led_green.port->name, led_green.pin);


    // Configura o pino como saída
    ret_blue = gpio_pin_configure_dt(&led_blue, GPIO_OUTPUT_INACTIVE);
    if (ret_blue < 0) {
        printk("Error %d: failed to configure LED pin\n", ret_blue);
        return;
    }

    printk("LED blinking on %s pin %d\n", led_green.port->name, led_green.pin);




    while (1) {
        // Toggle do led 

        // O LED verde pisca a cada 1 segundo durante 50ms e o azul a cada 500ms durante 50ms
        // como eles estam em fases, eles piscam juntos no ciano 
        gpio_pin_toggle_dt(&led_green);
        gpio_pin_toggle_dt(&led_blue);
        k_msleep(50);
        gpio_pin_toggle_dt(&led_green);
        gpio_pin_toggle_dt(&led_blue);

        
        k_msleep(450);
        gpio_pin_toggle_dt(&led_blue);
        k_msleep(50);
        gpio_pin_toggle_dt(&led_blue);
        k_msleep(450);
    }
}