#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/devicetree.h>

#define SLEEP_TIME_MS 500
#define STACK_SIZE 1024
#define PRIORITY 5

// Define LEDs usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

// Verifica se os LEDs estão definidos no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led1 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED2_NODE, okay)
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
#else
#error "Unsupported board: led1 devicetree alias is not defined"
#endif

static bool running_1s = false;
static bool running_500ms = false;
static bool running_350ms = false;

void LED_1s() {
    while (running_1s) {
        gpio_pin_toggle_dt(&led0);
        k_msleep(1000);
    }
}

void LED_500ms() {
    while (running_500ms) {
        gpio_pin_toggle_dt(&led1);
        k_msleep(SLEEP_TIME_MS);
    }
}

void LED_350ms() {
    while (running_350ms) {
        gpio_pin_toggle_dt(&led2);
        k_msleep(350);
    }
}

K_THREAD_DEFINE(thread_1s, STACK_SIZE, LED_1s, NULL, NULL, NULL, PRIORITY * 1, 0, 0);
K_THREAD_DEFINE(thread_500ms, STACK_SIZE, LED_500ms, NULL, NULL, NULL, PRIORITY * 2, 0, 0);
K_THREAD_DEFINE(thread_350ms, STACK_SIZE, LED_350ms, NULL, NULL, NULL, PRIORITY * 2, 0, 0);

int main(void)
{
    int ret;

    // Verifica se os devices estão prontos
    if (!gpio_is_ready_dt(&led0)) {
        printk("Error: LED0 device %s is not ready\n", led0.port->name);
        return 1;
    }

    if (!gpio_is_ready_dt(&led1)) {
        printk("Error: LED1 device %s is not ready\n", led1.port->name);
        return 1;
    }

    if (!gpio_is_ready_dt(&led2)) {
        printk("Error: LED2 device %s is not ready\n", led2.port->name);
        return 1;
    }

    // Configura os pinos como saída
    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED0 pin\n", ret);
        return 1;
    }

    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED1 pin\n", ret);
        return 1;
    }

    ret = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED2 pin\n", ret);
        return 1;
    }

    printk("LED0 blinking on %s pin %d\n", led0.port->name, led0.pin);
    printk("LED1 blinking on %s pin %d\n", led1.port->name, led1.pin);
    printk("LED2 blinking on %s pin %d\n", led2.port->name, led2.pin);

    while (1) {
        
        gpio_pin_set_dt(&led0, 0); // Ensure LED0 is off before next pattern
        gpio_pin_set_dt(&led1, 0); // Ensure LED1 is off before next pattern
        gpio_pin_set_dt(&led2, 0); // Ensure LED2 is off before next pattern
        running_1s = true;
        running_350ms = true;
        k_msleep(SLEEP_TIME_MS * 7 * 10); // Let the 1s and 350ms threads run for 10 cycles
        running_1s = false;
        running_350ms = false;
    }
    return 0;
}

// funcionamento esperado: Piscagem dos LEDs vermelho (0) e azul (2) em intervalos de 1s e 350ms respectivamente. 
// Piscarão verdadeiramente juntos apenas depois de 7 segundos, mas a olho nu não parecerá dessa forma pois piscam em intervalos muito próximos em certos momentos