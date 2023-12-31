// Giulio Zanardi 2076063

#include "../include/Casella_laterale.h"

Casella_Laterale::Casella_Laterale(int R, int C, char cont) : Casella(R, C, cont)
{
    // Il contenuto e la coordinata li faccio settare alla superclasse casella
    reset(); // Per settare _albergo, _casa e _proprietario

    if (_type == 'E')
    {
        _prezzo_terreno = Variabili::prezzoTerrenoE;
        _prezzo_casa = Variabili::prezzoCasaE;
        _prezzo_albergo = Variabili::prezzoAlbergoE;
        _affitto_casa = Variabili::affittoCasaE;
        _affitto_albergo = Variabili::affittoAlbergoE;
    }
    if (_type == 'S')
    {
        _prezzo_terreno = Variabili::prezzoTerrenoS;
        _prezzo_casa = Variabili::prezzoCasaS;
        _prezzo_albergo = Variabili::prezzoAlbergoS;
        _affitto_casa = Variabili::affittoCasaS;
        _affitto_albergo = Variabili::affittoAlbergoS;
    }
    if (_type == 'L')
    {
        _prezzo_terreno = Variabili::prezzoTerrenoL;
        _prezzo_casa = Variabili::prezzoCasaL;
        _prezzo_albergo = Variabili::prezzoAlbergoL;
        _affitto_casa = Variabili::affittoCasaL;
        _affitto_albergo = Variabili::affittoAlbergoL;
    }
}

std::string Casella_Laterale::to_String()
{
    // Ogni casella viene rappresentata da una stringa di dim_ma spazi in output (a seconda di cosa c'è "sopra alla casella" inserisco i relativi spazi)
    std::string s = "|";

    // Salva in s il contenuto (E, S o L)
    s = s + _type;

    // Se c'è una casa o un'albergo lo salvo in s
    if (_albergo)
        s = s + "^";
    else if (_casa)
        s = s + "*";

    // Salva in s eventuali giocatori
    for (int i = 0; i < _players.size(); i++)
    {
        s = s + std::to_string(_players.at(i));
    }

    s = s + "|";
    s = normalize(s);
    return s;
}

void Casella_Laterale::buy(Giocatore *g)
{
    // Se il giocatore possiede già il terreno e la casa, si procede all'acquisto di un albergo
    if ((_proprietario == g) && (!_albergo) && (_casa == true))
    {
        _albergo = true;
    }
    // Se il giocatore possiede già il terreno, si procede all'acquisto di una casa
    else if ((_proprietario == g) && (_casa == false))
    {
        _casa = true;
    }
    // Se la casella non è di nessuno, si procede all'acquisto del terreno
    else if ((_proprietario == nullptr))
    {
        _proprietario = g;
    }
}

int Casella_Laterale::getAffitto() const
{
    if (_albergo)
        return _affitto_albergo;
    if (_casa)
        return _affitto_casa;
    // Se non ci sono case o alberghi l'affitto da pagare è 0
    // (Nella consegna del progetto NON c'è scritto di far pagare la rendita del solo terreno, come avviene nel "vero" gioco del monopoli)
    return 0;
}

void Casella_Laterale::reset()
{
    _casa = false;
    _albergo = false;
    _proprietario = nullptr;
}

int Casella_Laterale::getPrezzo()
{
    if (_albergo)
        return _prezzo_albergo;
    if (_casa)
        return _prezzo_casa;
    return _prezzo_terreno;
}