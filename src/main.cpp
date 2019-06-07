#include <iostream>
#include <vector>
#include <string>
#include <sndfile.h>

#include "distortion.h"
#include "delay.h"

using namespace std;

/**
 * @brief load_mono_wave_file loads a vector with samples in floating point format. Closely follows some
 * of the examples at: https://github.com/erikd/libsndfile/tree/master/examples
 *
 * @param[in] filename of the wav file to load.
 * @param[in] sample_rate of the wav file.
 *
 * @returns sample buffer.
 */
vector<double> load_mono_wave_file(string filename, double sample_rate);


/**
 * @brief save_mono_wave_file saves a vector of samples in floating point format to disk. Closely follows some
 * of the examples at: https://github.com/erikd/libsndfile/tree/master/examples
 *
 * @param[in] filename of the wav file to save.
 * @param[in] sample_rate of the wav file.
 * @param[in] samples to save.
 */
void save_mono_wave_file(string filename, double sample_rate, vector<double> samples);


int main(int argc, char* argv[]) {
    if (argc != 3 || atof(argv[2]) == 0.0) {
        cout << "Usage: " << argv[0] << " file_to_process.wav sample_rate_in_Hz" << endl;
        return 1;
    }

    // Load parameters from command line.
    double sample_rate = atof(argv[2]);
    string filename = argv[1];

    // Load wave file samples into buffer.
    vector<double> buffer_to_process = load_mono_wave_file(filename, sample_rate);

    // Run and save each effect (as a demo).

    vector<double> buffer_light_distortion(buffer_to_process);
    if (Distortion::AddDistortion(buffer_light_distortion, 0.9999)) {
        save_mono_wave_file("guitar_distortion_light.wav", sample_rate, buffer_light_distortion);
    }

    vector<double> buffer_heavy_distortion(buffer_to_process);
    if (Distortion::AddDistortion(buffer_heavy_distortion, 0.9)) {
        save_mono_wave_file("guitar_distortion_heavy.wav", sample_rate, buffer_heavy_distortion);
    }

    vector<double> buffer_fir_echo(buffer_to_process);
    if (Delay::AddEcho_FIR(buffer_fir_echo, 0.5, 0.4, sample_rate)) {
        save_mono_wave_file("guitar_echo_fir.wav", sample_rate, buffer_fir_echo);
    }

    vector<double> buffer_iir_echo(buffer_to_process);
    if (Delay::AddEcho_IIR(buffer_iir_echo, 0.6, 0.4, sample_rate)) {
        save_mono_wave_file("guitar_echo_iir.wav", sample_rate, buffer_iir_echo);
    }

    vector<double> buffer_universal_echo(buffer_to_process);
    if (Delay::AddEcho_Universal(buffer_universal_echo, 0.5, -0.1, 0.01, 0.25, 0.5, sample_rate)) {
        save_mono_wave_file("guitar_echo_universal.wav", sample_rate, buffer_universal_echo);
    }

    return 0;
}



vector<double> load_mono_wave_file(string filename, double sample_rate) {
    vector<double> filter_samples;
    SNDFILE* file;
    SF_INFO sfinfo;

    // Wave file settings.
    sfinfo.samplerate = static_cast<int>(sample_rate);
    sfinfo.frames = (static_cast<int>(sample_rate) * 4);
    sfinfo.channels = 1;
    sfinfo.format = (SF_FORMAT_WAV | SF_FORMAT_PCM_16);

    // Open and check for error.
    file = sf_open(filename.c_str(), SFM_READ, &sfinfo);
    if (!file) {
        cout << "File read error." << endl;
        exit(1);
    }

    // File processing variables.
    sf_count_t samples_read = 0;
    vector<double> samples_read_buffer;
    samples_read_buffer.resize(128);

    // Load samples from file in chunks of 128 bytes and append to output vector.
    samples_read = sf_read_double(file, samples_read_buffer.data(), 128);
    while (samples_read > 0) {
        filter_samples.insert(filter_samples.end(), samples_read_buffer.begin(), samples_read_buffer.end());
        samples_read = sf_read_double(file, samples_read_buffer.data(), 128);
    }

    return filter_samples;
}



void save_mono_wave_file(string filename, double sample_rate, vector<double> samples) {
    SF_INFO	sfinfo;

    // Wave file settings.
    sfinfo.samplerate = static_cast<int>(sample_rate);
    sfinfo.frames = (static_cast<int>(sample_rate) * 4);
    sfinfo.channels = 1;
    sfinfo.format = (SF_FORMAT_WAV | SF_FORMAT_PCM_16);

    SNDFILE* file = sf_open(filename.c_str(), SFM_WRITE, &sfinfo);

    sf_writef_double(file, samples.data(), samples.size());
    sf_close(file) ;
}
