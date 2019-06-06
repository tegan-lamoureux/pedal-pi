#include "echo.h"
#include <cmath>
#include <queue>

using namespace std;

// TODO: There's a lot I can refactor out of these into a common function. The only real
// FIR vs IIR difference is the input to the delay line being the modified sample or the
// original sample.

bool Echo::AddEcho_FIR(std::vector<double>& buffer, double gain, double time, double sample_rate) {
	const double buffer_length_seconds = static_cast<double>(buffer.size()) / sample_rate;
	const int delay_time_in_samples = static_cast<int>(time * sample_rate);

	// TODO: Check this and the other ones as well for better error handling.
	// also make sure all casing is consistent.
	if (buffer.empty() || gain > 1.0 || time < buffer_length_seconds) {
		return false;
	}

	// Initialize delay tracking structure. Holds input data offset by delay time and is
	// used to modify input signal. Init to zero because we don't want to affect the start
	// of the sample before first delay kicks in.
	queue<double> delay_line;
	for (int i = 0; i < delay_time_in_samples; i++) {
		delay_line.push(0);
	}

	// For every sample:
	// 1. Add sample from offset delay line.
	// 2. Update back offset delay line with current sample.
	for (auto sample = buffer.begin(); sample != buffer.end(); sample++) {
		auto cached_sample = *sample;
		*sample = *sample + (gain * delay_line.front());
		delay_line.push(cached_sample);
		delay_line.pop();
	}

	return true;
}

bool Echo::AddEcho_IIR(std::vector<double>& buffer, double gain, double time, double sample_rate) {
	const double buffer_length_seconds = static_cast<double>(buffer.size()) / sample_rate;
	const int delay_time_in_samples = static_cast<int>(time * sample_rate);

	// TODO: Check this and the other ones as well for better error handling.
	// also make sure all casing is consistent.
	if (buffer.empty() || gain > 1.0 || time < buffer_length_seconds) {
		return false;
	}

	// Initialize delay tracking structure. Holds input data offset by delay time and is
	// used to modify input signal. Init to zero because we don't want to affect the start
	// of the sample before first delay kicks in.
	queue<double> delay_line;
	for (int i = 0; i < delay_time_in_samples; i++) {
		delay_line.push(0);
	}

	// For every sample:
	// 1. Add sample from offset delay line.
	// 2. Update back offset delay line with current modified sample.
	for (auto sample = buffer.begin(); sample != buffer.end(); sample++) {
		*sample = *sample + (gain * delay_line.front());
		delay_line.push(*sample);
		delay_line.pop();
	}

	return true;}

//bool Echo::AddEcho_Universal(std::vector<double>& buffer, double magnitude, double feedback, double time, double sample_rate) {

//	return true;
//}

