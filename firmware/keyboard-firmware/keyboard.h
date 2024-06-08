#ifndef KEYBOARD_H
#define KEYBOARD_H

#if defined(__cplusplus)
extern "C"
{
#endif

  #define ROWS 6
  #define COLS 12

  // Keycodes in keycode.h are 1 byte. 
  typedef unsigned char KeyCode;
  
  void keyboard_loop();

#if defined(__cplusplus)
}
#endif

#endif
