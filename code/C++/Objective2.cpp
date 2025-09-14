// =============================================================================
#include "include/before.hpp"
// main-file ===================================================================
int main(){

    // starting timer
    auto logfile    {string("../csv-files/logfile.csv")};
    Timer timer(logfile);

    // init-variables
    auto f                  {200};                                     // frequency of signal
    auto Fs                 {12800};                                    // sampling frequency
    auto Ts                 {1/static_cast<double>(Fs)};                // corresponding time-period
    auto N                  {128};                                      // num-samples

    auto m                  {4};
    auto angleofarrival     {60};
    auto speedofsound       {1500};
    auto lambda             {static_cast<double>(speedofsound)/static_cast<double>(f)};
    auto x                  {lambda/2};
    auto d                  {x * std::cos(angleofarrival * std::numbers::pi / 180) / speedofsound};

    auto snr                {10};                                       // signal-to-noise ratio
    auto snrweight          {std::pow(10, (-1 * snr * 0.05))};          // corresponding weight

    // building time-array
    vector<double> t(N,0); t.reserve(N);
    t = linspace(0.0, 
                 static_cast<double>(N-1), 
                 static_cast<size_t>(N)) * Ts;
    fWriteVector(t, "../csv-files/timeaxis-Objective2.csv");

    // building matrix
    auto matrix = Zeros({m, N});

    // creating sine-wave
    auto y = sin(2 * std::numbers::pi * f * t);
    fWriteVector(y, "../csv-files/y-Objective2.csv");

    // building the matrix
    for(int i = 0; i<m; ++i)
        matrix[i] = sin(2 * std::numbers::pi * f * (t  -  i * d ));
    fWriteMatrix(matrix, "../csv-files/matrix-Objective2.csv");

    // Adding noise to the matrix
    vector<vector<double>> additivenoise = snrweight * rand(0.0, 1.0, {m, N});
    fWriteMatrix(additivenoise, "../csv-files/additivenoise-Objective2.csv");
    
    auto newmat {matrix + additivenoise};
    fWriteMatrix(newmat, "../csv-files/newmat-Objective2.csv");

    // return
    return(0);
    
}
