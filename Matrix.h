#include <Arduino.h>
#include <bitset>

#include "BleKeyboard.h"
#include "Constants.h"

enum Layer{   
    layer1 = 0,
    layer2 = 1,
};

class Matrix {
    std::bitset<NUM_ROWS * NUM_COLS> isPressed;
    Layer currentLayer;

    // Pins in rows need to be RTC GPIO to wakeup device.
    short rows[NUM_ROWS] = {
        PIN_ROW_1,
        PIN_ROW_2,
        PIN_ROW_3,
        PIN_ROW_4,
        PIN_ROW_5,
    };
    short cols[NUM_COLS] = {
        PIN_COL_1,
        PIN_COL_2,
        PIN_COL_3,
        PIN_COL_4,
        PIN_COL_5,
        PIN_COL_6,
    };

    int layerKeys[NUM_LAYERS][NUM_ROWS][NUM_COLS] = {
        {
            {
                KEY_ESC, '1', '2', '3', '4', '5', 
            },
            {
                KEY_TAB, 'q', 'w', 'e', 'r', 't', 
            },
            {
                KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g',
            },
            {
                KEY_LEFT_SHIFT, 'z', 'x', 'c', 'v', '6',
            },
            {
                KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, ' ', KEY_PAGE_UP, ' ', 
            },
        },
        {
            {
                KEY_ESC, '1', '2', '3', '4', '5', 
            },
            {
                KEY_TAB, 'q', 'w', 'e', 'r', 't', 
            },
            {
                KEY_CAPS_LOCK, 'a', 's', 'd', 'f', 'g',
            },
            {
                KEY_LEFT_SHIFT, 'z', 'x', 'c', 'v', '6',
            },
            {
                KEY_LEFT_CTRL, KEY_LEFT_GUI, KEY_LEFT_ALT, ' ', KEY_PAGE_DOWN, ' ', 
            },
        }
    };


    int getBitsetIndex(int row, int col);
    bool isLayerKeyPressed();
    void scanMatrix(BleKeyboard& bleKeyboard, Layer layer);
    void pressKey(BleKeyboard& bleKeyboard, Layer layer, int row, int col, int bitsetIndex);
    void releaseKey(BleKeyboard& bleKeyboard, Layer layer, int row, int col, int bitsetIndex);
    static void callback();
public:
    void begin();
    void keyScan(BleKeyboard& bleKeyboard);
    void sleep();
    void wakeup();
};
