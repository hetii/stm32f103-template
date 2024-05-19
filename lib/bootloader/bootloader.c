#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/pwr.h>
#include <libopencm3/stm32/f1/bkp.h>
#include <libopencm3/cm3/scb.h>
#include "bootloader.h"

// USB pins from socket are also exposed on:
// A11 D-
// A12 D+

void jump_into_bootloader(void){
  // Backup interface clock enable & power interface clock enable.
  rcc_peripheral_enable_clock(&RCC_APB1ENR, RCC_APB1ENR_BKPEN | RCC_APB1ENR_PWREN); // RCC->APB1ENR |= RCC_APB1ENR_BKPEN | RCC_APB1ENR_PWREN;
  pwr_disable_backup_domain_write_protect(); // PWR_CR |= PWR_CR_DBP; or PWR->CR |= (1<<8);
  BKP_DR1 = 0x1234;   // BKP->DR1 = 0x1234;
  BKP_DR2 = 0x8765;   // BKP->DR2 = 0x8765;
  scb_reset_system(); // SCB->AIRCR = 0x05FA0004;
}

