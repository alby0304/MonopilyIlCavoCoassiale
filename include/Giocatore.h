#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <vector>
#include <string>
#include "Casella_Laterale.h"

class Casella_Laterale;
class Computer;
class Human;

class Giocatore
{
public:
    // Costruttore
    Giocatore(int, Casella*,int money);
    Giocatore() {};

    Giocatore& operator=(Giocatore* g);

    // Funzioni membro
    void buy(); // Effettua l'acquisto (push della casella in elenco proprietà, set variabili casella_laterale)

    virtual bool choice(){return false;}; 

    void resetPlayer();              // Per quando un giocatore perde

    // Scambi di denaro tra giocatori
    void Transfert (int n, Giocatore* Other);
    void pay(int n);     // Se non si hanno abbastanza soldi il giocatore non può pagare e lancio eccezione
    void deposit(int n); // Quando un altro giocatore cade su un mio terreno e mi deve pagare o quando passo dal via

    // Funzione GET
    int getMoney()          const   {return _money;}
    Casella* getPosition()  const   {return _pos;}
    int getID()             const   {return ID;}
    bool isInGame()         const   {return _isInGame;}
    
    // Move
    void move(int n);   //aggiornare _pos in cella;
    //***************
    // da implementare in futuro ;)
    // void move(position n);
    // void move(Casella c);
    //***************

    std::string to_String_elenco_proprieta();

    // Distruttore
    ~Giocatore(); // _elenco_proprietà, _pos

    // Eccezioni
    class You_Loosed{};
    class Not_Enough_Money{};
    
    static const int _moneyPassaggioVia = 20;
protected:
    std::vector<Casella_Laterale*> _elenco_proprieta;
    int _money;
    int ID;         // Variabile che identi si trova il giocatore nel tabellone
    bool _isInGame; // = true (utile per lfica il giocatore come giocatore 1, 2, 3, ecc. (utile per la stampa)
    Casella* _pos;  // La posizione in cuia stampa)
};

#endif // GIOCATORE_H