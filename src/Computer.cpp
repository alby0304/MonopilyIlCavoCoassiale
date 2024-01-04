#include "../include/Computer.h"
#include <random>

bool Computer::makeChoice() // il computer effettua l'acquisto solo se il numero generato randomicamente è 1 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distr(1, 4);

    return distr(gen) == 1;
}