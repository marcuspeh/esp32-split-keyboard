#include <Arduino.h>

#include "BleKeyboard.h"
#include "Constants.h"
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
            if (val == LOW) {
                continue;
            }
            bleKeyboard.press(layer[i][j]);
        }
        digitalWrite(cols[i], LOW);
    }
    bleKeyboard.release();
}
