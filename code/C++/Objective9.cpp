// =============================================================================
#include "include/before.hpp"
// main-file ===================================================================
int main(){

    // starting timer
    auto logfile    {string("../csv-files/logfile-Objective9.csv")};
    Timer timer(logfile);

    // Initializing the variables
    auto f                      {2000.00};
    auto Fs                     {12800.00};
    auto Ts                     {1.00/Fs};
    auto N                      {128};
    auto m                      {32};
    auto angle                  {60.00};
    auto c                      {1500.00};
    auto lambda                 {c/f};
    auto x                      {lambda/2};
    auto d                      {x * cosd(angle)/c};
    auto snr                    {4};
    auto snr_weight             {std::pow(10, -1 * snr * 0.05)};
    auto t                      {linspace(0.00, (N-1)*Ts, N)};
    auto matrix                 {Zeros({m, N})};


    // ULA signal simulation 
    auto y              {sin(2 * std::numbers::pi * f * t)};
    for(auto sensor_index = 0; sensor_index < m; ++sensor_index){
        matrix[sensor_index] = sin(2.00 * std::numbers::pi * f * (t - static_cast<double>(sensor_index) * d));
    }
    auto new_mat        {matrix + snr_weight * rand({m, N})};
    

    // Moving signal to fourier-bases
    auto& nfft      {N};
    auto fend       {static_cast<double>((nfft-1)*Fs/nfft)};
    auto waxis      {linspace(0.00, fend, nfft)};
    auto Fourier    {fft(new_mat, nfft)};


    // Choosing the frequency row
    auto index      {static_cast<int>(static_cast<double>(f * nfft)/static_cast<double>(Fs))};
    auto f_mat      {slice(Fourier, {-1, -2, index, index})};

    
    // Building and applying chebyshev window
    auto cheb_window    {vector<double>{0.4439, 0.2433, 0.3035, 0.3684, 0.4367, 
                                        0.5072, 0.5785, 0.6490, 0.7170, 0.7809, 
                                        0.8392, 0.8904, 0.9330, 0.9660, 0.9886, 
                                        1.0000, 1.0000, 0.9886, 0.9660, 0.9330, 
                                        0.8904, 0.8392, 0.7809, 0.7170, 0.6490, 
                                        0.5785, 0.5072, 0.4367, 0.3684, 0.3035, 
                                        0.2433, 0.4439}};
    
    std::transform(f_mat.begin(), f_mat.end(),
                   cheb_window.begin(),
                   f_mat.begin(),
                   [](auto argx, auto argy){
                    return vector<complex<double>>{argx[0] * argy};
                   });

    
    // Beamforming
    auto angle_matrix   {vector<double>(181, 0)};
    auto delay_column   {vector<complex<double>>(32, 0)};

    for(auto test_angle = 0; test_angle < 181; ++test_angle){
        
        auto test_d         {x * cosd(test_angle)/c};
        
        for(auto sensor_index = 0; sensor_index < m; ++sensor_index)
            delay_column[sensor_index]  = \
                std::exp(1i * 2.00 * std::numbers::pi * f * sensor_index * test_d);
        
        angle_matrix[test_angle] = \
            std::abs(std::inner_product(f_mat.begin(), f_mat.end(),
                                        delay_column.begin(), 
                                        complex<double>(0),
                                        std::plus<complex<double>>(),
                                        [](auto argx, auto argy){
                                            return argx[0] * argy;
                                        }));
    }

    
    // saving the tensors
    auto angle_axis     {linspace(0.0, 180.0, 181)};
    fWriteVector(angle_axis,    "../csv-files/angle-axis-Objective9.csv");
    fWriteVector(angle_matrix,  "../csv-files/angle-matrix-Objective9.csv");
    
    
    // return
    return(0);
    
}
