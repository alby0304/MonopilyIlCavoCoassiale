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
std::string startingOrder(std::vector<Giocatore *> &players); // ordina i players in base ai lanci dei dadi

// Mode passata come argomento da terminale
int main(int argc, char *argv[])
{
    // Lettura di ciò che c'è scritto in riga di comando
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <argument>" << std::endl;
        return 1; // Restituisce 1 in caso di errore
    }

    // Dichiarazione di costanti e di metodi
    const int nGiocatori = 4;
    const int nMaxTurni = 400; // Ogni giocatore se sono in una partita tra robot fa al massimo N_Max_turni
    const int startMoney = 100;

    int j = 1;  // Contatore di turni
    bool human; // Variabile che mi dice se ho creato un giocatore Human (=true), o un giocatore computer (=false)
    bool game_is_On = true;
    Tabellone T;                      // creo il tabellone
    std::vector<Giocatore *> players; // I giocatori che sono dentro players sono quelli che giocano, se un giocatore viene eliminato esce dal vettore
    std::vector<int> winner;          // Vettore che serve a fine partita, conterrà il/i vincitore/i

    // Creo il file log
    std::ofstream file("log.txt");
    // Verifica se il file è stato aperto correttamente
    if (!file.is_open())
    {
        std::cerr << "Impossibile aprire il file." << std::endl;
        return 1; // Esce con un codice di errore
    }
    file << "CREAZIONE GIOCO\n";

    std::string mode = argv[1]; // salvo l'argomento passato da terminale
    file << "Modalita' selezionata: " << mode << ".\n";
    // Creazione del primo giocatore a seconda del mode
    if (mode == "computer")
    {
        human = false;
        Giocatore *player1 = new Computer{1, T.partenza, startMoney};
        players.push_back(player1);
        std::cout << "\nCreato Giocatore 1, Computer." << std::endl;
        file << "\nCreato Giocatore 1, Computer." << std::endl;
    }
    else if (mode == "human")
    {
        human = true;
        Giocatore *player1 = new Human{1, T.partenza, startMoney};
        players.push_back(player1);
        std::cout << "\nCreato Giocatore 1, Human." << std::endl;
        file << "\nCreato Giocatore 1, Human." << std::endl;
    }
    else
    {
        std::cout << "Argomenti errati riprovate, argomenti accettari\n computer: partita con 4 Computer \n human: partita con 3 Computer e un Human";
        file.close();
        return 1;
    }

    // Creazione degli altri 3 giocatori e relativo push nel vettore players
    for (int i = 2; i <= nGiocatori; i++)
    {
        Giocatore *player = new Computer{i, T.partenza, startMoney};
        players.push_back(player);
        std::cout << "\nCreato Giocatore " << i << ", Computer.";
        file << "\nCreato Giocatore " << i << ", Computer.";
    }

    std::string s = startingOrder(players); // I giocatori lanciano tutti un dado per vedere chi inizia (ordinamento di players)
    s += "\nOrdine dei giocatori: ";
    for (int i = 0; i < players.size(); i++)
    {
        s += std::to_string(players[i]->getID()) + " ";
    }
    std::cout << s << "\n";
    file << s << "\n";

    std::cout << "\nBenvenuto, questo e' il tabellone:" << T << "\nOra inizia il gioco.";
    file << "\nBenvenuto, questo e' il tabellone:" << T << "\nOra inizia il gioco.";

    while (game_is_On)
    {
        std::cout << "\nN Turno: " << j << ".\n";
        file << "\nN° Turno: " << j << ".\n";
        // I giocatori ancora in gioco (quelli dentro players) fanno il loro turno
        for (int i = 0; i < players.size(); i++)
        {
            // Turno di un giocatore
            std::cout << "Inizio turno " << j << " del giocatore " << players[i]->getID() << ".\n";
            file << "Inizio turno " << j << " del giocatore " << players[i]->getID() << ".\n";

            // Il giocatore tira i dadi
            int n = getDiceRoll();
            std::cout << "Giocatore " << players[i]->getID() << " ha tirato i dadi e ha fatto " << n << ".\n";
            file << "Giocatore " << players[i]->getID() << " ha tirato i dadi e ha fatto " << n << ".\n";
            
            int tmpMoney = players[i]->getMoney();
            
            // Movimento su un'altra casella
            players[i]->getPosition()->removePlayer(); // Rimozione dal tabellone del giocatore dalla casella vecchia
            players[i]->move(n);
            players[i]->getPosition()->addPlayer(players[i]->getID()); // Aggiunta al tabellone del giocatore (nella casella dove si è spostato)
            
            std::cout << "Giocatore " << players[i]->getID() << " si e' mosso sulla casella " << players[i]->getPosition()->getCoordinata_to_String() << ".\n";
            file << "Giocatore " << players[i]->getID() << " si e' mosso sulla casella " << players[i]->getPosition()->getCoordinata_to_String() << ".\n";
            
            // Stampo il passaggio dal via (intercettato nel move)
            if (players[i]->getMoney() > tmpMoney)
            {    
                std::cout << "Giocatore " << players[i]->getID() << " e' passato dal via e ha ritirato " << players[i]->_moneyPassaggioVia << " fiorini.\n";
                file << "Giocatore " << players[i]->getID() << " e' passato dal via e ha ritirato " << players[i]->_moneyPassaggioVia << " fiorini.\n";
            }
            // Se il giocatore è umano c'è un interazione con l'utente
            if ((players[i]->getID() == 1) && (human))
            {
                std::string s;
                std::cout << "\nComandi\n  show: per visualizzare il tabellone e la legenda. \n  more: per visualizzare lista delle proprieta e i fiorini di ogni giocatore: ";
                std::cin >> s;
                if (s == "show")
                {
                    std::cout << T;
                    std::cout << T.getLegenda();
                }
                else if (s == "more")
                {
                    for (int i = 0; i < players.size(); i++)
                    {
                        std::cout << players[i]->to_String_elenco_proprieta();
                        std::cout << "\nGiocatore " << players[i]->getID() << " ha: " << players[i]->getMoney() << " fiorini.";
                    }
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
                                    file << "Giocatore " << players[i]->getID() << " ha acquistato un albergo in " << pos1->getCoordinata_to_String() << ".\n";
                                }
                                else
                                {
                                    std::cout << "Giocatore " << players[i]->getID() << " ha acquistato una casa in " << pos1->getCoordinata_to_String() << ".\n";
                                    file << "Giocatore " << players[i]->getID() << " ha acquistato una casa in " << pos1->getCoordinata_to_String() << ".\n";
                                }
                            }
                            else
                            {
                                std::cout << "Giocatore " << players[i]->getID() << " ha acquistato casella " << pos1->getCoordinata_to_String() << ".\n";
                                file << "Giocatore " << players[i]->getID() << " ha acquistato casella " << pos1->getCoordinata_to_String() << ".\n";
                            }
                        }
                        catch (const Giocatore::Not_Enough_Money& e)
                        {
                            std::cout << "Tentativo di acquisto non riuscito, soldi non sufficenti.\n";
                            file << "Tentativo di acquisto non riuscito, soldi non sufficenti.\n";
                        }
                    }
                }
                else if ((pos1->getProprietario()!=players[i])&&((pos1->isCasa()) || (pos1->isAlbergo()))) //Se la casella laterale non è del giocatore-iesimo e c'è un albergo o una casa        
                {
                    try
                    {
                        players[i]->Transfert(pos1->getAffitto(), pos1->getProprietario());
                        // Il metodo Transfert gestisce l'eccezione lanciata in caso di mancanza di soldi eliminando
                        // il giocatore (se deve pagare 10 e ha solo 5 paga 5, arriva a 0 euro, perde tutte le proprietà
                        // (che tornano senza proprietario, nuovamente acquistabili) e viene settato che ha perso, quando
                        // tutti i giocatori avranno finito il loro turno il giocatore verrà rimosso dal vettore player, vedi codice uscito dal ciclo for).
                        std::cout << "Il giocatore " << players[i]->getID() << "ha pagato un affitto di " << pos1->getAffitto() << " fiorini al giocatore " << pos1->getProprietario()->getID() << " per il pernottamento nella casella " << pos1->getCoordinata_to_String() << ".\n";
                        file << "Il giocatore " << players[i]->getID() << "ha pagato un affitto di " << pos1->getAffitto() << " fiorini al giocatore " << pos1->getProprietario()->getID() << " per il pernottamento nella casella " << pos1->getCoordinata_to_String() << ".\n";
                    }
                    catch (const Giocatore::You_Loosed& e)
                    {
                        std::cout << "Il giocatore " << players[i]->getID() << " ha perso perche' non aveva abbastanza soldi per pagare l'affitto al giocatore " << pos1->getProprietario()->getID() << ".\n";
                        file << "Il giocatore " << players[i]->getID() << " ha perso perche' non aveva abbastanza soldi per pagare l'affitto al giocatore " << pos1->getProprietario()->getID() << ".\n";
                    }
                }
                // Se il giocatore-iesimo è arrivato fino a qui senza entrare in nessun if significa che è il proprietario e ha già costruito tutto nei turni prima (fino all'albergo) e quindi siccome non può fare nulla il suo turno finisce
            }
            // Il giocatore è in una casella angolare, non succede nulla.
            std::cout << "Giocatore " << players[i]->getID() << " ha finito il turno.\n";
            file << "Giocatore " << players[i]->getID() << " ha finito il turno.\n";
        }
        // Tutti i giocatori hanno finito il loro turno
        j++; // aumento il conteggio dei turni

        // Verifica se i giocatori (contenuti in player) sono ancora in gioco, se non si è più in gioco si viene rimossi dal vettore
        for (int i = 0; i < players.size(); i++)
        {
            if (!players[i]->isInGame()) // Se il giocatore non è più in game
            {                            // lo tolgo dal vettore di players
                players.erase(players.begin() + i);
                // Qualche chiamata al distruttore del giocatore eliminato per liberare spazio in memoria (se serve, come fare??)
            }
        }

        // Verifiche per capire se continuare a giocare (set game_is_On = false)
        
        if (players.size() == 1)    // C'è 1 solo giocatore, il gioco si ferma e vince l'ultimo rimasto
        {
            winner.push_back(players[0]->getID());
            game_is_On = false;
        }
        else if ((j >= nMaxTurni))   // Arrivo al turno di gioco max per ogni giocatore, il gioco si ferma e vince chi ha più soldi
        {
            // Stampo il tabellone per vedere la situa a fine partita
            std::cout << T;
            file << T; 
            // Stampo quanti soldi ha ogni giocatore
            for (int i = 0; i < players.size(); i++)
            {
                std::cout << "\nGiocatore " << players[i]->getID() << " ha: " << players[i]->getMoney() << " fiorini.";
                file << "\nGiocatore " << players[i]->getID() << " ha: " << players[i]->getMoney() << " fiorini.";
            }
            // Ordino il vettore da quello con più soldi [0], a quello con meno soldi [players.size()-1]
            for (int i = 1; i < players.size(); i++)
            {
                if (players[i]->getMoney() > players[i-1]->getMoney())
                {
                    // Scambio di posto i 2 player
                    Giocatore* tmp = players[i-1];
                    players[i-1] = players[i];
                    players[i] = tmp;
                    i=0;    // Se viene effettuato uno scambio torno all'inizio del vettore e ricomincio la verifica se è ordinato
                }
            }
            // Ora che il vettore players è ordìdinato in modo che il primo giocatore sia quello con più soldi
            // Controllo se qualche altro giocatore ha lo stesso quantitativo di soldi
            for (int i = 1; i < players.size(); i++)
            {
                if (players[i]->getMoney() == players[0]->getMoney())   // C'è più di un vincitore
                {
                    winner.push_back(players[i]->getID());  // push ID del possibile altro vincitore tra i winner
                }
            }
            winner.push_back(players[0]->getID());  // push dell'ID del primo elemento di players (quello con più soldi)
            // Se c'erano altri giocatori con lo stesso ammontare di soldi
            game_is_On = false;
        }
    }

    // Stampo chi ha vinto
    if (j >= nMaxTurni)
    {
        std::cout << "\nGioco finito per raggiungimento limite massimo di turni (turni giocati da ogni giocatore = " << j << ")";
        file << "\nGioco finito per raggiungimento limite massimo di turni (turni giocati da ogni giocatore = " << j << ")";
    }

    if (winner.size() == 1)
    {
        std::cout << "\nHa vinto il giocatore " << players[0]->getID();
        file << "\nHa vinto il giocatore " << players[0]->getID();
        if (human) // Se nella partita c'era un giocatore umano
        {
            if (players[0]->getID() == 1) // Se l'ultimo giocatore rimasto è l'1, allora è l'umano
                std::cout << "\nComplimenti, hai vinto !!!";
        }
    }
    else    // if (winner.size() > 1), se non è 1 è per forza maggiore di uno
    {
        std::string s = "\nVittoria a parimerito, hanno vinto i giocatori ";
        for (int i=0; i < winner.size(); i++)
        {
            s += std::to_string(winner[i]);
        }
        std::cout << s;
        file << s;
    }
    if (winner.size() == 0) // Non dovrebbe succedere MAI
    {
        std::cout << "Vincitore non chiaro, qualcosa è andato storto nella chiusura del game.";
        file << "Vincitore non chiaro, qualcosa è andato storto nella chiusura del game.";
    }

    file.close();
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

