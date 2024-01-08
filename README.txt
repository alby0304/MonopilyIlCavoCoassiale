Il codice scritto per realizzare questo progetto funziona sul caso specifico richiesto, ma si può 
facilmente adattare a diversi tipi di tabelloni (5x7, 8x8, 10x19, ecc.) cambiando 3 variabili 
a noi fornite nella consegna del progetto (il numero di caselle economiche, standard e lusso) e 
stando attenti a sistemare il metodo int_to_char secondo le proprie esigenze.
Le partite sono con un numero variabile di giocatori (quanti computer si vuole e sempre 1 solo giocatore 
umano cambiando il valore di 1 variabile nel main).
Ad esempio un Monopoli versione 2.0 potrebbe essere in un campo 10x10, e 6 giocatori.
In pratica è semplice cambiare di molto il gioco cambiando quelle variabili dichiarate const (attenzione
se si cambia la dimesione di quelle utili per l'output come _dim_max_Casella) e qualche piccolo
aggiustamento al codice.
Proprio per questo ci siamo messi a giocare con le seguenti variabili per testare il comportamento del programma sotto vari stimoli:
- _moneyPassaggioVia (=20 nella richiesta del progetto, troppo alta e il gioco non finisce mai)
- _affitto_casa e _affitto_albergo (nella richiesta del progetto troppo basse e il gioco non finisce mai)
Nei casi di richiesta del progetto i giocatori accumulano più soldi di quanti riescano a spenderne (a meno
che il giocatore umano non si metta a comprare tutto e perde per mancanza di soldi, comunque raro).
Abbiamo provato i seguenti test (su partite tra pc):
_moneyPassaggioVia = 1 => l'ultimo giocatore arriva al turno n, con n variabile tra 80 e 280 (a seconda dei casi).
Già più accettabile, anche se è ancora troppo lunga per essere definita una "normale" partita di monopoly (non con un giocatore che arrivi a quasi 300 turni)
allora abbiamo cambiato anche le altre 2 variabili (_affitto_casa e _affitto_albergo) raddoppiando il valore
che ci è stato suggerito nella consegna del progetto per ogni tipo di casella (E, S ed L).
Così facendo l'ultimo giocatore arriva al turno n, con n variabile tra 60 e 140 (a seconda dei casi).
Abbiamo provato a raddoppiare di nuovo tutti i valori.
Così facendo l'ultimo giocatore arriva al turno n, con n variabile tra 60 e 120 (a seconda dei casi).
Solo in un caso (probabilmente un caso raro) l'ultimo giocatore è arrivato al turno 48.
Nonostante abbiamo raddoppitato una seconda volta il range di valori non è cambiato molto (si è abbassata la media, di 80 turni circa).
Se si volesse ancora raddoppiare si sfocerebbe in qualcosa di troppo diverso da monopoli
(il pernottamento in una casella di lusso con albergo verrebbe a costare 112 fiorini, un po assurdo).
Se volessimo fare un calcolo un giocatore parte con 100 fiorini.
In un suo turno fa un lancio generato casualmente tra 2 e 12. Prendiamo come media di una lunga serie di lanci (12+2)/2 = 7
Mediamente quindi un giocatore tira i dadi e fa 7, si sposta di 7 caselle, quindi 1/4 del tabellone.
In 4 turni quindi mediamente è già ripassato dal via e ha ritirato 20 fiorini.
In questi 4 turni il robot ha:
- 1/8 di possibilità di finire su una casella angolare (non succede nulla, nessun uscita)
- 7/8 di possibilità di finire su una casella laterale (con 1/4 di possibilità di acquisto e 3/4 di possibilità di nessun uscita).
Quindi mediamente il giocatore computer fa un giro del tabellone e forse acquista 1 proprietà, già 2 in un giro è poco probabile.
Finito il giro ritira 20 fiorini e fa scorta.
Per i primi turni di una partita i robot hanno pochissime uscite, e moltissime entrate (passando dal via).
In questo gioco non vi è nemmeno la rendita del solo terreno quindi prima che i robot comincino a pagarsi a
vicenda dei pernottamenti ci vogliono almeno un 20 turni ciascuno; e quando cominciano a pagarsi a vicenda hanno
già molti soldi (non possono essere eliminati, vanno solo in svantaggio). inoltre il passaggio dal via continua a
generare troppo capitale, così che sia impossibile perdere per i giocatori.
