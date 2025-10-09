// Led verde pisca a cada 1000 ms e o LED vermelho pisca a cada 350 ms. Período de duração do sinal de 25 ms.
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

void main(void)
{
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

    while (1) {
    
        for(int t = 0; t < 7000; t++){
            if((t % 1000) == 0){
                if(((t-25) % 350) == 0){
                    //LEDs verde e vermelho piscam
                    gpio_pin_toggle_dt(&ledverde);
                    gpio_pin_toggle_dt(&ledvermelho);
                    k_msleep(25);
                    printk("Led verde piscou! (t = %d ms)\n", t);
                    printk("Led vermelho piscou! (t = %d ms)\n", t);
                    gpio_pin_toggle_dt(&ledverde);
                    gpio_pin_toggle_dt(&ledvermelho);
                    t += 24;
                } else {
                    //LED verde pisca
                    gpio_pin_toggle_dt(&ledverde);
                    k_msleep(25);
                    printk("Led verde piscou! (t = %d ms)\n", t);
                    gpio_pin_toggle_dt(&ledverde);
                    t += 24;
                }
            } else if(((t-25) % 350) == 0) {
                //LED vermelho pisca
                gpio_pin_toggle_dt(&ledvermelho);
                k_msleep(25);
                printk("Led vermelho piscou! (t = %d ms)\n", t);
                gpio_pin_toggle_dt(&ledvermelho);
                t += 24;
            } else {
                k_msleep(1);
            }
        }
    }
}