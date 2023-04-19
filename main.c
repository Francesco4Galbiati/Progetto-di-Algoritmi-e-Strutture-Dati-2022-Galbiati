#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 64
#define M 10000

typedef struct nodo_{
    char *parola;
    char colore;
    struct nodo_ *padre;
    struct nodo_ *figlio_dx;
    struct nodo_ *figlio_sx;
}nodo_albero;

typedef struct{
    nodo_albero *radice;
    nodo_albero *nil;
}albero_rb;

typedef struct{
    int8_t appartiene;
    int8_t *comparse;
    int8_t n_minimo;
    int8_t n_esatto;
    int8_t n_massimo;
    int8_t conto;
}vincoli_t;

void rb_insert(albero_rb *T, nodo_albero *z, int k);
void rb_insert_fixup(albero_rb *T, nodo_albero *z);
void left_rotate(albero_rb *T, nodo_albero *x);
void right_rotate(albero_rb *T, nodo_albero *x);
void inorder_tree_walk(albero_rb *T, nodo_albero *x, int k);
void valida_albero1(albero_rb *T, albero_rb *T_v, nodo_albero *x, int k, vincoli_t *vincoli, char *corr, int *v);
void valida_albero2(albero_rb *T_1, albero_rb *T_o, nodo_albero *x, int k, vincoli_t *vincoli, char *corr, int *v);
void rb_delete_fixup(albero_rb *T, nodo_albero *x);
nodo_albero* rb_delete(albero_rb *T, nodo_albero *z);
nodo_albero* tree_successor(albero_rb *T, nodo_albero *x);
nodo_albero* tree_minimum(albero_rb *T, nodo_albero *x);
nodo_albero* tree_search(albero_rb *T, nodo_albero *x, char* s, int k);
char inizializza_partita(int* t, char* r, char c, int k);
int pos_carattere(char c);
int valida_parola(char *w, int k, vincoli_t *vincoli, char *corr);
int comp_str(char* s1, char* s2, int k);

int nodi, str;

