#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define STACK_SIZE 1024
#define PRIORITY_LED0 5
#define PRIORITY_LED1 5

#define PERIOD_LED0_MS 1000
#define PERIOD_LED1_MS 350

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

#if !DT_NODE_HAS_STATUS(LED0_NODE, okay)
#error "Unsupported board: led0 devicetree alias is not defined"
#endif
#if !DT_NODE_HAS_STATUS(LED1_NODE, okay)
#error "Unsupported board: led1 devicetree alias is not defined"
#endif

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

//Declaração das funções thread
void led0_thread_func(void *arg1, void *arg2, void *arg3);
void led1_thread_func(void *arg1, void *arg2, void *arg3);

//Criação estática das threads
K_THREAD_DEFINE(led0_tid, STACK_SIZE, led0_thread_func, NULL, NULL, NULL, PRIORITY_LED0, 0, 0);
K_THREAD_DEFINE(led1_tid, STACK_SIZE, led1_thread_func, NULL, NULL, NULL, PRIORITY_LED1, 0, 0);

int main(void)
{
    int ret;

    if (!gpio_is_ready_dt(&led0) || !gpio_is_ready_dt(&led1)) {
        printk("Error: LED device not ready\n");
        return 0;
    }

    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED0\n", ret);
        return 0;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED1\n", ret);
        return 0;
    }

    printk("Hardware inicializado!\n");

    return 0;

}

void led0_thread_func(void *arg1, void *arg2, void *arg3)
{
    while (1){
        gpio_pin_toggle_dt(&led0);
        k_msleep(PERIOD_LED0_MS);

    }
}

void led1_thread_func(void *arg1, void *arg2, void *arg3)
    while (1){
        gpio_pin_toggle_dt(&led1);
        k_msleep(PERIOD_LED1_MS);

    }
}
