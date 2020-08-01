from pynput.keyboard import Key

# Keyboard/Keypad Page (0x07)
hid_to_key_list = [
    None, # KC_NO = 0x00
    None, # KC_ROLL_OVER
    None, # KC_POST_FAIL
    None, # KC_UNDEFINED
    "a", # KC_A
    "b", # KC_B
    "c", # KC_C
    "d", # KC_D
    "e", # KC_E
    "f", # KC_F
    "g", # KC_G
    "h", # KC_H
    "i", # KC_I
    "j", # KC_J
    "k", # KC_K
    "l", # KC_L
    "m", # KC_M  // 0x10
    "n", # KC_N
    "o", # KC_O
    "p", # KC_P
    "q", # KC_Q
    "r", # KC_R
    "s", # KC_S
    "t", # KC_T
    "u", # KC_U
    "v", # KC_V
    "w", # KC_W
    "x", # KC_X
    "y", # KC_Y
    "z", # KC_Z
    "1", # KC_1
    "2", # KC_2
    "3", # KC_3  // 0x20
    "4", # KC_4
    "5", # KC_5
    "6", # KC_6
    "7", # KC_7
    "8", # KC_8
    "9", # KC_9
    "0", # KC_0
    Key.enter, # KC_ENTER
    Key.esc, # KC_ESCAPE
    Key.backspace, # KC_BSPACE
    Key.tab, # KC_TAB
    Key.space, # KC_SPACE
    "-", # KC_MINUS
    "=", # KC_EQUAL
    "[", # KC_LBRACKET
    "]", # KC_RBRACKET  // 0x30
    "\\", # KC_BSLASH
    None, # KC_NONUS_HASH
    ";", # KC_SCOLON
    "'", # KC_QUOTE
    "`", # KC_GRAVE
    ",", # KC_COMMA
    ".", # KC_DOT
    "/", # KC_SLASH
    Key.caps_lock, # KC_CAPSLOCK
    Key.f1, # KC_F1
    Key.f2, # KC_F2
    Key.f3, # KC_F3
    Key.f4, # KC_F4
    Key.f5, # KC_F5
    Key.f6, # KC_F6
    Key.f7, # KC_F7  // 0x40
    Key.f8, # KC_F8
    Key.f9, # KC_F9
    Key.f10, # KC_F10
    Key.f11, # KC_F11
    Key.f12, # KC_F12
    Key.print_screen if hasattr(Key, 'print_screen') else None, # KC_PSCREEN
    Key.scroll_lock  if hasattr(Key, 'scroll_lock') else None, # KC_SCROLLLOCK
    Key.pause if hasattr(Key, 'pause') else None, # KC_PAUSE
    Key.insert if hasattr(Key, 'insert') else None, # KC_INSERT
    Key.home, # KC_HOME
    Key.page_up, # KC_PGUP
    Key.delete, # KC_DELETE
    Key.end, # KC_END
    Key.page_down, # KC_PGDOWN
    Key.right, # KC_RIGHT
    Key.left, # KC_LEFT  // 0x50
    Key.down, # KC_DOWN
    Key.up, # KC_UP
    Key.num_lock if hasattr(Key, 'num_lock') else None, # KC_NUMLOCK
    None, # KC_KP_SLASH
    None, # KC_KP_ASTERISK
    None, # KC_KP_MINUS
    None, # KC_KP_PLUS
    None, # KC_KP_ENTER
    None, # KC_KP_1
    None, # KC_KP_2
    None, # KC_KP_3
    None, # KC_KP_4
    None, # KC_KP_5
    None, # KC_KP_6
    None, # KC_KP_7
    None, # KC_KP_8  // 0x60
    None, # KC_KP_9
    None, # KC_KP_0
    None, # KC_KP_DOT
    None, # KC_NONUS_BSLASH
    None, # KC_APPLICATION
    None, # KC_POWER
    None, # KC_KP_EQUAL
    Key.f13, # KC_F13
    Key.f14, # KC_F14
    Key.f15, # KC_F15
    Key.f16, # KC_F16
    Key.f17, # KC_F17
    Key.f18, # KC_F18
    Key.f19, # KC_F19
    Key.f20, # KC_F20
    Key.f21 if hasattr(Key, 'f21') else None, # KC_F21  // 0x70
    Key.f22 if hasattr(Key, 'f22') else None, # KC_F22
    Key.f23 if hasattr(Key, 'f23') else None, # KC_F23
    Key.f24 if hasattr(Key, 'f24') else None, # KC_F24
    None, # KC_EXECUTE
    None, # KC_HELP
    None, # KC_MENU
    None, # KC_SELECT
    None, # KC_STOP
    None, # KC_AGAIN
    None, # KC_UNDO
    None, # KC_CUT
    None, # KC_COPY
    None, # KC_PASTE
    None, # KC_FIND
    Key.media_volume_mute, # KC__MUTE (macOS)
    Key.media_volume_up, # KC__VOLUP  // 0x80
    Key.media_volume_down, # KC__VOLDOWN
    None, # KC_LOCKING_CAPS
    None, # KC_LOCKING_NUM
    None, # KC_LOCKING_SCROLL
    None, # KC_KP_COMMA
    None, # KC_KP_EQUAL_AS400
    None, # KC_INT1
    None, # KC_INT2
    None, # KC_INT3
    None, # KC_INT4
    None, # KC_INT5
    None, # KC_INT6
    None, # KC_INT7
    None, # KC_INT8
    None, # KC_INT9
    None, # KC_LANG1  // 0x90
    None, # KC_LANG2
    None, # KC_LANG3
    None, # KC_LANG4
    None, # KC_LANG5
    None, # KC_LANG6
    None, # KC_LANG7
    None, # KC_LANG8
    None, # KC_LANG9
    None, # KC_ALT_ERASE
    None, # KC_SYSREQ
    None, # KC_CANCEL
    None, # KC_CLEAR
    None, # KC_PRIOR
    None, # KC_RETURN
    None, # KC_SEPARATOR
    None, # KC_OUT  // 0xA0
    None, # KC_OPER
    None, # KC_CLEAR_AGAIN
    None, # KC_CRSEL
    None, # KC_EXSEL
]

hid_to_key_modifiers_list = [
    Key.ctrl_l, # KC_LCTRL = 0xE0
    Key.shift_l, # KC_LSHIFT
    Key.alt_l, # KC_LALT
    Key.cmd_l, # KC_LGUI
    Key.ctrl_r, # KC_RCTRL
    Key.shift_r, # KC_RSHIFT
    Key.alt_r, # KC_RALT
    Key.cmd_r, # KC_RGUI 0xE7
]

def hid_to_key(keycode):
    if keycode >= 0 and keycode <= 0xa4:
        return hid_to_key_list[keycode]
    elif keycode >= 0xe0 and keycode <= 0xe7:
        return hid_to_key_modifiers_list[keycode - 0xe0]
    else:
        return None