int main(){
    int i, j, t, n, sbagliate[N], n_valide;
    int k;
    char c;
    char *tmp, *ref, *res, *corrette, *word;
    albero_rb *tree_o, *tree_v1;
    nodo_albero *nil, *nodo, *nodo2;
    vincoli_t vincoli[N];


    //inizializzo l'albero vuoto
    tree_o = malloc(sizeof(albero_rb)*3);
    tree_v1 = &tree_o[1];
    nil = malloc(sizeof(nodo_albero));

    nil->padre = nil;
    nil->figlio_sx = nil;
    nil->figlio_dx = nil;
    nil->parola = NULL;
    nil->colore = 'b';
    tree_o->radice = nil;
    tree_o->nil = nil;
    tree_v1->radice = nil;
    tree_v1->nil = nil;
    n_valide = 0;
    n = 0;
    nodi = 0;
    str = 0;

    if(scanf("%d", &k)){}
    tmp = malloc(sizeof(char)*k*4);
    corrette = &tmp[0];
    res = &tmp[k];
    ref = &tmp[2*k];
    word = &tmp[3*k];

    tmp = malloc(sizeof(const char)*k*M);
    nodo = malloc(sizeof(nodo_albero)*M);


    for(i = 0; i < N; i++){
        vincoli[i].comparse = malloc(sizeof(int8_t)*k);
        for(j = 0; j < k; j++){
            vincoli[i].comparse[j] = 0;
        }
        vincoli[i].appartiene = 0;
        vincoli[i].n_esatto = -1;
        vincoli[i].n_minimo = 0;
        vincoli[i].n_massimo = k;
        vincoli[i].conto = 0;
        sbagliate[i] = 0;
    }

    //inizializza il risultato a '/////...' e le lettere corrette a '.....'
    for(i = 0; i < k; i++){
        res[i] = '/';
        corrette[i] = '.';
    }

    //riempio l'albero
    c = (char)getchar_unlocked();
    while(c == '\n' || c == '\r'){
        c = (char)getchar_unlocked();
    }

    while(c != '+'){
        for(i = 0; i < k; i++){
            tmp[k * str + i] = c;
            c = (char)getchar_unlocked();
        }
        if(nodi == M){
            nodo = malloc(sizeof(nodo_albero)*M);
            nodi = 0;
        }
        nodo[nodi].parola = &tmp[k * str];
        rb_insert(tree_o, &nodo[nodi], k);
        nodi++;
        str++;
        if(str == M){
            tmp = malloc(sizeof(char)*k*M);
            str = 0;
        }
        while(c == '\r' || c == '\n'){
            c = (char)getchar_unlocked();
        }
    }

    while(c != EOF){
        //controlla se è istruzione o parola
        if(c == '+'){
            c = (char)getchar_unlocked();
            //controlla se è un nuova_partita, inserisci o stampa_filtrate
            if(c == 'n'){
                c = inizializza_partita(&t, ref, c, k);
                if(n != 0){
                    for(i = 0; i < k; i++){
                        corrette[i] = '.';
                    }
                    for(i = 0; i < N; i++){
                        for(j = 0; j < k; j++){
                            vincoli[i].comparse[j] = 0;
                        }
                        vincoli[i].appartiene = 0;
                        vincoli[i].n_esatto = -1;
                        vincoli[i].n_minimo = 0;
                        vincoli[i].n_massimo = k;
                        vincoli[i].conto = 0;
                    }
                    while(tree_v1->radice != nil){
                        nodo2 = rb_delete(tree_v1, tree_v1->radice);
                        rb_insert(tree_o, nodo2, k);
                    }
                    n = 0;
                }
            } else if(c == 'i'){
                while(c != '\n'){
                    c = (char)getchar_unlocked();
                }
                c = (char)getchar_unlocked();
                while(c != '+'){
                    for(i = 0; i < k; i++){
                        tmp[k * str + i] = c;
                        c = (char)getchar_unlocked();
                    }
                    if(nodi == M){
                        nodo = malloc(sizeof(nodo_albero)*M);
                        nodi = 0;
                    }
                    nodo[nodi].parola = &tmp[k * str];
                    if(valida_parola(&tmp[str * k], k, vincoli, corrette) && n != 0){
                        rb_insert(tree_v1, &nodo[nodi], k);
                    } else{
                        rb_insert(tree_o, &nodo[nodi], k);
                    }
                    nodi++;
                    str++;
                    if(str == M){
                        tmp = malloc(sizeof(char)*k*M);
                        str = 0;
                    }
                    while(c == '\r' || c == '\n'){
                        c = (char)getchar_unlocked();
                    }
                }
            } else if(c == 's'){
                if(n == 0){
                    inorder_tree_walk(tree_o, tree_o->radice, k);
                } else{
                    inorder_tree_walk(tree_v1, tree_v1->radice, k);
                }
            }
            while(c != '\r' && c != '\n'){
                c = (char)getchar_unlocked();
            }
        } else{
            for(i = 0; i < N; i++){
                sbagliate[i] = 0;
            }
            for(i = 0; i < k; i++){
                word[i] = c;
                c = (char)getchar_unlocked();
            }
            if(tree_search(tree_o, tree_o->radice, word, k) == nil && tree_search(tree_v1, tree_v1->radice, word, k) == nil){
                printf("not_exists\n");
            } else if(comp_str(ref, word, k) == 0){
                printf("ok\n");
            }else{
                //inizia il confronto
                for(i = 0; i < k; i++){
                    if(ref[i] == word[i]){
                        res[i] = '+';
                        corrette[i] = word[i];
                    } else{
                        sbagliate[pos_carattere(ref[i])]++;
                    }
                }
                for(i = 0; i < k; i++){
                    if(res[i] != '+' && sbagliate[pos_carattere(word[i])] > 0){
                        res[i] = '|';
                        sbagliate[pos_carattere(word[i])]--;
                    }
                }
                //apprende i vincoli dati dalla parola
                for(i = 0; i < k; i++){
                    if(res[i] == '+'){
                        vincoli[pos_carattere((word[i]))].appartiene = 1;
                        vincoli[pos_carattere(word[i])].conto++;
                    } else if(res[i] == '|'){
                        vincoli[pos_carattere((word[i]))].appartiene = 1;
                        vincoli[pos_carattere(word[i])].comparse[i] = -1;
                        vincoli[pos_carattere(word[i])].conto++;
                    } else{
                        vincoli[pos_carattere(word[i])].comparse[i] = -1;
                        if(vincoli[pos_carattere(word[i])].appartiene == 0){
                            vincoli[pos_carattere(word[i])].appartiene = -1;
                        }
                    }
                }
                for(i = 0; i < N; i++){
                    if(vincoli[i].conto > vincoli[i].n_minimo){
                        vincoli[i].n_minimo = vincoli[i].conto;
                    }
                    vincoli[i].conto = k;
                }
                for(i = 0; i < N; i++){
                    if(vincoli[i].n_minimo > 0){
                        for(j = 0; j < N; j++){
                            if(i != j){
                                vincoli[j].conto--;
                            }
                        }
                    }
                }
                for(i = 0; i < N; i++){
                    if(vincoli[i].conto < vincoli[i].n_massimo){
                        vincoli[i].n_massimo = vincoli[i].conto;
                    }
                    vincoli[i].conto = 0;
                }
                for(i = 0; i < k; i++){
                    if(res[i] == '/' && vincoli[pos_carattere(word[i])].n_esatto == -1){
                        vincoli[pos_carattere(word[i])].n_esatto = vincoli[pos_carattere(word[i])].n_minimo;
                    }
                }
                //valida le parole nell'albero
                if(n == 0){
                    valida_albero1(tree_o, tree_v1, tree_o->radice, k, vincoli, corrette, &n_valide);
                } else{
                    valida_albero2(tree_v1, tree_o, tree_v1->radice, k, vincoli, corrette, &n_valide);
                }

                for(i = 0; i < N; i++){
                    vincoli[i].conto = 0;
                }
                for(i = 0; i < k; i++){
                    putchar_unlocked(res[i]);
                }
                printf("\n%d\n", n_valide);
                n_valide = 0;
                n++;
                if(n == t){
                    printf("ko\n");
                }
            }
            for(i = 0; i < k; i++){
                res[i] = '/';
            }
        }
        while(c == '\r' || c == '\n'){
            c = (char)getchar_unlocked();
        }
    }
    //libera la memoria allocata

    for(i = 0; i < N; i++){
        free(vincoli[i].comparse);
    }
    free(tmp);
    free(corrette);
    free(tree_o);
    free(nil);
    free(nodo);

   return 0;
}

