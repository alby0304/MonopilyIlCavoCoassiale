#include <iostream>
#include <vector>
#include <random>
#include <string>
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

    Tabellone T; // creo il tabellone
    std::vector<int> order = startingOrder();
    
    std::vector<Giocatore*> players; // inizializzo il vettore di Giocatori
    if (mode == "computer")
    {   
        // Creo il primo giocatore Computer
        Computer player(order[0], T.partenza);
        players.push_back(&player);
        
        // Numero di turni massimo per partita tra soli computer
        const int max_Iteration = 4000;
    }
    else if (mode == "human")
    {
        // Creo il primo giocatore Human
        Human player(order[0], T.partenza);
        players.push_back(&player);
        T.partenza->addPlayer(order[0]);
    }
    else
    {
        std::cout << "Argomenti errati riprovate, Argomenti accettari\n computer: partita con 4 Computer \n human: partita con 3 Computer e un Human";
        return 1;
    }
    std::cout << *players[0];
    // Creo gli altri 3 giocatori (in ogni caso ci sono sempre 3 Computer)
    for (int i = 1; i < 4; i++)
    {
        std::cout << "FOR CREAZIONE COMPUTER";
        Computer player(order[i], T.partenza);
        std::cout << " A";
        players.push_back(&player);
        std::cout << *players[i];
        std::cout << i;
    }

    std::cout << "ola cicho";
    /*TODO
    // Ora capiamo l'ordine di gioco (ordine del vettore players)

    bool playing = true;
    bool scelta;
    while (playing)
    {
        // Turno di ogni giocatore
        for (int i = 0; i < 4; i++)
        {
            players[i].move(getDiceRoll());
            // Vedo dove sono capitato
            Casella_Laterale *_pos1 = dynamic_cast<Casella_Laterale *>(players[i].getPosition()); // se il casting va a buon fine
            if (_pos1)  // Se sono su una casella laterale
            {
                Giocatore* player_i = &players[i];
                if (_pos1->getProprietario()==player_i)
                {}  // Sono il proprietario
                else
                {
                    // Verifico chi è il proprietario
                    if (_pos1->getProprietario()==nullptr)  // Se il proprietario non è nessuno
                    {                               // allora posso decidere se acquistare il terreno
                        std::cout << "Benvenuto nella casella " << _pos1->getCoordinata() << "\nVuoi comprarla?" std::endl;
                        scelta = players[i].makeChoice();
                        if (scelta)     // Se il giocatore vuole comprare
                        {
                            players[i].buy();
                        }
                    }
                    
                }
                
                if (scelta == true) // verifico che il giocatore sia il proprietario
                 
            }
            else
            {
                // Non succede nulla, poichè sono in una casella angolare
            }
            
        }
    }*/
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
    std::vector<int> order = {1,2,3,4};
    bool isOrder = false;
    while(!isOrder)
    {
        isOrder = true;
        for (int i = 1; i < lanci.size(); i++)
        {
            if(lanci[i-1]<lanci[i])
            {
                int tmp = lanci[i-1];
                lanci[i-1] = lanci[i];
                lanci[i] = tmp;
                tmp = order[i-1];
                order[i-1] = order[i];
                order[i] = tmp;
                isOrder = false;
            }
        }
    }    
    return order;
}
