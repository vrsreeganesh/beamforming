template<typename T>
auto slice(const std::vector<std::vector<T>>&   inputMatrix, 
           vector<int>                          arglist)
{
    
    // updating rows and columns
    if (arglist[0] == -1)       {arglist[0] = 0;}
    else if(arglist[0] == -2)   {arglist[0] = inputMatrix.size()-1;}
    if (arglist[1] == -1)       {arglist[1] = 0;}
    else if(arglist[1] == -2)   {arglist[1] = inputMatrix.size()-1;}
    if (arglist[2] == -1)       {arglist[2] = 0;}
    else if(arglist[2] == -2)   {arglist[2] = inputMatrix[0].size()-1;}
    if (arglist[3] == -1)       {arglist[3] = 0;}
    else if(arglist[3] == -2)   {arglist[3] = inputMatrix[0].size()-1;}

    // storing dimension values
    int rowsize    {arglist[1] - arglist[0] + 1};
    int colsize    {arglist[3] - arglist[2] + 1};

    // building the final-output matrix
    std::vector<std::vector<T>> finaloutput;
    for(int row = arglist[0]; row <= arglist[1]; ++row){

        // creating empty sub-row
        vector<T> temp(colsize, 0);
        
        // copying corrresponding region to subrow
        std::copy(inputMatrix[row].begin() + arglist[2],
                  inputMatrix[row].begin() + arglist[3]+1,
                  temp.begin());
 
        // pushing to final output
        finaloutput.push_back(std::move(temp));
    }

    // returning the final output
    return finaloutput;
}