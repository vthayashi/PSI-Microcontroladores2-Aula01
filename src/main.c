#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#define STACK_SIZE 1024
#define PRIORITY 5
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

void minha_thread(void)
{
     int ret;

    if (!gpio_is_ready_dt(&led)) {
        printk("Error: LED device %s is not ready\n", led.port->name);
        return;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    while (1) {
        gpio_pin_toggle_dt(&led);
        printk("LED blinking on %s pin %d\n", led.port->name, led.pin);
        k_msleep(1000);
    }
}

void minha_thread1(void)
{
    int ret;

    if (!gpio_is_ready_dt(&led1)) {
        printk("Error: LED device %s is not ready\n", led.port->name);
        return;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }
    
    while (1) {
        gpio_pin_toggle_dt(&led1);
        printk("LED blinking on %s pin %d\n", led1.port->name, led1.pin);
        k_msleep(350);
    }
}

// Criar a thread
K_THREAD_DEFINE(minha_thread_id, 512, minha_thread, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(minha_thread_id1, 512, minha_thread1, NULL, NULL, NULL, 7, 0, 0);

void main(void)
{
    while (1) {
        k_thread_suspend(k_current_get());
        printk("teste main");
    }
}