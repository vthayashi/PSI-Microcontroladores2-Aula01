#include <kernel.h>
#include <drivers/gpio.h>


#define GREEN_LED_NODE DT_ALIAS(led0)
#define BLUE_LED_NODE  DT_ALIAS(led1)
#define RED_LED_NODE   DT_ALIAS(led2)

#if !DT_NODE_HAS_STATUS(GREEN_LED_NODE, okay)
#error "led0 alias is not defined"
#endif

#if !DT_NODE_HAS_STATUS(BLUE_LED_NODE, okay)
#error "led1 alias is not defined"
#endif

#if !DT_NODE_HAS_STATUS(RED_LED_NODE, okay)
#error "led2 alias is not defined"
#endif

static const struct gpio_dt_spec green_led =
    GPIO_DT_SPEC_GET(GREEN_LED_NODE, gpios);
static const struct gpio_dt_spec blue_led =
    GPIO_DT_SPEC_GET(BLUE_LED_NODE, gpios);
static const struct gpio_dt_spec red_led =
    GPIO_DT_SPEC_GET(RED_LED_NODE, gpios);

static int configure_led(const struct gpio_dt_spec *led, const char *name)
{

    int ret = gpio_pin_configure_dt(led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        printk("Falha ao configurar LED %s: %d\n", name, ret);
    }

    return ret;
}

void main(void)
{
    int ret = configure_led(&green_led, "verde");
    if (ret < 0) {
        return;
    }

    ret = configure_led(&blue_led, "azul");
    if (ret < 0) {
        return;
    }

    ret = configure_led(&red_led, "vermelho");
    if (ret < 0) {
        return;
    }

    gpio_pin_set_dt(&red_led, 0);
    gpio_pin_set_dt(&green_led, 0);
    gpio_pin_set_dt(&blue_led, 0);

    while (1) {
        gpio_pin_set_dt(&red_led, 1);
        k_msleep(100);
        gpio_pin_set_dt(&red_led, 0);
        k_msleep(1000);
        gpio_pin_set_dt(&red_led, 1);
        k_msleep(100);
        gpio_pin_set_dt(&red_led, 0);
        k_msleep(1000);
        gpio_pin_set_dt(&red_led, 1);
        k_msleep(100);
        gpio_pin_set_dt(&red_led, 0);
        k_msleep(1000);
        
        gpio_pin_set_dt(&green_led, 1);
        k_msleep(100);
        gpio_pin_set_dt(&green_led, 0);
        k_msleep(500);
        gpio_pin_set_dt(&green_led, 1);
        k_msleep(100);
        gpio_pin_set_dt(&green_led, 0);
        k_msleep(500);
        gpio_pin_set_dt(&green_led, 1);
        k_msleep(100);
        gpio_pin_set_dt(&green_led, 0);
        k_msleep(1000);
    }
}
