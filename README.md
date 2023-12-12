# Progetto-di-Algoritmi-e-Strutture-Dati
Progetto di laurea di algoritmi e strutture dati (parte del corso di Algoritmi e Principi dell'Informatica al Politecnico di Milano A.A. 2021/2022\
Tema: Wordchecker\
Linguaggio: C11

# Descrizione del progetto
L'obiettivo del progetto era di realizzare un sistema che,
al suo cuore, controllasse la corrispondenza tra le lettere di 2 parole di
ugual lunghezza, parole sda intendere come sequenze di simboli che possono essere
caratteri alfabetici minuscoli (a-z) o maiuscoli (A-Z), cifre numeriche
(0-9), oppure i simboli - e _

Il sistema legge da standard input:\
• un valore k, che indica la lunghezza delle parole\
• una sequenza (di lunghezza arbitraria) di parole, ognuna di lunghezza k, che\
costituisce l'insieme delle parole ammissibili\

Oltre alle parole possono essere letti dei comandi:
• +nuova_partita: segna l'inizio di una partita\
• +stampa_filtrate: segna l'elenco delle parole ancora valide a quel punto della partita\
• +inserisci_inizio: segna l'inizio dell'inserimento di nuove parole\
• +inserisci_fine: segna la fine dell'inserimento di nuove parole\

All'inizio di una partita viene data la parola di riferimento r, seguita da una serie di altre parole da confrontare con r.\

Per ogni parola letta p, da confrontare con la parola di riferimento r, il programma scrive su stdout una sequenza di k caratteri fatta in questo modo:\
Per ogni 1 ≤ i ≤ k, si ha che:\
• res[i] è il carattere ‘+’ se l'i-esimo carattere di p è uguale all'i-esimo carattere di r\
• cioè se vale che p[i] = r[i], quindi p[i] è "in posizione corretta"\
• res[i] è il carattere ‘/’ se p[i] non compare da nessuna parte in r\
• res[i] è il carattere ‘|’ se p[i] compare in r, ma non in posizione i-esima; tuttavia, se in
r compaiono n istanze di p[i], se ci è il numero di istanze del carattere p[i] che sono in
posizione corretta (chiaramente ci ≤ ni) e se ci sono prima del carattere i-esimo in p
almeno ni-ci caratteri uguali a p[i] che sono in posizione scorretta, allora res[i] deve
essere / invece di

Dopo ogni confronto, il programma deve stampare in output il
numero di parole ammissibili ancora compatibili con i vincoli appresi

Input di esempio:\
5\
8adfs\
5sjaH\
KS06l\
Hi23a\
laj74\
-s9k0\
sm_ks\
okauE\
+nuova_partita\
5sjaH\
4\
KS06l -> /////, 5\
had7s -> not_exists\
okauE -> //|//, 3\
+stampa_filtrate\
+inserisci_inizio\
PsjW5\
asHdd\
paF7s\
+inserisci_fine\
-s9k0\
sghks\
+stampa_filtrate\
sm_ks\
+inserisci_inizio\
_fah-\
0D7dj\
+inserisci_fine\
+nuova_partita\
okauE\
3\
laj74\
+stampa_filtrate\
sm_ks\
okauE\
