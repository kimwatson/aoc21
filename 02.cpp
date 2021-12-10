#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 

int main()
{
    std::ifstream file("02.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();

    int x = 0;
    int z = 0;

    std::string directionPair;
    while (std::getline(buffer, directionPair, '\n')) 
    {
        int distance = std::stoi(&directionPair.back());

        if(directionPair.front() == 'f')
        {
            x += distance;
        }
        else if(directionPair.front() == 'd')
        {
            z += distance;
        }
        else if(directionPair.front() == 'u')
        {
            z -= distance;
        }
    }

    std::cout << x << " , " << z << " : " << x*z << "\n";
}
