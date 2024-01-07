// Autore Alberto Bettini N°matricola 2074984

#include <fstream>
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "../include/Giocatore.h"
#include "../include/Human.h"
#include "../include/Computer.h"
#include "../include/Tabellone.h"

int getDiceRoll();                                     // restituisce la somme di due numeri casuali tra 1 e 6
void startingOrder(std::vector<Giocatore *> &players); // ordina i players in base ai lanci dei dadi
void show(Tabellone T);

// Mode passata come argomento da terminale
int main(int argc, char *argv[])
{
    // Dichiarazione di variabili
    const int nGiocatori = 4;
    const int nMaxTurni = 400; // Ogni giocatore se sono in una partita tra robot fa al massimo N_Max_turni
    const int startMoney = 100;
    int j = 1;  // Contatore di turni
    bool human; // Variabile che mi dice se ho creato un giocatore Human (=true), o un giocatore computer (=false)
    bool game_is_On = true;
    Tabellone T;                      // creo il tabellone
    std::vector<Giocatore *> players; // I giocatori che sono dentro players sono quelli che giocano, se un giocatore viene eliminato esce dal vettore

    // Lettura di ciò che c'è scritto in riga di comando
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <argument>" << std::endl;
        return 1; // Restituisce 1 in caso di errore
    }
    std::string mode = argv[1]; // salvo l'argomento passato da terminale
    std::cout << "Modalita' selezionata: " << mode << ".\n";
    // Creazione del primo giocatore a seconda del mode
    if (mode == "computer")
    {
        human = false;
        Giocatore *player1 = new Computer{1, T.partenza, startMoney};
        players.push_back(player1);
        std::cout << "\nCreato Giocatore 1, Computer." << std::endl;
    }
    else if (mode == "human")
    {
        human = true;
        Giocatore *player1 = new Human{1, T.partenza, startMoney};
        players.push_back(player1);
        std::cout << "\nCreato Giocatore 1, Human." << std::endl;
    }
    else
    {
        std::cout << "Argomenti errati riprovate, argomenti accettari\n computer: partita con 4 Computer \n human: partita con 3 Computer e un Human";
        return 1;
    }

    // Creazione degli altri 3 giocatori e relativo push nel vettore players
    for (int i = 2; i <= nGiocatori; i++)
    {
        Giocatore *player = new Computer{i, T.partenza, startMoney};
        players.push_back(player);
        std::cout << "Creato Giocatore " << i << ", Computer.\n";
    }

    startingOrder(players); // I giocatori lanciano tutti un dado per vedere chi inizia (ordinamento di players)
    std::cout << "\nOrdine dei giocatori: ";
    for (int i = 0; i < players.size(); i++)
    {
        std::cout << players[i]->getID() << " ";
    }
    std::cout << "\n";

    std::cout << "Ora inizia il gioco, questo e' il tabellone:" << T;
