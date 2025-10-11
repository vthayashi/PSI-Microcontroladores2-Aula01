#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

// Tempos de piscar
#define LED0_SLEEP_TIME_MS 1000
#define LED1_SLEEP_TIME_MS 350

// Define os LEDs usando Device Tree
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

// Verifica se estão definidos no Device Tree
#if !DT_NODE_HAS_STATUS(LED0_NODE, okay)
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

#if !DT_NODE_HAS_STATUS(LED1_NODE, okay)
#error "Unsupported board: led1 devicetree alias is not defined"
#endif

// Estruturas dos LEDs
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

// Pilhas das threads
#define STACK_SIZE 512
#define PRIORITY 7

// Função da thread do LED0
void led0_thread(void)
{
    int ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED0\n", ret);
        return;
    }

    printk("Thread LED0 rodando no pino %d (%s)\n", led0.pin, led0.port->name);

    while (1) {
        gpio_pin_toggle_dt(&led0);
        k_msleep(LED0_SLEEP_TIME_MS);
    }
}

// Função da thread do LED1
void led1_thread(void)
{
    int ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        printk("Error %d: failed to configure LED1\n", ret);
        return;
    }

    printk("Thread LED1 rodando no pino %d (%s)\n", led1.pin, led1.port->name);

    while (1) {
        gpio_pin_toggle_dt(&led1);
        k_msleep(LED1_SLEEP_TIME_MS);
    }
}

// Cria as threads com K_THREAD_DEFINE
K_THREAD_DEFINE(led0_tid, STACK_SIZE, led0_thread, NULL, NULL, NULL,
                PRIORITY, 0, 0);
K_THREAD_DEFINE(led1_tid, STACK_SIZE, led1_thread, NULL, NULL, NULL,
                PRIORITY, 0, 0);

void main(void)
{
    printk("Sistema iniciado — controle dos LEDs via threads\n");

    // Verifica se os dispositivos estão prontos
    if (!gpio_is_ready_dt(&led0) || !gpio_is_ready_dt(&led1)) {
        printk("Erro: LED devices não estão prontos\n");
        return;
    }

    // A partir daqui, as threads já estão rodando em paralelo
}
