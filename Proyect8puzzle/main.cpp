
#include "cabereca.h"

int main() {
    srand(time(NULL));
    cola ColaPrioridad;

    estado EstadoInicial;

    //EstadoInicial.print();
    //cout<<EstadoInicial.calcularDistanciaManhattan()<<endl;


    nodo* NodoInicial = new nodo;
    NodoInicial->e = EstadoInicial;

    ColaPrioridad.push(NodoInicial);
    NodoInicial->e.print();
    cout<<"Resolucion:"<<endl;
    //cout<<NodoInicial->e.calcularDistanciaManhattan()<<endl;

    while (!ColaPrioridad.isEmpty()) {

        nodo* NodoActual = ColaPrioridad.pop();
        //NodoActual->e.print();
        //cout<<"Profundidad del arbol "<<NodoActual->n<<endl;
        if (NodoActual->e.testObjetivo()) {
            //cout<<"++++++++++++++++++++"<<endl;
            NodoActual->hallarRaiz(NodoActual,true);
            cout << "Se ha alcanzado el estado objetivo" << endl;
            break;
        }


        NodoActual->funcionSucesor();
        for (int i = 0; i < 4; i++) {
            if (NodoActual->h[i] != NULL) {
                ColaPrioridad.push(NodoActual->h[i]);
            }
        }
    }
    //EstadoInicial.genNumRand();
    NodoInicial->eliminarArbol(NodoInicial);


    return 0;
}
