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

    // verifico che
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <argument>" << std::endl;
        return 1; // Restituisce 1 in caso di errore
    }
    std::string mode = argv[1]; // salvo l'argomento passato da terminale

    // std::vector<int> order = startingOrder();
    Tabellone T; // creo il tabellone
    std::cout << "\nTabellone creato, ora passo alla creazione dei giocatori.";
    Giocatore players[4]; // inizializzo il vettore di Giocatori
    std::cout << "\nVector creato";
    try
    {
        // Giocatore player1;
        if (mode == "computer")
        {
            // Creo il primo giocatore Computer e lo inserisco nel vettore di players
            std::cout << "CREAZIONE COMPUTER";
            players[0] = Giocatore(1, T.partenza);
            std::cout << "COMPUTER creato";
            // Numero di turni massimo per partita tra soli computer
            const int max_Iteration = 4000;
        }
        else if (mode == "human")
        {
            // Creo il primo giocatore Human e lo inserisco nel vettore di players
            std::cout << "CREAZIONE HUMAN";
            players[0] = Giocatore(1, T.partenza);
        }
        else
        {
            std::cout << "Argomenti errati riprovate, Argomenti accettari\n computer: partita con 4 Computer \n human: partita con 3 Computer e un Human";
            return 1;
        }
        // Giocatore* _pos1 = dynamic_cast<Giocatore*>(player1); //se il casting va a buon fine 
        
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

        Giocatore player2(2, T.partenza->getSucc());
        players[1] = player2;
        Giocatore player3(3, T.partenza->getSucc());
        players[2] = player3;
        Giocatore player4(4, T.partenza->getSucc());
        players[3] = player4;

        std::cout << T;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Errore durante l'esecuzione del programma: " << e.what() << std::endl;
        return 1; 
    }
    std::cin.get();
    /*
    // Creo gli altri 3 giocatori (in ogni caso ci sono sempre 3 Computer)
    Computer player(1, T.partenza);
    std::cout << "\ncreazione 2";
    Computer player2(2, T.partenza);
    std::cout << "\ncreato 2";
    // players.push_back(&player2);
    std::cout << "\npush 2";
    std::cout << "\ncreazione 3";
    Computer player3(3, T.partenza->getSucc());
    std::cout << "\ncreato 3";
    // players.push_back(&player3);
    std::cout << "\npush 3";
    Computer player4(4, T.partenza);
    std::cout << "\ncreato 4";
    // players.push_back(&player4);
    std::cout << "\npush 4";
    std::cout << "I 4 Giocatori sono stati creati";


    std::cout << "\n ola cicho";
    std:: cout << T;
    return 0;
    */
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
