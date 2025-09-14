// scalar * vector =============================================================
template <typename T>
auto operator*(T                    scalar, 
               const vector<T>&     inputvector){
    vector<T> temp(inputvector.size());
    std::transform(inputvector.begin(), 
                   inputvector.end(), 
                   temp.begin(), 
                   [&scalar](T x){return scalar * x;});
    return temp;
}
// vector * scalar =============================================================
template <typename T>
auto operator*(const vector<T>& inputvector, 
               T                scalar){
    vector<T> temp(inputvector.size());
    std::transform(inputvector.begin(), inputvector.end(), temp.begin(), [&scalar](T x){return scalar * x;});
    return temp;
}
// scalar * matrix =============================================================
template <typename T>
auto operator*(T                                    scalar, 
               const std::vector<std::vector<T>>&   inputMatrix){
    std::vector<std::vector<T>> temp    {inputMatrix};
    for(int i = 0; i<inputMatrix.size(); ++i){
        std::transform(inputMatrix[i].begin(),
                       inputMatrix[i].end(),
                       temp[i].begin(),
                       [&scalar](T x){return scalar * x;});
    }
    return temp;
}
// scalar * matrix =============================================================
template <typename T1, typename T2>
auto operator*(T1 scalar, const std::vector<std::vector<T2>>& inputMatrix){
    std::vector<std::vector<T2>> temp    {inputMatrix};
    for(int i = 0; i<inputMatrix.size(); ++i){
        std::transform(inputMatrix[i].begin(),
                       inputMatrix[i].end(),
                       temp[i].begin(),
                       [&scalar](T2 x){return static_cast<T2>(scalar) * x;});
    }
    return temp;
}
// matrix * matrix =============================================================
template <typename T>
auto operator*(const std::vector<std::vector<T>>& matA,
               const std::vector<std::vector<T>>& matB)
{

    // throwing error
    if (matA.size() != matB.size() || matA[0].size() != matB[0].size())     {std::cerr << "size issues\n";}

    // creating placeholder
    auto temp   {matA};

    // performing multiplication
    for(int i = 0; i<matA.size(); ++i){
        for(int j = 0; j<matA[0].size(); ++j){
            temp[i][j] *= matB[i][j];
        }
    }

    // returning 
    return temp;
}
// matrix-multiplication =======================================================
template <typename T1, typename T2>
auto matmul(const std::vector<std::vector<T1>>& matA,
            const std::vector<std::vector<T2>>& matB)
{

    // throwing error
    if (matA[0].size() != matB.size())      {std::cerr << "dimension-mismatch \n";}

    // getting result-type
    using ResultType    = decltype(std::declval<T1>() * std::declval<T2>() + \
                                   std::declval<T1>() * std::declval<T2>() );

    // creating aliasses
    auto finalnumrows  {matA.size()};
    auto finalnumcols  {matB[0].size()};

    // creating placeholder
    auto rowcolproduct  = [&](auto rowA, auto colB){
        ResultType temp   {0};
        for(int i = 0; i < matA.size(); ++i)    {temp += static_cast<ResultType>(matA[rowA][i]) + static_cast<ResultType>(matB[i][colB]);}
        return temp;
    };

    // producing row-column combinations
    std::vector<std::vector<ResultType>> finaloutput(finalnumrows, std::vector<ResultType>(finalnumcols));
    for(int row = 0; row < finalnumrows; ++row){for(int col = 0; col < finalnumcols; ++col){finaloutput[row][col]   = rowcolproduct(row, col);}}

    // // // making a scalar out of that one
    // PRINTLINE PRINTLINE PRINTLINE PRINTLINE PRINTLINE PRINTLINE 
    // cout << format("\t\t finaloutput.shape = {}, {}\n", finaloutput.size(), finaloutput[0].size());
    // if (finaloutput.size() == 1 && finaloutput[0].size() == 1)  {return finaloutput[0][0];}

    // returning 
    return finaloutput;
}
// =============================================================================
