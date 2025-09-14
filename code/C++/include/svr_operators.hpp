template <typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b) {
    // Identify which is bigger
    const auto& big = (a.size() > b.size()) ? a : b;
    const auto& small = (a.size() > b.size()) ? b : a;

    std::vector<T> result = big;  // copy the bigger one

    // Add elements from the smaller one
    for (size_t i = 0; i < small.size(); ++i) {
        result[i] += small[i];
    }

    return result;
}
template <typename T>
std::vector<T>& operator+=(std::vector<T>& a, const std::vector<T>& b) {
    
    const auto& small = (a.size() < b.size()) ? a : b;
    const auto& big   = (a.size() < b.size()) ? b : a;

    // If b is bigger, resize 'a' to match
    if (a.size() < b.size())                        {a.resize(b.size());}

    // Add elements
    for (size_t i = 0; i < small.size(); ++i)       {a[i] += b[i];}

    // returning elements
    return a;
}
template <typename T>
std::vector<std::vector<T>> operator+(const std::vector<std::vector<T>>& a,
                                      const std::vector<std::vector<T>>& b)
{
    // throwing an error if dimension error occurrs
    if ((a.size() != b.size()) || (a[0].size() != b[0].size()))           {
        cout << format("a.dimensions = [{},{}], b.shape = [{},{}]\n",
            a.size(), a[0].size(), b.size(), b[0].size());
        std::cerr << "dimensions don't match\n";
    }
    

    // performing the addition
    auto temp   {a};
    for(int i = 0; i<b.size(); ++i){
        for(int j = 0; j<b[0].size(); ++j){
            temp[i][j] += b[i][j];
        }
    } 

    // retuerning 
    return temp;
}
// =============================================================================
// Aim: substracting scalar from a vector
template <typename T>
std::vector<T> operator-(const std::vector<T>& a, const T scalar){
    std::vector<T> temp(a.size());
    std::transform(a.begin(),
                   a.end(),
                   temp.begin(),
                   [scalar](T x){return (x - scalar);});
    return temp;
}
// =============================================================================
// multiplying scalar and double

auto operator*(const std::complex<double> complexscalar, const double doublescalar){
    return complexscalar * static_cast<std::complex<double>>(doublescalar);
}
auto operator*(const double doublescalar, const std::complex<double> complexscalar){
    return complexscalar * static_cast<std::complex<double>>(doublescalar);
}
auto operator*(const std::complex<double> complexscalar, const int scalar){
    return complexscalar * static_cast<std::complex<double>>(scalar);
}
auto operator*(const int scalar, const std::complex<double> complexscalar){
    return complexscalar * static_cast<std::complex<double>>(scalar);
}