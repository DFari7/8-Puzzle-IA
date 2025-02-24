#ifndef CABECERA_H
#define CABECERA_H
#include <iostream>
#include <time.h>

using namespace std;

class estado {
public:
    int mcb[3][3];
    int obj[3][3]= {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    estado() {
        genEstadoInicial();
    }

    void operator=(estado e) {
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                mcb[i][j] = e.mcb[i][j];
            }
        }
    }

    void operator=(int n) {
        for(int i=0; i<3; i++) {
            for(int j=0; j<3; j++) {
                mcb[i][j]=n;
            }
        }
    }

    bool operator==(estado e) {
        bool flag = true;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if (mcb[i][j] != e.mcb[i][j]) {
                    flag = false;
                    break;
                }
            }
            if (!flag) {
                break;
            }
        }
        return flag;
    }

    bool operator!=(estado e) {
        bool flag = false;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if (mcb[i][j] != e.mcb[i][j]) {
                    flag = true;
                    break;
                }
            }
            if (flag) {
                break;
            }
        }
        return flag;
    }

    int calcularPiezasMalColocadas() {
        int piezasMalColocadas = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (mcb[i][j] != obj[i][j] && mcb[i][j] != 0) {
                    piezasMalColocadas++;
                }
            }
        }
        return piezasMalColocadas;
    }
    int calcularDistanciaManhattan() {
        int distanciaManhattan = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int valor = mcb[i][j];
                if (valor != 0) {
                    int filaObjetivo = (valor) / 3;
                    int columnaObjetivo = (valor) % 3;
                    distanciaManhattan += abs(filaObjetivo - i) + abs(columnaObjetivo - j);
                }
            }
        }

        return distanciaManhattan;
    }
    bool contInver(int arr[],int n) {
        int inversionCount = 0;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                if (arr[i] > arr[j]) {
                    inversionCount++;
                }
            }
        }
        //cout<<inversionCount<<endl;
        if(inversionCount % 2 == 0) { //Es par
            return true;
        }
        else {
            return false;
        }
    }
    void genNumRand(int numero[],int m,int cont) {

        bool flag=true;

        while(cont<m) {//Generación de arreglo de 30 numeros aleatorios no repetidos del 0 al 99
            int num = 1 + rand() % 9; // Genero numero aleatorio
            if (num==9)
                num=0;
            bool band=false;
            for(int a=cont-1; a>=0; a--) {
                if (num==numero[a])
                    band=true;
            }
            if (band==false) {
                numero[cont]=num;
                cont++;
            }
        }

        //int numer[]={2,7,1,3,0,5,6,4,8};

        mcb[0][0] = numero[0];
        mcb[0][1] = numero[1];
        mcb[0][2] = numero[2];

        mcb[1][0] = numero[3];
        mcb[1][1] = numero[4];
        mcb[1][2] = numero[5];

        mcb[2][0] = numero[6];
        mcb[2][1] = numero[7];
        mcb[2][2] = numero[8];

    }

    void genEstadoInicial() {
        int numero[9];
        int m=9;
        int cont=0;
        bool flag;
        flag = true;
        while(flag) {
            flag=true;
            genNumRand(numero,m,cont);
            //print();
            if(!contInver(numero,m)||calcularDistanciaManhattan()>7) {
                flag = true;
            } else {
                break;
                //flag = false;
            }
        }
    }

    bool testObjetivo() {
        bool objetivo=true;

        for(int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if(mcb[i][j]!=obj[i][j]) {
                    objetivo=false;
                }
            }
        }
        return objetivo;
    }

    void print() {
        cout << "Estado actual:\n";
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << mcb[i][j] << " ";
            }
            cout << endl;
        }
        cout << "-------------\n";
    }
};

class nodo {
public:
    estado e;
    nodo *p;
    nodo *h[4];
    bool est;
    int n;



    nodo() {

        p=NULL;
        est=false;
        n=0;
        for(int i=0; i<4; i++) {
            h[i]=NULL;
        }
    }