void rb_insert(albero_rb *T, nodo_albero *z, int k){
    nodo_albero *x, *y;

    y = T->nil;
    x = T->radice;
    while(x != T->nil){
        y = x;
        if(comp_str(z->parola, x->parola, k) < 0) {
            x = x->figlio_sx;
        } else{
            x = x->figlio_dx;
        }
    }
    z->padre = y;
    if(y == T->nil){
        T->radice = z;
    } else if(comp_str(z->parola, y->parola, k) < 0){
        y->figlio_sx = z;
    } else{
        y->figlio_dx = z;
    }
    z->figlio_sx = T->nil;
    z->figlio_dx = T->nil;
    z->colore = 'r';
    rb_insert_fixup(T, z);
}

void rb_insert_fixup(albero_rb *T, nodo_albero *z){
    nodo_albero *x, *y;

    if(z == T->radice){
        T->radice->colore = 'b';
    } else{
        x = z->padre;
        if(x->colore == 'r'){
            if(x == x->padre->figlio_sx){
                y = x->padre->figlio_dx;
                if(y->colore == 'r'){
                    x->colore = 'b';
                    y->colore = 'b';
                    x->padre->colore = 'r';
                    rb_insert_fixup(T, x->padre);
                } else{
                    if(z == x->figlio_dx){
                        z = x;
                        left_rotate(T, z);
                        x = z->padre;
                    }
                    x->colore = 'b';
                    x->padre->colore = 'r';
                    right_rotate(T, x->padre);
                }
            } else{
                y = x->padre->figlio_sx;
                if(y->colore == 'r'){
                    x->colore = 'b';
                    y->colore = 'b';
                    x->padre->colore = 'r';
                    rb_insert_fixup(T, x->padre);
                } else{
                    if(z == x->figlio_sx){
                        z = x;
                        right_rotate(T, z);
                        x = z->padre;
                    }
                    x->colore = 'b';
                    x->padre->colore = 'r';
                    left_rotate(T, x->padre);
                }
            }
        }
    }
}

void left_rotate(albero_rb *T, nodo_albero *x){
    nodo_albero *y;

    y = x->figlio_dx;
    x->figlio_dx = y->figlio_sx;
    if(y->figlio_sx != T->nil){
        y->figlio_sx->padre = x;
    }
    y->padre = x->padre;
    if(x->padre == T->nil){
        T->radice = y;
    } else if(x == x->padre->figlio_sx){
        x->padre->figlio_sx = y;
    } else{
        x->padre->figlio_dx = y;
    }
    y->figlio_sx = x;
    x->padre = y;
}

