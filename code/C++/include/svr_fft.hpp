template<typename T>
auto fft(vector<T> inputarray){

    // building just the time thing 
    vector<complex<T>> basiswithoutfrequency(inputarray.size(), 0);
    linspace(basiswithoutfrequency, 0, basiswithoutfrequency.size()-1, basiswithoutfrequency.size());
    
    auto lambda = [&basiswithoutfrequency](const complex<T> arg){
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
                       [i](const auto arg1){return std::pow(arg1, i);});

        // pushing to end of basis vectors
        basisvectors.push_back(std::move(temp));
    }

    // building the projection
    vector<complex<T>> finaloutput(inputarray.size(), 0); 
    finaloutput.reserve(finaloutput.size());
    
    // producing inner-products
    for(int i = 0; i<inputarray.size(); ++i){

        // multiplying each-basis vector with input vector
        vector<complex<T>> temp(inputarray.size(), complex<T>{0,0});
        std::ranges::transform(basisvectors[i],
                               inputarray,
                               temp.begin(),
                               [](const auto x, const auto y){return x * y;});

        // summing them up to produce the dotproduct
        auto coefficient = std::accumulate(temp.begin(),
                                           temp.end(),
                                           complex<T>{0,0});

        // writing to final output
        finaloutput[i] = coefficient;
    }

    // returning finaloutput
    return finaloutput;
}

template<typename T>
auto fft(vector<T> inputarray, size_t nfft){

    // throwing an error
    if (nfft < inputarray.size())   {std::cerr << "size-mistmatch\n";}

    // building just the time thing 
    vector<complex<T>> 
    basiswithoutfrequency = linspace(static_cast<std::complex<T>>(0), 
                                     static_cast<std::complex<T>>(nfft-1), 
                                     nfft);
    
    auto lambda = [&basiswithoutfrequency](const complex<T> arg){
        return std::exp(-1.00 * complex<double>{0, 1} * 2.00 * std::numbers::pi * static_cast<complex<T>>(arg) / static_cast<complex<T>>(basiswithoutfrequency.size()));
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

        // exponentiating with associated frequency
        std::transform(temp.begin(),
                       temp.end(),
                       temp.begin(),
                       [i](const auto arg1){return std::pow(arg1, i);});

        // pushing to end of basis vectors
        basisvectors.push_back(std::move(temp));
    }

    // building the projection
    vector< complex<T> > finaloutput(inputarray.size(), 0); 
    finaloutput.reserve(finaloutput.size());
    #pragma omp parallel for
    for(int i = 0; i<inputarray.size(); ++i){

        // multiplying each-basis vector with input vector
        vector<complex<T>> temp(inputarray.size(), complex<T>{0,0});
        std::ranges::transform(basisvectors[i],
                               inputarray,
                               temp.begin(),
                               [](const auto x, const auto y){return x * y;});

        // summing them up to produce the dotproduct
        auto coefficient = std::accumulate(temp.begin(),
                                           temp.end(),
                                           complex<T>{0,0});

        // writing to final output
        finaloutput[i] = coefficient;
    }

    // returning finaloutput
    return finaloutput;
}

// =============================================================================
template <>
auto fft(vector<complex<double>> inputarray){

    // aliasing 
    using T = double;

    // building just the time thing 
    vector<complex<T>> basiswithoutfrequency(inputarray.size(), 0);
    // linspace(basiswithoutfrequency, 0, basiswithoutfrequency.size()-1, basiswithoutfrequency.size());
    basiswithoutfrequency = linspace(std::complex<T>(0), 
                                     std::complex<T>(basiswithoutfrequency.size()-1),
                                     basiswithoutfrequency.size());
    
    auto lambda = [&basiswithoutfrequency](const complex<T> arg){
        return std::exp(-1.00 * complex<double>{0, 1} * 2.00 * std::numbers::pi * static_cast<complex<T>>(arg) / static_cast<complex<T>>(basiswithoutfrequency.size()));
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

        // exponentiating with associated frequency
        std::transform(temp.begin(),
                       temp.end(),
                       temp.begin(),
                       [i](const auto arg1){return std::pow(arg1, i);});

        // pushing to end of basis vectors
        basisvectors.push_back(std::move(temp));
    }

    // building the projection
    vector< complex<T> > finaloutput(inputarray.size(), 0); 
    finaloutput.reserve(finaloutput.size());
    #pragma omp parallel for
    for(int i = 0; i<inputarray.size(); ++i){

        // multiplying each-basis vector with input vector
        vector<complex<T>> temp(inputarray.size(), complex<T>{0,0});
        std::ranges::transform(basisvectors[i],
                               inputarray,
                               temp.begin(),
                               [](const auto x, const auto y){return x * y;});

        // summing them up to produce the dotproduct
        auto coefficient = std::accumulate(temp.begin(),
                                           temp.end(),
                                           complex<T>{0,0});

        // writing to final output
        finaloutput[i] = coefficient;
    }

    // returning finaloutput
    return finaloutput;
}

// =============================================================================
template<typename T>
auto fft(std::vector<std::vector<T>> inputMatrix, 
         int                         nfft){

    // initializing 
    std::vector<std::vector<std::complex<T>>> finaloutput(inputMatrix.size(), 
                                                          std::vector<std::complex<T>>(inputMatrix[0].size(), 0));

    // checking if we need to pad the rows
    if (inputMatrix[0].size() > nfft)   {std::cerr << "nfft < row-size\n";}
    else if (inputMatrix[0].size() < nfft)    {
        
        // creating a placeholder
        std::vector<std::vector<std::complex<T>>> temp(inputMatrix.size(), std::vector<std::complex<T>>(nfft, 0));

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
    // for(auto& row: finaloutput)     {row = fft(row);}
    for(int i = 0; i<finaloutput.size(); ++i){
        auto temp   {fft(finaloutput[i])};
        finaloutput[i]  = std::move(temp);
    }

    // returning the matrix
    return finaloutput;

}