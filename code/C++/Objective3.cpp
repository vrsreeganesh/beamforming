// =============================================================================
#include "include/before.hpp"
// main-file ===================================================================
int main(){

    // starting timer
    auto logfile    {string("../csv-files/logfile-Objective3.csv")}; 
    Timer timer(logfile);

    // init-variables
    auto f                  {2000};                                     // frequency of signal
    auto Fs                 {12800};                                    // sampling frequency
    auto Ts                 {1.00/static_cast<double>(Fs)};                // corresponding time-period
    auto N                  {128};                                      // num-samples

    auto m                  {32};
    auto angleofarrival     {135};
    auto speedofsound       {1500};
    auto lambda             {static_cast<double>(speedofsound)/static_cast<double>(f)};
    auto x                  {lambda/2.00};
    auto d                  {x * std::cos(static_cast<double>(angleofarrival) * std::numbers::pi / 180) / speedofsound};

    auto snr                {100};                                       // signal-to-noise ratio
    auto snrweight          {std::pow(10, (-1 * snr * 0.05))};          // corresponding weight


    // building time-array
    vector<double>t = linspace(0.0, 
                               static_cast<double>(N-1) * Ts, 
                               static_cast<size_t>(N));
    fWriteVector(t, "../csv-files/t-Objective3.csv");

    // building matrix
    auto matrix = Zeros({m, N});

    // creating sine-wave
    auto y                  {sin(2 * std::numbers::pi * f * t)};
    fWriteVector(y, "../csv-files/y-Objective3.csv");

    // building the matrix
    for(int sensorindex = 0; sensorindex < m; ++sensorindex)
        matrix[sensorindex] = sin(2.00 * std::numbers::pi * f * (t - sensorindex * d));
    fWriteMatrix(matrix, "../csv-files/matrix-Objective3.csv");


    // Adding noise to the matrix
    auto newmat             {matrix + snrweight * rand(0.0, 1.0, {m, N})};
    fWriteMatrix(newmat, "../csv-files/newmat-Objective3.csv");

    
    // Taking the fourier-transform
    auto nfft       {N};
    auto fend       {static_cast<double>(nfft - 1) * static_cast<double>(Fs) / static_cast<double>(nfft)};
    auto waxis      {linspace(0, fend, nfft)};
    auto Fourier    {fft(newmat, nfft)};
    fWriteMatrix(Fourier, "../csv-files/Fourier-Objective3.csv");

    
    // choosing the frequency row
    int index  = std::floor(static_cast<double>(f)/  (static_cast<double>(Fs)/static_cast<double>(nfft)));
    auto fmat   {slice(Fourier, {-1, -2, index, index})};
    
    
    // Bringing the delay in frequency region
    auto anglematrix    {vector<double>(181)};
    auto delaycolumn    {vector<complex<double>>(m)};

    // moving through angle
    for(int testangle = 0; testangle<181; ++testangle){
        
        double testd  {x * cosd(testangle) / speedofsound};

        for(int currsensor = 0; currsensor < m; ++currsensor){
            delaycolumn[currsensor] = \
                std::exp( 1 * std::complex<double>{0, 1} * 2 * std::numbers::pi * f * currsensor * testd);
        }

        // calculating inner-product
        auto innerproduct_value {delaycolumn[0] * fmat[0][0]};
        for(int i = 1; i<delaycolumn.size(); ++i)
            innerproduct_value += delaycolumn[i] * fmat[i][0];

        // storing to the angle-matrix
        anglematrix[testangle] = std::abs(innerproduct_value);
    }
    fWriteVector(anglematrix, "../csv-files/anglematrix-Objective3.csv");

    // creating angle-axis
    auto angleaxis  {linspace(0, 180, 181)};
    fWriteVector(angleaxis, "../csv-files/angleaxis-Objective3.csv");

    // return
    return(0);
    
}