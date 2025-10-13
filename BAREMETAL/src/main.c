#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/devicetree.h>

#define SLEEP_TIME_MS 500

//change 1

// Define LEDs usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

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

    printk("LED0 blinking on %s pin %d\n", led0.port->name, led0.pin);
    printk("LED1 blinking on %s pin %d\n", led1.port->name, led1.pin);

    while (1) {
        printk("Toggling LEDs 1s-350ms for 5 times in a row (each loop takes 7s) \n");
        for(int j = 0; j < 5; j++) {
        // 0s
        gpio_pin_toggle_dt(&led0);
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 350ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 700ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(300); // 1s
        gpio_pin_toggle_dt(&led0);
        k_msleep(50); // 1s-50ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 1s-400ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 1s-750ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(250); // 2s
        gpio_pin_toggle_dt(&led0);
        k_msleep(100); // 2s-100ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 2s-450ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 2s-800ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(200); // 3s
        gpio_pin_toggle_dt(&led0);
        k_msleep(150); // 3s-150ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 3s-500ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 3s-850ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(150); // 4s
        gpio_pin_toggle_dt(&led0);
        k_msleep(200); // 4s-200ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 4s-550ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 4s-900ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(100); // 5s
        gpio_pin_toggle_dt(&led0);
        k_msleep(250); // 5s-250ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 5s-600ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 5s-950ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(50); // 6s
        gpio_pin_toggle_dt(&led0);
        k_msleep(300); // 6s-300ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 6s-650ms
        gpio_pin_toggle_dt(&led1);
        k_msleep(350); // 7s
        gpio_pin_toggle_dt(&led0);
        gpio_pin_toggle_dt(&led1);
        k_msleep(1000);
        }
    }
    return 0;
}

// funcionamento esperado: Piscagem dos LEDs vermelho (0) e verde (1) em intervalos de 1s e 350ms respectivamente. 
// Piscarão verdadeiramente juntos apenas depois de 7 segundos, mas a olho nu não parecerá dessa forma pois piscam em intervalos muito próximos em certos momentos