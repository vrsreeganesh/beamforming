template <size_t Axis, typename T>
auto sum(const vector<vector<T>>& inputMatrix){

	// asserting dimensions for now
	static_assert(Axis == 0 || Axis == 1, "Axis must be 0 or 1\n");

	// splitting based on dimensions
	if constexpr (Axis == 0){
		auto returnTensor	{std::vector<T>(inputMatrix[0].size(), 0.00)};
		for(auto row = 0; row < inputMatrix.size(); ++row){
			std::transform(inputMatrix[row].begin(), 
						   inputMatrix[row].end(),
						   returnTensor.begin(),
						   returnTensor.begin(),
						   std::plus<T>{});
		}
		return returnTensor;
	}
	else{
		auto returnTensor	{std::vector<std::vector<T>>(inputMatrix.size(),
														 std::vector<T>(1, 0.00))};
		for(auto row = 0; row < inputMatrix.size(); ++row){
			auto temp	{std::accumulate(inputMatrix[row].begin(),
										 inputMatrix[row].end(),
										 T{0})};
			returnTensor[row][0]	= temp;
		}
		return returnTensor;
	}
}