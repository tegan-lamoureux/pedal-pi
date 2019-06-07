### Guitar Effects Library
#### Tegan Lamoureux; CS410P Term Project

Guitar effects in DSP.

There are four filters in two categories.
1. A distortion filter will add (ideally desirable) distortion to an input signal. It can be configured for the magnitude of the applied distortion.
2. A series of delay filters will give echo-based effects to an input signal. Three are available:
  * FIR Comb Filter - This is a finite impulse response filter. In practice, this will give a single echo to a signal at the parameterized gain and delay time.
* IIR Comb Filter - This is an infinite impulse response filter. In practice, this will give a more rich, decaying echo to a signal at the parameterized gain and delay time. It will continue to propagate at decreasing amplitude at the specified delay time until undetectable.
* Universal Comb Filter - This is a combination of the FIR and IIR filter algorithms, which allows for a complex configuration that can emulate an FIR, IIR or Allpass comb filter.

#### Building
It's cmake, so to build the application and unit tests you'll need to do the following:
* `git clone https://github.com/tegan-lamoureux/pedal-pi.git`
* `cd pedal-pi`
* `mkdir build`
* `cd build`
* `cmake ../`
* `make`

#### Requirements
* cmake
* jackaudio development files
* libsndfile development files
* gtest and unit tests are automatically downloaded and built as part of the cmake setup process.
