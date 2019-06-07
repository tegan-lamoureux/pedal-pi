#include <iostream>
#include <vector>
#include <string>
#include <sndfile.h>

#include "distortion.h"
#include "echo.h"

using namespace std;


/** @brief load_mono_wave_file loads a vector with samples in floating point format. Closely follows some
 *         of the examples at: https://github.com/erikd/libsndfile/tree/master/examples
 *
 *  @param[in] filename of the wav file to load.
 *  @param[in] sample_rate of the wav file.
 *
 *  @returns sample buffer.
 */
vector<double> load_mono_wave_file(string filename, double sample_rate);

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

    vector<double> buffer_1(buffer_to_process);
    Distortion::AddDistortion(buffer_1, 0.9999);
    save_mono_wave_file("guitar_distortion_light.wav", sample_rate, buffer_1);

    vector<double> buffer_2(buffer_to_process);
    Distortion::AddDistortion(buffer_2, 0.9);
    save_mono_wave_file("guitar_distortion_heavy.wav", sample_rate, buffer_2);

    vector<double> buffer_3(buffer_to_process);
    if (Echo::AddEcho_FIR(buffer_3, 0.5, 0.4, sample_rate)) {
        save_mono_wave_file("guitar_echo_fir.wav", sample_rate, buffer_3);
    }

    vector<double> buffer_4(buffer_to_process);
    if (Echo::AddEcho_IIR(buffer_4, 0.6, 0.4, sample_rate)) {
        save_mono_wave_file("guitar_echo_iir.wav", sample_rate, buffer_4);
    }

    vector<double> buffer_5(buffer_to_process);
    if (Echo::AddEcho_Universal(buffer_5, 0.5, -0.1, 0.01, 0.25, 0.5, sample_rate)) {
        save_mono_wave_file("guitar_echo_universal.wav", sample_rate, buffer_5);
    }

    return 0;
}


vector<double> load_mono_wave_file(string filename, double sample_rate) {
    vector<double> filter_samples;
    SNDFILE* file;
    SF_INFO sfinfo;

    // Wave file settings.
    sfinfo.samplerate = static_cast<int>(sample_rate);
    sfinfo.frames     = (static_cast<int>(sample_rate) * 4);
    sfinfo.channels   = 1;
    sfinfo.format     = (SF_FORMAT_WAV | SF_FORMAT_PCM_16);

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


// Referenced from: https://github.com/erikd/libsndfile/blob/master/examples/make_sine.c
void save_mono_wave_file(string filename, double sample_rate, vector<double> samples) {
    SF_INFO	sfinfo ;

    // Wave file settings.
    sfinfo.samplerate = static_cast<int>(sample_rate);
    sfinfo.frames     = (static_cast<int>(sample_rate) * 4);
    sfinfo.channels   = 1;
    sfinfo.format     = (SF_FORMAT_WAV | SF_FORMAT_PCM_16);

    SNDFILE* file = sf_open(filename.c_str(), SFM_WRITE, &sfinfo);

    sf_writef_double(file, samples.data(), samples.size());

    sf_close (file) ;
}














