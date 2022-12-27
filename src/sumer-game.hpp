#ifndef ALGOLABS_SUMER_GAME_HPP
#define ALGOLABS_SUMER_GAME_HPP

#include <random>

#define GAME_DEFAULT_SAVE "save/state.sav"

#define GAME_RATS_MIN 0.0f
#define GAME_RATS_MAX 0.07f
#define GAME_YIELD_MIN 1
#define GAME_YIELD_MAX 6
#define GAME_AREA_PRICE_MIN 17
#define GAME_AREA_PRICE_MAX 26
#define GAME_POP_GAIN 50
#define GAME_PLAGUE_CHANCE 15
#define GAME_PLAGUE_RATIO 2
#define GAME_AREA_PER_POP 10
#define GAME_AREA_PER_WHEAT 2
#define GAME_WHEAT_PER_POP 20
#define GAME_LENGTH 10
#define GAME_LOSE_DEATH_THRESH 0.45f

#define GAME_START_WHEAT 2800
#define GAME_START_AREA 1000
#define GAME_START_POP 100

std::uniform_real_distribution<> distrRats(GAME_RATS_MIN, GAME_RATS_MAX);
std::uniform_int_distribution<> distrYield(GAME_YIELD_MIN, GAME_YIELD_MAX);
std::uniform_int_distribution<> distrAreaPrice(GAME_AREA_PRICE_MIN, GAME_AREA_PRICE_MAX);
std::uniform_int_distribution<> distrPercent(1, 100);

std::random_device rd;
std::mt19937 randomGenerator(rd());

struct GameState {
  int round = 1;

  int wheat = GAME_START_WHEAT;
  int area = GAME_START_AREA;
  int pop = GAME_START_POP;

  bool plague = false;
  int wheatYield = 0;
  int wheatLost = 0;
  int areaUsed = 0;
  int areaCost = 0;

  int popGot = 0;
  int popLostStarve = 0;
  int popLostPlague = 0;
  float deathsPerRound = 0.0f;
};

struct PlayerAction {
  int wheatToEat = 0;
  int areaToBuy = 0;
  int areaToSell = 0;
  int areaToUse = 0;
};

std::string readFileKey(std::istream&);
template <typename T>
void getInput(T&);

int saveGame(GameState&, const std::string&);
int loadGame(GameState&, const std::string&);
PlayerAction getAction(GameState&);
void adviserReport(GameState&);
int gameLoop(GameState&);

#endif //ALGOLABS_SUMER_GAME_HPP
