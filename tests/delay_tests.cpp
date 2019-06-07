#include "gtest/gtest.h"

#include <vector>
#include <cstdlib>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

#include "delay.h"

using namespace std;

namespace {

class EchoTests : public ::testing::Test {
protected:
    virtual void SetUp() {}

    virtual void TearDown() {}

    static jack_ringbuffer_t *buffer;
};

jack_ringbuffer_t* EchoTests::buffer;


TEST_F(EchoTests, can_use_echo) {
    vector<double> test;
    Delay::AddEcho_FIR(test, 0.0, 0.0, 0.0);
}

TEST_F(EchoTests, can_run_fir_algorithm) {
    vector<double> buffer;
    const int buffer_length = 1024;
    const int buffer_magnitude = 128;

    // Populate with noise test data.
    for (int sample = 0; sample < buffer_length; sample++) {
        buffer.emplace_back(rand() % buffer_magnitude);
    }

    // Call echo algo on it.
    ASSERT_TRUE(Delay::AddEcho_FIR(buffer, 0.5, 0.5, 128));
}

TEST_F(EchoTests, can_run_iir_algorithm) {
    vector<double> buffer;
    const int buffer_length = 1024;
    const int buffer_magnitude = 128;

    // Populate with noise test data.
    for (int sample = 0; sample < buffer_length; sample++) {
        buffer.emplace_back(rand() % buffer_magnitude);
    }

    // Call echo algo on it.
    ASSERT_TRUE(Delay::AddEcho_IIR(buffer, 0.5, 0.5, 128));
}

TEST_F(EchoTests, can_run_universal_algorithm) {
    vector<double> buffer;
    const int buffer_length = 1024;
    const int buffer_magnitude = 128;

    // Populate with noise test data.
    for (int sample = 0; sample < buffer_length; sample++) {
        buffer.emplace_back(rand() % buffer_magnitude);
    }

    // Call echo algo on it.
    ASSERT_TRUE(Delay::AddEcho_Universal(buffer, 0.5, -0.1, 0.1, 0.5, 0.5, 128));
}

TEST_F(EchoTests, can_run_algorithms_on_jack_ring_buffer) {
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
    vector<double> fir_buffer(retrievedData);
    vector<double> iir_buffer(retrievedData);
    vector<double> universal_buffer(retrievedData);

    ASSERT_TRUE(Delay::AddEcho_FIR(fir_buffer, 0.5, 0.5, 128));
    ASSERT_TRUE(Delay::AddEcho_IIR(iir_buffer, 0.5, 0.5, 128));
    ASSERT_TRUE(Delay::AddEcho_Universal(universal_buffer, 0.5, -0.1, 0.1, 0.5, 0.5, 128));
}

}

