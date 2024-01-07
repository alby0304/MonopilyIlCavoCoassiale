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

int getDiceRoll();                   // restituisce la somme di due numeri casuali tra 1 e 6
void startingOrder(std::vector<Giocatore*>& players); // ordina i players in base ai lanci dei dadi

// Mode passata come argomento da terminale
int main(int argc, char *argv[])
{
    // Lettura di ciò che c'è scritto in riga di comando
    // verifico che
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <argument>" << std::endl;
        return 1; // Restituisce 1 in caso di errore
    }

    // Dichiarazione di variabili
    const int nGiocatori = 4;
    const int nMaxTurni = 50; // Ogni giocatore se sono in una partita tra robot fa al massimo N_Max_turni
    const int startMoney = 100; 

    
    int j = 0;                // Contatore di turni
    bool human;               // Variabile che mi dice se ho creato un giocatore Human (=true), o un giocatore computer (=false)
    bool game_is_On = true;
    Tabellone T;                      // creo il tabellone
    std::vector<Giocatore *> players; // I giocatori che sono dentro players sono quelli che giocano, se un giocatore viene eliminato esce dal vettore

    std::string mode = argv[1]; // salvo l'argomento passato da terminale
    // Creazione del primo giocatore a seconda del mode
    if (mode == "computer")
    {
        human = false;
        Giocatore *player1 = new Computer{1, T.partenza, startMoney};
        players.push_back(player1);
    }
    else if (mode == "human")
    {
        human = true;
        Giocatore *player1 = new Human{1, T.partenza, startMoney};
        players.push_back(player1);
    }
    else
    {
        std::cout << "Argomenti errati riprovate, Argomenti accettari\n computer: partita con 4 Computer \n human: partita con 3 Computer e un Human";
        return 1;
    }

    // Creazione degli altri 3 giocatori e relativo push nel vettore players
    for (int i = 2; i <= nGiocatori; i++)
    {
        Giocatore *player = new Computer{i, T.partenza, startMoney};
        players.push_back(player);
    }

    startingOrder(players); // Ordine dei giocatori


    std::cout << "\nL'ordine di gioco dei giocatori è";
    for (int i = 0; i < players.size(); i++)
    {
        std::cout << players[i]->getID() << " ";
    }
    std::cout << "\nBenvenuto, questo e' il tabellone:"
              << T << "\nOra inizia il gioco.";
    while (game_is_On)
    {
        // I giocatori fanno il loro turno
        for (int i = 0; i < players.size(); i++)
        {
            // Turno di un giocatore
            // Movimento su un'altra casella
            std::cout << "\nTurno " << j << "\nInizio turno del giocatore " << players[i]->getID();
            int n = getDiceRoll();
            std::cout << "\nGiocatore " << players[i]->getID() << " ha tirato i dadi e ha fatto " << n;
            int tmpMoney = players[i]->getMoney();
            // Rimozione dal tabellone del giocatore dalla casella vecchia
            players[i]->getPosition()->removePlayer();
            players[i]->move(n);
            // Aggiunta al tabellone del giocatore (nella casella dove si è spostato)
            players[i]->getPosition()->addPlayer(players[i]->getID());
            std::cout << "\nGiocatore " << players[i]->getID() << " si e' mosso sulla casella " << players[i]->getPosition()->getCoordinata_to_String();
            // Stampo il passaggio dal via (intercettato nel move)
            if (players[i]->getMoney() > tmpMoney)
                std::cout << "\nGiocatore " << players[i]->getID() << " e' passato dal via e ha ritirato " << players[i]->_moneyPassaggioVia << " fiorini.";

            // Verifico su che casella sono capitato
            Casella_Laterale *pos1 = dynamic_cast<Casella_Laterale *>(players[i]->getPosition()); // se il casting va a buon fine
            if (pos1)                                                                             // Se mi trovo su una casella laterale
            {
                if ((pos1->getProprietario() == nullptr) || ((pos1->getProprietario() == players[i]) && (!pos1->isAlbergo()))) // La casella laterale non è di nessuno o del giocatore, quindi posso l'azione di buy
                {
                    bool scelta = players[i]->choice();
                    if (scelta)
                    {
                        try
                        {
                            players[i]->buy();
                            if (pos1->isCasa())
                            {
                                if (pos1->isAlbergo())
                                {
                                    std::cout << "\nGiocatore " << players[i]->getID() << " ha acquistato albergo in " << pos1->getCoordinata_to_String();
                                }
                                else
                                {
                                    std::cout << "\nGiocatore " << players[i]->getID() << " ha acquistato casa in " << pos1->getCoordinata_to_String();
                                }
                            }
                            else
                            {
                                std::cout << "\nGiocatore " << players[i]->getID() << " ha acquistato casella " << pos1->getCoordinata_to_String();
                            }
                        }
                        catch (const std::exception &Not_Enough_Money)
                        {
                            std::cout << "\nTentativo di acquisto non riuscito, troppi pochi soldi.";
                        }
                    }
                }
                else // La casella laterale non è del giocatore e non è "della banca" (nullptr), quindi è di qualcuno e se c'è almeno una casa devo pagare l'affitto
                {
                    if ((pos1->isCasa()) || (pos1->isAlbergo())) // Se sono su un terreno non mio con una casa o un albergo devo pagare l'affitto al proprietario
                    {
                        try
                        {
                            players[i]->Transfert(pos1->getAffitto(), pos1->getProprietario());
                            // Il metodo Transfert gestisce l'eccezione lanciata in caso di mancanza di soldi eliminando
                            // il giocatore (se deve pagare 10 e ha solo 5 paga 5, arriva a 0 euro, perde tutte le proprietà
                            // (che tornano senza proprietario, nuovamente acquistabili) e viene settato che ha perso, quando
                            // tutti i giocatori avranno finito il loro turno il giocatore verrà rimosso dal vettore player, vedi codice uscito dal ciclo for).
                            std::cout << "\nIl giocatore " << players[i]->getID() << "ha pagato un affitto di " << pos1->getAffitto() << " al giocatore " << pos1->getProprietario()->getID();
                        }
                        catch (const Giocatore::You_Loosed& e)
                        {
                            std::cout << "\nIl giocatore " << players[i]->getID() << " ha perso perche' non aveva abbastanza soldi per pagare l'affitto al giocatore " << pos1->getProprietario()->getID();
                        }
                    }
                }
                // Se il giocatore è arrivato fino a qui senza entrare in nessun if significa che è il proprietario e ha già costruito tutto nei turni prima (fino all'albergo) e quindi siccome non può fare nulla il suo turno finisce
            }

            // Se non è una casella Laterale, Non succede nulla.
        }
        // Tutti i giocatori hanno finito il loro turno
        j++; // aumento il conteggio dei turni
        // Stampo tabellone
        std::cout << T;
        // Stampo i fiorini e le proprietà di ogni giocatore
        for (int i = 0; i < players.size(); i++)
        {
            std::cout << players[i]->to_String() << ". Fiorini = " << players[i]->getMoney()<< ".";
        }
        // Il programma fa una pausa di 1 secondo ogni volta che tutti i giocatori hanno finito il proprio turno
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // std::system("cls");     // Pulizia schermo (funzionante solo su windows)

        // Verifiche per capire se continuare a giocare (set game_is_On = false)
        // Verifica se i giocatori (contenuti in player) sono ancora in gioco, se non si è più in gioco si viene rimossi dal vettore
        for (int i = 0; i < players.size(); i++)
        {
            if (!players[i]->isInGame()) // Se il giocatore non è più in game
            {                            // lo tolgo dal vettore di players
                players.erase(players.begin() + i);
                // Qualche chiamata al distruttore del giocatore eliminato per liberare spazio in memoria (se serve, come fare??)
            }
        }
        // C'è 1 solo giocatore, il gioco si ferma e vince l'ultimo rimasto
        if (players.size() == 1)
            game_is_On = false;
        // Arrivo al turno di gioco max per ogni giocatore, il gioco si ferma e vince chi ha più soldi
        if ((j > nMaxTurni)) // partita tra soli robot
        {
            // sposto come primo elmento del vettore il giocatore con più soldi e poi esco dal ciclo
            for (int i = 1; i < players.size(); i++)
            {
                if (players[i]->getMoney() > players[0]->getMoney())
                {
                    players[0] = players[i];
                }
            }
            game_is_On = false;
        }
    }

    // Stampo chi ha vinto
    if (j > nMaxTurni)
    {
        std::cout << "\nGioco finito per raggiungimento limite massimo di turni (turni giocati = " << nMaxTurni << ")";
        
    }

    std::cout << "\nHa vinto il giocatore " << players[0]->getID();
    if (human) // Se nella partita c'era un giocatore umano
    {
        if (players[0]->getID() == 1) // Se l'ultimo giocatore rimasto è l'1, allora è l'umano
            std::cout << "\nComplimenti, hai vinto !!!";
    }
    
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

void startingOrder(std::vector<Giocatore*>& players)
{

    std::vector<int> lanci;
    for (int i = 0; i < players.size(); i++) //assegno a ogni elemento un lancio di dadi
    {
        int l = getDiceRoll();
        std::cout << "\nGiocatore " << i + 1 << " ha tirato i dadi e ha fatto " << l;
        lanci.push_back(l);
    }
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
                Giocatore* gTmp = players[i - 1];
                players[i - 1] = players[i];
                players[i] = gTmp;
                isOrder = false;
            }
        }
    }
}
