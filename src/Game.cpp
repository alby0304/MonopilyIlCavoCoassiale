#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "../include/Giocatore.h"
#include "../include/Human.h"
#include "../include/Computer.h"
#include "../include/Tabellone.h"

// void show();
int getDiceRoll();                // restituisce la somme di due numeri casuali tra 1 e 6
std::vector<int> startingOrder(); // mi restituisce un vettore di int con l'ordine di partenza dei vari giocatori es [1,3,4,2];

// Mode passata come argomento da terminale
int main(int argc, char *argv[])
{
    bool human;
    Tabellone T;                    // creo il tabellone
    std::vector<Giocatore> players; // Vector di giocatori

    // Lettura di ciò che c'è scritto in riga di comando
    // verifico che
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <argument>" << std::endl;
        return 1; // Restituisce 1 in caso di errore
    }
    std::string mode = argv[1]; // salvo l'argomento passato da terminale
    if (mode == "computer")
    {
        human = false;
        // Numero di turni massimo per partita tra soli computer
        const int max_Iteration = 4000;
    }
    else if (mode == "human")
    {
        human = true;
    }
    else
    {
        std::cout << "Argomenti errati riprovate, Argomenti accettari\n computer: partita con 4 Computer \n human: partita con 3 Computer e un Human";
        return 1;
    }

    // Creazione degli altri 3 giocatori
        Giocatore player1(1, T.partenza);
        players.push_back(player1);
        Giocatore player2(2, T.partenza);
        players[1] = player2;
        Giocatore player3(3, T.partenza);
        players[2] = player3;
        Giocatore player4(4, T.partenza);
        players[3] = player4;

    // Giocatore* _pos1 = dynamic_cast<Giocatore*>(player1); //se il casting va a buon fine         
    // std::vector<int> order = startingOrder();

        // for (int i = 1; i < 4; i++)
        // {
        //     std::cout << "FOR CREAZIONE COMPUTER";
        //     try
        //     {
        //         players.push_back(Computer(i, T.partenza));
        //     }
        //     catch(const std::exception& e)
        //     {
        //         std::cerr << e.what() << '\n';
        //     }
        //     std::cout << i;
        // }

        std::cout << T;
    
    return 0;
}

int getDiceRoll()
{
    // Inizializza il generatore di numeri casuali con un seed basato sull'orologio di sistema
    std::random_device rd;
    std::mt19937 gen(rd());

    // Definisci la distribuzione uniforme per generare numeri tra 1 e 6
    std::uniform_int_distribution<int> distr(1, 6);

    return distr(gen) + distr(gen); // restituisce la somma di 2 numeri casuali tra 1 e 6
}

std::vector<int> startingOrder()
{
    std::vector<int> lanci;
    for (int i = 0; i < 4; i++)
    {
        int l = getDiceRoll();
        lanci.push_back(l);
    }
    std::vector<int> order = {1, 2, 3, 4};
    bool isOrder = false;
    while (!isOrder)
    {
        isOrder = true;
        for (int i = 1; i < lanci.size(); i++)
        {
            if (lanci[i - 1] < lanci[i])
            {
                int tmp = lanci[i - 1];
                lanci[i - 1] = lanci[i];
                lanci[i] = tmp;
                tmp = order[i - 1];
                order[i - 1] = order[i];
                order[i] = tmp;
                isOrder = false;
            }
        }
    }
    return order;
}
