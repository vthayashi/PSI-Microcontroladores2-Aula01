//Testando na Baremetal com o planejamento de testes

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 1000

// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec ledG = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if DT_NODE_HAS_STATUS(LED1_NODE, okay)
static const struct gpio_dt_spec ledB = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#define STACK_SIZE 1024
#define PRIORITY 7

void pisca_verde (void *arg1, void *arg2, void *arg3) {
    while (1) {
        gpio_pin_toggle_dt(&ledG);
        printk("\n Green LED Toggle");
        k_msleep(1000);
    }
}

void pisca_azul (void *arg1, void *arg2, void *arg3) {
    while (1) {
        gpio_pin_toggle_dt(&ledB);
        printk("\n Blue LED Toggle");
        k_msleep(350);
    }
}

K_THREAD_DEFINE(piscar_Verde, STACK_SIZE, pisca_verde, NULL, NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(piscar_Azul, STACK_SIZE, pisca_azul, NULL, NULL, NULL, PRIORITY, 0, 0);

int main(void)
{
    int ret;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&ledG)) {
        printk("Error: LED device %s is not ready\n", ledG.port->name);
        return;
    }

     if (!gpio_is_ready_dt(&ledB)) {
        printk("Error: LED device %s is not ready\n", ledB.port->name);
        return;
    }

    // Configura o pino como saída
    ret = gpio_pin_configure_dt(&ledB, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    ret = gpio_pin_configure_dt(&ledG, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED pin\n", ret);
        return;
    }

    printk("LED blinking on %s pin %d\n", ledG.port->name, ledG.pin);
    printk("LED blinking on %s pin %d\n", ledB.port->name, ledB.pin);

    while (1) {
        printk("Main executando\n");
        k_msleep(2000);
    }
}