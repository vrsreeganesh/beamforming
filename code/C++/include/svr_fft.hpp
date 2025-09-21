// =============================================================================
template<typename T>
auto fft(vector<T> inputarray){

    // building just the time thing 
    vector<complex<T>> basiswithoutfrequency(inputarray.size(), 0);
    linspace(basiswithoutfrequency, 
             0, 
             basiswithoutfrequency.size()-1, 
             basiswithoutfrequency.size());
    
    auto lambda = \
        [&basiswithoutfrequency](const complex<T> arg){
        return std::exp(-1.00 * \
                        std::complex<T>{0, 1} * \
                        2.00 * std::numbers::pi * \
                        static_cast<complex<T>>(arg) \
                        / static_cast<complex<T>>(basiswithoutfrequency.size()));
    };
    std::transform(basiswithoutfrequency.begin(),
                   basiswithoutfrequency.end(),
                   basiswithoutfrequency.begin(),
                   lambda);

    // building basis vectors
    vector<vector<complex<T>>> basisvectors;
    for(auto i = 0; i < inputarray.size(); ++i){

        // making a copy of the basis-without-frequency
        auto temp   = basiswithoutfrequency;

        // exponentiating with associated frequency
        std::transform(temp.begin(),
                       temp.end(),
                       temp.begin(),
                       [i](const auto arg1){
                        return std::pow(arg1, i);
                    });

        // pushing to end of basis vectors
        basisvectors.push_back(std::move(temp));
    }

    // building coefficient arrays
    vector<complex<double>> finaloutput(inputarray.size(), 0); 
    finaloutput.reserve(finaloutput.size());
    
    // producing inner-products
    for(int i = 0; i<inputarray.size(); ++i){
        finaloutput[i] = \
            std::inner_product(basisvectors[i].begin(),
                               basisvectors[i].end(),
                               inputarray.begin(),
                               complex<double>(0),
                               std::plus<std::complex<double>>(),
                               [&inputarray](complex<double> a, T b){
                                    return a * static_cast<complex<double>>(b) / static_cast<double>(std::sqrt(inputarray.size()));
                                });
    }

    // returning finaloutput
    return finaloutput;
}
// =============================================================================
template<typename T>
auto fft(vector<T> inputarray, size_t nfft){

    // throwing an error
    if (nfft < inputarray.size())   {std::cerr << "size-mistmatch\n";}

    // building time-only basis
    vector<complex<T>> 
    basiswithoutfrequency = linspace(static_cast<std::complex<T>>(0), 
                                     static_cast<std::complex<T>>(nfft-1), 
                                     nfft);
    auto lambda = [&basiswithoutfrequency](const complex<T> arg){
        return std::exp(-1.00 * complex<double>{0, 1} * 2.00 * \
            std::numbers::pi * static_cast<complex<T>>(arg) / \
            static_cast<complex<T>>(basiswithoutfrequency.size()));
    };
    std::transform(basiswithoutfrequency.begin(),
                   basiswithoutfrequency.end(),
                   basiswithoutfrequency.begin(),
                   lambda);

    
    // building basis vectors
    vector<vector<complex<double>>> basisvectors;
    for(auto i = 0; i < inputarray.size(); ++i){

        // making a copy of the basis-without-frequency
        vector<complex<double>> temp = basiswithoutfrequency;

        // exponentiating with associated frequency
        std::transform(temp.begin(),
                       temp.end(),
                       temp.begin(),
                       [i](const auto arg1){return std::pow(arg1, i);});

        // pushing to end of basis vectors
        basisvectors.push_back(std::move(temp));
    }

    
    // building the projection
    vector<complex<double>> finaloutput(inputarray.size(), 0); 
    finaloutput.reserve(finaloutput.size());
    #pragma omp parallel for
    for(int i = 0; i<inputarray.size(); ++i){
        // writing coefficients
        finaloutput[i] = \
            std::inner_product(basisvectors[i].begin(),
                               basisvectors[i].end(),
                               inputarray.begin(),
                               complex<double>(0),
                               std::plus<std::complex<double>>(),
                               [&nfft](const complex<double>   a,
                                  const T                 b){
                                    return a * static_cast<complex<double>>(b) / static_cast<double>(std::sqrt(nfft));
                               });
    }

    // returning finaloutput
    return finaloutput;
}

// =============================================================================
template <>
auto fft(vector<complex<double>> inputarray){

    // aliasing 
    using T = double;

    // building time-only basis-vector
    vector<complex<T>>
    basiswithoutfrequency = linspace(std::complex<T>(0), 
                                     std::complex<T>(inputarray.size()-1),
                                     inputarray.size());
    auto lambda = [&basiswithoutfrequency](const complex<T> arg){
        return std::exp(-1.00 * complex<double>{0, 1} * 2.00 * \
                        std::numbers::pi * static_cast<complex<T>>(arg) \
                        / static_cast<complex<T>>(basiswithoutfrequency.size()));
    };
    std::transform(basiswithoutfrequency.begin(),
                   basiswithoutfrequency.end(),
                   basiswithoutfrequency.begin(),
                   lambda);

    
    // building basis vectors
    vector<vector<complex<T>>> basisvectors;
    for(auto i = 0; i < inputarray.size(); ++i){

        // making a copy of the basis-without-frequency
        vector<complex<T>> temp = basiswithoutfrequency;

        // adding frequency component
        std::transform(temp.begin(),
                       temp.end(),
                       temp.begin(),
                       [i](const auto arg1){return std::pow(arg1, i);});

        // pushing to end of basis vectors
        basisvectors.push_back(std::move(temp));
    }

    
    // building the coefficients
    vector< complex<T> > finaloutput(inputarray.size(), 0); 
    finaloutput.reserve(finaloutput.size());
    for(int i = 0; i<inputarray.size(); ++i)
        finaloutput[i] = std::inner_product(basisvectors[i].begin(),
                                            basisvectors[i].end(),
                                            inputarray.begin(),
                                            std::complex<double>(0));

    // scaling down the coefficients
    std::transform(finaloutput.begin(),
                   finaloutput.end(),
                   finaloutput.begin(),
                   [&inputarray](auto argx){
                        return argx / static_cast<T>(std::sqrt(inputarray.size()));
                   });

    
    // returning finaloutput
    return finaloutput;
}

