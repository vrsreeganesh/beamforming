// =============================================================================
#include "include/before.hpp"
// main-file ===================================================================
int main(){

    // starting timer
    auto logfile    {string("../csv-files/logfile-Objective8.csv")};
    Timer timer(logfile);

    // init-variables
    auto angle              {120};
    auto f                  {2000};
    auto Fs                 {12800};
    auto Ts                 {1.00/static_cast<double>(Fs)};
    auto c                  {1500};
    
    auto m                  {32};
    auto N                  {256};
    auto t                  {linspace(0.0, (N-1)*Ts, N)};

    auto lambda             {static_cast<double>(c)/2000};
    auto x                  {lambda/2.00};
    auto d                  {x * cosd(static_cast<double>(angle))/static_cast<double>(c)};
    auto matrix             {Zeros({m, N})};

    // far-field signal simulation
    auto& xaxis             {t};
    for(auto sensor_index = 0; sensor_index < m; ++sensor_index)
        matrix[sensor_index]    = \
            sin(2.00 * std::numbers::pi * static_cast<double>(f) * (t - sensor_index * d));

    // adding gaussian noise to sensor-outputs
    auto snr                {2.00};
    auto snr_weight         {std::pow(10, -1 * snr * 0.05)};
    auto new_mat            {matrix + snr_weight * rand({m, N})};

    // Performing a basis-change
    auto& nfft              {N};
    auto fend               {static_cast<double>((nfft-1)*Fs)/static_cast<double>(nfft)};
    auto waxis              {linspace(0.00, fend, nfft)};
    auto Fourier            {fft(new_mat, nfft)};

    // Beamforming
    auto delay_column       {vector<complex<double>>(m, static_cast<complex<double>>(0.00))};
    auto frequency_inter    {Fs/N};
    auto f_mat              {vector<complex<double>>(m, 0.00)};
    auto angle_matrix       {Zeros({N, 181})};
    auto frequency_matrix   {Zeros({9, 180})};
    auto index              {0};

    for(auto sweep_angle = 1; sweep_angle < 181; ++sweep_angle){
        for(auto f_sweep = 1000.00; f_sweep <= 3000.00; f_sweep += 1.00){

            // extracting frequency-indices
            index   = static_cast<double>(f * N)/static_cast<double>(Fs);
            auto temp   = slice(Fourier, {-1, -2, index, index});
            std::transform(temp.begin(), temp.end(), 
                           f_mat.begin(),
                           [](auto argx){return argx[0];});

            // building delay-vector
            for(auto sensor_index = 0; sensor_index < m ; ++sensor_index)
                delay_column[sensor_index]  = \
                    std::exp(1i * sensor_index * 2.00 * \
                             std::numbers::pi * f * (x/c) * \
                             cosd(sweep_angle));

            // writing to frequency-matrix
            auto row_target     {static_cast<size_t>(f/250) - 3};
            frequency_matrix[row_target][sweep_angle]   = \
                std::abs(std::inner_product(f_mat.begin(),
                                            f_mat.end(),
                                            delay_column.begin(),
                                            complex<double>(0.00),
                                            std::plus<complex<double>>(),
                                            [](auto argx, auto argy){
                                                return argx * argy;
                                            }));
        }
    }

    // saving assets
    auto angle_axis     {linspace(1, 180, 180)};
    auto sum_matrix     {sum<0>(frequency_matrix)};
    fWriteVector(angle_axis, "../csv-files/angle_axis-Objective8.csv");
    fWriteVector(sum_matrix, "../csv-files/sum_matrix-Objective8.csv");
    
    // return
    return(0);
    
}
