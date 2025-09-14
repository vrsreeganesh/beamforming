template<typename T>
constexpr auto repmat(const vector<vector<T>>&    input,
            const vector<int>           dimensions){

    // calculating resulting dimensions
    auto numrows    {static_cast<int>(input.size())     * dimensions[0]};
    auto numcols    {static_cast<int>(input[0].size())  * dimensions[1]};

    // creating new matrix
    vector<vector<T>>   finaloutput;
    vector<T>         temp;
    auto sourcerow  {-1};
    auto sourcecol  {-1};
    for(int i = 0; i<numrows; ++i){
        temp.clear();
        for(int j = 0; j<numcols; ++j){
            sourcerow = i % static_cast<int>(input.size());
            sourcecol = j % static_cast<int>(input[0].size());
            temp.push_back(input[sourcerow][sourcecol]);
        }
        finaloutput.push_back(temp);
    }

    // returning the final output
    return finaloutput;
    
};

template <typename T>
constexpr auto repmat(const vector<T>&            input,
            const vector<int>           dimensions){

    // calculating resulting dimensions
    auto numrows    {static_cast<int>(dimensions[0])};
    auto numcols    {static_cast<int>(input.size())  * dimensions[1]};

    // creating new matrix
    vector<vector<T>>   finaloutput;
    vector<T>           temp;

    // filling up the vector
    auto sourcerow  {-1};
    auto sourcecol  {-1};
    for(int i = 0; i<numrows; ++i){
        temp.clear();
        for(int j = 0; j<numcols; ++j){
            sourcerow = i % 1;
            sourcecol = j % static_cast<int>(input.size());
            temp.push_back(input[sourcecol]);
        }
        finaloutput.push_back(temp);
    }

    // returning the final output
    return finaloutput;
    
};