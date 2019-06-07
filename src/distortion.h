#ifndef DISTORTION_H
#define DISTORTION_H

#include <vector>

/**
 * @brief The Distortion class implements an overdriven, clipping effect.
 * This was heavily influenced by the discussion at:
 * https://dsp.stackexchange.com/questions/13142/digital-distortion-effect-algorithm/
 * particularly, the following response: https://dsp.stackexchange.com/a/28962
 */
class Distortion
{
public:
    /**
     * @brief A filter to add (ideally, desireable) distortion to a signal.
     * @param buffer Samples to process.
     * @param gain Magnitude of the distortion.
     * @returns true when successfully processed, or false when invalid parameters are passed.
     */
	static bool AddDistortion(std::vector<double>& buffer, double gain);

private:
    Distortion() = delete;
};

#endif // DISTORTION_H