void right_rotate(albero_rb *T, nodo_albero *x){
    nodo_albero *y;

    y = x->figlio_sx;
    x->figlio_sx = y->figlio_dx;
    if(y->figlio_dx != T->nil){
        y->figlio_dx->padre = x;
    }
    y->padre = x->padre;
    if(x->padre == T->nil){
        T->radice = y;
    } else if(x == x->padre->figlio_dx){
        x->padre->figlio_dx = y;
    } else{
        x->padre->figlio_sx = y;
    }
    y->figlio_dx = x;
    x->padre = y;
}

nodo_albero* rb_delete(albero_rb *T, nodo_albero *z){
    nodo_albero *x, *y;
    char *tmp;
    tmp = z->parola;

    if(z->figlio_sx == T->nil || z->figlio_dx == T->nil){
        y = z;
    } else{
        y = tree_successor(T, z);
    }
    if(y->figlio_sx != T->nil){
        x = y->figlio_sx;
    } else{
        x = y->figlio_dx;
    }
    x->padre = y->padre;
    if(y->padre == T->nil){
        T->radice = x;
    } else if(y == y->padre->figlio_sx){
        y->padre->figlio_sx = x;
    } else{
        y->padre->figlio_dx = x;
    }
    if(y != z){
        z->parola = y->parola;
        y->parola = tmp;
    }
    if(y->colore == 'b'){
        rb_delete_fixup(T, x);
    }

    return y;
}

void rb_delete_fixup(albero_rb *T, nodo_albero *x){
    nodo_albero *w;

    if(x->colore == 'r' || x->padre == T->nil){
        x->colore = 'b';
    } else if(x == x->padre->figlio_sx){
        w = x->padre->figlio_dx;
        if(w->colore == 'r'){
            w->colore = 'b';
            x->padre->colore = 'r';
            left_rotate(T, x->padre);
            w = x->padre->figlio_dx;
        }
        if(w->figlio_sx->colore == 'b' && w->figlio_dx->colore == 'b'){
            w->colore = 'r';
            rb_delete_fixup(T, x->padre);
        } else{
            if(w->figlio_dx->colore == 'b'){
                w->figlio_sx->colore = 'b';
                w->colore = 'r';
                right_rotate(T, w);
                w = x->padre->figlio_dx;
            }
            w->colore = x->padre->colore;
            x->padre->colore = 'b';
            w->figlio_dx->colore = 'b';
            left_rotate(T, x->padre);
        }
    } else{
        w = x->padre->figlio_sx;
        if(w->colore == 'r'){
            w->colore = 'b';
            x->padre->colore = 'r';
            right_rotate(T, x->padre);
            w = x->padre->figlio_sx;
        }
        if(w->figlio_dx->colore == 'b' && w->figlio_sx->colore == 'b'){
            w->colore = 'r';
            rb_delete_fixup(T, x->padre);
        } else{
            if(w->figlio_sx->colore == 'b'){
                w->figlio_dx->colore = 'b';
                w->colore = 'r';
                left_rotate(T, w);
                w = x->padre->figlio_sx;
            }
            w->colore = x->padre->colore;
            x->padre->colore = 'b';
            w->figlio_sx->colore = 'b';
            right_rotate(T, x->padre);
        }
    }
}

nodo_albero* tree_successor(albero_rb *T, nodo_albero *x){
    nodo_albero *y;

    if(x->figlio_dx != T->nil){
        return tree_minimum(T, x->figlio_dx);
    }
    y = x->padre;
    while(y != T->nil && x == y->figlio_dx){
        x = y;
        y = y->padre;
    }

    return y;
}

nodo_albero* tree_minimum(albero_rb *T, nodo_albero *x){
    while(x->figlio_sx != T->nil){
        x = x->figlio_sx;
    }

    return x;
}

void inorder_tree_walk(albero_rb *T, nodo_albero *x, int k){
    int i;

    if(x != T->nil){
        inorder_tree_walk(T, x->figlio_sx, k);
        for(i = 0; i < k; i++){
            putchar_unlocked(x->parola[i]);
        }
        putchar_unlocked('\n');
        inorder_tree_walk(T, x->figlio_dx, k);
    }
}

