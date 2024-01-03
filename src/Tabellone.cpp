#include "../include/Tabellone.h"
#include "Casella_laterale.cpp"

/*  Il meccanismo di creazione del tabellone viene brevemente spiegato qui.
    Il tabellone ha come variabile membro un puntatore alla casella di partenza.
    Creo la casella di partenza.
    Poi in base a quanto grande è il campo da gioco inserisco n-1 caselle (Ex. 8x8 => n_caselle = 24, quindi ne devo inserire altre 23).
    Per ogni casella setto la posizione (Ex. A2) andrà inserita tramite le proprietà del labirinto (numero di caselle orizzontali e verticali)
    Una volta capito se angolare o laterale la creo e la aggiungo alla lista.
    Per la creazione casuale delle caselle laterali c'è il metodo decide_type e ho a disposizione E = 8 economiche, S = 10 Standard, L = 6 lusso (da creare).
    Ogni volta che ne viene creata una, diminuisce il numero di caselle disponibili da creare.
    Alla fine del processo l'ultima casella punterà alla casella di partenza creando così una lista concatenata di caselle chiusa in sè stassa.
*/
Tabellone::Tabellone(int tot_R, int tot_C) 
{    
    // Set delle variabili di default del tabellone
    dim_y = tot_R;
    dim_x = tot_C;
    tot_caselle = 2 * (dim_x + dim_y) - 4; // -4 per togliere gli angoli contati 2 volte

    // Indici di riga e colonna
    int indice_riga = tot_R - 1;
    int indice_colonna = tot_C;

    // Creo e riempio di dati la prima casella
    partenza = new Casella {indice_riga,indice_colonna,'P'};

    // Creo un puntatore con cui spostarmi per creare le caselle successive alla prima
    Casella* Casella_Now = partenza;
    // Utili per le variazioni degli indici (assumono solo 0 e 1 e -1)
    int vx = -1, vy = 0;
    
    // Creo le altre caselle
    for (int i=1; i < tot_caselle; i++) // i=1 perchè ho già sistemato la rpima casella
    {
        // Aggiorno gli indice di riga e colonna
        indice_colonna += vx;
        indice_riga    += vy;
        // Creo il puntatore ad una nuova casella
        Casella* New_Casella;

        if ((i == dim_x - 1) || (i == dim_x + dim_y - 2) || (i == 2*dim_x + dim_y - 3)) // Mi trovo agli angoli (escluso P, già creato)
        {
            // Creo una nuova casella angolare
            New_Casella = new Casella{indice_riga,indice_colonna,' '};

            // Cambio di direzione della variazione degli indici (lo faccio quando creo un angolo)
            if (i == dim_x + dim_y - 2)     // Sono nel secondo angolo, ora gli indici devono aumentare quindi cambio il segno alla velocità
                vy = -vy;
            int tmp = vx;
            vx = vy;
            vy = tmp;
        }
        else
        {
            // Creo una nuova casella laterale
            New_Casella = new Casella_Laterale {indice_riga,indice_colonna,decide_type(E, S, L)};
        }
        
        // Aggiungo la casella al tabellone e mi sposto su di essa
        Casella_Now->setSucc(New_Casella);
        Casella_Now = New_Casella;
        
        // Chiusura della lista concatenata su sè stessa ("head" = "tail" = "tabellone")
        if(i==tot_caselle-1)
            Casella_Now->setSucc(partenza);

    }
}

char Tabellone::decide_type(int& E, int& S, int& L)
{
    // Inizializza il generatore di numeri casuali con un seed basato sull'orologio di sistema
    std::random_device rd;
    std::mt19937 gen(rd());

    // Definisci la distribuzione uniforme per generare numeri tra 1 e 3
    std::uniform_int_distribution<int> distr(1, 3);

    char c = 'j'; // Valore iniziale scelto arbitrariamente (non E, S o L)
    do
    {
        int numeroCasuale = distr(gen);
        if ((numeroCasuale==1)&&(E>0))
        {
            c = 'E';
            (E)--;
        }
        if ((numeroCasuale==2)&&(S>0))
        {
            c = 'S';
            (S)--;
        }
        if ((numeroCasuale==3)&&(L>0))
        {
            c = 'L';
            (L)--;
        }
    } while (c=='j');

    return c;
}

std::string Tabellone::to_String()
{
    
    std::string tmp;
    std::string space;
    // Creo la stringa space in base alla dimensione di una Casella
    for (int i=0; i < _dim_max_Casella; i++)
    {
        space += " ";
    }

    std::string s = ""; // stringa che conterrà tutto il tabellone
    // Comincio a salvare la prima riga
    s = s + space;
    // Finisco di salvare tutta la prima riga (l'intestazione con le colonne A, B, C ...)
    for (int i=1; i <= dim_x; i++)
    {
        tmp = std::to_string(i);
        s += normalize(tmp);
    }
    // Vado a capo
    s = s + "\n";

    // Ora stampo il tabellone
    Casella* Target;
    for (int i=0; i < dim_y; i++)
    {
        // Inizio di riga
        tmp = int_to_char(i);
        s += normalize(tmp);
        for (int j=0; j < dim_x; j++)
        {
            if ((i==0)||(i==dim_y-1)||(j==0)||(j==dim_x-1)) // Se sono ai bordi del tabellone
            {
                std::pair<char, int> target(int_to_char(i), j+1);
                Target = partenza->find(target);
                s = s + Target->to_String();
            }
            else    // Sono in mezzo, quindi devo stampare spazio vuoto
            s = s + space;
        }
        s = s + "\n";
    }
    
    /*
    std::string s = "Celle di gioco:\n" + partenza->to_String();
    Casella* next = partenza->getSucc();
    while (next->getType() != 'P')
    {
        if (next->getType() == ' ')
        { s= s + "\n";}
        s = s + next->to_String();
        next = next->getSucc();
    }
    */
    return s;
}

std::ostream& operator<< (std::ostream& os, Tabellone A)
{
    return os << A.to_String();
}
