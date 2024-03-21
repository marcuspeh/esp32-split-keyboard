#pragma once

#include "Matrix.h"

class MainMatrix : public Matrix {
    void pressKey(int row, int col, int bitsetIndex);
    void releaseKey(int row, int col, int bitsetIndex);
};
