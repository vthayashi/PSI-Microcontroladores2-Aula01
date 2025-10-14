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

void piscarled(){
    while(1){
    gpio_pin_toggle_dt(&led);
    k_msleep(1000)
}}
void piscarledd(){
    while(1){
    gpio_pin_toggle_dt(&ledd);
    k_msleep(350)
}}

K_THREAD_DEFINE(piscar_led1, 512, piscarled, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(piscar_led2, 1024, piscarledd, NULL, NULL, NULL, 7, 0, 0);

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
    while (1){}
}
