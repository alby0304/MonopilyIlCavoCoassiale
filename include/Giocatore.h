#ifndef GIOCATORE_H
#define GIOCATORE_H

#include <vector>
#include "Casella.h"

class Giocatore
{
    // Costruttori
    Giocatore();
    Giocatore(std::string Name);

    //funzioni membro
    void buy(); //verificare se si ha abbastanza soldi (lancio eccezione)
    virtual bool makeChoice() = 0; // Restituisce true se il giocatore vuole e può comprare il terreno/casa/albergo
    
    // Scambi di denaro tra giocatori
    void pay(int n);     // Se non si hanno abbastanza soldi il giocatore ha perso e lancio ecezione
    void deposit(int n); // Quando un giocatore cade su un mio terreno e mi deve pagare

    // Funzione GET
    int getMoney(){return _money;}
    
    // Move
    void move(int n);   //aggiornare _pos in cella;
    //***************
    // da implementare in futuro ;)
    void move(position n);
    void move(Casella c);
    //***************

    // Distruttore
    ~Giocatore(); // _elenco_proprietà, pos

    //ecezione
    class youArePoor{}; //:(
private:
    std::vector<Casella*> _elenco_proprietà;
    int _money;
    std::string _name;
    Casella* _pos;
    bool _isInGame; // = true
};

std::ostream &operator<<(std::ostream &, Giocatore); // ES Giocatore1 : A2, B6 (elenco proprietà);

#endif // GIOCATORE_H