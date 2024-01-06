#include <chrono>
#include <thread>
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
    // Dichiarazione di variabili
    const int N_giocatori = 4;
    const int max_Iteration = 4000; // Numero di turni massimo per partita tra soli computer
    int j = 0;                      // Contatore di turni
    bool human;
    bool game_is_On = true;
    Tabellone T; // creo il tabellone
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

    // Creazione del primo giocatore a seconda del mode
    if (human)
    {
        Giocatore* player1 = new Human {1,T.partenza};
        players.push_back(*player1);
    }
    else
    {
        Giocatore* player1 = new Computer {1,T.partenza};
        players.push_back(*player1);
    }
    // Creazione degli altri 3 giocatori
    /*Giocatore* player2 = new Computer {2,T.partenza};
    players.push_back(*player2);
    Giocatore* player3 = new Computer {3,T.partenza};
    players.push_back(*player3);
    Giocatore* player4 = new Computer {4,T.partenza};
    players.push_back(*player4);*/
    
    std::cout << "\nBenvenuto, questo e' il tabellone:"
              << T << "\nOra inizia il gioco.";
    while (game_is_On)
    {
        // I giocatori fanno il loro turno
        for (int i = 0; i < players.size(); i++)
        {
            // Turno di un giocatore
            // Movimento su un'altra casella
            std::cout << "\nTurno " << j << "\nInizio turno del giocatore " << players[i].getID();
            int n = getDiceRoll();
            std::cout << "\nGiocatore " << players[i].getID() << " ha tirato i dadi e ha fatto " << n;
            int tmpMoney = players[i].getMoney();
            // Rimozione dal tabellone del giocatore dalla casella vecchia
            players[i].getPosition()->removePlayer();
            players[i].move(n);
            // Aggiunta al tabellone del giocatore (nella casella dove si è spostato)
            players[i].getPosition()->addPlayer(players[i].getID());
            std::cout << "\nGiocatore " << players[i].getID() << " si e' mosso sulla casella " << players[i].getPosition()->getCoordinata_to_String();
            // Stampo il passaggio dal via (intercettato nel move)
            if (players[i].getMoney() != tmpMoney)
                std::cout << "\nGiocatore " << players[i].getID() << " e' passato dal via e ha ritirato 20 fiorini.";

            // Verifico su che casella sono capitato
            Casella_Laterale *_pos1 = dynamic_cast<Casella_Laterale *>(players[i].getPosition()); // se il casting va a buon fine
            if (_pos1)                                                                            // Se mi trovo su una casella laterale
            {
                Giocatore *player = &players[i];
                if (_pos1->getProprietario() == nullptr) // La casella laterale non è di nessuno, quindi posso comprarla
                {
                    bool scelta = players[i].want_to_buy_terreno();
                    if (scelta)
                    {
                        try
                        {
                            players[i].buy();
                            std::cout << "\nGiocatore " << players[i].getID() << " ha acquistato casella " << players[i].getPosition()->getCoordinata_to_String();
                        }
                        catch(const std::exception& Not_Enough_Money)
                        {
                            std::cout << "\nTentativo di acquisto terreno non riuscito, troppi pochi soldi.";
                        }
                    }
                }
                else if (_pos1->getProprietario() == player) // La casella laterale è del giocatore che ci è appena finito sopra
                {
                    if (!_pos1->isCasa()) // Se non c'è una casa il giocatore può decidere di comprarla (acquisto consentito se ha abbastanza soldi)
                    {
                        bool scelta = players[i].want_to_buy_casa();
                        if (scelta)
                        {
                            try
                            {
                                players[i].buy();
                                std::cout << "\nGiocatore " << players[i].getID() << " ha acquistato casa in " << players[i].getPosition()->getCoordinata_to_String();
                            }
                            catch(const std::exception& Not_Enough_Money)
                            {
                                std::cout << "\nTentativo di acquisto casa non riuscito, troppi pochi soldi.";
                            }
                        }
                    }
                    if ((!_pos1->isAlbergo()) && (_pos1->isCasa())) // Se non c'è un albergo e c'è una casa (deve esserci già una casa per costruire un albergo) il giocatore può decidere di comprare l'albergo (acquisto consentito se ha abbastanza soldi)
                    {
                        bool scelta = players[i].want_to_buy_albergo();
                        if (scelta)
                        {
                            try
                            {
                                players[i].buy();
                                std::cout << "\nGiocatore " << players[i].getID() << " ha acquistato albergo in " << players[i].getPosition()->getCoordinata_to_String();
                            }
                            catch(const std::exception& Not_Enough_Money)
                            {
                                std::cout << "\nTentativo di acquisto albergo non riuscito, troppi pochi soldi.";
                            }
                        }
                    }
                }
                else // La casella laterale non è del giocatore e non è "della banca" (nullptr), quindi è di qualcuno e se c'è almeno una casa devo pagare l'affitto
                {
                    if ((_pos1->isCasa()) || (_pos1->isAlbergo())) // Se sono su un terreno non mio con una casa o un albergo devo pagare l'affitto al proprietario
                    {
                        try
                        {
                            players[i].Transfert(_pos1->getAffitto(), _pos1->getProprietario());
                            // Il metodo Transfert gestisce l'eccezione lanciata in caso di mancanza di soldi eliminando
                            // il giocatore (se deve pagare 10 e ha solo 5 paga 5, arriva a 0 euro, perde tutte le proprietà
                            // (che tornano senza proprietario, nuovamente acquistabili) e viene settato che ha perso, quando
                            // tutti i giocatori avranno finito il loro turno il giocatore verrà rimosso dal vettore player, vedi codice uscito dal ciclo for).
                            std::cout << "\nIl giocatore " << players[i].getID() << "ha pagato un affitto di " << _pos1->getAffitto() << " al giocatore " << _pos1->getProprietario()->getID();
                        }
                        catch (const std::exception &You_Loosed)
                        {
                            std::cout << "\nIl giocatore " << players[i].getID() << "ha perso perchè non aveva abbastanza soldi per pagare l'affitto al giocatore " << _pos1->getProprietario()->getID();
                        }
                    }
                }
                // Se il giocatore è arrivato fino a qui senza entrare in nessun if significa che è il proprietario e ha già costruito tutto nei turni prima (fino all'albergo) e quindi siccome non può fare nulla il suo turno finisce
            }
            else
            {
                // Non succede nulla, poichè mi trovo su una casella angolare
            }
            // Fine turno
            j++;
        }
        // Ogni volta che i giocatori hanno fatto tutti il loro turno stampo tabellone e quanti chei ha il giocatore 1
        std::cout << T;
        // Il programma fa una pausa di 6 secondi ogni volta che tutti i giocatori hanno finito il proprio turno, poi pulisce lo schermo
        std::this_thread::sleep_for(std::chrono::seconds(6));
        // std::system("cls");     // Pulizia schermo

        // Verifiche per capire se continuare a giocare (set game_is_On = false)
        // Verifica se i giocatori (contenuti in player) sono ancora in gioco, se non si è più in gioco si viene rimossi dal vettore
        for (int i = 0; i < players.size(); i++)
        {
            if (!players[i].isInGame()) // Se il giocatore non è più in game
            {                           // lo tolgo dal vettore di players
                // players[i].resetPlayer(); => quest'istruzione non serve perchè se un giocatore non è più in game si auto-elimina, in game bisogna solo toglierlo dal vettore di players
                players.erase(players.begin() + i);
                // Qualche chiamata al distruttore del giocatore eliminato per liberare spazio in memoria (se serve, come fare??)
            }
        }
        // C'è 1 solo giocatore, il gioco si ferma e vince l'ultimo rimasto
        //if (players.size() == 1)
        //   game_is_On = false;
        // Arrivo al turno di gioco 4000 per ogni giocatore, il gioco si ferma e vince chi ha più soldi
        if ((!human) && (j > max_Iteration)) // partita tra soli robot
        {
            // sposto come primo elmento del vettore il giocatore con più soldi e poi esco dal ciclo
            for (int i = 1; i < players.size(); i++)
            {
                if (players[i].getMoney() > players[0].getMoney())
                {
                    players[0] = players[i];
                }
            }
            game_is_On = false;
        }
    }

    // Stampo chi ha vinto
    if (human) // Se nella partita c'era un giocatore umano
    {
        if (players[0].getID() == 1) // Se l'ultimo giocatore rimasto è l'1, allora è l'umano
            std::cout << "Complimenti, hai vinto !!!";
        else
            std::cout << "Ha vinto il giocatore " << players[0].getID();
    }
    else
        std::cout << "Ha vinto il giocatore " << players[0].getID();

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