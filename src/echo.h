#ifndef ECHO_H
#define ECHO_H

#include <vector>

// Note that I referenced: http://users.cs.cf.ac.uk/Dave.Marshall/CM0268/PDF/10_CM0268_Audio_FX.pdf
// for the concepts behind this implementation.
class Echo
{
public:
	/**
	 * @brief AddEcho_CombFIR is a finite impulse response filter...
	 * @param buffer
	 * @param magnitude
	 * @param feedback
	 * @param time
	 * @return
	 */
	static bool AddEcho_FIR(std::vector<double>& buffer, double gain, double feedback, double time, double sample_rate);

	/**
	 * @brief AddEcho_CombIIR is an infinite impulse response filter...
	 * @param buffer
	 * @param magnitude
	 * @param feedback
	 * @param time
	 * @return
	 */
	static bool AddEcho_IIR(std::vector<double>& buffer, double gain, double feedback, double time, double sample_rate);

	/**
	 * @brief AddEcho_CombUniversal is a combination of both, and can form any comb filter, allpass, or delay.
	 * @param buffer
	 * @param magnitude
	 * @param feedback
	 * @param time
	 * @return
	 */
	static bool AddEcho_Universal(std::vector<double>& buffer, double gain, double feedback, double time, double sample_rate);

private:
    Echo() = delete;
};

#endif // ECHO_H

