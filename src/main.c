#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "bootloader/bootloader.h"
// #include "api/api.h"
// #include "api/api-asm.h"

static volatile uint32_t _millis = 0;
void delay(uint32_t duration);

static void systick_setup(void) {
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
  STK_CVR = 0;
  systick_set_reload(rcc_ahb_frequency / 1000 - 1);
  systick_interrupt_enable();
  systick_counter_enable();
}

void sys_tick_handler(void) {
  _millis++;
}

void delay(uint32_t duration) {
  const uint32_t until = _millis + duration;
  while (_millis < until);
}

static void clock_setup(void) {
  rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_64MHZ]);
  rcc_periph_clock_enable(RCC_GPIOC);
  rcc_periph_clock_enable(RCC_AFIO);
}

int main(void) {
  clock_setup();
  systick_setup();
  gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

  // Blink 10 times and back to bootloader.
  int i=0;
  while (true) {
    gpio_set(GPIOC, GPIO13);
    delay(1000);

    gpio_clear(GPIOC, GPIO13);
    delay(1000);

    if (i++>=10){
      jump_into_bootloader();
    }
  }

  return 0;

  // Below code is just for example from libopencm3-template, as
  // I don't use api part at all.
  //
  // uint32_t rev = 0xaabbccdd;
  // rev = rev_bytes(rev);
  // return my_func(rev);
}
