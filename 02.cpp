#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 

void PartOneSingleLineAggregator(const char direction, const int units, int& x, int& z)
{
    if(direction == 'f')
    {
        x += units;
    }
    else if(direction == 'd')
    {
        z += units;
    }
    else if(direction == 'u')
    {
        z -= units;
    }
}

void PartTwoSingleLineAggregator(const char direction, const int units, int& x, int& z, int& aim)
{
    if(direction == 'f')
    {
        x += units;
        z += aim * units;
    }
    else if(direction == 'd')
    {
        aim += units;
    }
    else if(direction == 'u')
    {
        aim -= units;
    }
}

int main()
{
    std::ifstream file("02.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();

    int partOneX = 0;
    int partOneZ = 0;
 
    int partTwoX = 0;
    int partTwoZ = 0;
    int aim = 0;

    std::string directionPair;
    while (std::getline(buffer, directionPair, '\n')) 
    {
        const char direction = directionPair.front();
        const int units = std::stoi(&directionPair.back());

        PartOneSingleLineAggregator(direction, units, partOneX, partOneZ);
        PartTwoSingleLineAggregator(direction, units, partTwoX, partTwoZ, aim);
    }

    std::cout << "Part 1: " << partOneX << " , " << partOneZ << " : " << partOneX*partOneZ << "\n";
    std::cout << "Part 2: " << partTwoX << " , " << partTwoZ << " : " << partTwoX*partTwoZ << "\n";
}