/*
    while (game_is_On)
    {
        // I giocatori ancora in gioco (quelli dentro players) fanno il loro turno
        for (int i = 0; i < players.size(); i++)
        {
            // Turno di un giocatore
            // std::cout << "\nInizio turno " << j << " del giocatore " << players[i]->getID() << ".";
            
            // Il giocatore tira i dadi
            int n = getDiceRoll();
            std::cout << "\nGiocatore " << players[i]->getID() << " ha tirato i dadi e ha fatto " << n << ".\n";
            int tmpMoney = players[i]->getMoney();
            // Movimento su un'altra casella
            players[i]->getPosition()->removePlayer(); // Rimozione dal tabellone del giocatore dalla casella vecchia
            players[i]->move(n);
            players[i]->getPosition()->addPlayer(players[i]->getID()); // Aggiunta al tabellone del giocatore (nella casella dove si è spostato)
            std::cout << "Giocatore " << players[i]->getID() << " si e' mosso sulla casella " << players[i]->getPosition()->getCoordinata_to_String() << ".\n";
            // Stampo il passaggio dal via (intercettato nel move)
            if (players[i]->getMoney() > tmpMoney)
                std::cout << "Giocatore " << players[i]->getID() << " e' passato dal via e ha ritirato " << players[i]->_moneyPassaggioVia << " fiorini.\n";

            // Se il giocatore è umano c'è un interazione con l'utente
            if ((players[i]->getID() == 1) && (human))  // Se è il turno del giocatore 1 ed è un umano gli si fa vedere il tabellone e altre cose
            {
                std::cout << T;
                for (int i = 0; i < players.size(); i++)
                {
                    std::cout << players[i]->to_String_elenco_proprieta();
                    std::cout << "\nGiocatore " << players[i]->getID() << " ha: " << players[i]->getMoney() << " fiorini.";
                }
            }

            // Verifico su che casella è il giocatore
            Casella_Laterale *pos1 = dynamic_cast<Casella_Laterale *>(players[i]->getPosition()); // se il casting va a buon fine
            if (pos1)                                                                             // allora mi trovo su una casella laterale
            {
                if ((pos1->getProprietario() == nullptr) || ((pos1->getProprietario() == players[i]) && (!pos1->isAlbergo()))) // La casella laterale non è di nessuno o è del giocatore, quindi il giocatore può effetturare il buy
                {
                    bool scelta = players[i]->choice(); // Il giocatore sceglie se comprare
                    if (scelta)
                    {
                        try
                        {
                            players[i]->buy();
                            if (pos1->isCasa())
                            {
                                if (pos1->isAlbergo())
                                {
                                    std::cout << "Giocatore " << players[i]->getID() << " ha acquistato un albergo in " << pos1->getCoordinata_to_String() << ".\n";
                                }
                                else
                                {
                                    std::cout << "Giocatore " << players[i]->getID() << " ha acquistato una casa in " << pos1->getCoordinata_to_String() << ".\n";
                                }
                            }
                            else
                            {
                                std::cout << "Giocatore " << players[i]->getID() << " ha acquistato casella " << pos1->getCoordinata_to_String() << ".\n";
                            }
                        }
                        catch (const std::exception &Not_Enough_Money)
                        {
                            // std::cout <<"Tentativo di acquisto non riuscito, troppi pochi soldi.\n";
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
                            std::cout << "Il giocatore " << players[i]->getID() << "ha pagato un affitto di " << pos1->getAffitto() << " fiorini al giocatore " << pos1->getProprietario()->getID() << " per il pernottamento nella casella " << pos1->getCoordinata_to_String() << ".\n";
                        }
                        catch (const Giocatore::You_Loosed &e)
                        {
                            std::cout << "Il giocatore " << players[i]->getID() << " ha perso perche' non aveva abbastanza soldi per pagare l'affitto al giocatore " << pos1->getProprietario()->getID() << ".\n";
                        }
                    }
                }
                // Se il giocatore è arrivato fino a qui senza entrare in nessun if significa che è il proprietario e ha già costruito tutto nei turni prima (fino all'albergo) e quindi siccome non può fare nulla il suo turno finisce
            }
            else
            {
                // Il giocatore è in una casella angolare, non succede nulla.
            }

            std::cout << "Giocatore " << players[i]->getID() << " ha finito il turno.\n";
        }
        // Tutti i giocatori hanno finito il loro turno
        j++; // aumento il conteggio dei turni

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
        std::cout << "Gioco finito per raggiungimento limite massimo di turni (turni giocati = " << nMaxTurni << ")";
       }

    std::cout << "\nHa vinto il giocatore " << players[0]->getID();
    if (human) // Se nella partita c'era un giocatore umano
    {
        if (players[0]->getID() == 1) // Se l'ultimo giocatore rimasto è l'1, allora è l'umano
            std::cout << "\nComplimenti, hai vinto !!!";
    }
*/
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

void startingOrder(std::vector<Giocatore *> &players)
{
    std::vector<int> lanci;
    for (int i = 0; i < players.size(); i++) // assegno a ogni elemento un lancio di dadi
    {
        int l = getDiceRoll();
        std::cout << "\nGiocatore " << players[i]->getID() << " ha tirato i dadi e ha fatto " << l;
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
                Giocatore *gTmp = players[i - 1];
                players[i - 1] = players[i];
                players[i] = gTmp;
                isOrder = false;
            }
        }
    }

    // Vado a caccia di eventuali doppioni
    std::vector<int> indicidoppioni;
    for (int i=1; i < players.size(); i++)
    {
        if (lanci[i-1]==lanci[i])
        {
            if (indicidoppioni.empty())   // Lo inserisco solo se è il primo doppione che trovo
            {
                indicidoppioni.push_back(i-1);  // eventuali successivi indici verranno salvati senza eseguire questa operazione
            }
            indicidoppioni.push_back(i);
        }
    }
    if (indicidoppioni.size()>0) // Se ci sono almeno 2 giocatori che hanno fatto un tiro uguale
    {
        std::vector<Giocatore*> tmp;
        std::string output = "\nI giocatori ";
        for (int i=0; i < indicidoppioni.size(); i++)
        {
            tmp.push_back(players[indicidoppioni[i]]);
            output +=  std::to_string(players[indicidoppioni[i]]->getID()) + " ";
        }
        output +=  " hanno fatto lo stesso numero, quindi ritirano i dadi.";
        std::cout << output;
        startingOrder(tmp);
        // Ora che il vettore tmp è ordinato aggiorno il vettore players
        for (int i=0; i < indicidoppioni.size(); i++)
        {
            players[indicidoppioni[i]] = tmp [i];
        }
    }
}
