// cpp_Arbol_general_con_menu_18_10_2026_Fabián_mijangos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//Arbol general con menu, usando apuntadores de memoria c++

#include <iostream>
using namespace std;

struct nodo {
    int dato;
    nodo* hijo; // primer hijo (baja un nivel)
    nodo* hermano; //siguiente hermano (mismo nivel)
};

nodo* crearnodo(int valor) {
    nodo* nuevonodo = new nodo; //se crea el apuntador de la estructura
    nuevonodo->dato = valor;
    nuevonodo->hijo = nullptr;
    nuevonodo->hermano = nullptr;
    return nuevonodo;
}

//agrega un hijo al final de la lista de hijos del padre (igual que agregarnodo en la lista enlazada)
nodo* agregarhijo(nodo* padre, int valor) {
    nodo* nuevonodo = crearnodo(valor);
    if (padre->hijo == nullptr) {
        padre->hijo = nuevonodo;
    }
    else {
        nodo* actual = padre->hijo;
        while (actual->hermano != nullptr) {
            actual = actual->hermano;
        }
        actual->hermano = nuevonodo;
    }
    return nuevonodo;
}

void construirarbol(nodo* cons) {
    int cantidadhijos;
    cout << "Cuantos hijos tiene el nodo " << cons->dato << "? ";
    cin >> cantidadhijos;
    for (int i = 0; i < cantidadhijos; i++) {
        int valor;
        cout << "Ingrese el valor del hijo " << i + 1 << " de " << cons->dato << ": ";
        cin >> valor; 
        nodo* nuevo = agregarhijo(cons, valor);
        construirarbol(nuevo); //ahora pedimos los hijos del nuevo nodo
    }
}

//Busca un nodo por su valor (recorrido en preorden)
nodo* buscarnodo(nodo* nu, int valor) {
    if (nu == nullptr) return nullptr;
    if (nu->dato == valor) return nu;

    nodo* actual = nu->hijo;
    while (actual != nullptr) {
        nodo* encontrado = buscarnodo(actual, valor);
        if (encontrado != nullptr) return encontrado;
        actual = actual->hermano;
    }
    return nullptr;
}

//Una hoja es un nodo que no tiene hijos
void mostrarhojas(nodo* most, int& contador) {
    if (most == nullptr)return;
    if (most->hijo == nullptr) {
        cout << most->dato << " (Direccion: " << most << ")" << endl;
        contador++;
    }
    nodo* actual = most->hijo;
    while (actual != nullptr) {
        mostrarhojas(actual, contador);
        actual = actual->hermano;
    }
}

void imprimirarbol(nodo* imp, int nivel) {
    if (imp == nullptr) return;
    for (int i = 0; i < nivel; i++) {
        cout << "     "; //sangria segun el nivel
    }
    cout << imp->dato << "    (direccion:  " << imp << ")" << endl;

    nodo* actual = imp->hijo;
    while (actual != nullptr) {
        imprimirarbol(actual, nivel + 1);
        actual = actual->hermano;
    }
}

//Recorrido en postorden: primero se borran los hijos, luego el padre
void borrararbol(nodo* bor, int& contador) {
    if (bor == nullptr) return;
    nodo*actual = bor->hijo;
    while (actual != nullptr) {
        nodo* siguiente = actual->hermano; // Guardar antes de borrar
        borrararbol(actual, contador);
        actual = siguiente; 
    }
    cout << "Elemento borrado " << contador
        << " |dato: " << bor->dato
        << " |direccion: " << bor << endl;
    contador++;
    delete bor;
}


int main() {
    nodo* raiz = nullptr;
    int opc;
    cout << "actividad 12 - Arbol general\n" << endl;

    do {
        cout << "\n ____Menu principal___" << endl;
        cout << "1. Ingresar elementos____" << endl;
        cout << "2. Mostrar hojas_________" << endl;
        cout << "3. Visualizar arbol______" << endl;
        cout << "0. Salir_________________" << endl; 
        cout << "=========================" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opc;
        switch (opc) {
        case 1: {
            if (raiz == nullptr) {
                //arbol vacio: primero se crea la raiz
                int valorraiz;
                cout << "Ingrese el valor de la raiz: ";
                cin >> valorraiz;
                raiz = crearnodo(valorraiz);
                construirarbol(raiz);
            }
            else {
                //arbol existente: se agregan hijos a un nodo que ya existe
                int valorpadre;
                cout << "ingrese el valor del nodo padre: ";
                cin >> valorpadre;
                nodo* padre = buscarnodo(raiz, valorpadre);
                if (padre == nullptr) {
                    cout << "El nodo " << valorpadre << "no existe en el arbol " << endl;
                }
                else {
                    int cantidad;
                    cout << "cuantos hijos nuevos tendra el nodo " << padre->dato << "? ";
                    cin >> cantidad;
                    for (int i = 0; i < cantidad; i++) {
                        int valor = 0;
                        cout << "Ingrese el valor del hijo nuevo " << i + 1 << valor;
                        nodo* nuevo = agregarhijo(padre, valor);
                        construirarbol(nuevo);
                    }
                }
            }
            break;
        }
        case 2: {
            if (raiz == nullptr) {
                cout << "El arbol esta vacio" << endl;
                break;
            }
            int totalhojas = 0;
            cout << "hojas del arbol: " << endl;
            mostrarhojas(raiz, totalhojas);
            cout << "total de hojas: " << totalhojas << endl;
            break;
        }
        case 3: {
            if (raiz == nullptr) {
                cout << "el arbol esta vacio" << endl;
                break;
            }
            cout << "arbol (preorden):" << endl;
            imprimirarbol(raiz, 0);
            break;
        }
        case 0: {
            cout << "Borrando arbol antes de salir: " << endl;
            int contador = 1;
            borrararbol(raiz, contador);
            raiz = nullptr;
            cout << "Total de elementos borrados: " << contador - 1 << endl; 
            cout << "saliendo del programa..." << endl;
            break;
        }
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    } while (opc != 0);
    return 0;
}