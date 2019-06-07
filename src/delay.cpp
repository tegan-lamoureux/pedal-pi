#include "delay.h"
#include <cmath>

using namespace std;


bool Delay::AddEcho_FIR(std::vector<double>& buffer, double gain, double time, double sample_rate) {
    const double buffer_length_seconds = static_cast<double>(buffer.size()) / sample_rate;
    const int delay_time_in_samples = static_cast<int>(time * sample_rate);

    // Sanity check.
    if (buffer.empty() || gain > 1.0 || time > buffer_length_seconds) {
        return false;
    }

    // Initialize delay tracking structure. Holds input data offset by delay time and is
    // used to modify input signal.
    queue<double> delay_line = init_delay_buffer(delay_time_in_samples);

    // Process signal. Modify input but keep original unmodified signal
    // in delay line.
    for (auto sample = buffer.begin(); sample != buffer.end(); sample++) {
        auto cached_sample = *sample;
        *sample = *sample + (gain * delay_line.front());
        delay_line.push(cached_sample);
        delay_line.pop();
    }

    return true;
}


bool Delay::AddEcho_IIR(std::vector<double>& buffer, double gain, double time, double sample_rate) {
    const double buffer_length_seconds = static_cast<double>(buffer.size()) / sample_rate;
    const int delay_time_in_samples = static_cast<int>(time * sample_rate);

    // Sanity check.
    if (buffer.empty() || gain > 1.0 || time > buffer_length_seconds) {
        return false;
    }

    // Initialize delay tracking structure. Holds input data offset by delay time and is
    // used to modify input signal.
    queue<double> delay_line = init_delay_buffer(delay_time_in_samples);

    // Process signal. Modify input and in this case propogate the modified signal
    // through the delay line.
    for (auto sample = buffer.begin(); sample != buffer.end(); sample++) {
        *sample = *sample + (gain * delay_line.front());
        delay_line.push(*sample);
        delay_line.pop();
    }

    return true;
}


bool Delay::AddEcho_Universal(std::vector<double>& buffer, double gain, double feedforward, double feedback, double blend, double time, double sample_rate) {
    const double buffer_length_seconds = static_cast<double>(buffer.size()) / sample_rate;
    const int delay_time_in_samples = static_cast<int>(time * sample_rate);

    // Sanity check.
    if (buffer.empty() || gain > 1.0 || time > buffer_length_seconds) {
        return false;
    }

    // Initialize delay tracking structure. Holds input data offset by delay time and is
    // used to modify input signal.
    queue<double> delay_line = init_delay_buffer(delay_time_in_samples);

    // Process with aspects of both FIR and IIR filter.
    for (auto sample = buffer.begin(); sample != buffer.end(); sample++) {
        double processed = *sample + feedback + delay_line.front();
        *sample = feedforward * delay_line.front() + blend * processed;
        delay_line.push(processed);
        delay_line.pop();
    }

    return true;
}


queue<double> Delay::init_delay_buffer(int length) {
    queue<double> buffer;

    for (int i = 0; i < length; i++) {
        buffer.push(0);
    }

    return buffer;
}






