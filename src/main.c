#include <stdint.h>

#define GPIO_BASE 0x40014000
#define FUNCSEL_MASK 0x1F
#define TIME_BASE 0x40054000
#define CPUID 0x000

static uint32_t get_core(){
  volatile uint32_t* cpu_id = (uint32_t*)CPUID;
  volatile uint32_t core = *cpu_id;  

  return core;
}

volatile static uint64_t time_read(void){
  volatile uint32_t* timelw = (uint32_t*)TIME_BASE;
  volatile uint32_t* timehr = timelw + 1;

  uint32_t low,high;

  do{
    low = *timelw;
    high = *timehr;
  }while(low != *timelw);

  uint64_t time = (uint64_t)high << 32 | low;

  return time;
} 

static void delay(uint64_t ms){
  uint64_t start_time = time_read();
  while(start_time < start_time+ms){};
}

static void pin_config(uint8_t pin){
  uint32_t* pin_address = (uint32_t*)GPIO_BASE + pin;
  *pin_address &= ~FUNCSEL_MASK; 
  *pin_address |= 0x05;
}

static inline void core1_entry(void){

}

static inline void core0_entry(void){
  
}
