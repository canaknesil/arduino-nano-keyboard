#ifndef PLATFORM_DEPENDENT_H
#define PLATFORM_DEPENDENT_H

#if defined(__cplusplus)
extern "C"
{
#endif

  #include "keyboard.h"

  extern int row_pins[ROWS];
  extern int col_pins[COLS];
  
  void d_print(char *str, ...);
  void d_delay(unsigned long ms);
  char d_read_pin(int pin);
  void d_write_pin(int pin, char val);

#if defined(__cplusplus)
}
#endif

#endif
