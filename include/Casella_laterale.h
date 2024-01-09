// Giulio Zanardi 2076063

#ifndef CASELLA_LATERALE_H
#define CASELLA_LATERALE_H

#include "Casella.h"
#include "Giocatore.h"

// Forward declaration di Giocatore
class Giocatore;

class Casella_Laterale : public Casella
{
public:
    // Costruttore
    Casella_Laterale(int R, int C, char cont);

    // Funzioni Membro
    void buy(Giocatore* g); // compro casella (set proprietario), se ho casella compro casa, se ho casa compro albergo
    void reset();           // reset cella (per quando un giocatore perde)
    int getAffitto() const; // ritorna il prezzo da pagare di pernottamento (in casa o in albergo)
    int getPrezzo();        // restituisce il prezzo per aquistare la casella/casa/albergo
    Giocatore* getProprietario() const { return _proprietario; }
    bool isCasa() const { return _casa; }
    bool isAlbergo() const { return _albergo; }

    // Utile per la stampa
    std::string to_String() override;

private:
    bool _casa;               // true se c'è una casa
    bool _albergo;            // true se c'è un albergo
    Giocatore* _proprietario; // Utile per capire se posso acquistarla o per sapere a chi devo pagare.

    // Variabili default casella
    int _prezzo_terreno;  // Quanto costa l'acquisto
    int _prezzo_casa;     // Quanto costa l'acquisto
    int _prezzo_albergo;  // Quanto costa l'acquisto
    int _affitto_casa;    // Quanto costa pernottare
    int _affitto_albergo; // Quanto costa pernottare
};

#endif // CASELLA_LATERALE_H