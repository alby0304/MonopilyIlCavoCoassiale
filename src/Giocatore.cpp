#include "../include/Casella_Laterale.h"
#include "../include/Giocatore.h"

Giocatore::Giocatore(int n, Casella* P, int money) : _pos{P}, ID{n}, _isInGame{true}, _money{money}{
    _pos->addPlayer(ID);
}

Giocatore& Giocatore::operator=(Giocatore* g){
    _pos= g->getPosition();
    ID = g->getID();
    _isInGame = g->isInGame();
    _money = g->getMoney();
    // Aggiungo il giocatore al tabellone
    _pos->addPlayer(ID);
    return *this;
}

void Giocatore::buy() // si effettua il cast della posizione 
{
    Casella_Laterale* _pos1 = dynamic_cast<Casella_Laterale*>(_pos); //se il casting va a buon fine 
    if (_pos1)
    {
        try
        {
            pay(_pos1->getPrezzo()); //lancia eccezione se il igocatore non ha abbastanza soldi
            _pos1->buy(this);  //buy di Casella Laterale setta le sue cose in
            if (!_pos1->isCasa()&&(_pos1->getProprietario()==this))   // Se non c'è stato l'acquisto di una casa significa che il giocatore ha acquistato il terreno (verifico cmq che ne sia il proprietario)
            _elenco_proprieta.push_back(_pos1);                       // e quindi aggiungo la casella alla lista di proprietà
        }
        catch(const Giocatore::Not_Enough_Money& e)
        {
            // std::cout << "\nAcquisto non avvenuto, lanciata Not_Enough_Money.";
        }
    }
}

void Giocatore::pay(int n){ // se il giocatore ha abbastanza soldi paga altrimenti si lancia l'eccezione e il giocatore perde  
    if (n<_money)
        _money =_money-n;
    else
        throw Not_Enough_Money();
}

void Giocatore::Transfert (int n, Giocatore* Other){ // trasferisco i soldi da un giocatore all'altro se finisco su una sua proprietà 

    try
    {
        this->pay(n);
        Other->deposit(n);
    }
    catch(const Giocatore::Not_Enough_Money& e)
    {
        _isInGame = false;
        Other->deposit(_money); // il giocatore paga tutti i soldi che ha 
        resetPlayer();
        throw You_Loosed();    // se il giocatore non ha abbastanza soldi per pagare perde ed esce dalla partita 
    }
}

void Giocatore::deposit(int n){ //deposito

    _money =_money + n;
}

void Giocatore::move(int n){  // mi sposto da una posizione alla successiva 

    for (int i=0; i < n; i++)
    {
        _pos = _pos->getSucc();
        if (_pos->getType() == 'P') // Passaggio dal via che incrementa il budget dei giocatori 
            deposit(_moneyPassaggioVia);
    }
}

Giocatore::~Giocatore() // elimino il puntatore alla posizione 
{
    delete _pos;
}

void Giocatore::resetPlayer()
{
    for (int i=0; i < _elenco_proprieta.size(); i++)
    {
        _elenco_proprieta[i]->reset();
    }
}

std::string Giocatore::to_String_elenco_proprieta()
{
    std::string s= "\nGiocatore " + std::to_string(ID) + ": ";
    for (int i=0; i< _elenco_proprieta.size(); i++)
    {
        s +=  _elenco_proprieta[i]->getCoordinata_to_String() + " ";
    }
    return s;
}
