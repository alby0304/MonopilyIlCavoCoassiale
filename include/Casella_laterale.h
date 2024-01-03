#ifndef CASELLA_LATERALE_H
#define CASELLA_LATERALE_H

#include "Casella.h"

class Casella_Laterale : public Casella
{
public:
    // Costruttore
    Casella_Laterale(int R, int C, char cont);

    // Funzioni Membro
    void buy(int* g); // compro casella, se ho casella compro casa, se ho casa compro albergo (set proprietario)
    int  getAffitto() const; // ritorna il prezzo da pagare di pedaggio (if casa e if albergo)
    int getProprietario();
    void reset(); // reset cella (per quando un giocatore perde)

    

    // Utile per la stampa
    std::string to_String() override;

private:
    bool _casa;
    bool _albergo;
    int  _proprietario; // Utile per capire se posso acquistarla o per sapere a chi devo pagare.

    // Variabili default casella
    int _prezzo_terreno;  // Quanto costa quando lo si acquista
    int _prezzo_casa;     // Quanto costa quando la si acquista
    int _prezzo_albergo;  // Quanto costa quando lo si acquista
    int _affitto_casa;    // Quanto costa pernottare
    int _affitto_albergo; // Quanto costa pernottare
};

#endif // CASELLA_LATERALE_H