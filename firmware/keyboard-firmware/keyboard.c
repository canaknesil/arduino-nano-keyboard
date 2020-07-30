#include "keyboard.h"
#include "platform_dependent.h"

char matrix[ROWS][COLS] = {{0}};
char matrix_change[ROWS][COLS] = {{0}};

void scan_matrix()
{
  for (int i=0; i<COLS; i++) {
    d_write_pin(col_pins[i], 1);
    for (int j=0; j<ROWS; j++) {
      char val = d_read_pin(row_pins[j]);
      matrix_change[j][i] = val - matrix[j][i];
      matrix[j][i] = val;
    }
    d_write_pin(col_pins[i], 0);
  }
}

void report_change()
{
  for (int i=0; i<ROWS; i++)
    for (int j=0; j<COLS; j++) {
      char change = matrix_change[i][j];
      if (change)
	d_print("Change (%d,%d) %d", i, j, change);
    }
}

void keyboard_loop()
{
  scan_matrix();
  report_change();
  d_delay(100);
}
