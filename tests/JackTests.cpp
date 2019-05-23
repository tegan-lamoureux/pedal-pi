#include "gtest/gtest.h"

#include <jack/jack.h>

using namespace std;

namespace {

TEST(JackTests, can_use_jack) {
    jack_status_t status;
    jack_client_t* client = jack_client_open("testing", JackNullOption, &status);

    ASSERT_NE(nullptr, client);
}

}
