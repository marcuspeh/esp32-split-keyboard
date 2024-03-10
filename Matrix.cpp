#include "BleConnectionManager.h"
#include "Matrix.h"

void Matrix::begin() {
    for (short row: rows) {
        pinMode(row, OUTPUT);
    }
    for (short col: cols) {
        pinMode(col, INPUT);
    }
}

bool Matrix::isLayerKeyPressed() {
    digitalWrite(LAYER_KEY_ROW, HIGH);
    int val = digitalRead(LAYER_KEY_COL);
    digitalWrite(LAYER_KEY_ROW, HIGH);
    return val == HIGH;
}

void Matrix::scanLayer2(BleKeyboard& bleKeyboard) {
    if (!isLayerKeyPressedPreviously) {
        bleKeyboard.releaseAll();
        isPressed.reset();
        isLayerKeyPressedPreviously = true;
    }

    scanMatrix(bleKeyboard, 1);
}

void Matrix::scanLayer1(BleKeyboard& bleKeyboard) {
    if (isLayerKeyPressedPreviously) {
        bleKeyboard.releaseAll();
        isPressed.reset();
        isLayerKeyPressedPreviously = false;
    }
    
    scanMatrix(bleKeyboard, 0);
}


void Matrix::scanMatrix(BleKeyboard& bleKeyboard, int layer) {
    for (int i = 0; i < NUM_ROWS; i++) {
        digitalWrite(rows[i], HIGH);
        for (int j = 0; j < NUM_COLS; j++) {
            if (i == LAYER_KEY_ROW && j == LAYER_KEY_COL) {
                continue;
            }

            int val = digitalRead(cols[j]);
            int bitsetIndex = getBitsetIndex(i, j);
            if (val == HIGH && !isPressed[bitsetIndex]) {
                pressKey(bleKeyboard, layer, i, j, bitsetIndex);
            } else if (val == LOW && isPressed[bitsetIndex]) {
                releaseKey(bleKeyboard, layer, i, j, bitsetIndex);
            }
        }
        digitalWrite(cols[i], LOW);
    }
}


void Matrix::pressKey(BleKeyboard& bleKeyboard, int layer, int row, int col, int bitsetIndex) {
    isPressed[bitsetIndex] = true;

    // Devices switching
    if (layer == 2) {
        switch (layerKeys[layer][row][col]) {
            case 0:
            case 1:
            case 2:
                BleConnectionManager::changeID(layerKeys[layer][row][col]);
                return;
            default:
                break;
        }
    }

    bleKeyboard.press(layerKeys[layer][row][col]);
}

void Matrix::releaseKey(BleKeyboard& bleKeyboard, int layer, int row, int col, int bitsetIndex) {
    isPressed[bitsetIndex] = false;

    // Devices switching
    if (layer == 2) {
        switch (layerKeys[layer][row][col]) {
            case 0:
            case 1:
            case 2:
                return;
            default:
                break;
        }
    }

    bleKeyboard.release(layerKeys[layer][row][col]);
}

void Matrix::keyScan(BleKeyboard& bleKeyboard) {
    if (isLayerKeyPressed()) {
        scanLayer2(bleKeyboard);
        return;
    }
    scanLayer1(bleKeyboard);
}


int Matrix::getBitsetIndex(int row, int col) {
    return row * NUM_COLS + col;
}