// =============================================================================
template<typename T>
auto fft(std::vector<std::vector<T>> inputMatrix, 
         int                         nfft){

    // initializing 
    std::vector<std::vector<std::complex<T>>> 
    finaloutput(inputMatrix.size(), 
                std::vector<std::complex<T>>(inputMatrix[0].size(), 0));

    // checking if we need to pad the rows
    if (inputMatrix[0].size() > nfft)   {std::cerr << "nfft < row-size\n";}
    else if (inputMatrix[0].size() < nfft)    {
        
        // creating a placeholder
        std::vector<std::vector<std::complex<T>>> 
        temp(inputMatrix.size(), 
             std::vector<std::complex<T>>(nfft, 0));

        // moving to the finaloutput
        finaloutput.clear();
        finaloutput = std::move(temp);

    }

    // filling final-output with the input-values
    for(int i = 0; i<inputMatrix.size(); ++i)
        std::copy(inputMatrix[i].begin(),
                  inputMatrix[i].end(),
                  finaloutput[i].begin());

    // performing fft
    #pragma omp parallel for
    for(auto& row: finaloutput)     {row = fft(row);}

    // returning the matrix
    return finaloutput;

}
// =============================================================================
template<>
auto fft(std::vector<std::vector<std::complex<double>>> inputMatrix, 
         int                                            nfft){

    // changing types
    using T = double;

    // initializing 
    std::vector<std::vector<std::complex<T>>> 
    finaloutput(inputMatrix.size(), 
                std::vector<std::complex<T>>(inputMatrix[0].size(), complex<T>(0)));

    // checking if we need to pad the rows
    if (inputMatrix[0].size() > nfft)   {std::cerr << "nfft < row-size\n";}
    else if (inputMatrix[0].size() < nfft)    {
        
        // creating a placeholder
        std::vector<std::vector<std::complex<T>>> 
        temp(inputMatrix.size(), 
             std::vector<std::complex<T>>(nfft, std::complex<T>(0)));

        // moving to the finaloutput
        finaloutput.clear();
        finaloutput = std::move(temp);
    }

    // filling final-output with the input-values
    for(int i = 0; i<inputMatrix.size(); ++i){
        std::copy(inputMatrix[i].begin(),
                  inputMatrix[i].end(),
                  finaloutput[i].begin());
    }

    // performing fft
    for(int i = 0; i<finaloutput.size(); ++i)
        finaloutput[i]  = std::move(fft(finaloutput[i]));

    // returning the matrix
    return finaloutput;

}
// ifft (vector) ===============================================================
template <typename T>
auto ifft(const std::vector<T> inputvector){

    // setting up data type
    using T2 = std::conditional_t<std::is_same_v<T, std::complex<float>>, 
                                  std::complex<float>, 
                                  std::complex<double>>;
    using T3 = typename T2::value_type;

    // building basis
    vector<T2> 
    basiswithoutfrequency   {linspace(static_cast<T2>(0),
                                      static_cast<T2>(inputvector.size()-1),
                                      inputvector.size())};

    // lambda for building basis without frequency
    auto lambda = \
        [&basiswithoutfrequency](const T2 arg){
            return std::exp(1.00 * T2{0, 1} * 2.00 * \
                            std::numbers::pi * arg / \
                            static_cast<T2>(basiswithoutfrequency.size()));
    };

    // building the basis without frequency
    std::transform(basiswithoutfrequency.begin(),
                   basiswithoutfrequency.end(),
                   basiswithoutfrequency.begin(),
                   lambda);

    // building basis vectors
    std::vector<std::vector<T2>> bases;
    for(int i = 0; i < inputvector.size(); ++i){

        // creating bases with frequency components
        auto basiswithfrequency = basiswithoutfrequency;
        std::transform(basiswithfrequency.begin(),
                       basiswithfrequency.end(),
                       basiswithfrequency.begin(),
                       [i](T2 argx){
                            return static_cast<T2>(std::pow(argx, static_cast<T3>(i)));
                       });

        // pushing to the basis vectors
        bases.push_back(std::move(basiswithfrequency));
    }

    // computing projections 
    std::vector<T2> projection_coefficients(inputvector.size());
    for(auto i = 0; i < bases.size(); ++i){

        // calculating inner-product
        auto temp   {std::inner_product(bases[i].begin(), bases[i].end(),
                                        inputvector.begin(),
                                        static_cast<T2>(0),
                                        std::plus<T2>(),
                                        [&inputvector](auto arg_bases, auto arg_inputvector){
                                            return static_cast<T2>(arg_bases) *         \
                                                   static_cast<T2>(arg_inputvector) /   \
                                                   static_cast<T3>(std::sqrt(inputvector.size()));
                                        })};

        // writing to the final output
        projection_coefficients[i] = std::move(temp);
    }

    // returning the coefficients
    return projection_coefficients;

}