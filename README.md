### Guitar Effects Library
#### Tegan Lamoureux; CS410P Term Project

Guitar effects in DSP.

There are four filters in two categories.

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
