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
int getDiceRoll();                   // restituisce la somme di due numeri casuali tra 1 e 6
std::vector<int> startingOrder(int); // mi restituisce un vettore di int con l'ordine di partenza dei vari giocatori es [1,3,4,2];

// Mode passata come argomento da terminale
int main(int argc, char *argv[])
{
    // Dichiarazione di variabili
    const int N_giocatori = 4;
    const int N_Max_turni = 50;                          // Ogni giocatore se sono in una partita tra robot fa al massimo N_Max_turni
    const int max_Iteration = N_Max_turni * N_giocatori; // Numero di turni massimo per partita tra soli computer
    int j = 0;                                           // Contatore di turni
    bool human;                                          // Variabile che mi dice se ho creato un giocatore Human (=true), o un giocatore computer (=false)
    bool game_is_On = true;
    Tabellone T;                      // creo il tabellone
    std::vector<Giocatore *> players; // I giocatori che sono dentro players sono quelli che giocano, se un giocatore viene eliminato esce dal vettore

    // Lettura di ciò che c'è scritto in riga di comando
    // verifico che
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <argument>" << std::endl;
        return 1; // Restituisce 1 in caso di errore
    }
    std::string mode = argv[1]; // salvo l'argomento passato da terminale
    // Creazione del primo giocatore a seconda del mode
    if (mode == "computer")
    {
        human = false;
        Giocatore *player1 = new Computer{1, T.partenza};
        players.push_back(player1);
    }
    else if (mode == "human")
    {
        human = true;
        Giocatore *player1 = new Human{1, T.partenza};
        players.push_back(player1);
    }
    else
    {
        std::cout << "Argomenti errati riprovate, Argomenti accettari\n computer: partita con 4 Computer \n human: partita con 3 Computer e un Human";
        return 1;
    }

    // Creazione degli altri 3 giocatori e relativo push nel vettore players
    for (int i = 2; i <= N_giocatori; i++)
    {
        Giocatore *player = new Computer{i, T.partenza};
        players.push_back(player);
    }

    std::vector<int> ordine = startingOrder(N_giocatori);

    std::cout << "\nL'ordine di gioco dei giocatori è";
    for (int i = 0; i < ordine.size(); i++)
    {
        std::cout << ordine[i] << " ";
    }
    std::cout << "\nBenvenuto, questo e' il tabellone:"
              << T << "\nOra inizia il gioco.";
    while (game_is_On)
    {
        // I giocatori fanno il loro turno
        for (int t = 0; t < players.size(); t++)
        {
            // All'inzio di ogni turno capisco a che giocatore spetta di giocare secondo il vettore order
            int i = ordine[t] - 1; // -1 perchè agli elelemti di players si accede con l'indice = ID-1 (Ex. Al giocatore con ID = 4 si accede con players[3])
            // Faccio un cambio di indice d'accesso, da t passo a i
            // Sfrutto il fatto che in players i giocatori sono salvati con ID crescente a partire da 1, quindi se nel vettore order
            // come primo elemento c'è un 3, allora i = order[0] - 1 = 3 - 1 = 2. players[i] punta al giocatore con ID = 3
            j++;
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
            if (players[i]->getMoney() != tmpMoney)
                std::cout << "\nGiocatore " << players[i]->getID() << " e' passato dal via e ha ritirato 20 fiorini.";
                
            // Verifico su che casella sono capitato
            Casella_Laterale *_pos1 = dynamic_cast<Casella_Laterale *>(players[i]->getPosition()); // se il casting va a buon fine
            if (_pos1)                                                                             // Se mi trovo su una casella laterale
            {
                if (_pos1->getProprietario() == nullptr) // La casella laterale non è di nessuno, quindi posso comprarla
                {
                    bool scelta = players[i]->want_to_buy_terreno();
                    if (scelta)
                    {
                        try
                        {
                            players[i]->buy();
                            std::cout << "\nGiocatore " << players[i]->getID() << " ha acquistato casella " << players[i]->getPosition()->getCoordinata_to_String();
                        }
                        catch (const std::exception &Not_Enough_Money)
                        {
                            std::cout << "\nTentativo di acquisto terreno non riuscito, troppi pochi soldi.";
                        }
                    }
                }
                else if (_pos1->getProprietario() == players[i]) // La casella laterale è del giocatore che ci è appena finito sopra
                {
                    if ((!_pos1->isAlbergo()) && (_pos1->isCasa())) // Se non c'è un albergo e c'è una casa (deve esserci già una casa per costruire un albergo) il giocatore può decidere di comprare l'albergo (acquisto consentito se ha abbastanza soldi)
                    {
                        bool scelta = players[i]->want_to_buy_albergo();
                        if (scelta)
                        {
                            try
                            {
                                players[i]->buy();
                                std::cout << "\nGiocatore " << players[i]->getID() << " ha acquistato albergo in " << players[i]->getPosition()->getCoordinata_to_String();
                            }
                            catch (const std::exception &Not_Enough_Money)
                            {
                                std::cout << "\nTentativo di acquisto albergo non riuscito, troppi pochi soldi.";
                            }
                        }
                    }
                    if (!_pos1->isCasa()) // Se non c'è una casa il giocatore può decidere di comprarla (acquisto consentito se ha abbastanza soldi)
                    {
                        bool scelta = players[i]->want_to_buy_casa();
                        if (scelta)
                        {
                            try
                            {
                                players[i]->buy();
                                std::cout << "\nGiocatore " << players[i]->getID() << " ha acquistato casa in " << players[i]->getPosition()->getCoordinata_to_String();
                            }
                            catch (const std::exception &Not_Enough_Money)
                            {
                                std::cout << "\nTentativo di acquisto casa non riuscito, troppi pochi soldi.";
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
                            players[i]->Transfert(_pos1->getAffitto(), _pos1->getProprietario());
                            // Il metodo Transfert gestisce l'eccezione lanciata in caso di mancanza di soldi eliminando
                            // il giocatore (se deve pagare 10 e ha solo 5 paga 5, arriva a 0 euro, perde tutte le proprietà
                            // (che tornano senza proprietario, nuovamente acquistabili) e viene settato che ha perso, quando
                            // tutti i giocatori avranno finito il loro turno il giocatore verrà rimosso dal vettore player, vedi codice uscito dal ciclo for).
                            std::cout << "\nIl giocatore " << players[i]->getID() << "ha pagato un affitto di " << _pos1->getAffitto() << " al giocatore " << _pos1->getProprietario()->getID();
                        }
                        catch (const std::exception &You_Loosed)
                        {
                            std::cout << "\nIl giocatore " << players[i]->getID() << "ha perso perchè non aveva abbastanza soldi per pagare l'affitto al giocatore " << _pos1->getProprietario()->getID();
                        }
                    }
                }
                // Se il giocatore è arrivato fino a qui senza entrare in nessun if significa che è il proprietario e ha già costruito tutto nei turni prima (fino all'albergo) e quindi siccome non può fare nulla il suo turno finisce
            }
            else
            {
                // Non succede nulla, poichè mi trovo su una casella angolare
            }
        }
        // Tutti i giocatori hanno finito il loro turno
        // Stampo tabellone
        std::cout << T;
        // Stampo gli schei e le proprietà di ogni giocatore
        for (int i = 0; i < players.size(); i++)
        {
            std::cout << players[i]->to_String() << ". Fiorini = " << players[i]->getMoney();
        }
        // Il programma fa una pausa di 1 secondo ogni volta che tutti i giocatori hanno finito il proprio turno
        std::this_thread::sleep_for(std::chrono::seconds(1));
        // std::system("cls");     // Pulizia schermo

        // Verifiche per capire se continuare a giocare (set game_is_On = false)
        // Verifica se i giocatori (contenuti in player) sono ancora in gioco, se non si è più in gioco si viene rimossi dal vettore
        for (int i = 0; i < players.size(); i++)
        {
            if (!players[i]->isInGame()) // Se il giocatore non è più in game
            {                            // lo tolgo dal vettore di players
                // players[i].resetPlayer(); => quest'istruzione non serve perchè se un giocatore non è più in game si auto-elimina, in game bisogna solo toglierlo dal vettore di players
                players.erase(players.begin() + i);
                // Qualche chiamata al distruttore del giocatore eliminato per liberare spazio in memoria (se serve, come fare??)
            }
        }
        // C'è 1 solo giocatore, il gioco si ferma e vince l'ultimo rimasto
        if (players.size() == 1)
            game_is_On = false;
        // Arrivo al turno di gioco 4000 per ogni giocatore, il gioco si ferma e vince chi ha più soldi
        if ((!human) && (j > max_Iteration)) // partita tra soli robot
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
    if (human) // Se nella partita c'era un giocatore umano
    {
        if (players[0]->getID() == 1) // Se l'ultimo giocatore rimasto è l'1, allora è l'umano
            std::cout << "\nComplimenti, hai vinto !!!";
        else
            std::cout << "\nHa vinto il giocatore " << players[0]->getID();
    }
    else if (j > max_Iteration)
        std::cout << "\nGioco finito per raggiungimento limite massimo di turni (turni giocati = " << N_Max_turni << ")";
    std::cout << "\nHa vinto il giocatore " << players[0]->getID();

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

std::vector<int> startingOrder(int N_giocatori)
{
    std::vector<int> lanci;
    for (int i = 0; i < N_giocatori; i++)
    {
        int l = getDiceRoll();
        std::cout << "\nGiocatore " << i + 1 << " ha tirato i dadi e ha fatto " << l;
        lanci.push_back(l);
    }
    std::vector<int> order;
    for (int i = 1; i <= N_giocatori; i++)
    {
        order.push_back(i);
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
                tmp = order[i - 1];
                order[i - 1] = order[i];
                order[i] = tmp;
                isOrder = false;
            }
        }
    }
    return order;
}