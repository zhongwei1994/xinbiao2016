#include "MPC5604B.h"

#include "includes.h"

int main(void) {
  volatile int i = 0;
  initALL();
  


  /* Loop forever */
  for (;;) {
    i++;
    D0 = 0;
    delay_ms(1000);
    D0 = 1;
  }
}



