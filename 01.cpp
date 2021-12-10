#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 

int main()
{
    std::ifstream file("01.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();

    int lastLowestDepth = -1;
    int increasedDepthCount = 0;

    std::string depthString;
    while (std::getline(buffer, depthString, '\n')) 
    {
        int depth = std::stoi(depthString);

        if(depth > lastLowestDepth && lastLowestDepth > 0)
        {
            ++ increasedDepthCount;
        } 

        lastLowestDepth = depth;
    }

    std::cout << increasedDepthCount << "\n";
}
