#include "distortion.h"
#include <cmath>

bool Distortion::AddDistortion(std::vector<double> &buffer, double magnitude) {
    if (buffer.empty()) {
        return false;
    }

    for (auto sample = buffer.begin(); sample != buffer.end(); sample++) {
        if (*sample > 0) {
            *sample = magnitude - exp(-(*sample));
        }
        else {
            *sample = -magnitude + exp(-(*sample));
        }
    }

    return true;
}
