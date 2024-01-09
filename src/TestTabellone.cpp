// Giulio Zanardi 2076063

#include "Tabellone.h"

int main()
{
    bool creatoT = false;
    int R,C;
    std::cout << "Benvenuto/a";
    do
    {
        std::cout << "\nQuanto lo facciamo grande il tabellone?"
                  << "\nInserisci quante righe deve avere (>2):";
        std::cin >> R;
        std::cout << "\nInserisci quante colonne deve avere (>2):";
        std::cin >> C;

        try
        {
            Tabellone T(R,C);
            std::cout << "\nQuesto e' il tuo tabellone:\n" << T;
            creatoT = true;
        }
        catch(const Tabellone::Too_Small& e)
        {
            std::cout << "\nErrore, non e' possibile creare un tabellone di monopoli con " << R << " righe e " << C << " colonne.\nRiprovare";
        }
    } while (!creatoT);

    return 0;
}