#include <Arduino.h>
#include <bitset>

#include "BleKeyboard.h"
#include "Constants.h"

class Matrix {
    bitset<NUM_ROWS * NUM_COLS> isPressed;
    short rows[NUMS_ROW] = {
        PIN_ROW_1,
        PIN_ROW_2,
        PIN_ROW_3,
        PIN_ROW_4,
        PIN_ROW_5,
    }
    short cols[NUM_COLS] = {
        PIN_COL_1,
        PIN_COL_2,
        PIN_COL_3,
        PIN_COL_4,
        PIN_COL_5,
        PIN_COL_6,
        PIN_COL_7,
        PIN_COL_8,
        PIN_COL_9,
    }
    int layer[NUM_ROWS][NUM_COLS] = {
        {
            KEY_F1, KEY_F2 ,KEY_ESC, '1', '2', '3', '4', '5', '6',
        },
        {
            KEY_F3, KEY_F4, KEY_TAB, 'q', 'w', 'e', 'r', 't', ' ',
        },
        {
            KEY_F5, KEY_F6, KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g', ' ',
        },
        {
            KEY_F7, KEY_K8, KEY_LEFT_SHIFT, 'z', 'x', 'c', 'v', 'b', ' ',
        },
        {
            KEY_F9, KEY_F10, KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, KEY_HOME, ' ', ' ', ' ',
        },
    }

    int getBitsetIndex(int row, int col);
public:
    void begin();
    void keyScan(BleKeyboard& bleKeyboard);
}