# #1: Hammurabi
## Реализация
### Код
Код: [src/sumer-game.hpp](../src/sumer-game.hpp) и [src/sumer-game.cpp](../src/sumer-game.cpp)
### Структуры
```c++
struct GameState; // состояние игры
struct PlayerAction; // действие игрока
```
### Константы
```c++
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
```
## Вывод программы
```text
Welcome, my lord. 
My lord, I brought some news for you
    your reign begins today, at year 1;
    you have 100 peasants, 2800 wheat bushels and area of 1000 acres;
    one acre of land costs exactly 25 wheat bushels.

My lord, what do you want?
< We can buy 112 acres at most.
> Area to buy: 0
> Area to sell: 0
< For everyone we will need 2000 bushels.
< Currently we have 2800 of them.
> Wheat to use as food: 2000
We have people for 1000 acres.
We have wheat for 5600 acres.
Currently our area is 1000 acres.
> Area to use for wheat: 1000

My lord, I brought some news for you
    it's year 2 of your reign,
    0 peasants died from starvation, but we got 0 new citizens;
    plague has killed 50 of them;
    this year we have 50 citizens;
    our wheat fields yield 6000 bushels of grain, 6 per acre;
    rats eaten 367 wheat bushels, leaving us with only 6433
    our city has area of 1000 acres;
    one acre of land costs exactly 21 wheat bushels.
Do you want to save your progress so far, my lord (y/n): n

My lord, what do you want?
< We can buy 307 acres at most.
> Area to buy: 0
> Area to sell: 0
< For everyone we will need 1000 bushels.
< Currently we have 6433 of them.
> Wheat to use as food: 1000

We have people for 500 acres.
We have wheat for 12866 acres.
Currently our area is 1000 acres.
> Area to use for wheat: 500

My lord, I brought some news for you
    it's year 3 of your reign,
    0 peasants died from starvation, but we got 38 new citizens;
    plague has killed 44 of them;
    this year we have 44 citizens;
    our wheat fields yield 500 bushels of grain, 1 per acre;
    rats eaten 261 wheat bushels, leaving us with only 5672
    our city has area of 1000 acres;
    one acre of land costs exactly 18 wheat bushels.
Do you want to save your progress so far, my lord (y/n): n

My lord, what do you want?
< We can buy 316 acres at most.
> Area to buy: 0
> Area to sell: 0
< For everyone we will need 880 bushels.
< Currently we have 5672 of them.
> Wheat to use as food: 880
We have people for 440 acres.
We have wheat for 11344 acres.
Currently our area is 1000 acres.
> Area to use for wheat: 440

My lord, I brought some news for you
    it's year 4 of your reign,
    0 peasants died from starvation, but we got 27 new citizens;
    plague has killed 36 of them;
    this year we have 35 citizens;
    our wheat fields yield 880 bushels of grain, 2 per acre;
    rats eaten 288 wheat bushels, leaving us with only 5384
    our city has area of 1000 acres;
    one acre of land costs exactly 20 wheat bushels.
Do you want to save your progress so far, my lord (y/n): n

My lord, what do you want?
< We can buy 270 acres at most.
> Area to buy: 0
> Area to sell: 0
< For everyone we will need 700 bushels.
< Currently we have 5384 of them.
> Wheat to use as food: 700
We have people for 350 acres.
We have wheat for 10768 acres.
Currently our area is 1000 acres.
> Area to use for wheat: 350

My lord, I brought some news for you
    it's year 5 of your reign,
    0 peasants died from starvation, but we got 0 new citizens;
    plague has killed 18 of them;
    this year we have 17 citizens;
    our wheat fields yield 2100 bushels of grain, 6 per acre;
    rats eaten 42 wheat bushels, leaving us with only 6742
    our city has area of 1000 acres;
    one acre of land costs exactly 24 wheat bushels.
Do you want to save your progress so far, my lord (y/n): y
y
Where do you want to save your city, my lord?
save.sav

Process finished with exit code 0
```