#include <iostream>
#include <fstream>
#include <sstream>
#include "sumer-game.hpp"

int intDivCeil(int lhs, int rhs) {
  return (lhs + rhs - 1) / rhs;
}

std::string readFileKey(std::istream& file) {
  std::string result;
  getline(file, result);
  std::istringstream istring(result);
  while(getline(istring, result, ':')) { }
  return result;
}

template <typename T>
void getInput(T& variable) {
  while (true) {
    std::cin >> variable;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "My lord, I can't understand you. What again?" << std::endl;
    }
    else
      break;
  }
}

int saveGame(GameState& gs, const std::string& fn = GAME_DEFAULT_SAVE) {
  std::ofstream of(fn, std::ios::out | std::ios::trunc);
  if (!of.is_open()) {
    std::cerr << "Cannot open file \"" << fn << "\".";
    return -1;
  }

  of << "Round:" << gs.round << std::endl;

  of << "Wheat:" << gs.wheat << std::endl;
  of << "City area:" << gs.area << std::endl;
  of << "Population:" << gs.pop << std::endl;

  of << "Plague:" << gs.plague << std::endl;
  of << "Wheat yield:" << gs.wheatYield << std::endl;
  of << "Wheat lost by rats:" << gs.wheatLost << std::endl;
  of << "Area used for wheat:" << gs.areaUsed << std::endl;
  of << "Area cost:" << gs.areaCost << std::endl;

  of << "Population got to the city:" << gs.popGot << std::endl;
  of << "Population died from starvation:" << gs.popLostPlague << std::endl;
  of << "Population died from plague:" << gs.popLostStarve << std::endl;
  of << "Average death percent:" << gs.deathsPerRound << std::endl;

  return 0;
}

int loadGame(GameState& gs, const std::string& fn = GAME_DEFAULT_SAVE) {
  std::ifstream of(fn, std::ios::in);
  if (!of.is_open()) {
    return -1;
  }

  gs.round = std::stoi(readFileKey(of));

  gs.wheat = std::stoi(readFileKey(of));
  gs.area = std::stoi(readFileKey(of));
  gs.pop = std::stoi(readFileKey(of));

  gs.plague = std::stoi(readFileKey(of));
  gs.wheatYield = std::stoi(readFileKey(of));
  gs.wheatLost = std::stoi(readFileKey(of));
  gs.areaUsed = std::stoi(readFileKey(of));
  gs.areaCost = std::stoi(readFileKey(of));

  gs.popGot = std::stoi(readFileKey(of));
  gs.popLostStarve = std::stoi(readFileKey(of));
  gs.popLostPlague = std::stoi(readFileKey(of));
  gs.deathsPerRound = std::stof(readFileKey(of));
  return 0;
}

PlayerAction getAction(GameState& gs) {
  PlayerAction pa;
  bool error;
  for (;;) {
    std::cout << std::endl << "My lord, what do you want?" << std::endl;

    std::cout << "< We can buy " << intDivCeil(gs.wheat, gs.areaCost) << " acres at most." << std::endl;
    std::cout << "> Area to buy: ";
    getInput(pa.areaToBuy);
    std::cout << "> Area to sell: ";
    getInput(pa.areaToSell);
    std::cout << "< For everyone we will need " << gs.pop * GAME_WHEAT_PER_POP << " bushels." << std::endl;
    std::cout << "< Currently we have " << gs.wheat << " of them." << std::endl;
    std::cout << "> Wheat to use as food: ";
    getInput(pa.wheatToEat);
    std::cout << "We have people for " << gs.pop * GAME_AREA_PER_POP << " acres." << std::endl;
    std::cout << "We have wheat for " << gs.wheat * GAME_AREA_PER_WHEAT << " acres." << std::endl;
    std::cout << "Currently our area is " << gs.area << " acres." << std::endl;
    std::cout << "> Area to use for wheat: ";
    getInput(pa.areaToUse);

    error = (pa.areaToBuy < 0) || (pa.areaToSell < 0) || (pa.wheatToEat < 0) || (pa.areaToUse < 0);
    error = error || (pa.areaToSell > gs.area + pa.areaToBuy);
    int wheatToUseArea = intDivCeil(pa.areaToUse, GAME_AREA_PER_WHEAT);
    int wheatToUseTotal = pa.areaToBuy * gs.areaCost + pa.wheatToEat + wheatToUseArea;
    error = error || (wheatToUseTotal > gs.wheat);
    error = error || (intDivCeil(pa.areaToUse, GAME_AREA_PER_POP) > gs.pop);

    if (error) {
      std::cout << "My lord, but we can't do that!" << std::endl;
      std::cout << "We currently have only " << gs.pop << " peasants, ";
      std::cout << gs.wheat << " bushels of wheat and area of " << gs.area << " acres!" << std::endl;
    } else {
      break;
    }
  }
  return pa;
}

