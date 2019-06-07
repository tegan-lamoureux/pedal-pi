#ifndef DELAY_H
#define DELAY_H

#include <vector>
#include <queue>

/**
 * @brief The Delay class implements echo based effects.
 * Many of these were adapted from matlab algorithms at:
 * http://users.cs.cf.ac.uk/Dave.Marshall/CM0268/PDF/10_CM0268_Audio_FX.pdf
 */
class Delay
{
public:
    /**
     * @brief A finite impulse response comb filter to add echo / delay to a signal.
     * @param buffer Samples to process.
     * @param gain Magnitude of the echo signal.
     * @param time How long the echo's delay will be.
     * @param sample_rate Sample rate (hz) of the incoming signal.
     * @returns true when successfully processed, or false when invalid parameters are passed.
	 */
	static bool AddEcho_FIR(std::vector<double>& buffer, double gain, double time, double sample_rate);

	/**
	 * @brief An infinite impulse response comb filter to add echo / delay to a signal.
     * @param buffer Samples to process.
     * @param gain Magnitude of the echo signal.
     * @param time How long the echo's delay will be.
     * @param sample_rate Sample rate (hz) of the incoming signal.
     * @returns true when successfully processed, or false when invalid parameters are passed.
     */
	static bool AddEcho_IIR(std::vector<double>& buffer, double gain, double time, double sample_rate);

    /**
     * @brief AddEcho_Universal A combination of both FIR and IIR comb filters with more control over feedback and decay.
     * @param buffer Samples to process.
     * @param gain Magnitude of the echo signal.
     * @param feedforward Forward magnitude for the FIR component.
     * @param feedback Backwards magnitude for the IIR component.
     * @param blend FIR vs IIR filter presence.
     * @param time How long the echo's delay will be.
     * @param sample_rate Sample rate (hz) of the incoming signal.
     * @returns true when successfully processed, or false when invalid parameters are passed.
     */
    static bool AddEcho_Universal(std::vector<double>& buffer, double gain, double feedforward, double feedback, double blend, double time, double sample_rate);

private:
    Delay() = delete;

    static std::queue<double> init_delay_buffer(int length);
};

#endif // DELAY_H

