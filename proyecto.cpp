//g++ archivo.cpp -o programa
// ./programa


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// =========================================================================
// ESTRUCTURAS Y CLASES
// =========================================================================

// --- LISTA SIMPLE: UNIVERSIDADES ---
struct NodoUniversidad {
    int id;
    string nombre;
    string pais;
    int ranking;
    NodoUniversidad* sig;
    
    NodoUniversidad(int i, string n, string p, int r) 
        : id(i), nombre(n), pais(p), ranking(r), sig(nullptr) {}
};

class ListaUniversidades {
private:
    NodoUniversidad* primero;
public:
    ListaUniversidades() : primero(nullptr) {}
    
    void insertarAlFinal(int id, string nombre, string pais, int ranking) {
        if (buscarPorId(id) != nullptr) {
            cout << "Error: El ID de universidad " << id << " ya existe.\n";
            return;
        }
        NodoUniversidad* nuevo = new NodoUniversidad(id, nombre, pais, ranking);
        if (!primero) {
            primero = nuevo;
        } else {
            NodoUniversidad* temp = primero;
            while (temp->sig) temp = temp->sig;
            temp->sig = nuevo;
        }
        cout << "Universidad insertada correctamente.\n";
    }
    
    NodoUniversidad* buscarPorId(int id) {
        NodoUniversidad* temp = primero;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->sig;
        }
        return nullptr;
    }
    
    void mostrar() {
        NodoUniversidad* temp = primero;
        if (!temp) { cout << "No hay universidades registradas.\n"; return; }
        cout << "\n--- LISTA DE UNIVERSIDADES ---\n";
        while (temp) {
            cout << "ID: " << temp->id << " | Nombre: " << temp->nombre 
                 << " | Pais: " << temp->pais << " | Ranking: " << temp->ranking << endl;
            temp = temp->sig;
        }
    }
    
    bool modificar(int id, string nuevoNombre, string nuevoPais, int nuevoRanking) {
        NodoUniversidad* temp = buscarPorId(id);
        if (temp) {
            temp->nombre = nuevoNombre;
            temp->pais = nuevoPais;
            temp->ranking = nuevoRanking;
            return true;
        }
        return false;
    }
    
    bool eliminar(int id) {
        if (!primero) return false;
        if (primero->id == id) {
            NodoUniversidad* aBorrar = primero;
            primero = primero->sig;
            delete aBorrar;
            return true;
        }
        NodoUniversidad* actual = primero;
        while (actual->sig && actual->sig->id != id) {
            actual = actual->sig;
        }
        if (actual->sig) {
            NodoUniversidad* aBorrar = actual->sig;
            actual->sig = aBorrar->sig;
            delete aBorrar;
            return true;
        }
        return false;
    }
    
    NodoUniversidad* getPrimero() { return primero; }
};

// --- LISTA SIMPLE: AREAS DE INVESTIGACION ---
struct NodoArea {
    int id;
    string nombre;
    string descripcion;
    NodoArea* sig;
    
    NodoArea(int i, string n, string d) : id(i), nombre(n), descripcion(d), sig(nullptr) {}
};

class ListaAreas {
private:
    NodoArea* primero;
public:
    ListaAreas() : primero(nullptr) {}
    
    void insertarAlFinal(int id, string nombre, string descripcion) {
        if (buscarPorId(id) != nullptr) {
            cout << "Error: El ID de area " << id << " ya existe.\n";
            return;
        }
        NodoArea* nuevo = new NodoArea(id, nombre, descripcion);
        if (!primero) primero = nuevo;
        else {
            NodoArea* temp = primero;
            while (temp->sig) temp = temp->sig;
            temp->sig = nuevo;
        }
        cout << "Area insertada correctamente.\n";
    }
    
