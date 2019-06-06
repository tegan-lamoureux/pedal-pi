#ifndef DISTORTION_H
#define DISTORTION_H

#include <vector>

// Note that I referenced: https://dsp.stackexchange.com/questions/13142/digital-distortion-effect-algorithm/
// for this implementation.
class Distortion
{
public:
	// FIXME: Add sample rate to this. Or do I not need it?
	static bool AddDistortion(std::vector<double>& buffer, double gain);

private:
    Distortion() = delete;
};

#endif // DISTORTION_H
