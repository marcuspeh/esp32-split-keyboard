#include "Matrix.h"

void Matrix::begin() {
    for (short row: rows) {
        pinMode(row, OUTPUT);
    }
    for (short col: cols) {
        pinMode(col, INPUT);
    }
}

void Matrix::isLayerKeyPressed() {
    digitalWrite(LAYER_KEY_ROW, HIGH);
    int val = digitalRead(LAYER_KEY_COL);
    digitalWrite(LAYER_KEY_ROW, HIGH);
    return val == HIGH;
}

void Matrix::scanLayer1(BleKeyboard& bleKeyboard) {
    if (!isLayerKeyPressedPreviously) {
        bleKeyboard.realeaseAll();
        isPressed.reset();
        isLayerKeyPressedPreviously = true;
    }

    for (auto layerKey: layerKeys) {
        int row = layerKey[0];
        int col = layerKey[1];
        int code = layerKey[2];

        digitalWrite(row, HIGH);
        int val = digitalRead(col);
        digitalWrite(row, HIGH);
        if (val == HIGH) {
            BleConnectionManager::changeID(code);
        }        
    }
}

void Matrix::scanLayer0(BleKeyboard& bleKeyboard) {
    if (isLayerKeyPressedPreviously) {
        isPressed.reset();
        isLayerKeyPressedPreviously = false;
    }

    for (int i = 0; i < NUM_ROWS; i++) {
        digitalWrite(rows[i], HIGH);
        for (int j = 0; j < NUM_COLS; j++) {
            if (i == LAYER_KEY_ROW && j == LAYER_KEY_COL) {
                continue;
            }
            int val = digitalRead(cols[j]);
            int bitsetIndex = getBitsetIndex(i, j);
            if (val == HIGH && !isPressed[bitsetIndex]) {
                isPressed[bitsetIndex] = true;
                bleKeyboard.press(layer[i][j]);
            }
            if (val == LOW && isPressed[bitsetIndex]) {
                isPressed[bitsetIndex] = false;
                bleKeyboard.release(layer[i][j]);
            }
        }
        digitalWrite(cols[i], LOW);
    }
}

void Matrix::keyScan(BleKeyboard& bleKeyboard) {
    if (isLayerKeyPressed()) {
        scanLayer1();
        return;
    }
    scanLayer0(bleKeyboard);
}


int Matrix::getBitsetIndex(int row, int col) {
    return row * NUM_COLS + col;
}