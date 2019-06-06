#ifndef ECHO_H
#define ECHO_H

#include <vector>

// Note that I referenced: http://users.cs.cf.ac.uk/Dave.Marshall/CM0268/PDF/10_CM0268_Audio_FX.pdf
// for this implementation.
class Echo
{
public:
    static bool AddEcho(std::vector<double>& buffer, double magnitude, double feedback);

private:
    Echo() = delete;
};

#endif // ECHO_H