    NodoArea* buscarPorId(int id) {
        NodoArea* temp = primero;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->sig;
        }
        return nullptr;
    }
    
    void mostrar() {
        NodoArea* temp = primero;
        if (!temp) { cout << "No hay areas registradas.\n"; return; }
        cout << "\n--- AREAS DE INVESTIGACION ---\n";
        while (temp) {
            cout << "ID: " << temp->id << " | Nombre: " << temp->nombre 
                 << " | Desc: " << temp->descripcion << endl;
            temp = temp->sig;
        }
    }
    
    bool modificar(int id, string nuevoNombre, string nuevaDesc) {
        NodoArea* temp = buscarPorId(id);
        if (temp) {
            temp->nombre = nuevoNombre;
            temp->descripcion = nuevaDesc;
            return true;
        }
        return false;
    }
    
    bool eliminar(int id) {
        if (!primero) return false;
        if (primero->id == id) {
            NodoArea* aux = primero;
            primero = primero->sig;
            delete aux;
            return true;
        }
        NodoArea* actual = primero;
        while (actual->sig && actual->sig->id != id) actual = actual->sig;
        if (actual->sig) {
            NodoArea* aux = actual->sig;
            actual->sig = aux->sig;
            delete aux;
            return true;
        }
        return false;
    }
    
    NodoArea* getPrimero() { return primero; }
};

// --- LISTA DOBLE: COAUTORES (Sublista dentro de Investigador) ---
struct NodoCoautor {
    int id;
    string nombre;
    string universidad;
    int publicacionesConjuntas;
    NodoCoautor* sig;
    NodoCoautor* ant;
    
    NodoCoautor(int i, string n, string u, int p) 
        : id(i), nombre(n), universidad(u), publicacionesConjuntas(p), sig(nullptr), ant(nullptr) {}
};

class ListaCoautores {
private:
    NodoCoautor* primero;
public:
    ListaCoautores() : primero(nullptr) {}
    
    void insertarAlInicio(int id, string nombre, string universidad, int pubs) {
        if (buscarPorId(id) != nullptr) {
            cout << "Error: El ID de coautor " << id << " ya existe.\n";
            return;
        }
        NodoCoautor* nuevo = new NodoCoautor(id, nombre, universidad, pubs);
        if (!primero) {
            primero = nuevo;
        } else {
            nuevo->sig = primero;
            primero->ant = nuevo;
            primero = nuevo;
        }
    }
    
    NodoCoautor* buscarPorId(int id) {
        NodoCoautor* temp = primero;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->sig;
        }
        return nullptr;
    }
    
    void mostrar() {
        NodoCoautor* temp = primero;
        if (!temp) { cout << "  (Sin coautores registrados)\n"; return; }
        while (temp) {
            cout << "  -> Coautor ID: " << temp->id << " | Nombre: " << temp->nombre 
                 << " | Uni: " << temp->universidad << " | Pubs: " << temp->publicacionesConjuntas << endl;
            temp = temp->sig;
        }
    }
    
    bool modificar(int id, string nuevoNombre, string nuevaUni, int nuevasPubs) {
        NodoCoautor* temp = buscarPorId(id);
        if (temp) {
            temp->nombre = nuevoNombre;
            temp->universidad = nuevaUni;
            temp->publicacionesConjuntas = nuevasPubs;
            return true;
        }
        return false;
    }
    
    bool eliminar(int id) {
        NodoCoautor* temp = buscarPorId(id);
        if (!temp) return false;
        
        if (temp->ant) temp->ant->sig = temp->sig;
        else primero = temp->sig;
        
        if (temp->sig) temp->sig->ant = temp->ant;
        
        delete temp;
        return true;
    }
    
    NodoCoautor* getPrimero() { return primero; }
};

// --- LISTA SIMPLE: INVESTIGADORES ---
struct NodoInvestigador {
    int id;
    string nombreCompleto;
    int idUniversidad; // Relación con Universidad
    string pais;
    int idArea;        // Relación con Área
    string correo;
    int indiceH;
    ListaCoautores* sublistaCoautores; // Sublista de Coautores
    NodoInvestigador* sig;
    
    NodoInvestigador(int i, string n, int idU, string p, int idA, string c, int h) 
        : id(i), nombreCompleto(n), idUniversidad(idU), pais(p), idArea(idA), correo(c), indiceH(h), sig(nullptr) {
        sublistaCoautores = new ListaCoautores();
    }
};

class ListaInvestigadores {
private:
    NodoInvestigador* primero;
public:
    ListaInvestigadores() : primero(nullptr) {}
    
    void insertarAlFinal(int id, string nombre, int idUni, string pais, int idArea, string correo, int h) {
        if (buscarPorId(id) != nullptr) {
            cout << "Error: El ID de investigador " << id << " ya existe.\n";
            return;
        }
        NodoInvestigador* nuevo = new NodoInvestigador(id, nombre, idUni, pais, idArea, correo, h);
        if (!primero) primero = nuevo;
        else {
            NodoInvestigador* temp = primero;
            while (temp->sig) temp = temp->sig;
            temp->sig = nuevo;
        }
        cout << "Investigador insertado correctamente.\n";
    }
    