void adviserReport(GameState& gs) {
  std::cout << std::endl << "My lord, I brought some news for you";

  if (gs.round > 1) {
    std::cout << std::endl << "    ";
    std::cout << "it's year " << gs.round << " of your reign,";

    std::cout << std::endl << "    ";
    std::cout << gs.popLostStarve << " peasants died from starvation, but we got ";
    std::cout << gs.popGot << " new citizens;";

    if (gs.plague) {
      std::cout << std::endl << "    ";
      std::cout << "plague has killed " << gs.popLostPlague << " of them;";
    }

    std::cout << std::endl << "    ";
    std::cout << "this year we have " << gs.pop << " citizens;";

    std::cout << std::endl << "    ";
    std::cout << "our wheat fields yield " << gs.wheatYield * gs.areaUsed << " bushels of grain, ";
    std::cout << gs.wheatYield << " per acre;";

    std::cout << std::endl << "    ";
    std::cout << "rats eaten " << gs.wheatLost << " wheat bushels, leaving us with only " << gs.wheat;

    std::cout << std::endl << "    ";
    std::cout << "our city has area of " << gs.area << " acres;";
  } else {
    std::cout << std::endl << "    ";
    std::cout << "your reign begins today, at year " << gs.round << ';';

    std::cout << std::endl << "    ";
    std::cout << "you have " << gs.pop << " peasants, ";
    std::cout << gs.wheat << " wheat bushels and area of " << gs.area << " acres;";
  }
  std::cout << std::endl << "    ";
  std::cout << "one acre of land costs exactly " << gs.areaCost << " wheat bushels.";
  std::cout << std::endl;
}

int gameLoop(GameState& gs) {
  PlayerAction pa;
  bool first = true;
  while (gs.round < GAME_LENGTH) {
    gs.areaCost = distrAreaPrice(randomGenerator);

    adviserReport(gs);
    if (!first) {
      std::cout << "Do you want to save your progress so far, my lord (y/n): ";
      std::string input;
      getInput(input);
      if ((input == "y") || (input == "Y")) {
        return 1;
      }
      if (!(input == "n") && !(input == "N")) {
        std::cout << "I'll count that as \"no\", my lord." << std::endl;
      }
    }

    pa = getAction(gs);

    gs.wheatYield = distrYield(randomGenerator);
    gs.wheat += gs.wheatYield * pa.areaToUse;
    gs.areaUsed = pa.areaToUse;
    gs.wheat -= pa.wheatToEat;
    gs.wheat += (pa.areaToSell - pa.areaToBuy) * gs.areaCost;
    gs.wheatLost = ceil(gs.wheat * distrRats(randomGenerator));
    gs.wheat -= gs.wheatLost;

    int popEaten = intDivCeil(pa.wheatToEat, GAME_WHEAT_PER_POP);
    gs.popLostStarve = std::max(0, gs.pop - popEaten);
    float lostPerc = (float)gs.popLostStarve / (float)gs.pop;
    if (lostPerc > GAME_LOSE_DEATH_THRESH) {
      std::cout << std::endl << "I'm sorry, my lord, but our city died from starvation..." << std::endl;
      std::cout << "- - - GAME OVER / STARVATION - - -" << std::endl;
      return 0;
    }
    gs.pop -= gs.popLostStarve;
    gs.deathsPerRound += (lostPerc - gs.deathsPerRound) / (float)(gs.round + 1);

    gs.popGot = std::min(GAME_POP_GAIN, std::max(0, gs.popLostStarve / 2 + (5 - gs.wheatYield) * gs.wheat / 600 + 1));
    gs.pop += gs.popGot;

    int roll = distrPercent(randomGenerator);
    gs.plague = roll > GAME_PLAGUE_CHANCE;
    if (gs.plague) {
      gs.popLostPlague = intDivCeil(gs.pop, GAME_PLAGUE_RATIO);
      gs.pop -= gs.popLostPlague;
    }

    first = false;
    ++gs.round;
  }
  float areaPerPop = (float)gs.area / (float)gs.pop;
  if (gs.deathsPerRound > 0.33 && areaPerPop < 7) {
    std::cout << std::endl << "My lord, citizens are beginning a riot..." << std::endl;
    std::cout << "- - - GAME OVER / OVERTHROW - - -" << std::endl;
  } else if (gs.deathsPerRound > 0.10 && areaPerPop < 9) {
    std::cout << std::endl << "My lord, I think, most of the citizens want you to resign..." << std::endl;
    std::cout << "- - - GAME OVER / RESIGN - - -" << std::endl;
  } else if (gs.deathsPerRound > 0.03 && areaPerPop < 10) {
    std::cout << std::endl << "My lord, you did well!" << std::endl;
    std::cout << "- - - VICTORY / HAPPINESS - - -" << std::endl;
  } else {
    std::cout << std::endl << "Congratulations, my lord! You've made a great city!" << std::endl;
    std::cout << "- - - VICTORY / GOLDEN AGE - - -" << std::endl;
  }
  return 0;
}

int main(int argc, char* argv[]) {
  int status;
  GameState gameState;
  std::cout << "Welcome, my lord. ";
  if (argc > 2) {
    std::cout << "You made some mistakes in arguments, please, try again." << std::endl;
    return 0;
  }
  if (argc == 2) {
    std::cout << "Recovering city from \"" << argv[1] << "\"..." << std::endl;
    loadGame(gameState, argv[1]);
  }

  status = gameLoop(gameState);

  if (status == 1) {
    for(;;) {
      std::cout << "Where do you want to save your city, my lord?" << std::endl;
      std::string fileName;
      getInput(fileName);
      status = saveGame(gameState, fileName);
      if (status == -1) {
        std::cout << "I'm sorry, my lord, I can't. Let's try again. ";
      }
      break;
    }
  }

  return 0;
}
