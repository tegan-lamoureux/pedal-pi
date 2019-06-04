#include "gtest/gtest.h"

#include <jack/jack.h>
#include <jack/ringbuffer.h>

using namespace std;

namespace {

class JackTests : public ::testing::Test {
protected:
    virtual void SetUp() {}

    virtual void TearDown() {}

    static jack_port_t *input_port;
    static jack_port_t *output_port;

    static int jack_process_callback (jack_nframes_t nframes, void *arg) {
        jack_default_audio_sample_t *in, *out;

        in = static_cast<jack_default_audio_sample_t*>(jack_port_get_buffer(input_port, nframes));
        out = static_cast<jack_default_audio_sample_t*>(jack_port_get_buffer(output_port, nframes));
        memcpy(out, in, sizeof (jack_default_audio_sample_t) * nframes);

        return 0;
    }

    jack_status_t status;
    jack_client_t* client;
};


// Static instantiation.
jack_port_t* JackTests::input_port;
jack_port_t* JackTests::output_port;


TEST_F(JackTests, DISABLED_can_use_jack) {
    this->client = jack_client_open("testing", JackNullOption, &this->status);
    ASSERT_NE(nullptr, client);

    jack_client_close(client);
}


/** @brief Example taken from: https://github.com/jackaudio/example-clients/
  */
TEST_F(JackTests, can_run_basic_client_example) {
    const char **ports;
    const char *client_name = "simple";
    const char *server_name = NULL;
    jack_options_t options = JackNullOption;

    client = jack_client_open (client_name, options, &status, server_name);
    ASSERT_NE(nullptr, client);
    EXPECT_NE(0, status);
    ASSERT_NE(0, JackServerStarted);

    if (status & JackNameNotUnique) {
        client_name = jack_get_client_name(client);
    }

    jack_set_process_callback(client, jack_process_callback, 0);

    input_port = jack_port_register (client, "input", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    output_port = jack_port_register (client, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    ASSERT_NE(nullptr, input_port);
    ASSERT_NE(nullptr, output_port);

    auto activate_result = jack_activate(client);
    ASSERT_EQ(0, activate_result);

    // Hook up and test Output port.
    ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsOutput);
    ASSERT_NE(nullptr, ports);
    auto input_connect_result = jack_connect(client, ports[0], jack_port_name (input_port));
    EXPECT_EQ(0, input_connect_result);
    free(ports);

    // Hook up and test Output port.
    ports = jack_get_ports(client, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
    ASSERT_NE(nullptr, ports);
    auto output_connect_result = jack_connect(client, ports[0], jack_port_name(output_port));
    EXPECT_EQ(0, output_connect_result);
    free (ports);

    jack_client_close (client);
}

/** @brief Example taken from: http://harryhaaren.blogspot.com/2011/11/tutorial-jack-ringbuffers.html
 */
TEST_F(JackTests, can_use_ring_buffer) {

}

}
