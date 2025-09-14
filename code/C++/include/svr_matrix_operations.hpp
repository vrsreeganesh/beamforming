// =============================================================================
template <typename T>
auto dotproduct(const vector<T> argx,
				const vector<T> argy)
{
	// dimension checks
	if (argx.size() != argy.size())	{std::cerr << "size disparity\n";}	

	// accumulating
	T	temp	= 0;
	for(int i = 0; i<argx.size(); ++i){

		if constexpr(std::is_same_v<T, std::complex<double>> || 
					 std::is_same_v<T, std::complex<float>> || 
					 std::is_same_v<T, std::complex<long double>>){
			temp += std::conj(argx[i]) * argy[i];
		}
		else{
			temp += argx[i] * argy[i];
		}
	}
	

	return temp;
}