#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

// Define o LED verde usando Device Tree
#define LED_VERDE DT_ALIAS(led0)

// Define o LED azul usando o Device Tree
#define LED_AZUL DT_ALIAS(led1)

// Verifica se o LED verde está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED_VERDE, okay)
static const struct gpio_dt_spec ledverde = GPIO_DT_SPEC_GET(LED_VERDE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

// Verifica se o LED azul está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED_AZUL, okay)
static const struct gpio_dt_spec ledazul = GPIO_DT_SPEC_GET(LED_AZUL, gpios);
#else
#error "Unsupported board: led2 devicetree alias is not defined"
#endif


void pisca_verde(void)
{
    while (1) {
        gpio_pin_toggle_dt(&ledverde);
        k_msleep(25);
        printk("Led verde piscou!\n");
        gpio_pin_toggle_dt(&ledverde);
        k_msleep(975);
    }
}

void pisca_azul(void)
{
    while (1) {
        gpio_pin_toggle_dt(&ledazul);
        k_msleep(25);
        printk("Led azul piscou!\n");
        gpio_pin_toggle_dt(&ledazul);
        k_msleep(275);
    }
}

// Criar a thread para LED verde
K_THREAD_DEFINE(thread_led_verde, 512, pisca_verde, NULL, NULL, NULL, 7, 0, 0);

// Criar a thread para LED azul
K_THREAD_DEFINE(thread_led_azul, 512, pisca_azul, NULL, NULL, NULL, 7, 0, 0);

void main(void){

    printk("Main iniciou\n");

    int retverde, retazul;

    // Verifica se o device (LED verde) está pronto
    if (!gpio_is_ready_dt(&ledverde)) {
        printk("Error: Green LED device %s is not ready\n", ledverde.port->name);
        return;
    }

    // Configura o pino do LED verde como saída
    retverde = gpio_pin_configure_dt(&ledverde, GPIO_OUTPUT_INACTIVE);
    if (retverde < 0) {
        printk("Error %d: failed to configure green LED pin\n", retverde);
        return;
    }

    // Verifica se o device (LED azul) está pronto
    if (!gpio_is_ready_dt(&ledazul)) {
        printk("Error: Blue LED device %s is not ready\n", ledazul.port->name);
        return;
    }

    // Configura o pino do LED verde como saída
    retazul = gpio_pin_configure_dt(&ledazul, GPIO_OUTPUT_INACTIVE);
    if (retazul < 0) {
        printk("Error %d: failed to configure blue LED pin\n", retazul);
        return;
    }

    while (1) {
        printk("Main executando\n");
        k_msleep(7000);
    }
}
