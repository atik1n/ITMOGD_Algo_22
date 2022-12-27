#include <iostream>
#include <stdexcept>
#include "dice.hpp"

float dice(std::string line) {
  line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
  std::replace(line.begin(), line.end(), ',', '+');

  if (std::count(line.begin(), line.end(), '(') != std::count(line.begin(), line.end(), ')')) {
    throw std::invalid_argument("Non-consistent parentheses.");
  }
  if (line.empty()) {
    throw std::invalid_argument("Incorrect or empty line.");
  }

  for (;;) {
    size_t lpar = line.find('(');
    if (lpar == std::string::npos) {
      break;
    }
    size_t rpar = line.find(')', lpar);
    std::string ss = line.substr(lpar + 1, rpar - lpar - 1);
    float value = dice(ss);
    line = line.substr(0, lpar) + std::to_string(value) + line.substr(rpar + 1, line.length());
  }

  for (;;) {
    size_t op = line.find('+');
    if (op == std::string::npos) {
      break;
    }
    return dice(line.substr(0, op)) + dice(line.substr(op + 1, line.length()));
  }

  for (;;) {
    size_t op = line.find('-');
    if (op == std::string::npos) {
      break;
    }
    return dice(line.substr(0, op)) - dice(line.substr(op + 1, line.length()));
  }

  for (;;) {
    size_t op = line.find('*');
    if (op == std::string::npos) {
      break;
    }
    return dice(line.substr(0, op)) * dice(line.substr(op + 1, line.length()));
  }

  for (;;) {
    size_t op = line.find('/');
    if (op == std::string::npos) {
      break;
    }
    return dice(line.substr(0, op)) / dice(line.substr(op + 1, line.length()));
  }

  size_t die = line.find('d');
  if (die == std::string::npos) {
    std::stof(line);
  }
  if (die == line.length()) {
    throw std::invalid_argument("Die can't have no faces.");
  }

  int count = die > 0 ? std::stoi(line.substr(0, die)) : 1;
  int faces = std::stoi(line.substr(die + 1, line.length()));
  if (faces == 0) {
    throw std::invalid_argument("Die can't have no faces.");
  }

  int result = 0;
  std::uniform_int_distribution<> distr(1, faces);
  for (int i = 0; i < count; ++i) {
    result += distr(randomGenerator);
  }
  return (float)result;
}

void testDices(int count, int faces) {
  int results[count * faces - (count - 1)];
  std::string line = std::to_string(count) + 'd' + std::to_string(faces);
  for (int & result : results) {
    result = 0;
  }
  for (int i = 0; i < TEST_TRIES; ++i) {
    results[(int)dice(line) - count] += 1;
  }

  std::cout << "Distribution of " << line << ':' << std::endl;
  for (int i = 0; i < count * faces - (count - 1); ++i) {
    std::cout << i + count << ';' << results[i] << std::endl;
  }
  std::cout << std::endl;
}

int main() {
  testDices(1, 6);
  testDices(2, 6);
  testDices(3, 6);
  testDices(1, 10);
  testDices(2, 10);
  testDices(3, 10);
  return 0;
}
