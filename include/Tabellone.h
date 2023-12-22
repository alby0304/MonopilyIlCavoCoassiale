#include <random>
#include "Casella_laterale.h"

const int dim_x = 8; // Numero di colonne
const int dim_y = 8; // Numero di righe: A=1, B=2, ... , H = 8, conversione con Index_riga
const int tot_caselle = 2*(dim_x + dim_y) - 4;  // -4 per togliere gli angoli (contati 2 volte se calcolo il "perimetro")


class Tabellone
{
    public:
    // Costruttore
    Tabellone();

    // Variabili
    Casella* partenza;   // Puntatore alla casella di partenza P (assegnamento nel costruttore)

    // Utile per l'operatore <<
    std::string to_String();

    char decide_type(int&, int&, int&);

    //variabili Const Tabellone
    

};

std::ostream& operator<< (std::ostream&, Tabellone);