    void funcionSucesor() {
        int espacioFila, espacioColum;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                if (e.mcb[i][j]==0) {
                    espacioFila=i;
                    espacioColum=j;
                    break;
                }
            }
        }
        // Sucesor hacia arriba
        if (espacioFila > 0) {
            h[0] = new nodo;
            h[0]->p = this;
            h[0]->n = n + 1;
            h[0]->e = e;
            h[0]->e.mcb[espacioFila][espacioColum] = h[0]->e.mcb[espacioFila - 1][espacioColum];
            h[0]->e.mcb[espacioFila - 1][espacioColum] = 0;
            h[0]->est = false;
        } else {
            h[0] = NULL;
        }

        // Sucesor hacia abajo
        if (espacioFila < 2) {
            h[1] = new nodo;
            h[1]->p = this;
            h[1]->n = n + 1;
            h[1]->e = e;
            h[1]->e.mcb[espacioFila][espacioColum] = h[1]->e.mcb[espacioFila + 1][espacioColum];
            h[1]->e.mcb[espacioFila + 1][espacioColum] = 0;
            h[1]->est = false;
        } else {
            h[1] = NULL;
        }

        // Sucesor hacia la izquierda
        if (espacioColum > 0) {
            h[2] = new nodo;
            h[2]->p = this;
            h[2]->n = n + 1;
            h[2]->e = e;
            h[2]->e.mcb[espacioFila][espacioColum] = h[2]->e.mcb[espacioFila][espacioColum - 1];
            h[2]->e.mcb[espacioFila][espacioColum - 1] = 0;
            h[2]->est = false;
        } else {
            h[2] = NULL;
        }

        // Sucesor hacia la derecha
        if (espacioColum < 2) {
            h[3] = new nodo;
            h[3]->p = this;
            h[3]->n = n + 1;
            h[3]->e = e;
            h[3]->e.mcb[espacioFila][espacioColum] = h[3]->e.mcb[espacioFila][espacioColum + 1];
            h[3]->e.mcb[espacioFila][espacioColum + 1] = 0;
            h[3]->est = false;
        } else {
            h[3] = NULL;
        }
    }

    nodo* hallarRaiz(nodo *pnt, bool prtCm) {
        nodo *Padre;
        if(pnt->p!=NULL) {

            Padre=hallarRaiz(pnt->p, prtCm);
        }
        else {
            Padre=pnt;
        }
        pnt->e.print();
    }

    void eliminarArbol(nodo *pnt) {
        for (int a=0; a<5; a++) {
            if (pnt->h[a]!=NULL)
                eliminarArbol(pnt->h[a]);
        }
        delete pnt;
        pnt=NULL;
    }
};




class casilla {
public:
    nodo * pnt;
    casilla *sig,*ant;


    casilla() {
        pnt=NULL;
        sig=NULL;
        ant=NULL;
    };
    casilla(nodo *x) {
        pnt=x;
        sig=NULL;
        ant=NULL;
    };
};

class cola {

public:
    casilla *h;
    casilla *t;

    cola() {
        h=NULL;
        t=NULL;
    }

    nodo* pop() {
        nodo* r;
        if (h->sig == NULL && h->ant == NULL || t->sig == NULL && t->ant == NULL) {
            r = h->pnt;
            delete h;

            t = NULL;
            h = NULL;
        } else if (h != NULL && h->ant == NULL) {
            r = h->pnt;
            h = h->sig;
            delete h->ant;
            h->ant = NULL;
        }

        return r;
    }
    void push(nodo* r) {
        casilla* nuevaCasilla = new casilla(r);

        if (isEmpty()) {
            h = nuevaCasilla;
            t = h;
        } else {
            casilla* temp = h;
            int heuristicaNueva = r->e.calcularDistanciaManhattan()+r->n;

            while (temp != NULL &&(temp->pnt->e.calcularDistanciaManhattan()+temp->pnt->n) < heuristicaNueva) {
                temp = temp->sig;
            }

            if (temp == h) {
                // Insertar al principio
                nuevaCasilla->sig = h;
                h->ant = nuevaCasilla;
                h = nuevaCasilla;
            } else if (temp == NULL) {
                // Insertar al final
                t->sig = nuevaCasilla;
                nuevaCasilla->ant = t;
                t = nuevaCasilla;
            } else {
                // Insertar en el medio
                nuevaCasilla->ant = temp->ant;
                nuevaCasilla->sig = temp;
                temp->ant->sig = nuevaCasilla;
                temp->ant = nuevaCasilla;
            }
        }
    }

    bool isEmpty() {
        return (t == NULL || h == NULL);
    }
};

#endif // CABECERA_H*/
