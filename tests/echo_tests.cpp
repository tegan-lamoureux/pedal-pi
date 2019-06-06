#include "gtest/gtest.h"

#include <vector>
#include <cstdlib>

#include <jack/jack.h>
#include <jack/ringbuffer.h>

#include "echo.h"

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
	Echo::AddEcho_FIR(test, 0.0, 0.0, 0.0);
}

}