nodo_albero* tree_search(albero_rb *T, nodo_albero *x, char* s, int k){
    if(x == T->nil || comp_str(x->parola, s, k) == 0){
        return x;
    }
    if(comp_str(s, x->parola, k) < 0){
        return tree_search(T, x->figlio_sx, s, k);
    } else{
        return tree_search(T, x->figlio_dx, s, k);
    }
}

//legge il riferimento e il numero di tentativi
char inizializza_partita(int* t, char* r, char c, int k){
    int i;

    while(c != '\n'){
        c = (char)getchar_unlocked();
    }
    c = (char)getchar_unlocked();
    for(i = 0; i < k; i++){
        r[i] = c;
        c = (char)getchar_unlocked();
    }
    if(scanf("%d", t)){}

    return c;
}

int pos_carattere(char c){
    if(c >= '0' && c <= '9'){
        return c - 48;
    } else if(c >= 'A' && c <= 'Z'){
        return c - 55;
    } else if(c >= 'a' && c <= 'z'){
        return c - 61;
    } else if(c == '-'){
        return 62;
    } else{
        return 63;
    }
}

void valida_albero1(albero_rb *T, albero_rb *T_v,  nodo_albero *x, int k, vincoli_t *vincoli, char *corr, int *v){
    nodo_albero *tmp, *succ;

    x = tree_minimum(T, x);
    succ = tree_successor(T, x);
    while(x != T->nil){
        if(valida_parola(x->parola, k, vincoli, corr)){
            *v = *v + 1;
            tmp = rb_delete(T, x);
            if(x == tmp){
                x = succ;
            }
            succ = tree_successor(T, x);
            rb_insert(T_v, tmp, k);
        } else{
            x = succ;
            succ = tree_successor(T, x);
        }
    }
}

void valida_albero2(albero_rb *T, albero_rb *T_o, nodo_albero *x, int k, vincoli_t *vincoli, char *corr, int *v){
    nodo_albero *tmp, *succ;

    x = tree_minimum(T, x);
    succ = tree_successor(T, x);
    while(x != T->nil){
        if(valida_parola(x->parola, k, vincoli, corr)){
            *v = *v + 1;
            x = succ;
            succ = tree_successor(T, x);
        } else{
            tmp = rb_delete(T, x);
            if(x == tmp){
                x = succ;
            }
            succ = tree_successor(T, x);
            rb_insert(T_o, tmp, k);
        }
    }
}

int valida_parola(char *w, int k, vincoli_t *vincoli, char *corr){
    int i;

    //controlla che non ci siano lettere che non appartengono alla stringa
    for(i = 0; i < k; i++){
        if(vincoli[pos_carattere(w[i])].appartiene == -1){
            return 0;
        }
    }
    //controlla i posti in cui i caratteri non devono comparire
    for(i = 0; i < k; i++){
        if(vincoli[pos_carattere(w[i])].appartiene == 1 && vincoli[pos_carattere(w[i])].comparse[i] == -1){
            return 0;
        }
    }
    //controlla le lettere che devono essere in un determinato posto
    for(i = 0; i < k; i++){
        if(corr[i] != '.' && corr[i] != w[i]){
            return 0;
        }
    }
    //conta le lettere nella parola e le confronta
    for(i = 0; i < k; i++){
        vincoli[pos_carattere(w[i])].conto++;
    }
    for(i = 0; i < N; i++){ //forse è meglio i < k ma è da vedere a seconda dei test-case
        if(vincoli[i].n_esatto == -1){
            if(vincoli[i].n_minimo > vincoli[i].conto || vincoli[i].n_massimo < vincoli[i].conto){
                for(i = 0; i < k; i++){
                    vincoli[pos_carattere(w[i])].conto = 0;
                }
                return 0;
            }
        } else{
            if(vincoli[i].n_esatto != vincoli[i].conto){
                for(i = 0; i < k; i++){
                    vincoli[pos_carattere(w[i])].conto = 0;
                }
                return 0;
            }
        }
    }
    for(i = 0; i < k; i++){
        vincoli[pos_carattere(w[i])].conto = 0;
    }

    return 1;
}

int comp_str(char* s1, char* s2, int k){
    int i;

    for(i = 0; i < k; i++){
        if(s1[i] != s2[i]){
            if(s1[i] < s2[i]){
                return -1;
            } else{
                return 1;
            }
        }
    }

    return 0;
}