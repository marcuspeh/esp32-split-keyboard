#include "Matrix.h"

void Matrix::begin() {
    for (short row: rows) {
        pinMode(row, OUTPUT);
    }
    for (short col: cols) {
        pinMode(col, INPUT);
    }
}

void Matrix::keyScan(BleKeyboard& bleKeyboard) {
    for (int i = 0; i < NUM_ROWS; i++) {
        digitalWrite(rows[i], HIGH);
        for (int j = 0; j < NUM_COLS; j++) {
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
    bleKeyboard.release();
}


int Matrix::getBitsetIndex(int row, int col) {
    return row * NUM_COLS + col;
}