#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <vector>
#include "Casella_Laterale.h"

class Casella_Laterale;

class Giocatore
{
public:
    // Costruttore
    Giocatore(int, Casella*);

    // Funzioni membro
    void buy(); // Effettua l'acquisto (push della casella in elenco proprietà, set variabili casella_laterale)
    virtual bool makeChoice() {return false;}; // Restituisce true se il giocatore vuole comprare il terreno/casa/albergo
    
    bool checkPosition();

    // Scambi di denaro tra giocatori
    void Transfert (int n, Giocatore* Other);
    void pay(int n);     // Se non si hanno abbastanza soldi il giocatore ha perso e lancio eccezione
    void deposit(int n); // Quando un altro giocatore cade su un mio terreno e mi deve pagare o quando passo dal via

    // Funzione GET
    int getMoney()          const   {return _money;}
    Casella* getPosition()  const   {return _pos;}
    
    // Move
    void move(int n);   //aggiornare _pos in cella;
    //***************
    // da implementare in futuro ;)
    // void move(position n);
    // void move(Casella c);
    //***************

    std::string to_String();
    std::string to_String_elenco_proprietà();

    // Distruttore
    ~Giocatore(); // _elenco_proprietà, _pos

    void resetPlayer();

    // Eccezione
    class You_Loosed{};
    class Not_Enough_Money{};
    
protected:
    std::vector<Casella_Laterale*> _elenco_proprieta;
    int _money;
    int ID;         // Variabile che identi si trova il giocatore nel tabellone
    bool _isInGame; // = true (utile per lfica il giocatore come giocatore 1, 2, 3, ecc. (utile per la stampa)
    Casella* _pos;  // La posizione in cuia stampa)
};

std::ostream& operator<<(std::ostream& os, Giocatore G);

#endif // GIOCATORE_H