    NodoInvestigador* buscarPorId(int id) {
        NodoInvestigador* temp = primero;
        while (temp) {
            if (temp->id == id) return temp;
            temp = temp->sig;
        }
        return nullptr;
    }
    
    void mostrar() {
        NodoInvestigador* temp = primero;
        if (!temp) { cout << "No hay investigadores registrados.\n"; return; }
        cout << "\n--- LISTA DE INVESTIGADORES ---\n";
        while (temp) {
            cout << "ID: " << temp->id << " | Nombre: " << temp->nombreCompleto 
                 << " | ID Uni: " << temp->idUniversidad << " | ID Area: " << temp->idArea
                 << " | Indice H: " << temp->indiceH << endl;
            temp = temp->sig;
        }
    }
    
    bool modificar(int id, string nuevoNombre, int nuevaUni, string nuevoPais, int nuevaArea, string nuevoCorreo, int nuevoH) {
        NodoInvestigador* temp = buscarPorId(id);
        if (temp) {
            temp->nombreCompleto = nuevoNombre;
            temp->idUniversidad = nuevaUni;
            temp->pais = nuevoPais;
            temp->idArea = nuevaArea;
            temp->correo = nuevoCorreo;
            temp->indiceH = nuevoH;
            return true;
        }
        return false;
    }
    
    bool eliminar(int id) {
        if (!primero) return false;
        if (primero->id == id) {
            NodoInvestigador* aux = primero;
            primero = primero->sig;
            delete aux->sublistaCoautores;
            delete aux;
            return true;
        }
        NodoInvestigador* actual = primero;
        while (actual->sig && actual->sig->id != id) actual = actual->sig;
        if (actual->sig) {
            NodoInvestigador* aux = actual->sig;
            actual->sig = aux->sig;
            delete aux->sublistaCoautores;
            delete aux;
            return true;
        }
        return false;
    }
    
    NodoInvestigador* getPrimero() { return primero; }
    
    // --- CONSULTAS Y REPORTES ---
    
    void mostrarRedCoautoria(int idInvestigador) {
        NodoInvestigador* inv = buscarPorId(idInvestigador);
        if (inv) {
            cout << "\nRed de coautoria de: " << inv->nombreCompleto << endl;
            inv->sublistaCoautores->mostrar();
        } else {
            cout << "Investigador no encontrado.\n";
        }
    }
    
    void mostrarAgrupadosPorUniversidad(ListaUniversidades& listaUnis) {
        cout << "\n--- INVESTIGADORES AGRUPADOS POR UNIVERSIDAD ---\n";
        NodoUniversidad* uni = listaUnis.getPrimero();
        while (uni) {
            cout << "\nUniversidad: " << uni->nombre << endl;
            NodoInvestigador* inv = primero;
            bool hay = false;
            while (inv) {
                if (inv->idUniversidad == uni->id) {
                    cout << "  - " << inv->nombreCompleto << " (Indice H: " << inv->indiceH << ")" << endl;
                    hay = true;
                }
                inv = inv->sig;
            }
            if (!hay) cout << "  (No hay investigadores registrados en esta universidad)\n";
            uni = uni->sig;
        }
    }
    
    void mostrarOrdenadosPorIndiceH() {
        vector<NodoInvestigador*> vec;
        NodoInvestigador* temp = primero;
        while (temp) {
            vec.push_back(temp);
            temp = temp->sig;
        }
        
        for (size_t i = 0; i < vec.size(); i++) {
            for (size_t j = i + 1; j < vec.size(); j++) {
                if (vec[i]->indiceH < vec[j]->indiceH) {
                    swap(vec[i], vec[j]);
                }
            }
        }
        
        cout << "\n--- INVESTIGADORES ORDENADOS POR INDICE H (Descendente) ---\n";
        for (auto inv : vec) {
            cout << "Indice H: " << inv->indiceH << " | " << inv->nombreCompleto << endl;
        }
    }
    
