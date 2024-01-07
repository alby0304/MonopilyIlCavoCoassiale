// Giulio Zanardi 2076063
#include <random>
#include "Casella_Laterale.h"

/*  Il tabellone è una lista concatenata di caselle e può avere numero di righe indipendente dal numero di colonne
    Posso creare tabelloni 3x4, 9x15, ecc.
    Bisogna solo aggiornare quante caselle economiche, standard e di lusso posso inserire (variabili di dafault del tabellone)
    Inoltre il tabellone è sempre un quadrato (non un pentagono, o esagono o altre forme che non siano il classico tabellone quadrato del monopoli)
*/

class Tabellone
{
public:
    // Costruttori
    Tabellone() : Tabellone(8, 8){}; // Assegna di default 8 righe e 8 colonne
    Tabellone(int R, int C);

    // Utili per la stampa in output
    std::string to_String();
    std::string getLegenda();

    // Variabili oggetto del tabellone
    Casella* partenza; // Puntatore alla casella di partenza P (assegnamento nel costruttore)
private:
    // Variabili Membro "const" (caratteristiche del tabellone, utili per la stampa)
    int dim_x; // Numero di colonne
    int dim_y; // Numero di righe: A=1, B=2, ... , H = 8, conversione con Index_riga
    int tot_caselle;
    // Numero massimo (da inserire) di caselle per ogni tipo (sarebbe figo creare questi valori dal numero totale di caselle, tramite qualche % di tot_caselle)
    int E = 8;           // Numero massimo di caselle economiche
    int S = 10;          // Numero massimo di caselle standard
    int L = 6;           // Numero massimo di caselle lusso
    int dim_max_Casella; // Per l'output
    // Funzione membro per decidere il tipo di casella (E,S,L)
    char decide_type(int &, int &, int &);
};

std::ostream &operator<<(std::ostream &, Tabellone);