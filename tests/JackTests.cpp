#include "gtest/gtest.h"

#include <jack/jack.h>
#include <jack/ringbuffer.h>

using namespace std;

namespace {

class JackTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->buffer = 0;
    }

    virtual void TearDown() {}

    static jack_port_t *input_port;
    static jack_port_t *output_port;
    static jack_ringbuffer_t *buffer;

    static int jack_process_callback (jack_nframes_t nframes, void *arg) {
        jack_default_audio_sample_t *in, *out;

        in = static_cast<jack_default_audio_sample_t*>(jack_port_get_buffer(input_port, nframes));
        out = static_cast<jack_default_audio_sample_t*>(jack_port_get_buffer(output_port, nframes));
        memcpy(out, in, sizeof (jack_default_audio_sample_t) * nframes);

        return 0;
    }

    static int write_ring(int i) {
        // get amount of space we can write
        int availableWrite = jack_ringbuffer_write_space(buffer);

        if (availableWrite >= sizeof(int))
        {
            // tell it to write data, keep track of how much was written
            int written = jack_ringbuffer_write( buffer, (const char*) &i , sizeof(int) );

            // ensure we wrote an entire event
            if (written != sizeof(int) ) {
                std::cout << "ERROR! didn't write full integer!" << std::endl;
            }
        }
        else {
            std::cout << "ERROR! RingBuffer FULL! Skipping..." <<std::endl;
        }
    }

    static int process_ring(jack_nframes_t nframes, void* )
    {
        // check if there's anything to read
        int availableRead = jack_ringbuffer_read_space(buffer);

        if ( availableRead >= sizeof(int) )
        {
            // create int to read value into
            int tempInt;

            // read from the buffer
            int result = jack_ringbuffer_read(buffer, (char*)&tempInt, sizeof(int));

            if ( result != sizeof(int) ) {
                std::cout << "RtQueue::pull() WARNING! didn't read full event!" << std::endl;
                return -1;
            }

            std::cout << "Jack thread says int = " << tempInt << std::endl;
        }

        return 0;
    }

    jack_status_t status;
    jack_client_t* client;
};


// Static instantiation.
jack_port_t* JackTests::input_port;
jack_port_t* JackTests::output_port;
jack_ringbuffer_t* JackTests::buffer;


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
    std::cout << "Ring buffer tutorial" << std::endl;

    // create an instance of a ringbuffer that will hold up to 20 integers,
    // let the pointer point to it
    this->buffer = jack_ringbuffer_create(20);

    // lock the buffer into memory, this is *NOT* realtime safe, do it before
    // using the buffer!
    int res = jack_ringbuffer_mlock(this->buffer);

    // check if we've locked the memory successfully
    if ( res ) {
        std::cout << "Error locking memory!" << std::endl;
    }

    // create a JACK client, register the process callback and activate
    jack_client_t* client = jack_client_open ( "RingbufferDemo", JackNullOption , 0 , 0 );
//    jack_set_process_callback  (client, process_ring , 0);
//    jack_activate(client);

//    for ( int i = 0; i < 2; i++) {
//        // write an event, then pause a while, JACK will get a go and then
//        // we'll write another event... etc
//        write_ring(i);
//        sleep(0.1);
//    }
}

}
