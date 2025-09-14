std::vector<std::vector<double>> Zeros(vector<int> dimensions){

    // throwing an error if the dimension is more than 2
    if (dimensions.size() > 2) {std::cerr << "Dimensions are a little too much";}

    // building the vector
    std::vector<std::vector<double>> temp;
    for(int i = 0; i<dimensions[0]; ++i){
        temp.emplace_back(vector<double>(dimensions[1], 0));
    };

    // returning the output
    return temp;
}

auto Zeros_complex_double(vector<int> dimensions){

    // throwing an error if the dimension is more than 2
    if (dimensions.size() > 2) {std::cerr << "Dimensions are a little too much";}

    // building the vector
    std::vector<std::vector<std::complex<double>>> temp;
    for(int i = 0; i<dimensions[0]; ++i){
        temp.emplace_back(std::vector<std::complex<double>>(dimensions[1], std::complex<double>{0,0}));
    };

    // returning the output
    return temp;
}

// =============================================================================
std::vector<std::vector<double>> Ones(vector<int> dimensions){

    // throwing an error if the dimension is more than 2
    if (dimensions.size() > 2) {std::cerr << "Dimensions are a little too much";}

    // building the vector
    std::vector<std::vector<double>> temp;
    for(int i = 0; i<dimensions[0]; ++i){
        temp.emplace_back(vector<double>(dimensions[1], 1));
    };

    // returning the output
    return temp;
}