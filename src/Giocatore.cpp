// Christian De Chirico 2074972
#include "../include/Casella_Laterale.h"
#include "../include/Giocatore.h"

Giocatore::Giocatore(int n) : _ID{n}, _isInGame{true}, _money{Variabili::initialMoney}  {}

void Giocatore::setPos(Casella* P){
    _pos = P;
    _pos->addPlayer(_ID);
}
Giocatore &Giocatore::operator=(Giocatore *g){
    _pos = g->getPosition();
    _ID = g->getID();
    _isInGame = g->isInGame();
    _money = g->getMoney();
    // Aggiungo il giocatore al tabellone
    _pos->addPlayer(_ID);
    return *this;
}

void Giocatore::buy(){
    // si effettua il cast della posizione
    Casella_Laterale *_pos1 = dynamic_cast<Casella_Laterale *>(_pos); // se il casting va a buon fine
    if (_pos1)
    {
        try
        {
            pay(_pos1->getPrezzo());                                    // lancia eccezione se il giocatore non ha abbastanza soldi
            _pos1->buy(this);                                           // buy di Casella Laterale setta le sue cose in
            if (!_pos1->isCasa() && (_pos1->getProprietario() == this)) // Se è avvenuto l'acquisto del terreno (non c'è una casa e il proprietario è il giocatore)
                _elenco_proprieta.push_back(_pos1);                     // aggiungo la casella alla lista di proprietà
        }
        catch (const Giocatore::Not_Enough_Money &e)
        {
            // std::cout << "\nAcquisto non avvenuto, lanciata Not_Enough_Money.";
            // file << "\nAcquisto non avvenuto, lanciata Not_Enough_Money.";
        }
    }
}

void Giocatore::pay(int n){
    // se il giocatore ha abbastanza soldi, allora paga, altrimenti si lancia l'eccezione e il giocatore perde
    if (n <= _money)
        _money = _money - n;
    else
        throw Not_Enough_Money();
}

void Giocatore::Transfert(int n, Giocatore *Other){
    // trasferimento di soldi da un giocatore ad un altro (pagamento dell'affitto)
    try
    {
        this->pay(n);
        Other->deposit(n);
    }
    catch (const Giocatore::Not_Enough_Money &e)
    {
        // Il giocatore paga tutti i soldi che ha ...
        Other->deposit(_money);
        this->pay(n);

        // ... ed esce dal gioco
        resetPlayer();
        _isInGame = false;
        
        throw Player_Lost();
    }
}

void Giocatore::deposit(int n){
    // deposito n soldi sul conto del giocatore
    _money = _money + n;
}

void Giocatore::move(int n){
    // mi sposto di n posizioni in avanti rispetto alla posizione attuale (_pos)
    for (int i = 0; i < n; i++)
    {
        _pos = _pos->getSucc();
        if (_pos->getType() == 'P') // Passaggio dal via che incrementa il budget del giocatore
            deposit(Variabili::moneyPassaggioVia);
    }
}

void Giocatore::resetPlayer(){
    for (int i = 0; i < _elenco_proprieta.size(); i++)
    {
        _elenco_proprieta[i]->reset();
    }
}

std::string Giocatore::to_String_elenco_proprieta(){
    std::string s = "\nGiocatore " + std::to_string(_ID) + ": ";
    for (int i = 0; i < _elenco_proprieta.size(); i++)
    {
        s += _elenco_proprieta[i]->getCoordinata_to_String() + " ";
    }
    return s;
}
