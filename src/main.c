#include <stdint.h>
//poop
//Offset GPIO_BASE by 0x004 from base to get to the control register. 0x000 is the status register.
/* The controller has 8 bytes allocated to each pin. 4 bytes is read only that allows you to read pin status with the other 4 bytes having RW access and allowing you to
control the register.*/
#define GPIO_BASE 0x40014000
#define FUNCSEL_MASK 0x1F
#define TIME_BASE 0x40054000
#define CPUID 0x000

uint32_t get_core(){
  volatile uint32_t* cpu_id = (uint32_t*)CPUID;
  volatile uint32_t core = *cpu_id;  

  return core;
}

uint64_t time_read(void){
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

void delay(uint64_t ms){
  uint64_t start_time = time_read();
  while(start_time < start_time+ms){};
}

void pin_config(uint8_t pin){
  uint32_t* pin_address = (uint32_t*)GPIO_BASE + (uint32_t)pin;
  *pin_address &= ~FUNCSEL_MASK; 
  *pin_address |= 0x05;
}

void pin_set_high(void){
  
}

void pin_set_low(void){
  
}

int main(void){
  pin_config(1);
  
  for(;;){
    pin_set_high();
    delay(1000);
    pin_set_low();
    delay(1000);
  }
  
  return 0;
}