    void investigadorMayorIndiceH() {
        if (!primero) { cout << "No hay investigadores.\n"; return; }
        NodoInvestigador* mayor = primero;
        NodoInvestigador* temp = primero->sig;
        while (temp) {
            if (temp->indiceH > mayor->indiceH) mayor = temp;
            temp = temp->sig;
        }
        cout << "\nInvestigador con mayor Indice H: " << mayor->nombreCompleto 
             << " (Indice H: " << mayor->indiceH << ")" << endl;
    }
    
    void investigadorMasCoautores() {
        if (!primero) { cout << "No hay investigadores.\n"; return; }
        NodoInvestigador* mayor = primero;
        int maxCoautores = 0;
        NodoInvestigador* temp = primero;
        
        while (temp) {
            int cont = 0;
            NodoCoautor* c = temp->sublistaCoautores->getPrimero();
            while (c) { cont++; c = c->sig; }
            
            if (cont > maxCoautores) {
                maxCoautores = cont;
                mayor = temp;
            }
            temp = temp->sig;
        }
        cout << "\nInvestigador con mas coautores: " << mayor->nombreCompleto 
             << " (" << maxCoautores << " coautores)" << endl;
    }
    
    void universidadConMasInvestigadores(ListaUniversidades& listaUnis) {
        if (!primero) { cout << "No hay investigadores.\n"; return; }
        NodoUniversidad* uni = listaUnis.getPrimero();
        NodoUniversidad* mayorUni = nullptr;
        int maxInv = -1;
    
        while (uni) {
            int cont = 0;
            NodoInvestigador* inv = primero;
            while (inv) {
                if (inv->idUniversidad == uni->id) cont++;
                inv = inv->sig;
            }
            if (cont > maxInv) {
                maxInv = cont;
                mayorUni = uni;
            }
            uni = uni->sig;
        }
        if (mayorUni) {
            cout << "\nUniversidad con mas investigadores: " << mayorUni->nombre 
                 << " (" << maxInv << " investigadores)" << endl;
        }
    }
    
    void areaQueGeneraMasPublicaciones(ListaAreas& listaAreas) {
        cout << "\n--- AREA QUE GENERA MAS PUBLICACIONES (Aproximado por investigadores) ---\n";
        NodoArea* area = listaAreas.getPrimero();
        NodoArea* mayorArea = nullptr;
        int maxInv = -1;
    
        while (area) {
            int cont = 0;
            NodoInvestigador* inv = primero;
            while (inv) {
                if (inv->idArea == area->id) cont++;
                inv = inv->sig;
            }
            if (cont > maxInv) {
                maxInv = cont;
                mayorArea = area;
            }
            area = area->sig;
        }
        if (mayorArea) {
            cout << "Area con mas investigadores: " << mayorArea->nombre 
                 << " (" << maxInv << " investigadores)" << endl;
        }
    }
    
    void mostrarInvestigadoresConPublicaciones() {
        cout << "\n--- INVESTIGADORES CON SUS PUBLICACIONES ---\n";
        cout << "(Pendiente de integracion con el modulo de Publicaciones - Persona 3)\n";
        NodoInvestigador* temp = primero;
        while (temp) {
            cout << "Investigador: " << temp->nombreCompleto << endl;
            cout << "  -> (Aqui iran las publicaciones asociadas)\n";
            temp = temp->sig;
        }
    }
};

// =========================================================================
// FUNCION PRINCIPAL Y PRECARGA DE DATOS
// =========================================================================

