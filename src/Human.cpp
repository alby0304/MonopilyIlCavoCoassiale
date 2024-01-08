#include "../include/Human.h"

bool Human::choice()
{
    Casella_Laterale *posNow = dynamic_cast<Casella_Laterale *>(_pos); // se il casting va a buon fine
    if (posNow)
    {
        if (posNow->isCasa()&&(!posNow->isAlbergo())) //verifico che ci sia una casa e NON ci sia un albergo
        {
            std::cout << "\nRi-Bentornato nella casella " << posNow->getCoordinata_to_String() << " sultano, vuoi costruire un albergo? (Inserire S per si, N per no)";
        }
        else if (posNow->getProprietario()==this)
        {
            std::cout << "\nBentornato nella casella " << posNow->getCoordinata_to_String() << " padrone, vuoi costruire una casa? (Inserire S per si, N per no)";
        }
        else
        {
            std::cout << "\nVuoi comprare la casella " << posNow->getCoordinata_to_String() << "? (Inserire S per si, N per no)";
        }
        do
        {
            char risposta;
            std::cin >> risposta;
            if (risposta == 'S')
                return true;
            else if (risposta == 'N')
                return false;
            std::cout << "\nComando non riconosciuto (Inserire S per si, N per no)";
        } while (true);
    }
    return false; // Non lo farà mai perchè ritorna nel do while quando l'utente inserisce S o N
}


Giocatore &Human::operator=(Human *g)
{
    _pos = g->getPosition();
    ID = g->getID();
    _isInGame = g->isInGame();
    _money = g->getMoney();
    // Aggiungo il giocatore al tabellone
    _pos->addPlayer(ID);
    return *this;
}