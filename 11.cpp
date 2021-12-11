#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream> 

const auto ARRAY_WIDTH = 10;
const auto WHEN_FLASH_OCCURS = 9; 
const auto STEPS = 100;

void ReadFileIntoArray(std::vector<int>& array) 
{
    std::ifstream file("11.txt");
    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string line;
    while (std::getline(buffer, line, '\n')) 
    {
        for (const char& c : line) 
        {
            array.push_back(c - '0');
        }
    }
}

void IncrementElementXNeighbours(int element, std::vector<int>& array)
{
    // -x neighbour
    if(element % ARRAY_WIDTH > 0)
    {
        ++ array[element-1];
    }

    // +x neighbour
    if(element % ARRAY_WIDTH < ARRAY_WIDTH-1)
    {
        ++ array[element+1];
    }
}


void IncrementElementNeighbours(int element, std::vector<int>& array)
{
    // x-1 and x+1 of element
    IncrementElementXNeighbours(element, array);

    // -y [x-1, x, x+1]
    if(element >= ARRAY_WIDTH)
    {
        auto yElement = element-ARRAY_WIDTH;
        ++ array[yElement];
        IncrementElementXNeighbours(yElement, array);
    }

    // +y [x-1, x, x+1]
    if(element < array.size() - ARRAY_WIDTH)
    {
        auto yElement = element+ARRAY_WIDTH;
        ++ array[yElement];
        IncrementElementXNeighbours(yElement, array);
    }
}

int ProcessStepAndCalculateFlashes(std::vector<int>& array)
{
    // increase each octopus energy level
    for (auto& i : array)
    {
        ++i;
    }

    std::vector<bool> hasFlashed(array.size(), false);

    auto flashesExhausted = false;

    while (!flashesExhausted)
    {
        // assume no more flashes unless proven otherwise
        flashesExhausted = true;

        for (auto i = 0; i < array.size(); ++i)
        {
            if(array[i] > WHEN_FLASH_OCCURS && !hasFlashed[i])
            {
                IncrementElementNeighbours(i, array);
                hasFlashed[i] = true;

                // we need to do another loop
                flashesExhausted = false;
            }
        } 
    }

    auto flashes = 0;

    for (auto i = 0; i < array.size(); ++i)
    {
        if(hasFlashed[i])
        {
            array[i] = 0;
            ++ flashes;
        }  
    }

    return flashes;
}

int main()
{
    // array is cartesian quadrant iv
    std::vector<int> array;
    
    ReadFileIntoArray(array);

    // do the steps and count flashes 
    auto flashes = 0;
    for (auto i = 0; i < STEPS; ++i)
    {
        flashes += ProcessStepAndCalculateFlashes(array);
    }

    // calculate step when all flash accumulating the steps already performed
    auto stepWhenAllFlash = STEPS;
    while(true)
    {
        ++ stepWhenAllFlash;

        if(ProcessStepAndCalculateFlashes(array) == array.size())
        {
            break;
        }
    }
 
    std::cout << "Flashes: " << flashes << "\n";
    std::cout << "Step When All Flash: " << stepWhenAllFlash << "\n";
}
