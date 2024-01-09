Il codice scritto per realizzare questo progetto funziona sul caso specifico richiesto, inoltre si può 
personalizzare il gioco secondo le proprie preferenze cambiando le costanti definite e dichiarate nel file
Variabili.h (Le regole di gioco non cambiano se si cambiano queste costanti).
Ad esempio si può fare una partita di monopoly in un campo 10x10 con 6 giocatori.

Abbiamo notato che in TUTTE le partite avviate con le costanti settate in base alla consegna del progetto
i giocatori accumulano più soldi di quanti riescano a spenderne. Anche se il giocatore human decide di comprare
tutto sin da subito non finisce mai i soldi. Questo perchè i soldi ritirati al passaggio dal via sono troppi,
oppure perchè i costi di acquisto e di affitto sono troppo bassi.

Riporto qui il pezzo finale di output di una partita tra computer giocata per 4000 turni ciascuno
**************************
Giocatore 2 ha: 12642 fiorini.
Giocatore 1 ha: 17902 fiorini.
Giocatore 4 ha: 30513 fiorini.
Giocatore 3 ha: 18973 fiorini.

Gioco finito per raggiungimento limite massimo di turni (i giocatori rimasti in gioco hanno fatto 4000 turni).
Ha vinto il giocatore 4
**************************


Per risolvere per questo problema abbiamo testato il comportamento del programma cambiando le seguenti costanti (prima di avviare il game):
- moneyPassaggioVia = 1 (tutto il resto come da consegna)
  Così facendo l'ultimo giocatore arriva al turno n, con n variabile tra 80 e 280 (a seconda dei casi).
- affittocasa e affittoAlbergo raddoppiando il valore della consegna del progetto per ogni tipo di casella (E, S ed L) (tutto il resto come da consegna)
  Così facendo l'ultimo giocatore arriva al turno n, con n variabile tra 60 e 140 (a seconda dei casi).
  Provando a raddoppiare di nuovo tutti i valori precedentemente raddoppiati, l'ultimo giocatore arriva al turno n, con n variabile tra 60 e 120 (a seconda dei casi, media di 100 turni circa).
  Solo in un caso (probabilmente un caso raro) l'ultimo giocatore è arrivato al turno 48.
  Nonostante il secondo x2 il range di valori non è cambiato molto (si è abbassata la media, ora di 80 turni circa).
  Raddoppiare ancora i valori porterebbe a costi di pernottamento eccessivi (in una casella di lusso con albergo verrebbe a costare 112 fiorini), perciò ci siamo fermati

Se volessimo fare un calcolo un giocatore parte con 100 fiorini.
In un suo turno fa un lancio generato casualmente tra 2 e 12.
Calcoliamo il lancio medio come = (12+2)/2 = 7
Mediamente quindi un giocatore tira i dadi e fa 7, si sposta di 7 caselle, quindi 1/4 del tabellone.
In 4 turni quindi mediamente è già ripassato dal via e ha ritirato 20 fiorini.
In questi 4 turni il robot ha:
- 1/8 di possibilità di finire su una casella angolare (non succede nulla, nessun uscita)
- 7/8 di possibilità di finire su una casella laterale (con 1/4 di possibilità di acquisto e 3/4 di possibilità di non decidere di acquistarlo).
Quindi mediamente il giocatore computer fa un giro del tabellone e forse acquista 1-2 proprietà, 3-4 in un giro è poco probabile.
Finito il giro ritira 20 fiorini e fa scorta.
Per i giocatori hanno poche possibilità di uscite di denaro e moltissime entrate (passando dal via).
In questo gioco non vi è nemmeno la rendita del solo terreno quindi prima che i robot comincino a pagarsi a
vicenda dei pernottamenti ci vuole un tot di turni ciascuno; e quando cominciano a pagarsi a vicenda hanno
già molti soldi (non possono essere eliminati, vanno solo in svantaggio). Inoltre il passaggio dal via continua a
generare troppo capitale, così che sia impossibile perdere per i giocatori.

In sintesi:
- troppo bassi i prezzi di acquisto (terreni, case e alberghi)				                  => poche uscite
- troppo bassi anche gli affitti con casa/albergo (+ rendita solo terreno inesistente)	=> poche uscite
- troppo alto il quantitativo di soldi ritirati al passaggio dal via			              => poche entrate