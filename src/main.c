#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

// Tamanho da memória e prioriedade das threads
#define STACK_SIZE 1024
#define PRIORITY 7

// No LED RGB integrado da FRDM-KL25Z:
// led0 = Vermelho (PTB18)
// led1 = Verde (PTB19)
#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)

static const struct gpio_dt_spec led_1000ms = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led_350ms = GPIO_DT_SPEC_GET(LED1_NODE, gpios);

// Thread 1 (Pisca a cada 1 segundo)
void thread_led1() {
    if (!gpio_is_ready_dt(&led_1000ms)) return;
    gpio_pin_configure_dt(&led_1000ms, GPIO_OUTPUT_ACTIVE);

    while(1) {
        gpio_pin_toggle_dt(&led_1000ms);
        k_msleep(1000);
    }
}

// Thread 2 (Pisca a cada 350 ms - Desafio)
void thread_led2() {
    if (!gpio_is_ready_dt(&led_350ms)) return;
    gpio_pin_configure_dt(&led_350ms, GPIO_OUTPUT_ACTIVE);

    while(1) {
        gpio_pin_toggle_dt(&led_350ms);
        k_msleep(350);
    }
}

// Macros do Zephyr para registrar e iniciar as threads automaticamente
K_THREAD_DEFINE(thread1_id, STACK_SIZE, thread_led1, NULL, NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(thread2_id, STACK_SIZE, thread_led2, NULL, NULL, NULL, PRIORITY, 0, 0);