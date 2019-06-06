#include "gtest/gtest.h"

#include <vector>
#include <cstdlib>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

#include "distortion.h"

using namespace std;

namespace {

class DistortionTests : public ::testing::Test {
protected:
    virtual void SetUp() {}

    virtual void TearDown() {}

    static jack_ringbuffer_t *buffer;
};

jack_ringbuffer_t* DistortionTests::buffer;




TEST_F(DistortionTests, can_use_distortion) {
    vector<double> test;
    Distortion::AddDistortion(test, 0.0);
}


TEST_F(DistortionTests, can_run_algorithm_one_pass) {
    vector<double> buffer;
    const int buffer_length = 1024;
    const int buffer_magnitude = 128;

    // Populate with noise test data.
    for (int sample = 0; sample < buffer_length; sample++) {
        buffer.emplace_back(rand() % buffer_magnitude);
    }

    // Call distortion algo on it.
    ASSERT_TRUE(Distortion::AddDistortion(buffer, 1));
}


TEST_F(DistortionTests, can_run_algorithm_multiple_passes_multiple_magnitudes) {
    vector<double> buffer;
    const int buffer_length = 1024;
    const int buffer_magnitude = 128;

    // Populate with noise test data.
    for (int sample = 0; sample < buffer_length; sample++) {
        buffer.emplace_back(rand() % buffer_magnitude);
    }

    // Call distortion algo on it.
    for (int test_loop = 0; test_loop < 100; test_loop++) {
        ASSERT_TRUE(Distortion::AddDistortion(buffer, test_loop));
    }
}


TEST_F(DistortionTests, can_run_algorithm_on_jack_ring_buffer) {
    this->buffer = jack_ringbuffer_create(1200 * sizeof(double));
    vector<double> retrievedData;

    int res = jack_ringbuffer_mlock(this->buffer);
    ASSERT_EQ(0, res);

    // Populate with noise test data.
    for (int sample = 0; sample < 1024; sample++) {
        double sampleToWrite = rand() % 128;
        jack_ringbuffer_write(this->buffer, reinterpret_cast<char*>(&sampleToWrite), sizeof(double));
    }

    // Retrieve data.
    for (int sample = 0; sample < 1024; sample++) {
        double readValue;
        jack_ringbuffer_read(this->buffer, reinterpret_cast<char*>(&readValue), sizeof(double));
        retrievedData.emplace_back(readValue);
    }

    // Process data.
    ASSERT_TRUE(Distortion::AddDistortion(retrievedData, 64.0));
}

}
