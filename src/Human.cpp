#include "../include/Human.h"

bool Human::want_to_buy_terreno() 
{
    char risposta;
    std::cout << "\nVuoi comprare la casella " << _pos->getCoordinata_to_String() << "? (Inserire S per si, N per no)";
    std::cin>>risposta;
    if (risposta == 'S')
        return true;
    else if (risposta == 'N')
        return false;
    else
        std::cout << "\nComando non riconosciuto, come se avessi detto no.";
    return false;
}

bool Human::want_to_buy_casa() 
{
    char risposta;
    std::cout << "\nBentornato nella casella " << _pos->getCoordinata_to_String() << " padrone, vuoi costruire una casa? (Inserire S per si, N per no)";
    std::cin>>risposta;
    if (risposta == 'S')
        return true;
    else if (risposta == 'N')
        return false;
    else
        std::cout << "\nComando non riconosciuto, come se avessi detto no.";
    return false;
}

bool Human::want_to_buy_albergo() 
{
    char risposta;
    std::cout << "\nRi-Bentornato nella casella " << _pos->getCoordinata_to_String() << " sultano, vuoi costruire un albergo? (Inserire S per si, N per no)";
    std::cin>>risposta;
    if (risposta == 'S')
        return true;
    else if (risposta == 'N')
        return false;
    else
        std::cout << "\nComando non riconosciuto, come se avessi detto no.";
    return false;
}


Giocatore& Human::operator=(Human* g)
{
    _pos= g->getPosition();
    ID = g->getID();
    _isInGame = g->isInGame();
    _money = g->getMoney();
    // Aggiungo il giocatore al tabellone
    _pos->addPlayer(ID);
    return *this;
}


std::ostream& operator<<(std::ostream& os, Human G)
{
    return os << G.to_String();
}