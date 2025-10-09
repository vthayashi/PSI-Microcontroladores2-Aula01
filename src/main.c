// Led verde pisca a cada 1000 ms e vermelho pisca a cada 500 ms. Período do sinal de 100 ms.
// Verificar que a cada piscada, é enviada uma mensagem no terminal pela FRDM (estático)
// Verificar frequência de piscada no serial do notebook (dinâmico)

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

// Define o LED verde usando Device Tree
#define LED_VERDE DT_ALIAS(led0)

// Define o LED vermelho usando o Device Tree
#define LED_VERMELHO DT_ALIAS(led2)

// Verifica se o LED verde está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED_VERDE, okay)
static const struct gpio_dt_spec ledverde = GPIO_DT_SPEC_GET(LED_VERDE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

// Verifica se o LED vermelho está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED_VERMELHO, okay)
static const struct gpio_dt_spec ledvermelho = GPIO_DT_SPEC_GET(LED_VERMELHO, gpios);
#else
#error "Unsupported board: led2 devicetree alias is not defined"
#endif


void pisca_verde(void)
{
    while (1) {
        gpio_pin_toggle_dt(&ledverde);
        k_msleep(100);
        printk("Led verde piscou!\n");
        gpio_pin_toggle_dt(&ledverde);
        k_msleep(900);
    }
}

void pisca_vermelho(void)
{
    while (1) {
        gpio_pin_toggle_dt(&ledvermelho);
        k_msleep(100);
        printk("Led vermelho piscou!\n");
        gpio_pin_toggle_dt(&ledvermelho);
        k_msleep(400);
    }
}

// Criar a thread para LED verde
K_THREAD_DEFINE(thread_led_verde, 512, pisca_verde, NULL, NULL, NULL, 7, 0, 100);

// Criar a thread para LED vermelho
K_THREAD_DEFINE(thread_led_vermelho, 512, pisca_vermelho, NULL, NULL, NULL, 7, 0, 300);

void main(void){

    printk("Main iniciou\n");

    int retverde, retvermelho;

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

    // Verifica se o device (LED vermelho) está pronto
    if (!gpio_is_ready_dt(&ledvermelho)) {
        printk("Error: Red LED device %s is not ready\n", ledvermelho.port->name);
        return;
    }

    // Configura o pino do LED verde como saída
    retvermelho = gpio_pin_configure_dt(&ledvermelho, GPIO_OUTPUT_INACTIVE);
    if (retvermelho < 0) {
        printk("Error %d: failed to configure red LED pin\n", retvermelho);
        return;
    }

    printk("LED verde piscando no %s pino %d\n", ledverde.port->name, ledverde.pin);
    printk("LED vermelho piscando no %s pino %d\n", ledvermelho.port->name, ledvermelho.pin);

    k_msleep(100);
    while (1) {
        printk("Main executando\n");
        k_msleep(1000);
    }
}