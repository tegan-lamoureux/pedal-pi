#include "distortion.h"
#include <cmath>

bool Distortion::AddDistortion(std::vector<double> &buffer, double gain) {
    if (buffer.empty()) {
        return false;
    }

    for (auto sample = buffer.begin(); sample != buffer.end(); sample++) {
        if (*sample > 0) {
			*sample = gain - exp(-(*sample));
        }
        else {
			*sample = -gain + exp(-(*sample));
        }
    }

    return true;
}
