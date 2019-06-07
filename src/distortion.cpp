#include "distortion.h"
#include <cmath>

bool Distortion::AddDistortion(std::vector<double> &buffer, double gain) {
    // Sanity check.
    if (buffer.empty() || gain < 0 || gain > 1) {
        return false;
    }

    // Process the signal. Add desireable clipping to larger amplitudes of the singal.
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
