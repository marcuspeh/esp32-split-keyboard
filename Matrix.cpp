#include <Arduino.h>

#include "BleConnectionManager.h"
#include "Matrix.h"


void Matrix::begin() {
    layer = Layer::layer1;
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

void Matrix::scanMatrix() {
    for (int i = 0; i < NUM_ROWS; i++) {
        digitalWrite(rows[i], HIGH);
        for (int j = 0; j < NUM_COLS; j++) {
            if (i == LAYER_KEY_ROW && j == LAYER_KEY_COL) {
                continue;
            }

            int val = digitalRead(cols[j]);
            int bitsetIndex = getBitsetIndex(i, j);
            if (val == HIGH && !isPressed[bitsetIndex]) {
                pressKey(i, j, bitsetIndex);
            } else if (val == LOW && isPressed[bitsetIndex]) {
                releaseKey(i, j, bitsetIndex);
            }
        }
        digitalWrite(cols[i], LOW);
    }
}


void Matrix::pressKey(int row, int col, int bitsetIndex) {
    isPressed[bitsetIndex] = true;

    // Devices switching
    if (layer == Layer::layer2) {
        switch (layerKeys[layer][row][col]) {
            case 0:
            case 1:
            case 2:
                bleConnectionManager->changeID(layerKeys[layer][row][col]);
                return;
            default:
                break;
        }
    }

    bleKeyboard->press(layerKeys[layer][row][col]);
}

void Matrix::releaseKey(int row, int col, int bitsetIndex) {
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

    bleKeyboard->release(layerKeys[layer][row][col]);
}

void Matrix::keyScan() {
    setLayer(isLayerKeyPressed() ? Layer::layer2 : Layer::layer1);
    scanMatrix();
}

int Matrix::getBitsetIndex(int row, int col) {
    return row * NUM_COLS + col;
}

void Matrix::setBleConnectionManager(BleConnectionManager* bleConnectionManager) {
    this->bleConnectionManager = bleConnectionManager;
}

void Matrix::setLayer(Layer layer) {
    if (layer == this->layer) {
        return;
    }

    bleKeyboard->releaseAll();
    isPressed.reset();
    this->layer = layer;
}

void Matrix::setBleKeyboard(BleKeyboard* bleKeyboard) {
  this->bleKeyboard = bleKeyboard;
}