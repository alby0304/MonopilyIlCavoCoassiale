#include <random>
#include "Casella_laterale.h"

class Tabellone
{
public:
    // Costruttore
    Tabellone();  // Assegna di default 8 righe e 8 colonne
    Tabellone(int righe, int colonne); 
    
    std::string to_String(); // Utile per l'operatore <<
    
private:
    Casella *partenza; // Puntatore alla casella di partenza P (assegnamento nel costruttore)
    
    // Variabili Membro const
    const int dim_x;                             // Numero di colonne
    const int dim_y;                             // Numero di righe: A=1, B=2, ... , H = 8, conversione con Index_riga
    const int tot_caselle = 2 * (dim_x + dim_y) - 4; // -4 per togliere gli angoli (contati 2 volte se calcolo il "perimetro")

    //Funzioni membro per decdere il tipo di casella (E,S,L)
    char decide_type(int &, int &, int &);
};

std::ostream &operator<<(std::ostream &, Tabellone);