void precargarDatos(ListaUniversidades& unis, ListaAreas& areas, ListaInvestigadores& invs) {
    // Universidades (5)
    unis.insertarAlFinal(1, "TEC", "Costa Rica", 1);
    unis.insertarAlFinal(2, "UCR", "Costa Rica", 2);
    unis.insertarAlFinal(3, "UNA", "Costa Rica", 3);
    unis.insertarAlFinal(4, "MIT", "USA", 1);
    unis.insertarAlFinal(5, "Stanford", "USA", 2);

    // Areas (5)
    areas.insertarAlFinal(1, "Inteligencia Artificial", "IA y Machine Learning");
    areas.insertarAlFinal(2, "Ciberseguridad", "Seguridad informatica");
    areas.insertarAlFinal(3, "Redes", "Redes de computadoras");
    areas.insertarAlFinal(4, "Software", "Ingenieria de software");
    areas.insertarAlFinal(5, "Datos", "Bases de datos y Big Data");

    // Investigadores (5 minimo)
    invs.insertarAlFinal(1, "Ana Perez", 1, "Costa Rica", 1, "ana@tec.ac.cr", 15);
    invs.insertarAlFinal(2, "Carlos Lopez", 2, "Costa Rica", 2, "carlos@ucr.ac.cr", 8);
    invs.insertarAlFinal(3, "Maria Ruiz", 1, "Costa Rica", 3, "maria@tec.ac.cr", 22);
    invs.insertarAlFinal(4, "John Doe", 4, "USA", 1, "john@mit.edu", 45);
    invs.insertarAlFinal(5, "Elena Gomez", 5, "USA", 4, "elena@stanford.edu", 12);

    // Agregar coautores a los investigadores (Sublista - Lista Doble)
    NodoInvestigador* inv1 = invs.buscarPorId(1);
    if(inv1) {
        inv1->sublistaCoautores->insertarAlInicio(101, "Luis Solis", "UCR", 3);
        inv1->sublistaCoautores->insertarAlInicio(102, "Sara Mora", "TEC", 5);
    }
    NodoInvestigador* inv3 = invs.buscarPorId(3);
    if(inv3) {
        inv3->sublistaCoautores->insertarAlInicio(103, "Pedro Picapiedra", "UNA", 2);
        inv3->sublistaCoautores->insertarAlInicio(104, "Rocio Perez", "TEC", 4);
        inv3->sublistaCoautores->insertarAlInicio(105, "Marta Vega", "MIT", 1);
    }
    NodoInvestigador* inv5 = invs.buscarPorId(5);
    if(inv5) {
        inv5->sublistaCoautores->insertarAlInicio(106, "Albert Einstein", "Princeton", 10);
    }
    
    cout << "\n[INFO] Datos precargados correctamente (5 universidades, 5 areas, 5 investigadores).\n";
}

int main() {
    ListaUniversidades listaUnis;
    ListaAreas listaAreas;
    ListaInvestigadores listaInvs;

    precargarDatos(listaUnis, listaAreas, listaInvs);

    int opcion;
    do {
        cout << "\n============================================\n";
        cout << "INVESTIGADORES\n";
        cout << "============================================\n";
        cout << "1. Mostrar Universidades\n";
        cout << "2. Mostrar Areas\n";
        cout << "3. Mostrar Investigadores (con sus coautores)\n";
        cout << "4. Consulta: Investigador con mayor Indice H\n";
        cout << "5. Consulta: Investigador con mas coautores\n";
        cout << "6. Consulta: Universidad con mas investigadores\n";
        cout << "7. Consulta: Area que genera mas publicaciones (aprox)\n";
        cout << "8. Reporte: Agrupados por Universidad\n";
        cout << "9. Reporte: Ordenados por Indice H\n";
        cout << "10. Reporte: Red de coautoria de un investigador\n";
        cout << "11. Reporte: Investigadores con sus publicaciones\n";
        cout << "0. Salir\n";
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1: listaUnis.mostrar(); break;
            case 2: listaAreas.mostrar(); break;
            case 3: 
                listaInvs.mostrar();
                cout << "\n--- DETALLE DE COAUTORES ---\n";
                {
                    NodoInvestigador* temp = listaInvs.getPrimero();
                    while(temp) {
                        cout << "Investigador: " << temp->nombreCompleto << endl;
                        temp->sublistaCoautores->mostrar();
                        temp = temp->sig;
                    }
                }
                break;
            case 4: listaInvs.investigadorMayorIndiceH(); break;
            case 5: listaInvs.investigadorMasCoautores(); break;
            case 6: listaInvs.universidadConMasInvestigadores(listaUnis); break;
            case 7: listaInvs.areaQueGeneraMasPublicaciones(listaAreas); break;
            case 8: listaInvs.mostrarAgrupadosPorUniversidad(listaUnis); break;
            case 9: listaInvs.mostrarOrdenadosPorIndiceH(); break;
            case 10: {
                int id;
                cout << "Ingrese ID del investigador: ";
                cin >> id;
                listaInvs.mostrarRedCoautoria(id);
                break;
            }
            case 11: listaInvs.mostrarInvestigadoresConPublicaciones(); break;
            case 0: cout << "Saliendo del modulo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while(opcion != 0);

    return 0;
}