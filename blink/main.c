#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(run_led), gpios);

int
main(void)
{
    printk("== blink startup ==\n");
    gpio_pin_configure_dt(&led, GPIO_OUTPUT);

    for (;;) {
        gpio_pin_toggle_dt(&led);
        k_msleep(1000);
    }
}