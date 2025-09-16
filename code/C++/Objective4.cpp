// =============================================================================
#include "include/before.hpp"
// main-file ===================================================================
int main(){

    // starting timer
    auto logfile    {string("logfile.csv")};
    Timer timer(logfile);

    // init-variables
    auto f                  {2000};
    auto m                  {static_cast<double>(32)};
    auto angle              {135};
    auto c                  {1500};
    auto lambda             {static_cast<double>(c)/static_cast<double>(f)};
    auto x                  {lambda/2};
    auto d                  {x * cosd(angle)/c};
    
    // bringing about the natural delay
    auto matrix             {vector<complex<double>>(m, complex<double>(0))};
    for(auto sensorindex = 0; sensorindex < m; ++sensorindex){
        matrix[sensorindex] = \
            (1.00/static_cast<double>(m)) * \
            std::exp(-1.00 * 1i * 2.00 * \
                     std::numbers::pi * f * (sensorindex) * d);
    }
    
    // bringing the delay in frequency region
    auto delaycolumn    = vector<complex<double>>(m, complex<double>(0));
    auto anglematrix    = vector<double>(181, 0);

    // calculating
    for(int testangle = 0; testangle < 181; ++testangle){
        
        auto testd  {x * cosd(testangle)/c};

        for(int sensorindex = 0; sensorindex < m; ++sensorindex)
            delaycolumn[sensorindex]  = \
                std::exp(1.00 * 1i * 2.00 * \
                         std::numbers::pi * f * sensorindex * testd);

        // performing inner-product
        anglematrix[testangle] = \
            std::abs(std::inner_product(matrix.begin(),
                                        matrix.end(),
                                        delaycolumn.begin(),
                                        complex<double>{0}));

    }

    // producing angle axis
    auto angleaxis  {linspace(0, 180, 181)};

    // saving the tensors
    fWriteVector(angleaxis,     "../Figures/angleaxis-Objective4.csv");
    fWriteVector(anglematrix,   "../Figures/anglematrix-Objective4.csv");

    // return
    return(0);
    
}