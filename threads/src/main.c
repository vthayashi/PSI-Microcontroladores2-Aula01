#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define STACK_SIZE 512
#define PRIORITY   5

static const struct gpio_dt_spec led_a = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec led_b = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);

static void blink(const struct gpio_dt_spec *led, int period_ms)
{
    if (!gpio_is_ready_dt(led)) {
        return;
    }
    if (gpio_pin_configure_dt(led, GPIO_OUTPUT_INACTIVE) < 0) {
        return;
    }
    while (1) {
        gpio_pin_toggle_dt(led);
        k_msleep(period_ms);
    }
}

static void thread_led_a(void *p1, void *p2, void *p3)
{
    blink(&led_a, 1000);
}

static void thread_led_b(void *p1, void *p2, void *p3)
{
    blink(&led_b, 350); 
}

K_THREAD_DEFINE(tid_a, STACK_SIZE, thread_led_a, NULL, NULL, NULL, PRIORITY, 0, 0);
K_THREAD_DEFINE(tid_b, STACK_SIZE, thread_led_b, NULL, NULL, NULL, PRIORITY, 0, 0);

int main(void)
{
    return 0;
}