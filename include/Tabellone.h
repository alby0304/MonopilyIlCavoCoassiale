// Giulio Zanardi 2076063

#include <random>
#include "Casella_Laterale.h"

/*  
Il tabellone è una lista concatenata di caselle e può avere numero di righe indipendente dal numero di colonne
Posso creare tabelloni 3x4, 9x15, ecc.
Limitazioni:
- il tabellone è sempre un quadrato (non un pentagono, o esagono o altre forme che non siano il classico tabellone quadrato del monopoli)
- il tabellone più piccolo creabile è un 3x3 (scelta progettuale), perchè:
    -> se cerco di creare tabelloni 1xN o Nx1 => sto cercando di creare tabelloni con una sola dimensione
    (non ha senso per il gioco di monopoly)
    -> se cerco di creare tabelloni  2xN  Nx2 => sto cercando di creare tabelloni di 2 righe / 2 colonne,
    quindi con 2 caselle angolari vicine e quindi senza caselle laterali in verticale/orizzontale 
    (il tabellone non va bene per il gioco di monopoly)
*/

class Tabellone
{
public:
    // Costruttori
    Tabellone() : Tabellone(Variabili::nRigheT, Variabili::nColonneT){}; // Assegna di default le variabili predefinite
    Tabellone(int R, int C);

    // Utili per la stampa in output
    std::string to_String();
    std::string getLegenda();

    // Classe lanciata in caso di tentativo di creazione di un tabellone con righe/colonne troppo bassi
    class Too_Small{};

    // Variabili oggetto del tabellone
    Casella* partenza; // Puntatore alla casella di partenza P (assegnamento nel costruttore)
private:
    // Variabili Membro "const" (caratteristiche del tabellone, utili per la stampa)
    int dim_x; // Numero di colonne
    int dim_y; // Numero di righe: A=1, B=2, ... , H = 8, conversione con Index_riga
    int tot_caselle;

    // Numero massimo (da inserire) di caselle per ogni tipo
    int E, S, L;

    /* Il tabellone calcola autonomamente il valore di queste variabili nel costruttore secondo percentuali di tot_caselle, quindi non serve dichiararle così:
    int E = 8;           // Numero massimo di caselle economiche
    int S = 10;          // Numero massimo di caselle standard
    int L = 6;           // Numero massimo di caselle lusso
    */

    // Funzione membro per decidere il tipo di casella (E,S,L)
    char decide_type(int &, int &, int &);
};

std::ostream &operator<<(std::ostream &, Tabellone);