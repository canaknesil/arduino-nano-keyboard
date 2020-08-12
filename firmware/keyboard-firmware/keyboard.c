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
    {KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_FN2 , KC_FN3 },
    {KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_DEL , XXXXXXX},
    {KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP},
    {KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT , XXXXXXX, KC_PGDN},
    {KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, XXXXXXX, KC_UP  , XXXXXXX},
    {KC_LCTL, KC_LGUI, KC_LALT, KC_FN0 , KC_SPC , XXXXXXX, KC_SPC , XXXXXXX, KC_FN1 , KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT}
   },
   { // Function keys as media keys, condition: (fn0 OR fn1) XOR (NOT fn2)
    {_______, XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
   },
   { // Condition: fn0 0R fn1
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END },
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
   }
  };

// Dependent information about keymaps
// These information should be changed if number of position of Fn keys in keymaps is changed !!!

#define NR_OF_FN_KEYS 4
// From fn0, fn1, ...
char fn_key_indices[NR_OF_FN_KEYS][2] = {{5, 3}, {5, 8}, {0, 13}, {0, 14}};

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
  layer_status[1] = (fn_keys[0] | fn_keys[1]) ^ (~fn_keys[2]);
  layer_status[2] = fn_keys[0] || fn_keys[1];
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


/*
 *
 * KEYBAORD LOOP
 *
 */

void keyboard_loop()
{
  scan_matrix();
  report_change();
  d_delay(10);
}
