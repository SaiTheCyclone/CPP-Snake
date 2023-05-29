#pragma once

#include <string_view>
#include <vector>

bool isCStrInteger(std::string_view str); 
bool isOverlappingXY(std::vector<int> coordinates1,
    std::vector<int> coordinates2);
std::vector<int> randomizeCoordinates(int winRatio);
