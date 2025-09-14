// =============================================================================
#include "include/before.hpp"
// main-file ===================================================================
int main(){

    // starting timer
    auto logfile    {string("../csv-files/logfile.csv")};
    Timer timer(logfile);

    // init-variables
    auto f          {2000};                                     // frequency of signal
    auto Fs         {12800};                                    // sampling frequency
    auto Ts         {1/static_cast<double>(Fs)};                // corresponding time-period
    auto N          {128};                                      // num-samples

    auto snr        {10};                                       // signal-to-noise ratio
    auto snrweight  {std::pow(10, (-1 * snr * 0.05))};          // corresponding weight

    // building time-array
    vector<double> t(N,0); t.reserve(N);
    t = linspace(0.0, static_cast<double>(N-1), static_cast<size_t>(N)) * Ts;
    fWriteVector(t, "../csv-files/t-Objective1.csv");

    // creating sine-wave
    auto y = t;  
    std::transform(t.begin(), 
                   t.end(), 
                   y.begin(), 
                   [&](const auto x){return std::sin( 2 * std::numbers::pi * f * x);});

    // adding noise to the vector
    auto newmat     {y + snrweight * rand(-1.0, 1.0, y.size())};
    auto timeaxis   {linspace(static_cast<double>(0), 
                              static_cast<double>((N-1)*Ts), 
                              N)};
    fWriteVector(timeaxis,  "../csv-files/timeaxis-Objective1.csv");
    fWriteVector(newmat,    "../csv-files/newmat-Objective1.csv");

    // Taking the fourier transform
    auto nfft       {N};
    auto fend       {static_cast<double>((nfft-1) * Fs) / static_cast<double>(nfft)};
    auto waxis      {linspace(static_cast<double>(0),
                              static_cast<double>(fend),
                              nfft)};
    auto Fourier    {fft(newmat)};
    fWriteVector(waxis,     "../csv-files/waxis-Objective1.csv");
    fWriteVector(Fourier,   "../csv-files/Fourier-Objective1.csv");

    // return
    return(0);
    
}