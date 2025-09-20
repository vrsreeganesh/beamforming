// =============================================================================
#include "include/before.hpp"
// main-file ===================================================================
int main(){

    // starting timer
    auto logfile    {string("../csv-files/logfile-Objective6.csv")};
    Timer timer(logfile);

    // init-variables
    auto f                  {2800};
    auto Fs                 {12800};
    auto Ts                 {1.00/static_cast<double>(Fs)};
    auto N                  {128};

    auto m                  {32};
    auto angle              {90};
    auto c                  {1500};
    auto lambda             {static_cast<double>(c)/static_cast<double>(f)};
    auto x                  {lambda/2.00};
    auto d                  {static_cast<double>(x * cosd(angle)/c)};

    auto snr                {30};
    auto snrweight          {static_cast<double>(std::pow(10, -1 * snr * 0.05))};


    // simulating signals
    auto t                  {linspace(static_cast<double>(0),
                                      static_cast<double>(N-1) * Ts,
                                      N)};
    auto matrix             {Zeros({m, N})};
    
    
    // bringing about natural delay
    for(int sensorindex = 0; sensorindex < m ; ++sensorindex)
        matrix[sensorindex] = \
            sin( 2.00 * std::numbers::pi * f * (t - sensorindex * d));
    fWriteVector(t,         "../csv-files/timearray-Objective6.csv");
    fWriteMatrix(matrix,    "../csv-files/matrix-Objective6.csv");

    
    // adding the noise
    auto newmat  = matrix + snrweight * rand(0.00, 1.00, {m, N}); 
    fWriteMatrix(newmat, "../csv-files/newmat-Objective6.csv");

    
    // taking the fourier transform
    auto nfft       {N};
    auto fend       {static_cast<double>((nfft-1) * Fs) / static_cast<double>(nfft)};
    auto waxis      {linspace(0, fend, nfft)};
    auto Fourier    {fft(newmat, nfft)};
    fWriteVector(waxis,     "../csv-files/waxis.csv");
    fWriteMatrix(Fourier,   "../csv-files/Fourier.csv");

    // choosing the frequency row
    int index       {static_cast<int>(std::floor(static_cast<double>(f)/  (static_cast<double>(Fs)/static_cast<double>(nfft))))};
    auto fmat       {slice(Fourier, {-1, -2, index, index})};
    
    // bringing the delay in frequency region
    auto anglematrix    {vector<double>(181)};
    auto delaycolumn    {vector<complex<double>>(m, 0)};

    // building 
    for(int testangle = 0; testangle < 181; ++testangle){

        auto testd  {x * cosd(testangle)/c};

        for(int sensorindex = 0; sensorindex < m; ++sensorindex)
            delaycolumn[sensorindex]    = std::exp(1 * 1i * 2 * std::numbers::pi * f * sensorindex * testd);

        anglematrix[testangle] = \
            std::abs(std::inner_product(fmat.begin(), fmat.end(),
                                        delaycolumn.begin(),
                                        complex<double>{0},
                                        std::plus<complex<double>>(),
                                        [](vector<complex<double>> a, complex<double> b){
                                            return a[0]*b;
                                        }));
    }

    // building axes
    auto angleaxis   = linspace(0, 180, 181);

    // saving
    fWriteVector(angleaxis,     "../csv-files/angleaxis-Objective-6.csv");
    fWriteVector(anglematrix,   "../csv-files/anglematrix-Objective-6.csv");

    // return
    return(0);
    
}
