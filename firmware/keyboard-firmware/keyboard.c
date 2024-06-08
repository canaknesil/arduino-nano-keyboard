#include "keyboard.h"
#include "platform_dependent.h"
#include "keycode.h"


/* 
 *
 * KEYMAPS
 *
 */

#define XXXXXXX KC_NO
#define _______ KC_TRNS
#define LAYERS 3

KeyCode keymaps[LAYERS][ROWS][COLS] =
  {
   { // Default kayer
    {KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_FN3 },
    {KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL },
    {KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSLS},
    {KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, XXXXXXX},
    {KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT},
    {KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, KC_SPC , XXXXXXX, KC_ENT , KC_FN0 , KC_FN1 , KC_FN2 , KC_RALT, KC_RCTL}
   },
   { // Layer FN0
    {_______, KC_F11 , KC_F12 , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL , _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, KC_UP  , _______, KC_QUOT, _______},
    {_______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
   },
   { // Layer FN1
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, _______, _______, _______}
   }
  };

// Dependent information about keymaps
// These information should be changed if number of position of Fn keys in keymaps is changed !!!

#define NR_OF_FN_KEYS 4
// From fn0, fn1, ...
char fn_key_indices[NR_OF_FN_KEYS][2] = {{5, 7}, {5, 8}, {5, 9}, {0, 11}};

char layer_status[LAYERS] = {1, 0, 0}; // When no key is pressed, only default layer is active.


/*
 *
 * KEYBOARD MATRIX
 *
 */

char matrix[ROWS][COLS] = {{0}};
char matrix_change[ROWS][COLS] = {{0}};


/*
 *
 * UPDATE LAYER STATUS
 *
 */

// Read fn keys from matrix.
void get_fn_keys(char fn_keys[NR_OF_FN_KEYS])
{
  for (int i=0; i<NR_OF_FN_KEYS; i++)
    fn_keys[i] = matrix[fn_key_indices[i][0]][fn_key_indices[i][1]];
}

// Fn keys update layer status. 
void update_layer_status()
{
  char fn_keys[NR_OF_FN_KEYS];

  get_fn_keys(fn_keys);

  // Layer 0 (default layer) is always active.
  layer_status[1] = fn_keys[0];
  layer_status[2] = fn_keys[1];
}


/*
 *
 * GET KEYCODE FROM MATRIX
 *
 */

KeyCode get_key_code(int i, int j)
{
  for (int layer = LAYERS - 1; layer>=0; layer--) {
    if (layer_status[layer]) {
      if (keymaps[layer][i][j] == KC_TRNS)
	continue;
      else
	return keymaps[layer][i][j];
    } else
      continue;
  }

  // Since there are no KC_TRNS in default layer, execution should not come here.
  d_print("Error in get_key_code.");
  return KC_NO;
}


/*
 *
 * MATRIX SCAN
 *
 */

void scan_matrix()
{
	// Problem with scanning: When a switch is pressed, and after its
	// column is made HIGH, the corresponging row may stay HIGH during
	// the testing of the next column, resulting in a false registery as
	// if the switch corresponding to the next column and same row is
	// pressed.

	// Putting delay after writing to columns results in a noticibly
	// lagging operation.

	// Majority voting with different column orders, combined with delay
	// after writing to column.

	// For now column orders are hard-coded. They should be dynamically
	// generated. Consequtive pairs shouldn't repeat to reduce common
	// mode fault.
	char col_order[3][COLS] = {
		{0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10, 11}, // diff = 1
		{0 , 5 , 10, 3 , 8 , 1 , 6 , 11, 4 , 9 , 2 , 7 }, // diff = 5
		{0 , 7 , 2 , 9 , 4 , 1 , 6 , 1 , 8 , 3 , 10, 5 }  // diff = 7
	};

  char read_matrix[3][ROWS][COLS];

	// Read matrix multiple times
	for (int n=0; n<3; n++) {
		for (int i=0; i<COLS; i++) {
			int col_idx = col_order[n][i];
			d_write_pin(col_pins[col_idx], 1);
			d_delay(1);
			for (int j=0; j<ROWS; j++) {
				char val = d_read_pin(row_pins[j]);
				read_matrix[n][j][col_idx] = val;
			}
			d_write_pin(col_pins[col_idx], 0);
		}
	}

	for (int i=0; i<COLS; i++) {
		for (int j=0; j<ROWS; j++) {
			// majority voting
			int val = 0;
			for (int n=0; n<3; n++)
				val += read_matrix[n][j][i];
			if (val <= 1) val = 0;
			if (val >= 2) val = 1;

			// update state
			matrix_change[j][i] = val - matrix[j][i];
			matrix[j][i] = val;
		}
	}
	
  update_layer_status();
}

void report_change()
{
  for (int i=0; i<ROWS; i++) {
    for (int j=0; j<COLS; j++) {
      char change = matrix_change[i][j];
      if (change) {
				KeyCode key = get_key_code(i, j);
				if (!IS_FN(key)) {
					if (change == 1) {
						//d_print("Pressed  %d at (%d,%d)", (int) key, i, j);
						d_send_keycode(key, 1);
					} else if (change == -1) {
						//d_print("Released %d at (%d,%d)", (int) key, i, j);
						d_send_keycode(key, 0);
					}
				}
      }
    }
	}
}


/*
 *
 * KEYBAORD LOOP
 *
 */

void keyboard_loop()
{
  scan_matrix();
  report_change();
  //d_delay(10);
}
