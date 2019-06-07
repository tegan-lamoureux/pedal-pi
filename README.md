### Guitar Effects Library
#### Tegan Lamoureux; CS410P Term Project

Guitar effects in DSP.

#### What It Is; How It Works

There are four filters in two categories.
1. A distortion filter will add (ideally desirable) distortion to an input signal. It can be configured for the magnitude of the applied distortion.
2. A series of delay filters will give echo-based effects to an input signal. Three are available:
* FIR Comb Filter - This is a finite impulse response filter. In practice, this will give a single echo to a signal at the parameterized gain and delay time.
* IIR Comb Filter - This is an infinite impulse response filter. In practice, this will give a more rich, decaying echo to a signal at the parameterized gain and delay time. It will continue to propagate at decreasing amplitude at the specified delay time until undetectable.
* Universal Comb Filter - This is a combination of the FIR and IIR filter algorithms, which allows for a complex configuration that can emulate an FIR, IIR or Allpass comb filter.

#### What Didn't Work

This was originally intended to run on the Raspberry Pi, but due to time constraints I pivoted it to a generic c++ library that can run (alongside many platforms) on the raspberry pi. I also wished to implement many more filters than I did, but I am quite happy with the quality of the existing ones. This was fun! And I didn't expect it to sound as good as it does - especially the delays.

That said, in my project tests I dig into using jackaudio to read in samples and process them using a ring buffer. Further, on each filter's unit tests, I have a working example of this. This helps lower the barrier to implementation on an embedded system in the future.

In order to show the functionality, this repository contains a main that loads a sample (16 bit mono PCM) wave file and runs and saves examples of each filter. Example input along with a demonstration of each filter can be found in the `results` directory. Further, in the same directory can be found a log of all project unit tests (using google test framework) passing.

#### Lessons Learned

Hardware is difficult. I originally planned to implement this on a raspberry pi, but that proved to be too much for my time frame. Along the same vein, I think it's important to set realistic goals. This was a great demonstration of the importance of planning and correctly gauging time.

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
