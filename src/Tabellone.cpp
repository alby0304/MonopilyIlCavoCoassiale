// Giulio Zanardi 2076063

#include "../include/Tabellone.h"

/*  
Il meccanismo di creazione del tabellone viene brevemente spiegato qui:
Il tabellone ha come variabile membro un puntatore alla casella di partenza.
Creo la casella di partenza.
Poi in base a quanto grande è il campo da gioco inserisco n-1 caselle (Ex. 8x8 => n_caselle = 24, quindi ne devo inserire altre 23).
Per ogni casella setto la posizione (Ex. A2) in base alle proprietà del labirinto (numero di caselle orizzontali e verticali)
Una volta capito se angolare o laterale la creo e la aggiungo alla lista.
Per la creazione casuale delle caselle laterali c'è il metodo decide_type e ho a disposizione E = 8 economiche, S = 10 Standard, L = 6 lusso (da creare).
Ogni volta che ne viene creata una, diminuisce il numero di caselle disponibili da creare.
Alla fine del processo l'ultima casella punterà alla casella di partenza creando così una lista concatenata di caselle chiusa in sè stassa.
*/

Tabellone::Tabellone(int tot_R, int tot_C)
{
    // Scelta progettuale: non si possono creare tabelloni più piccoli di un 3x3
    if ((tot_R < 3) || (tot_C < 3) || (tot_R >= 27))
        throw Too_Small();

    // Set delle variabili di default del tabellone
    dim_y = tot_R;
    dim_x = tot_C;
    tot_caselle = 2 * (dim_x + dim_y) - 4; // -4 per togliere gli angoli contati 2 volte

    int tot_caselle_laterali = tot_caselle - 4; // -4 per togliere gli angoli
    // A seconda di percentuali che "saltavano all'occhio" dalla consegna del progetto il tabellone calcola sempre il numero di caselle E,S,L a seconda di tot_caselle
    E = tot_caselle_laterali / 3;     // il 33% circa delle caselle laterali totali (-4 per togliere gli angoli) saranno economiche
    L = tot_caselle_laterali / 4;     // il 25% circa delle caselle laterali totali saranno lusso
    S = tot_caselle_laterali - E - L; // il restante 42% circa delle caselle laterali totali (le rimanenti per arrivare a tot_caselle_laterali) saranno standard

    // Indici di riga e colonna
    int indice_riga = tot_R - 1;
    int indice_colonna = tot_C;

    // Creo e riempio di dati la prima casella
    partenza = new Casella{indice_riga, indice_colonna, 'P'};

    // Creo un puntatore con cui spostarmi per creare le caselle successive alla prima
    Casella *Casella_Now = partenza;
    // Utili per le variazioni degli indici (assumono solo 0 e 1 e -1)
    int vx = -1, vy = 0;

    // Creo le altre caselle
    for (int i = 1; i < tot_caselle; i++) // i=1 perchè ho già sistemato la prima casella
    {
        // Aggiorno gli indice di riga e colonna
        indice_colonna += vx;
        indice_riga += vy;
        // Creo il puntatore ad una nuova casella
        Casella *New_Casella;

        if ((i == dim_x - 1) || (i == dim_x + dim_y - 2) || (i == 2 * dim_x + dim_y - 3)) // Mi trovo agli angoli (escluso P, già creato)
        {
            // Creo una nuova casella angolare
            New_Casella = new Casella{indice_riga, indice_colonna, ' '};

            // Sono nel secondo angolo, ora gli indici devono aumentare quindi cambio il segno alla velocità
            if (i == dim_x + dim_y - 2)
                vy = -vy;

            // Cambio di direzione della variazione degli indici (lo faccio quando creo un angolo)
            int tmp = vx;
            vx = vy;
            vy = tmp;
        }
        else
        {
            // Creo una nuova casella laterale
            New_Casella = new Casella_Laterale{indice_riga, indice_colonna, decide_type(E, S, L)};
        }

        // Aggiungo la casella al tabellone e mi sposto su di essa
        Casella_Now->setSucc(New_Casella);
        Casella_Now = New_Casella;

        // Chiusura della lista concatenata su sè stessa ("head" = "tail" = "tabellone")
        if (i == tot_caselle - 1)
            Casella_Now->setSucc(partenza);
    }
}

