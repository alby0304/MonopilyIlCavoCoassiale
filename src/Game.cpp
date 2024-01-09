// Autore: Alberto Bettini, N°matricola: 2074984

#include <fstream>
#include "../include/Human.h"
#include "../include/Computer.h"
#include "../include/Tabellone.h"

int getDiceRoll();                                            // restituisce la somme di due numeri casuali tra 1 e 6
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

    // Dichiarazione di variabili
    int j = 0;  // Contatore di turni
    int nMaxTurni;
    bool human; // Variabile che mi dice se ho creato un giocatore Human (=true), o un giocatore computer (=false)
    bool game_is_On;
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
    file << "CREAZIONE GIOCO\n\n";

    std::string mode = argv[1]; // salvo l'argomento passato da terminale
    std::cout << "Modalita' selezionata: " << mode << ".\n\n";
    file << "Modalita' selezionata: " << mode << ".\n\n";
    // Creazione del primo giocatore a seconda del mode
    if (mode == "computer")
    {
        nMaxTurni = Variabili::maxTurniComputer;
        human = false;
        Giocatore *player1 = new Computer{1};
        players.push_back(player1);
        std::cout << "Creato Giocatore 1, Computer.";
        file << "Creato Giocatore 1, Computer.";
    }
    else if (mode == "human")
    {
        nMaxTurni = Variabili::maxTurniHuman;
        human = true;
        Giocatore *player1 = new Human{1};
        players.push_back(player1);
        std::cout << "Creato Giocatore 1, Human.";
        file << "Creato Giocatore 1, Human.";
    }
    else
    {
        std::cout << "Argomenti errati riprovate, argomenti accettari\n computer: partita con 4 Computer \n human: partita con 3 Computer e un Human";
        file.close();
        return 1;
    }

    // Creazione degli altri 3 giocatori e relativo push nel vettore players
    for (int i = 2; i <= Variabili::nGiocatori; i++)
    {
        Giocatore *player = new Computer{i};
        players.push_back(player);
        std::cout << "\nCreato Giocatore " << i << ", Computer.";
        file << "\nCreato Giocatore " << i << ", Computer.";
    }

    // Tutti i giocatori lanciano i dadi per determinare l’ordine di gioco (ordinamento di players)
    std::string s = "\n" + startingOrder(players);
    s += "\n\nOrdine dei giocatori: ";
    for (int i = 0; i < players.size(); i++)
    {
        s += std::to_string(players[i]->getID()) + " ";
    }

    // Aggiungo i giocatori al tabellone
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->setPos(T.partenza);
    }

    std::cout << "\n\nBenvenuto, questo e' il tabellone:" << T << "\n\nOra inizia il gioco. \n";
    file << "\n\nOra inizia il gioco.\n";
    game_is_On = true;

    while (game_is_On)
    {
        j++; // aumento il conteggio dei turni
        std::cout << "\nN Turno: " << j << ".\n";
        file << "\nN° Turno: " << j << ".\n";
        // I giocatori ancora in gioco (quelli dentro players) fanno il loro turno
        for (int i = 0; i < players.size(); i++)
        {
            // Turno di un giocatore
            std::cout << "\nInizio turno del giocatore " << players[i]->getID() << ".\n";
            file << "\nInizio turno del giocatore " << players[i]->getID() << ".\n";

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
                std::cout << "Giocatore " << players[i]->getID() << " e' passato dal via e ha ritirato " <<  Variabili::moneyPassaggioVia << " " << Variabili::getValuta() << ".\n";
                file << "Giocatore " << players[i]->getID() << " e' passato dal via e ha ritirato " << Variabili::moneyPassaggioVia << " " << Variabili::getValuta() << ".\n";
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
                        std::cout << "\nGiocatore " << players[i]->getID() << " ha: " << players[i]->getMoney() << " " << Variabili::getValuta() << ".";
                    }
                    std::cout << std::endl;
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
                            std::cout << "Tentativo di acquisto non riuscito, " << Variabili::getValuta() << " non sufficenti.\n";
                            file << "Tentativo di acquisto non riuscito, " << Variabili::getValuta() << " non sufficenti.\n";
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
                        std::cout << "Giocatore " << players[i]->getID() << " ha pagato un affitto di " << pos1->getAffitto() << " " << Variabili::getValuta() << " al giocatore " << pos1->getProprietario()->getID() << " per il pernottamento nella casella " << pos1->getCoordinata_to_String() << ".\n";
                        file << "Giocatore " << players[i]->getID() << " ha pagato un affitto di " << pos1->getAffitto() << " " << Variabili::getValuta() << " al giocatore " << pos1->getProprietario()->getID() << " per il pernottamento nella casella " << pos1->getCoordinata_to_String() << ".\n";
                    }
                    catch (const Giocatore::Player_Lost& e)
                    {
                        std::cout << "Giocatore " << players[i]->getID() << " ha perso perche' non aveva abbastanza " << Variabili::getValuta() << " per pagare l'affitto al giocatore " << pos1->getProprietario()->getID() << ".\n";
                        file << "Giocatore " << players[i]->getID() << " ha perso perche' non aveva abbastanza " << Variabili::getValuta() << " per pagare l'affitto al giocatore " << pos1->getProprietario()->getID() << ".\n";
                    }
                }
                // Se il giocatore-iesimo è arrivato fino a qui senza entrare in nessun if significa che è il proprietario e ha già costruito tutto nei turni prima (fino all'albergo) e quindi siccome non può fare nulla il suo turno finisce
            }
            // Il giocatore è in una casella angolare, non succede nulla.
            std::cout << "Giocatore " << players[i]->getID() << " ha finito il turno.\n";
            file << "Giocatore " << players[i]->getID() << " ha finito il turno.\n";
        }
        // Tutti i giocatori hanno finito il loro turno

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
                std::cout << "\nGiocatore " << players[i]->getID() << " ha: " << players[i]->getMoney() << " " << Variabili::getValuta() << ".";
                file << "\nGiocatore " << players[i]->getID() << " ha: " << players[i]->getMoney() << " " << Variabili::getValuta() << ".";
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
            // controllo se qualche altro giocatore ha lo stesso quantitativo di soldi
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
    std::cout << "\n";
    file << "\n";
    if (j >= nMaxTurni)
    {
        std::cout << "\nGioco finito per raggiungimento limite massimo di turni (i giocatori rimasti in gioco hanno fatto " << j << " turni).";
        file << "\nGioco finito per raggiungimento limite massimo di turni (i giocatori rimasti in gioco hanno fatto " << j << " turni).";
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
    else    // if (winner.size() > 1), se non è 1 è per forza maggiore di uno, perchè quando esco dal game c'è sempre almeno un push
    {
        s = "\nVittoria a parimerito, hanno vinto i giocatori ";
        for (int i=0; i < winner.size(); i++)
        {
            s += std::to_string(winner[i]);
        }
        std::cout << s;
        file << s;
    }
    if (winner.size() == 0) // Non dovrebbe succedere MAI
    {
        std::cout << "\nVincitore non chiaro, qualcosa è andato storto nella chiusura del game.";
        file << "\nVincitore non chiaro, qualcosa è andato storto nella chiusura del game.";
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
    std::uniform_int_distribution<int> distr(1, Variabili::nFacceDado);

    int tiro=0;
    for (int i=0; i < Variabili::nDadi; i++)
    {
        tiro += distr(gen);
    }
    return tiro;
}

std::string startingOrder(std::vector<Giocatore *> &players)
{
    std::string output = "";
    std::vector<int> lanci;
    for (int i = 0; i < players.size(); i++) // assegno a ogni elemento un lancio di dadi
    {
        int l;
        /* Codice utile per testare il metodo starting order (8 è un numero totalmente a caso, ci si può mettere il numero che si vuole):
            if (i < players.size() - 1)
                l = 8;
            else
        */
        l = getDiceRoll();
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
    std::vector<std::vector<int>> indicidoppioni; // Matrice che conterrà gli indici per accedere ad eventuali giocatori di players con un tiro di dadi uguale
    std::vector<int> v;
    bool to_push = false;
    for (int i = 1; i < lanci.size(); i++)
    {
        if (lanci[i - 1] == lanci[i]) // Controllo se il giocatore i ed il precedente hanno fatto lo stesso numero di dadi
        {
            if (v.size() == 0) // Se il vettore è vuoto, allora devo inserire 2 elementi
            {
                v.push_back(i - 1);
            }
            v.push_back(i);
            if ((i == lanci.size() - 1) && (v.size() > 0)) // Per gestire anche il caso in cui almeno gli ultimi 2 giocatori hanno fatto lo stesso numero
            {
                to_push = true;
            }
        }
        else
        {
            to_push = true;
        }
        if ((to_push) && (v.size() != 0))
        {
            indicidoppioni.push_back(v);
            v.clear();
            to_push = false;
        }
    }
    // Se c'erano dei giocatori che hanno fatto un numero di dadi =, ritirano i dadi (tramite ricorsione)
    for (int i = 0; i < indicidoppioni.size(); i++)
    {
        std::vector<Giocatore *> tmp;
        output += "\n\nI giocatori ";
        for (int k = 0; k < indicidoppioni[i].size(); k++)
        {
            output += std::to_string(players[indicidoppioni[i][k]]->getID()) + " ";
            tmp.push_back(players[indicidoppioni[i][k]]);
        }
        output += "hanno fatto lo stesso numero, quindi ritirano i dadi.";
        if (!tmp.empty())
        {
            output += startingOrder(tmp);
        }
        // Ora che il vettore tmp è ordinato aggiorno il vettore players
        for (int k = 0; k < indicidoppioni[i].size(); k++)
        {
            players[indicidoppioni[i][k]] = tmp[k];
        }
    }

    return output;
}
