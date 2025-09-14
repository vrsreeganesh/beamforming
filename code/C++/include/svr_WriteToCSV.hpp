// template <typename T>
// void fWriteVector(const vector<T>   inputvector, 
//                   const string      filename){

//     // opening a file
//     std::ofstream fileobj(filename);
//     if (fileobj){
//         for(int i = 0; i<inputvector.size(); ++i){
//             fileobj << inputvector[i];
//             if(i!=inputvector.size()-1) {fileobj << ",";}
//             else                        {fileobj << "\n";}
//         }
//     }
// }
// =============================================================================
template <typename T>
void fWriteVector(const vector<T>&              inputvector, 
                  const string&                 filename){

    // opening a file
    std::ofstream fileobj(filename);
    if (!fileobj)   {return;}

    // writing the real parts in the first column and the imaginary parts int he second column
    if constexpr(std::is_same_v<T, std::complex<double>>    || 
                 std::is_same_v<T, std::complex<float>>     || 
                 std::is_same_v<T, std::complex<long double>>){
        for(int i = 0;  i<inputvector.size(); ++i){
            // adding entry
            fileobj << inputvector[i].real() << "+" << inputvector[i].imag() << "i";

            // adding delimiter
            if(i!=inputvector.size()-1) {fileobj << ",";}
            else                        {fileobj << "\n";}
        }
    }
    else{
        for(int i = 0; i<inputvector.size(); ++i){
            fileobj << inputvector[i];
            if(i!=inputvector.size()-1) {fileobj << ",";}
            else                        {fileobj << "\n";}
        }
    }

    // return
    return;
}
// Matrix writing ==============================================================
template <typename T>
auto fWriteMatrix(const std::vector<std::vector<T>> inputMatrix, 
                  const string                      filename){

    // opening a file 
    std::ofstream fileobj(filename);

    // writing
    if (fileobj){
        for(int i = 0; i<inputMatrix.size(); ++i){
            for(int j = 0; j<inputMatrix[0].size(); ++j){
                fileobj << inputMatrix[i][j];
                if (j!=inputMatrix[0].size()-1)     {fileobj << ",";}
                else                                {fileobj << "\n";}
            }
        }
    }
    else{
        cout << format("File-write to {} failed\n", filename);
    }

}

template <>
auto fWriteMatrix(const std::vector<std::vector<std::complex<double>>>  inputMatrix, 
                  const string                                          filename){

    // opening a file 
    std::ofstream fileobj(filename);

    // writing
    if (fileobj){
        for(int i = 0; i<inputMatrix.size(); ++i){
            for(int j = 0; j<inputMatrix[0].size(); ++j){
                fileobj << inputMatrix[i][j].real() << "+" << inputMatrix[i][j].imag() << "i";
                if (j!=inputMatrix[0].size()-1)     {fileobj << ",";}
                else                                {fileobj << "\n";}
            }
        }
    }
    else{
        cout << format("File-write to {} failed\n", filename);
    }
}















//  AN EXAMPLE OF USING is_same_v<T, std::complex<double>>======================

// #include <complex>
// #include <fstream>
// #include <vector>
// #include <type_traits>

// template <typename T>
// void fWriteVector(const std::vector<T>& inputvector, const std::string& filename) {
//     std::ofstream fileobj(filename, std::ios::out | std::ios::trunc);
//     if (fileobj) {
//         for (size_t i = 0; i < inputvector.size(); ++i) {
//             if constexpr (std::is_same_v<T, std::complex<double>> ||
//                           std::is_same_v<T, std::complex<float>>) {
//                 // write as "real,imag"
//                 fileobj << inputvector[i].real() << "," << inputvector[i].imag();
//             } else {
//                 // normal types (double, int, etc.)
//                 fileobj << inputvector[i];
//             }

//             if (i != inputvector.size() - 1)
//                 fileobj << ",";
//             else
//                 fileobj << "\n";
//         }
//     }
// }