std::string startingOrder(std::vector<Giocatore *> &players)
{
    std::string output = "";
    std::vector<int> lanci;
    for (int i = 0; i < players.size(); i++) // assegno a ogni elemento un lancio di dadi
    {
        int l = getDiceRoll();
        output += "\nGiocatore " + std::to_string(players[i]->getID()) + " ha tirato i dadi e ha fatto " + std::to_string(l);
        lanci.push_back(l);
    }

    // utilizzio l'algoritmo boble sort
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

    // Vado a Verificare se ci sono doppioni
    std::vector<int> indicidoppioni;
    for (int i = 1; i < players.size(); i++)
    {
        if (lanci[i - 1] == lanci[i])
        {
            if (indicidoppioni.empty()) // Lo inserisco solo se è il primo doppione che trovo
            {
                indicidoppioni.push_back(i - 1); // eventuali successivi indici verranno salvati senza eseguire questa operazione
            }
            indicidoppioni.push_back(i);
        }
    }
    if (indicidoppioni.size() > 0) // Se ci sono almeno 2 giocatori che hanno fatto un tiro uguale
    {
        std::vector<Giocatore *> tmp;
        output += "\nI giocatori ";
        for (int i = 0; i < indicidoppioni.size(); i++)
        {
            tmp.push_back(players[indicidoppioni[i]]);
            output += std::to_string(players[indicidoppioni[i]]->getID()) + " ";
        }
        output += " hanno fatto lo stesso numero, quindi ritirano i dadi.";
        output += startingOrder(tmp);
        // Ora che il vettore tmp è ordinato aggiorno il vettore players
        for (int i = 0; i < indicidoppioni.size(); i++)
        {
            players[indicidoppioni[i]] = tmp[i];
        }
    }
    return output;
}
