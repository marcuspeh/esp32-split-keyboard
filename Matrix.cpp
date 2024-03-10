#include "BleConnectionManager.h"
#include "Matrix.h"

void Matrix::begin() {
    currentLayer = Layer::layer1;
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

void Matrix::scanMatrix(BleKeyboard& bleKeyboard, Layer layer) {
    if (currentLayer != layer) {
        bleKeyboard.releaseAll();
        isPressed.reset();
        currentLayer = layer;
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
                pressKey(bleKeyboard, layer, i, j, bitsetIndex);
            } else if (val == LOW && isPressed[bitsetIndex]) {
                releaseKey(bleKeyboard, layer, i, j, bitsetIndex);
            }
        }
        digitalWrite(cols[i], LOW);
    }
}


void Matrix::pressKey(BleKeyboard& bleKeyboard, Layer layer, int row, int col, int bitsetIndex) {
    isPressed[bitsetIndex] = true;

    // Devices switching
    if (layer == Layer::layer2) {
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

void Matrix::releaseKey(BleKeyboard& bleKeyboard, Layer layer, int row, int col, int bitsetIndex) {
    isPressed[bitsetIndex] = false;

    // Devices switching
    if (layer == Layer::layer2) {
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
        scanMatrix(bleKeyboard, Layer::layer2);
        return;
    }
    scanMatrix(bleKeyboard, Layer::layer1);
}


int Matrix::getBitsetIndex(int row, int col) {
    return row * NUM_COLS + col;
}