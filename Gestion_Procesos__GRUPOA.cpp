#include <iostream>
#include <string>
#include <fstream>
using namespace std;


// 1. ESTRUCTURA DEL NODO
struct nodo {
    int id;
    string nombre;
    int prioridad;
    int memoria;
    nodo *sig;
};
typedef nodo *pnodo;

// 2. CLASE LISTA
class lista {
private:
    pnodo pL;
public:
    lista();
    ~lista(); // Destructor de la lista
    void insertar();
    void eliminar();
    void buscar();
    void modificar();
    void mostrar();
    void guardar();
    void cargar();
};

// 3. CLASE COLA 
class cola {
private:
    pnodo pL;
public:
    cola();
    ~cola(); // Destructor 
    void encolar();
    void desencolar();
    void buscar();
    void mostrar();
};

// 4. CLASE PILA 
class pila {
private:
    pnodo pL;
public:
    pila();
    ~pila(); // Destructor
    void apilar();
    void desapilar();
    void buscar();
    void mostrar();
};


// IMPLEMENTACIÓN DE LA CLASE LISTA

lista::lista() {
    pL = NULL;
}

lista::~lista() {
    pnodo p = pL;
    pnodo q;
    while (p != NULL) {
        q = p->sig;
        delete p;
        p = q;
    }
    pL = NULL;
}

