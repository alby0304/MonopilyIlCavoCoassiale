// Christian De Chirico 2074972
#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Casella_Laterale.h"

class Casella_Laterale;

class Giocatore
{
public:
    // Costruttore
    Giocatore(int);
    Giocatore(){};

    Giocatore &operator=(Giocatore *g);

    // Funzioni membro
    void buy(); // Effettua l'acquisto (push della casella in elenco proprietà, set variabili casella_laterale)
    void move(int n);
    //***************
    // da implementare in futuro ;)
    // void move(position n);
    // void move(Casella c);
    //***************

    // Metodo per settare la casella, usato all'inizio del gioco per settare la posizone del giocatore nel tabellone (prima di iniziare a giocare)
    void setPos(Casella*);

    // Funzione GET
    int getMoney() const { return _money; }
    Casella *getPosition() const { return _pos; }
    int getID() const { return _ID; }
    bool isInGame() const { return _isInGame; }

    // Il giocatore sceglie se comprare (return true) o no (return false)
    virtual bool choice() { return false; };

    void resetPlayer(); // Per quando un giocatore perde

    // Funzioni di modifica soldi di un giocatore
    void Transfert(int n, Giocatore *Other); // Se non si hanno abbastanza soldi il giocatore non può pagare, viene eliminato e lancio eccezione
    void pay(int n);                         // Se non si hanno abbastanza soldi il giocatore non può pagare e lancio eccezione
    void deposit(int n);                     // chiamato quando un altro giocatore cade su un mio terreno e mi deve pagare o quando passo dal via

    std::string to_String_elenco_proprieta(); // Utile per la stampa

    // Eccezioni
    class Player_Lost
    {
    };
    class Not_Enough_Money
    {
    };

    // Variabili oggetto di giocatore
protected:
    std::vector<Casella_Laterale *> _elenco_proprieta;
    int _money;
    int _ID;        // Variabile che identifica il giocatore (tipo un codice fiscale, ogni giocatore ne avrà uno unico)
    bool _isInGame; // = true (nel costruttore), utile per capire se il giocatore è ancora in gioco
    Casella *_pos;  // La Casella su cui si trova il giocatore
};

#endif // GIOCATORE_H