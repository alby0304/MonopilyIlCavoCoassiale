#ifndef CASELLA_LATERALE_H
#define CASELLA_LATERALE_H

#include "Casella.h"
#include "Giocatore.h"

class Casella_Laterale : public Casella
{
    public:
    // Costruttore
    Casella_Laterale(Index_riga R, int C, char cont);

    void buyCell(Giocatore g);

    // Utile per la stampa
    std::string to_String() override;

    // Variabili
    bool _casa;
    bool _albergo;
    Giocatore*  _proprietario;     // Utile per capire se posso acquistarla o per sapere a chi devo pagare.
    int  _prezzo_terreno;   // Quanto costa quando lo si acquista
    int  _prezzo_casa;      // Quanto costa quando la si acquista
    int  _prezzo_albergo;   // Quanto costa quando lo si acquista
    int  _affitto_casa;     // Quanto costa pernottare
    int  _affitto_albergo;  // Quanto costa pernottare
};

#endif  // CASELLA_LATERALE_H