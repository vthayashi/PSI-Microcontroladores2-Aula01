#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

// Define o LED usando Device Tree
#define LEDG_NODE DT_ALIAS(led0)
#define LEDR_NODE DT_ALIAS(led2)

// Verifica se o LED está definido no Device Tree

#if DT_NODE_HAS_STATUS(LEDG_NODE, okay)
static const struct gpio_dt_spec ledg = GPIO_DT_SPEC_GET(LEDG_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined - Green LED"
#endif

#if DT_NODE_HAS_STATUS(LEDR_NODE, okay)
static const struct gpio_dt_spec ledr = GPIO_DT_SPEC_GET(LEDR_NODE, gpios);
#else
#error "Unsupported board: led2 devicetree alias is not defined - Red LED"
#endif


void main(void)
{
    int retg, retr;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&ledg)) {
		
        printk("Error: LED G is not ready\n");
        return;
    }
    if (!gpio_is_ready_dt(&ledr)) {
        printk("Error: LED R is not ready\n");
        return;
    }

    // Configura o pino como saída
    retg = gpio_pin_configure_dt(&ledg, GPIO_OUTPUT_ACTIVE);
    if (retg < 0) {
        printk("Error %d: failed to configure LED pin\n", retg);
        return;
    }
    retr = gpio_pin_configure_dt(&ledr, GPIO_OUTPUT_ACTIVE);
    if (retr < 0) {
        printk("Error %d: failed to configure LED pin\n", retr);
        return;
    }

    //LED verde a cada 1s, LED Vermelho a cada 350ms
    uint8_t counter = 0;
    while (1) {
        
        if (counter % 7 == 0)
        {
            gpio_pin_set_dt(&ledr, 1);
        }
        if (counter % 20 == 0)
        {
            gpio_pin_set_dt(&ledg, 1);
        }
        k_msleep(10);

        gpio_pin_set_dt(&ledg, 0);
        gpio_pin_set_dt(&ledr, 0);


        if (counter == 99)
        {
            counter =0;
        }
        else
        {
            counter++;
        }

        k_msleep(40);
    }
}