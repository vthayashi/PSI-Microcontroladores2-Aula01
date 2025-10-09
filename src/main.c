#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define STACK_SIZE 1024
#define PRIORITY 5

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);


void thread_pisca_led0(void *p1, void *p2, void *p3) {
    int ret;

    if (!gpio_is_ready_dt(&led0)) {
        printk("Erro: dispositivo led0 não está pronto\n");
        return;
    }
    ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        printk("Erro: falha ao configurar led0\n");
        return;
    }

    printk("Iniciando blink no pino %d\n", led0.pin);
	
    while (1) {
        gpio_pin_toggle_dt(&led0); 
        k_msleep(50); 
		gpio_pin_toggle_dt(&led0);
		k_msleep(300);          
    }
}


void thread_pisca_led1(void *p1, void *p2, void *p3) {
    int ret;

    if (!gpio_is_ready_dt(&led1)) {
        printk("Erro: dispositivo led1 não está pronto\n");
        return;
    }
    ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        printk("Erro: falha ao configurar led1\n");
        return;
    }

    printk("Iniciando blink no pino %d\n", led1.pin);

    while (1) {
        gpio_pin_toggle_dt(&led1);
        k_msleep(50); 
		gpio_pin_toggle_dt(&led1);
		k_msleep(950); 
    }
}

K_THREAD_DEFINE(tid_led0, STACK_SIZE, thread_pisca_led0, NULL, NULL, NULL,
                PRIORITY, 0, 0);

K_THREAD_DEFINE(tid_led1, STACK_SIZE, thread_pisca_led1, NULL, NULL, NULL,
                PRIORITY, 0, 0);


void main(void)
{
    printk("Threads runnin' baby.\n");
}