### Pi Guitar Pedal
#### Tegan Lamoureux; CS410P Term Project

A guitar pedal on the raspberry pi.

#### Building
It's cmake, so to build the application and unit tests:  
* `git clone https://github.com/tegan-lamoureux/pedal-pi.git`
* `cd pedal-pi`
* `mkdir build`
* `cd build`
* `cmake ../`
* `make`

#### Notes for me:
* https://dsp.stackexchange.com/questions/13142/digital-distortion-effect-algorithm
* https://en.wikipedia.org/wiki/Waveshaper
* https://dsp.stackexchange.com/questions/2792/high-quality-reverb-algorithm
* https://ccrma.stanford.edu/~jos/pasp/Schroeder_Reverberator_called_JCRev.html
* https://github.com/jackaudio/example-clients
* http://users.cs.cf.ac.uk/Dave.Marshall/CM0268/PDF/10_CM0268_Audio_FX.pdf
* http://jackaudio.org/files/docs/html/ringbuffer_8h.html#a6d2fc75510e4df62f5b3dd249047b132

#### TODO:
* For presentation/writeup, if just making a lib, run gcov and show a nice graph to prove test coverage.
