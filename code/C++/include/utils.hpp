// =============================================================================
#include "svr_WriteToCSV.hpp"
// =============================================================================
template <typename F, typename R>
constexpr auto fElementWise(F&& func, R& range){
    std::transform(std::begin(range),
                   std::end(range),
                   std::begin(range),
                   std::forward<F>(func));
    // return range;
}
// =============================================================================
#include "svr_repmat.hpp"
// =============================================================================
auto SineElementWise(auto& input, auto constantvalue){
    for(auto& x: input) {x = std::sin(constantvalue * x);}
    // replace this with std::transform
};
// =============================================================================
#include "svr_linspace.hpp"
// =============================================================================
#include "svr_fft.hpp"
// =============================================================================
template <typename T>
auto abs(vector<complex<T>> inputvector){
    vector<T> temp(inputvector.size(), 0);
    std::transform(temp.begin(), 
                   temp.end(), 
                   temp.begin(),
                   [](T a){return std::abs(a);});
    return temp;
}
// =============================================================================
#include "svr_rand.hpp"
// =============================================================================
#include "svr_operator_star.hpp"
// =============================================================================
#include "svr_operators.hpp"
// =============================================================================
#include "svr_tensor_inits.hpp"
// =============================================================================
#include "svr_sin.hpp"
// =============================================================================
#include "svr_slice.hpp"
// =============================================================================
#include "svr_matrix_operations.hpp"
// =============================================================================
#include <boost/type_index.hpp>
template <typename T>
auto type(T inputarg){
    std::cout << boost::typeindex::type_id_with_cvr<decltype(inputarg)>().pretty_name()<< "\n";
}
// =============================================================================
#include "svr_shape.hpp"
// =============================================================================
#include "svr_sum.hpp"
