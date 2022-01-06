#include <iostream>
#include <cmath>
#define FFT_SIZE 512

uint32_t i = 0, freq = 1;
float sin_val;
float sine_array[512];

int main() {
    std::cout << "Hello, World!" << std::endl;

    for (int i; i < FFT_SIZE; i++)
    {
        sine_array[i] += (float)0.5 * (float)sin((float)2 * (float)3.14159265359 * (float)1 * (float)freq * (float)i / (float)(FFT_SIZE / 2));
    }

}
