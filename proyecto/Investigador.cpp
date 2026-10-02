#include "Investigador.h"
#include <iostream>
#include <iomanip>

ListaInvestigadores::ListaInvestigadores() : cabeza(nullptr), tamano(0) {}

ListaInvestigadores::~ListaInvestigadores() {
    liberar();
}

void ListaInvestigadores::liberar() {
    NodoInvestigador* actual = cabeza;
    while (actual != nullptr) {
        NodoInvestigador* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    tamano = 0;
}

bool ListaInvestigadores::existeId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

bool ListaInvestigadores::insertarAlFinal(const std::string& id, const std::string& nom,
                                         NodoUniversidad* uni, const std::string& pais,
                                         NodoArea* ar, const std::string& email) {
    if (id.empty() || nom.empty()) {
        std::cout << "[ERROR] El ID y el nombre del investigador son obligatorios.\n";
        return false;
    }
    if (existeId(id)) {
        std::cout << "[ERROR] Ya existe un investigador con el ID: " << id << "\n";
        return false;
    }

    NodoInvestigador* nuevo = new NodoInvestigador(id, nom, uni, pais, ar, email);
    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        NodoInvestigador* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    tamano++;
    return true;
}

NodoInvestigador* ListaInvestigadores::buscarPorId(const std::string& id) const {
    NodoInvestigador* actual = cabeza;
    while (actual != nullptr) {
        if (actual->idInvestigador == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ListaInvestigadores::modificar(const std::string& id, const std::string& nuevoNombre,
                                    NodoUniversidad* nuevaUni, const std::string& nuevoPais,
                                    NodoArea* nuevaArea, const std::string& nuevoCorreo) {
    NodoInvestigador* inv = buscarPorId(id);
    if (inv == nullptr) {
        std::cout << "[ERROR] Investigador no encontrado con ID: " << id << "\n";
        return false;
    }
    if (!nuevoNombre.empty()) inv->nombreCompleto = nuevoNombre;
    if (nuevaUni != nullptr) inv->universidad = nuevaUni;
    if (!nuevoPais.empty()) inv->pais = nuevoPais;
    if (nuevaArea != nullptr) inv->area = nuevaArea;
    if (!nuevoCorreo.empty()) inv->correo = nuevoCorreo;
    return true;
}

bool ListaInvestigadores::eliminar(const std::string& id) {
    if (cabeza == nullptr) return false;

    if (cabeza->idInvestigador == id) {
        NodoInvestigador* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        tamano--;
        return true;
    }

    NodoInvestigador* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->idInvestigador != id) {
        actual = actual->siguiente;
    }

    if (actual->siguiente != nullptr) {
        NodoInvestigador* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        tamano--;
        return true;
    }

    return false;
}

void ListaInvestigadores::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "  (Lista de investigadores vacia)\n";
        return;
    }

    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(26) << "Nombre Completo"
              << std::setw(32) << "Universidad"
              << std::setw(26) << "Area"
              << std::setw(10) << "Indice H"
              << "Coautores" << "\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";

    NodoInvestigador* actual = cabeza;
    while (actual != nullptr) {
        std::string nomUni = (actual->universidad != nullptr) ? actual->universidad->nombre : "Sin asignar";
        std::string nomArea = (actual->area != nullptr) ? actual->area->nombre : "Sin asignar";

        std::cout << std::left << std::setw(10) << actual->idInvestigador
                  << std::setw(26) << actual->nombreCompleto
                  << std::setw(32) << nomUni
                  << std::setw(26) << nomArea
                  << std::setw(10) << actual->indiceH
                  << actual->sublistaCoautores.getTamano() << "\n";
        actual = actual->siguiente;
    }
    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "Total de investigadores registrados: " << tamano << "\n";
}

void ListaInvestigadores::mostrarConDetalles() const {
    if (cabeza == nullptr) {
        std::cout << "  (Lista de investigadores vacia)\n";
        return;
    }

    NodoInvestigador* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "================================================================================\n";
        std::cout << "ID: " << actual->idInvestigador << " | Nombre: " << actual->nombreCompleto << "\n";
        std::cout << "Universidad: " << (actual->universidad ? actual->universidad->nombre : "N/A")
                  << " (" << (actual->universidad ? actual->universidad->pais : "N/A") << ")\n";
        std::cout << "Pais: " << actual->pais
                  << " | Correo: " << actual->correo << "\n";
        std::cout << "Area: " << (actual->area ? actual->area->nombre : "N/A")
                  << " | Indice H actual: " << actual->indiceH << "\n";
        std::cout << "Red de Coautores (" << actual->sublistaCoautores.getTamano() << "):\n";
        actual->sublistaCoautores.mostrar();
        actual = actual->siguiente;
    }
    std::cout << "================================================================================\n";
}