char Tabellone::decide_type(int &E, int &S, int &L)
{
    // Inizializza il generatore di numeri casuali con un seed basato sull'orologio di sistema
    std::random_device rd;
    std::mt19937 gen(rd());

    // Definisci la distribuzione uniforme per generare numeri tra 1 e 3
    std::uniform_int_distribution<int> distr(1, 3);

    bool goodchar = false; // Valore iniziale scelto arbitrariamente (non E, S o L)
    char c;
    do
    {
        int numeroCasuale = distr(gen);
        if ((numeroCasuale == 1) && (E > 0))
        {
            c = 'E';
            goodchar = true;
            (E)--;
        }
        if ((numeroCasuale == 2) && (S > 0))
        {
            c = 'S';
            goodchar = true;
            (S)--;
        }
        if ((numeroCasuale == 3) && (L > 0))
        {
            c = 'L';
            goodchar = true;
            (L)--;
        }
    } while (!goodchar);

    return c;
}

std::string Tabellone::to_String()
{

    std::string tmp;
    std::string space;
    // Creo la stringa space in base alla dimensione di una Casella
    for (int i = 0; i < Variabili::dimMaxCasella; i++)
    {
        space += " ";
    }

    std::string s = "\n"; // stringa che conterrà tutto il tabellone
    // Comincio a salvare la prima riga
    s = s + space;
    // Finisco di salvare tutta la prima riga (l'intestazione con le colonne A, B, C ...)
    for (int i = 1; i <= dim_x; i++)
    {
        tmp = std::to_string(i);
        s += normalize(tmp);
    }
    // Vado a capo
    s = s + "\n";

    // Ora stampo il tabellone

    Casella *Target;
    for (int i = 0; i < dim_y; i++)
    {
        // Inizio di riga
        tmp = int_to_char(i);
        s += normalize(tmp);
        for (int j = 0; j < dim_x; j++)
        {
            if ((i == 0) || (i == dim_y - 1) || (j == 0) || (j == dim_x - 1)) // Se sono ai bordi del tabellone
            {
                std::pair<char, int> target(int_to_char(i), j + 1);
                Target = partenza->find(target);
                s = s + Target->to_String();
            }
            else // Sono in mezzo, quindi devo stampare spazio vuoto
                s = s + space;
        }
        s = s + "\n";
    }

    return s;
}

std::ostream &operator<<(std::ostream &os, Tabellone A)
{
    return os << A.to_String();
}

std::string Tabellone::getLegenda()
{
    std::string s = "\nLegenda:";

    // Ciclo per stampare in legenda dov'è ogni giocatore
    Casella *next = partenza;
    do
    {
        if (next->_players.size() > 0) // Se nella casella next ci sono giocatori
        {
            for (int i = 0; i < next->_players.size(); i++) // Questo for è per verificare se nella casella corrente c'è più di un giocatore
            {
                s += "\nGiocatore " + std::to_string(next->_players[i]) + " nella casella " + next->getCoordinata_to_String();
                Casella_Laterale *_pos1 = dynamic_cast<Casella_Laterale *>(next); // se il casting va a buon fine
                if (_pos1)
                {
                    if (_pos1->isAlbergo())
                    {
                        s += " con albergo.";
                    }
                    else if (_pos1->isCasa())
                    {
                        s += " con casa.";
                    }
                }
            }
        }
        next = next->getSucc(); // Passo alla successiva e ripeto
    } while (next->getType() != 'P');

    // Ciclo per stampare in legenda caselle con case/alberghi (caselle non ancora stampate)
    next = partenza;
    do
    {
        next = next->getSucc();                                           // Passo alla successiva e ripeto
        Casella_Laterale *_pos1 = dynamic_cast<Casella_Laterale *>(next); // se il casting va a buon fine
        if (_pos1)
        {
            if (_pos1->isAlbergo())
            {
                if (next->_players.size() > 0)
                {
                    // Non la stampo in legenda, perchè la ho già stampata prima con il/i giocatore/i che é/sono sopra alla casella
                }
                else
                {
                    s += "\nCasella " + _pos1->getCoordinata_to_String() + " con albergo.";
                }
            }
            else if (_pos1->isCasa())
            {
                if (next->_players.size() > 0)
                {
                    // Non la stampo in legenda, perchè la ho già stampata prima con il/i giocatore/i che é/sono sopra alla casella
                }
                else
                {
                    s += "\nCasella " + _pos1->getCoordinata_to_String() + " con casa.";
                }
            }
        }
    } while (next->getType() != 'P');

    return s + "\n";
}