void lista::insertar() {
    pnodo nuevo, aux;
    nuevo = new nodo;
    cout << "\n-- Nuevo Proceso --" << endl;
    cout << "ID: "; cin >> nuevo->id;
    cout << "Nombre: "; cin >> nuevo->nombre;
    cout << "Prioridad: "; cin >> nuevo->prioridad;
    cout << "Memoria (MB): "; cin >> nuevo->memoria;
    nuevo->sig = NULL;

    if (pL == NULL) {
        pL = nuevo;
    } else {
        aux = pL;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
    cout << "-> Proceso agregado exitosamente." << endl;
}

void lista::eliminar() {
    if (pL == NULL) {
        cout << "La lista de procesos esta vacia." << endl;
        return;
    }
    int id;
    cout << "ID del proceso a eliminar: "; cin >> id;

    pnodo aux = pL;
    pnodo ant = NULL;
    int encontrado = 0;
    
    while (aux != NULL) {
        if (aux->id == id) {
            encontrado = 1;
            if (ant == NULL) {
                pL = aux->sig;
            } else {
                ant->sig = aux->sig;
            }
            cout << "-> Proceso [" << aux->nombre << "] eliminado." << endl;
            delete aux;
            break;
        }
        ant = aux;
        aux = aux->sig;
    }
    if (encontrado == 0) cout << "No se encontro ningun proceso con ese ID." << endl;
}

void lista::buscar() {
    if (pL == NULL) {
        cout << "La lista de procesos esta vacia." << endl;
        return;
    }
    int op;
    cout << "1. Buscar por ID  |  2. Buscar por Nombre: "; cin >> op;
    pnodo aux = pL;
    int encontrado = 0;
    
    if (op == 1) {
        int id;
        cout << "ID a buscar: "; cin >> id;
        while (aux != NULL) {
            if (aux->id == id) {
                cout << "Encontrado -> Nombre: " << aux->nombre << " | Prioridad: " << aux->prioridad << " | Memoria: " << aux->memoria << "MB" << endl;
                encontrado = 1;
            }
            aux = aux->sig;
        }
    } else {
        string nom;
        cout << "Nombre a buscar: "; cin >> nom;
        while (aux != NULL) {
            if (aux->nombre == nom) {
                cout << "Encontrado -> ID: " << aux->id << " | Prioridad: " << aux->prioridad << " | Memoria: " << aux->memoria << "MB" << endl;
                encontrado = 1;
            }
            aux = aux->sig;
        }
    }
    if (encontrado == 0) cout << "Proceso no encontrado." << endl;
}

void lista::modificar() {
    if (pL == NULL) {
        cout << "La lista de procesos esta vacia." << endl;
        return;
    }
    int id;
    cout << "ID del proceso a modificar: "; cin >> id;
    pnodo aux = pL;
    int encontrado = 0;
    while (aux != NULL) {
        if (aux->id == id) {
            encontrado = 1;
            cout << "Prioridad actual de " << aux->nombre << ": " << aux->prioridad << endl;
            cout << "Nueva prioridad: "; cin >> aux->prioridad;
            cout << "-> Prioridad actualizada correctamente!" << endl;
            break;
        }
        aux = aux->sig;
    }
    if (encontrado == 0) cout << "No se encontro el proceso." << endl;
}

void lista::mostrar() {
    if (pL == NULL) {
        cout << "No hay procesos registrados en el sistema." << endl;
        return;
    }
    cout << "\n=== LISTA GENERAL DE PROCESOS ===" << endl;
    pnodo p = pL;
    while (p != NULL) {
        cout << "[ID: " << p->id << "] | " << p->nombre
             << " | Prioridad: " << p->prioridad
             << " | Memoria: " << p->memoria << "MB" << endl;
        p = p->sig;
    }
}

void lista::guardar() {
    ofstream archivo("datos.txt");
    if (archivo.is_open()) {
        pnodo p = pL;
        while (p != NULL) {
            archivo << p->id << " " << p->nombre << " "
                    << p->prioridad << " " << p->memoria << "\n";
            p = p->sig;
        }
        archivo.close();
        cout << "-> Datos guardados exitosamente en datos.txt" << endl;
    } else {
        cout << "Error: No se pudo abrir el archivo para guardar." << endl;
    }
}

void lista::cargar() {
    ifstream archivo("datos.txt");
    if (archivo.is_open()) {
        int _id, _pri, _mem;
        string _nom;
        
        // Limpiar lista actual antes de cargar para evitar duplicados en RAM
        this->~lista();
        
        while (archivo >> _id >> _nom >> _pri >> _mem) {
            pnodo nuevo = new nodo;
            nuevo->id = _id;
            nuevo->nombre = _nom;
            nuevo->prioridad = _pri;
            nuevo->memoria = _mem;
            nuevo->sig = NULL;

            if (pL == NULL) {
                pL = nuevo;
            } else {
                pnodo aux = pL;
                while (aux->sig != NULL) {
                    aux = aux->sig;
                }
                aux->sig = nuevo;
            }
        }
        archivo.close();
        cout << "-> Persistencia: Datos cargados correctamente desde datos.txt" << endl;
    } else {
        cout << "Aviso: No se encontro el archivo 'datos.txt'. Se iniciara un sistema nuevo." << endl;
    }
}


// IMPLEMENTACIÓN DE LA CLASE COLA

cola::cola() { 
    pL = NULL; 
}

cola::~cola() {
    pnodo p = pL;
    pnodo q;
    while (p != NULL) {
        q = p->sig;
        delete p;
        p = q;
    }
    pL = NULL;
}

void cola::encolar() {
    pnodo nuevo = new nodo;
    cout << "\n-- Encolar Proceso en CPU --" << endl;
    cout << "ID: "; cin >> nuevo->id;
    cout << "Nombre del proceso: "; cin >> nuevo->nombre;
    cout << "Prioridad (Numeros menores = mayor prioridad): "; cin >> nuevo->prioridad;
    nuevo->memoria = 0;
    nuevo->sig = NULL;

    // Inserción ordenada por prioridad
    if (pL == NULL || pL->prioridad > nuevo->prioridad) {
        nuevo->sig = pL;
        pL = nuevo;
    } else {
        pnodo aux = pL;
        pnodo ant = pL;
        while (aux != NULL && aux->prioridad <= nuevo->prioridad) {
            ant = aux;
            aux = aux->sig;
        }
        nuevo->sig = aux;
        ant->sig = nuevo;
    }
    cout << "-> Proceso encolado en el Planificador de CPU." << endl;
}

void cola::desencolar() {
    if (pL == NULL) {
        cout << "La cola de la CPU está vacia (Procesador Inactivo)." << endl;
        return;
    }
    pnodo aux = pL;
    pL = pL->sig;
    cout << "-> [CPU] Ejecutando proceso: " << aux->nombre << " ... Terminado con exito!" << endl;
    delete aux;
}

void cola::buscar() {
    if (pL == NULL) {
        cout << "La cola de la CPU está vacia." << endl;
        return;
    }
    int id;
    cout << "ID a buscar en la cola de CPU: "; cin >> id;
    pnodo aux = pL;
    int encontrado = 0;
    while (aux != NULL) {
        if (aux->id == id) {
            cout << "-> Encontrado en cola: " << aux->nombre << " (Prioridad en CPU: " << aux->prioridad << ")" << endl;
            encontrado = 1;
            break;
        }
        aux = aux->sig;
    }
    if (encontrado == 0) cout << "El proceso no está en la cola de ejecucion." << endl;
}

void cola::mostrar() {
    if (pL == NULL) {
        cout << "Cola de CPU vacia / Procesador Libre." << endl;
        return;
    }
    cout << "\n=== COLA DE PLANIFICACIÓN DE CPU ===" << endl;
    pnodo p = pL;
    cout << "FRENTE -> ";
    while (p != NULL) {
        cout << "[" << p->nombre << " | Pri:" << p->prioridad << "] -> ";
        p = p->sig;
    }
    cout << "FIN" << endl;
}


// IMPLEMENTACIÓN DE LA CLASE PILA
pila::pila() { 
    pL = NULL; 
}

pila::~pila() {
    pnodo p = pL;
    pnodo q;
    while (p != NULL) {
        q = p->sig;
        delete p;
        p = q;
    }
    pL = NULL;
}

void pila::apilar() {
    pnodo nuevo = new nodo;
    cout << "\n-- Asignar Bloque de Memoria RAM --" << endl;
    cout << "Nombre del proceso solicitante: "; cin >> nuevo->nombre;
    cout << "Cantidad de Memoria a asignar (MB): "; cin >> nuevo->memoria;
    nuevo->id = 0;
    nuevo->prioridad = 0;
    
    // Operación PUSH 
    nuevo->sig = pL;
    pL = nuevo;
    cout << "-> Bloque de memoria asignado correctamente (Estructura LIFO)." << endl;
}

void pila::desapilar() {
    if (pL == NULL) {
        cout << "No hay bloques asignados en el Gestor de Memoria." << endl;
        return;
    }
    // Operación POP
    pnodo aux = pL;
    pL = pL->sig;
    cout << "-> [MEMORIA] Liberando recursos del proceso: " << aux->nombre
         << " (" << aux->memoria << "MB liberados)" << endl;
    delete aux;
}

void pila::buscar() {
    if (pL == NULL) {
        cout << "El Gestor de Memoria esta vacio." << endl;
        return;
    }
    string nom;
    cout << "Nombre del proceso a buscar en RAM: "; cin >> nom;
    pnodo aux = pL;
    int encontrado = 0;
    while (aux != NULL) {
        if (aux->nombre == nom) {
            cout << "-> Encontrado en RAM: Proceso [" << aux->nombre << "] consume actualmente " << aux->memoria << "MB." << endl;
            encontrado = 1;
            break;
        }
        aux = aux->sig;
    }
    if (encontrado == 0) cout << "El proceso no tiene memoria RAM reservada." << endl;
}

void pila::mostrar() {
    if (pL == NULL) {
        cout << "Memoria RAM completamente libre." << endl;
        return;
    }
    cout << "\n=== MAPA DE LA MEMORIA RAM (PILA LIFO) ===" << endl;
    pnodo p = pL;
    cout << "CIMA (Ultimo asignado)" << endl;
    while (p != NULL) {
        cout << "   | [" << p->nombre << " - " << p->memoria << "MB] |" << endl;
        p = p->sig;
    }
    cout << "BASE (Primer asignado)" << endl;
}


// 5. MENÚ PRINCIPAL CON LAS OPERACIONES
int main() {
    lista _Lista;
    cola _Cola;
    pila _Pila;
    int opc; 
    
    // Intentamosvcargar datos guardados al iniciar el programa automáticamente
    _Lista.cargar();

    do {
        cout << "\n========================================" << endl;
        cout << "     SISTEMA DE GESTION DE PROCESOS     " << endl;
        cout << "========================================" << endl;
        cout << " [ LISTA - Gestor de Procesos ]" << endl;
        cout << "   1. Agregar Proceso" << endl;
        cout << "   2. Eliminar Proceso" << endl;
        cout << "   3. Buscar Proceso" << endl;
        cout << "   4. Modificar Prioridad de Proceso" << endl;
        cout << "   5. Mostrar Todos los Procesos" << endl;
        cout << " [ COLA - Planificador CPU ]" << endl;
        cout << "   6. Encolar Proceso en CPU" << endl;
        cout << "   7. Ejecutar Proceso (Desencolar)" << endl;
        cout << "   8. Buscar Proceso en CPU" << endl;
        cout << "   9. Mostrar Cola de CPU" << endl;
        cout << " [ PILA - Gestor de Memoria RAM ]" << endl;
        cout << "   10. Asignar Bloque de Memoria" << endl;
        cout << "   11. Liberar Memoria (Desapilar)" << endl;
        cout << "   12. Buscar Proceso en RAM" << endl;
        cout << "   13. Mostrar Mapa de Memoria" << endl;
        cout << " [ CONFIGURACION DEL SISTEMA ]" << endl;
        cout << "   14. Guardar Estado Actual Manualmente" << endl;
        cout << "   15. Guardar y Salir" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Seleccione una opcion (1-15): "; 
        cin >> opc;

        switch(opc) {
            case 1:  _Lista.insertar();  break;
            case 2:  _Lista.eliminar();  break;
            case 3:  _Lista.buscar();    break;
            case 4:  _Lista.modificar(); break;
            case 5:  _Lista.mostrar();   break;
            case 6:  _Cola.encolar();    break;
            case 7:  _Cola.desencolar(); break;
            case 8:  _Cola.buscar();     break;
            case 9:  _Cola.mostrar();    break;
            case 10: _Pila.apilar();     break;
            case 11: _Pila.desapilar();  break;
            case 12: _Pila.buscar();     break;
            case 13: _Pila.mostrar();    break;
            case 14: _Lista.guardar();   break;
            case 15: 
                _Lista.guardar(); 
                cout << "\nCerrando el sistema de forma segura. ¡Hasta luego!" << endl; 
                break;
            default: 
                cout << "Error: Opcion no valida. Intente nuevamente." << endl;
        }
    } while (opc != 15);
    
    return 0;
}
