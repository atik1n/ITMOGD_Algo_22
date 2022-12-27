#ifndef ALGOLABS_DICE_HPP
#define ALGOLABS_DICE_HPP

#include <string>
#include <random>

#define TEST_TRIES 10000

std::random_device rd;
std::mt19937 randomGenerator(rd());

float dice(std::string);

#endif //ALGOLABS_DICE_HPP
