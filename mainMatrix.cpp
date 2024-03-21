#include "MainMatrix.h"

void MainMatrix::pressKey(int row, int col, int bitsetIndex) {
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

void MainMatrix::releaseKey(int row, int col, int bitsetIndex) {
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