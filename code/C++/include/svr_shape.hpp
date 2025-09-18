// returning shape as vector ===================================================
template <typename T>
auto shape(const T& inputTensor){

	using U = std::decay_t<T>;

	// type-traits checking
	if constexpr (std::is_same_v<U, std::vector<double>> 			|| 
				  std::is_same_v<U, std::vector<float>> 			|| 
				  std::is_same_v<U, std::vector<int>>				||
				  std::is_same_v<U, std::vector<complex<double>>> 	|| 
				  std::is_same_v<U, std::vector<complex<float>>> 	|| 
				  std::is_same_v<U, std::vector<complex<int>>>		||
				  std::is_same_v<U, std::string>){
		return std::vector<int>{static_cast<int>(inputTensor.size())};
	}
	else if constexpr (std::is_same_v<U, std::vector<std::vector<double>>> ||
					   std::is_same_v<U, std::vector<std::vector<float>>> ||
					   std::is_same_v<U, std::vector<std::vector<int>>> ||
					   std::is_same_v<U, std::vector<std::vector<std::complex<double>>>> ||
					   std::is_same_v<U, std::vector<std::vector<std::complex<float>>>> ||
					   std::is_same_v<U, std::vector<std::vector<std::complex<int>>>>){
		return std::vector<int>{static_cast<int>(inputTensor.size()),
								static_cast<int>(inputTensor[0].size())};
	}
}
