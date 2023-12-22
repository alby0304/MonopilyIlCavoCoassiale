Il codice scritto fin'ora funziona sul caso specifico richiesto dal progetto, ma si può adattare a diversi tipi di tabelloni (anche non per forza quadrati)
Le variabili di scope globale (tutte const) sono le seguenti:
- dim_x, dim_y e tot_caselle 	in Tabellone.h
- dim_Max_Cella			in Cell.h
Sono dichiarate fuori dalle classi perchè se si vuole ingrandire/ridurre il tabellone (giocare con le dimensioni),
ciò è possibile semplicemente cambiando quei valori in fase di programmazione (*attenzione anche ad Index_riga.h)
Ad esempio un Monopoli versione 2.0 potrebbe essere in un campo 10x10, come nel gioco vero.

* Index_riga.h è un'enumerazione contenente caratteri da A fino ad H, perciò se si vuole ingrandire il tabellone bisogna aggiungere lettere.