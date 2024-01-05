#include "../include/Casella_Laterale.h"
#include "../include/Giocatore.h"

Giocatore::Giocatore(int n, Casella* P) : _pos{P}, ID{n}, _isInGame{true}, _money{100}{
    _pos->addPlayer(ID);
    std::cout << "\nCostruttore di giocatore ha fatto il suo sporco lavoro, creato giocatore " << ID << std::endl;
    
}

Giocatore& Giocatore::operator=(Giocatore* g){
    _pos= g->getPosition();
    ID = g->getID();
    _isInGame = g->isInGame();
    _money = g->getMoney();
    return *this;
}

void Giocatore::buy() // si effettua il cast della posizione 
{
    try
    {
        Casella_Laterale* _pos1 = dynamic_cast<Casella_Laterale*>(_pos); //se il casting va a buon fine 
        if (_pos1)
        {
            _pos1->buy(this);  // si richiama il buy della classe Casella Laterale 
        }
    }
    catch(const std::exception& e)
    {
        throw Not_Enough_Money();    // Sto cercando di acquistare una casella che non è laterale (una casella angolare)
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
    catch(const std::exception& e)
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
            deposit(20);
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

std::string Giocatore::to_String()
{
    std::string s= "Giocatore " + std::to_string(ID) + ": ";
    for (int i=0; i< _elenco_proprieta.size(); i++)
    {
        // s = s + 
    }
    return s;
}

std::string Giocatore::to_String_elenco_proprietà() { //inserisco in s il numero del giocatore con le rispettive proprietà
    std::string s = "Giocatore " + std::to_string(ID);
    s = s + " : ";
    for (int i=0; i< _elenco_proprieta.size(); i++)
        s = s + _elenco_proprieta[i]->to_String() +  " ";
    return s;
}

std::ostream& operator<<(std::ostream& os, Giocatore G)
{
    return os << G.to_String();
}