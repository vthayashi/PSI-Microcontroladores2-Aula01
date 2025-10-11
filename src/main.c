#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 350
#define SLEEP_TIME_MS1 1000
#define STACKSIZE 1024
#define PRIORITY 7
// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec verde = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif
#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec azul = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif
void thread_350ms(void)
{
    while (1) {
        gpio_pin_toggle_dt(&verde);
        k_msleep(SLEEP_TIME_MS);
    }
}
void thread_1000ms(void)
{
    while (1) {
        gpio_pin_toggle_dt(&azul);
        k_msleep(SLEEP_TIME_MS1);
    }
}
K_THREAD_DEFINE(id_pisca_350, STACKSIZE, thread_350ms, NULL, NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(id_pisca_1000, STACKSIZE, thread_1000ms, NULL, NULL, NULL, PRIORITY, 0, 0);
void main(void)
{
    int ret, ret1;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&verde)) {
        printk("Error: LED device %s is not ready\n", verde.port->name);
        return;
    }
     if (!gpio_is_ready_dt(&azul)) {
        printk("Error: LED device %s is not ready\n", azul.port->name);
        return;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&verde, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }
     ret1 = gpio_pin_configure_dt(&azul, GPIO_OUTPUT_ACTIVE);
    if (ret1 < 0) {
        printk("Error %d: failed to configure LED pin\n", ret1);
        return;
    }

    printk("LED blinking on %s pin %d\n", verde.port->name, verde.pin);
    printk("LED blinking on %s pin %d\n", azul.port->name, azul.pin);
   
}