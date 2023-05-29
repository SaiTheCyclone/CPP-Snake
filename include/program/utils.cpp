#include <cctype>
#include <random>
#include <string>
#include <string_view>
#include <vector>

bool isCStrInteger(std::string_view str)
{
    for (uint i{ 0 }; i < str.length(); ++i)
    {
        if (std::isdigit(str[i])) continue;
        else return false;
    }
    return true;
}

// Check if 2 coordinates are overlapping
bool isOverlappingXY(std::vector<int> coordinates1,
    std::vector<int> coordinates2)
{
    return coordinates1 == coordinates2;
}

std::vector<int> randomizeCoordinates(int winRatio)
{
    std::random_device random{};
    std::default_random_engine generator{ random() };
    std::uniform_int_distribution<int> distributeX{ 2, 2*winRatio-2 };
    std::uniform_int_distribution<int> distributeY{ 2, winRatio-2 };
    return { distributeX(generator), distributeY(generator) };
}
