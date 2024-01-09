// Giulio Zanardi 2076063

#ifndef VARIABILI_H
#define VARIABILI_H

#include <string>

// Cambiando i valori di questa struct si può personalizzare il gioco
// (valori delle costanti settate secondo la consegna del progetto)

struct Variabili
{
    public:
    // Variabili
    static const int nDadi = 2;
    static const int nFacceDado = 6;
    static const std::string getValuta() {return "fiorini";}
    static const int moneyPassaggioVia = 20;
    static const int initialMoney = 100;
    static const int nGiocatori = 4;
    static const int nRigheT = 8;
    static const int nColonneT = 8;
    static const int maxTurniComputer = 400;
    static const int maxTurniHuman = 100;
    static const int dimMaxCasella = nGiocatori + 5; // Per l'output del tabellone
    /*
    Per stampare il carattere di inizio casella "|"                                             (1)
    + il tipo di casella "E/S/L/ /P"                                                            (1)
    + il numero di giocatori sopra alla casella (massimo nGiocatori, caso raro ma possibile)    (nGiocatori)
    + eventuale casa/albergo                                                                    (0-1)
    + carattere di chiusura cella "|"                                                           (1)
    Aggiungo qualche spazio a destra e sinistra per avere un output del tabellone più omogeneo  (1-2)
    */
    
    static const int prezzoTerrenoE = 6;
    static const int prezzoCasaE = 3;
    static const int prezzoAlbergoE = 3;
    static const int affittoCasaE = 2;
    static const int affittoAlbergoE = 4;

    static const int prezzoTerrenoS = 10;
    static const int prezzoCasaS = 5;
    static const int prezzoAlbergoS = 5;
    static const int affittoCasaS = 4;
    static const int affittoAlbergoS = 8;

    static const int prezzoTerrenoL = 20;
    static const int prezzoCasaL = 10;
    static const int prezzoAlbergoL = 10;
    static const int affittoCasaL = 7;
    static const int affittoAlbergoL = 14;

};

#endif  // VARIABILI_H