#include <stdint.h>

#include <zephyr/devicetree.h>
#include <zephyr/devicetree/fixed-partitions.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

static const uint32_t addr_app1 = DT_FIXED_PARTITION_ADDR(DT_NODELABEL(app1));
static const uint32_t addr_app2 = DT_FIXED_PARTITION_ADDR(DT_NODELABEL(app2));

static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

/*
 * This is where magic happens. No I'm kidding it's just a disguised longjmp.
 */
static void
fly(uint32_t app)
{
    uint32_t msp, addr;
    void (*entry)(void);

    /* I don't know what it means, but it works. */
    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL = 0;

    /* Disable all interrupt and that stuff. */
    __set_PRIMASK(1);
    __disable_irq();

    /* Update stack pointer and vector table address. */
    SCB->VTOR = app;

    msp = *(__IO uint32_t *)app;
    __set_MSP(msp);

    /* Function address + pointer size. */
    addr = *(__IO uint32_t *)(app + 4);

    /* Jump to it. */
    entry = (void *)addr;
    printk("booting application at 0x%08x\n", app);
    entry();
}

int
main(void)
{
    uint32_t app;

    printk("== easyboot starting ==\n");

    gpio_pin_configure_dt(&button, GPIO_INPUT);

    if (gpio_pin_get_dt(&button)) {
        printk("button pressed, using app2\n");
        app = addr_app2;
    } else
        app = addr_app1;

    fly(app);

    return 0;
}