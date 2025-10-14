#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>


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
    while (1)
    {       
    gpio_pin_toggle_dt(&ledd);
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 350ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 700ms
        gpio_pin_toggle_dt(&led);
        k_msleep(300); // 1s
        gpio_pin_toggle_dt(&ledd);
        k_msleep(50); // 1s-50ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 1s-400ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 1s-750ms
        gpio_pin_toggle_dt(&led);
        k_msleep(250); // 2s
        gpio_pin_toggle_dt(&ledd);
        k_msleep(100); // 2s-100ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 2s-450ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 2s-800ms
        gpio_pin_toggle_dt(&led);
        k_msleep(200); // 3s
        gpio_pin_toggle_dt(&ledd);
        k_msleep(150); // 3s-150ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 3s-500ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 3s-850ms
        gpio_pin_toggle_dt(&led);
        k_msleep(150); // 4s
        gpio_pin_toggle_dt(&ledd);
        k_msleep(200); // 4s-200ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 4s-550ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 4s-900ms
        gpio_pin_toggle_dt(&led);
        k_msleep(100); // 5s
        gpio_pin_toggle_dt(&ledd);
        k_msleep(250); // 5s-250ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 5s-600ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 5s-950ms
        gpio_pin_toggle_dt(&led);
        k_msleep(50); // 6s
        gpio_pin_toggle_dt(&ledd);
        k_msleep(300); // 6s-300ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 6s-650ms
        gpio_pin_toggle_dt(&led);
        k_msleep(350); // 7s
        gpio_pin_toggle_dt(&ledd);
        gpio_pin_toggle_dt(&led);
        k_msleep(1000);

    }
}