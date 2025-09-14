template <typename T>
auto sin(vector<T> input){
    auto temp   {input};
    std::transform(input.begin(),
                   input.end(),
                   temp.begin(),
                   [](const T x){return std::sin(x);});
    return temp;
}

template <typename T>
auto sin_inplace(vector<T>& input) -> void
{
    std::transform(input.begin(),
                   input.end(),
                   input.begin(),
                   [](const T x){return std::sin(x);});
}

// =============================================================================
template <typename T>
auto cosd(T input){
    return std::cos(input * std::numbers::pi / 180); 
}