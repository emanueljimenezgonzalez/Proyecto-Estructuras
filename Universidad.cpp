#include "Universidad.h"
#include <iostream>
#include <iomanip>

ListaUniversidades::ListaUniversidades() : cabeza(nullptr), cola(nullptr), tamano(0) {}

ListaUniversidades::~ListaUniversidades() {
    liberar();
}

void ListaUniversidades::liberar() {
    NodoUniversidad* actual = cabeza;
    while (actual != nullptr) {
        NodoUniversidad* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}

bool ListaUniversidades::existeId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

bool ListaUniversidades::insertar(const std::string& id, const std::string& nom, const std::string& pais, int ranking) {
    if (id.empty() || nom.empty()) {
        std::cout << "[ERROR] El ID y nombre de la universidad no pueden ser vacios.\n";
        return false;
    }
    if (ranking <= 0) {
        std::cout << "[ERROR] El ranking debe ser un numero positivo.\n";
        return false;
    }
    if (existeId(id)) {
        std::cout << "[ERROR] Ya existe una universidad con el ID: " << id << "\n";
        return false;
    }

    NodoUniversidad* nuevo = new NodoUniversidad(id, nom, pais, ranking);
    if (cabeza == nullptr) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
    tamano++;
    return true;
}

NodoUniversidad* ListaUniversidades::buscarPorId(const std::string& id) const {
    NodoUniversidad* actual = cabeza;
    while (actual != nullptr) {
        if (actual->idUniversidad == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ListaUniversidades::modificar(const std::string& id, const std::string& nuevoNombre, const std::string& nuevoPais, int nuevoRanking) {
    NodoUniversidad* nodo = buscarPorId(id);
    if (nodo == nullptr) {
        std::cout << "[ERROR] No se encontro la universidad con ID: " << id << "\n";
        return false;
    }
    if (!nuevoNombre.empty()) nodo->nombre = nuevoNombre;
    if (!nuevoPais.empty()) nodo->pais = nuevoPais;
    if (nuevoRanking > 0) nodo->ranking = nuevoRanking;
    return true;
}

bool ListaUniversidades::eliminar(const std::string& id) {
    NodoUniversidad* nodo = buscarPorId(id);
    if (nodo == nullptr) return false;

    if (nodo == cabeza && nodo == cola) {
        cabeza = cola = nullptr;
    } else if (nodo == cabeza) {
        cabeza = cabeza->siguiente;
        cabeza->anterior = nullptr;
    } else if (nodo == cola) {
        cola = cola->anterior;
        cola->siguiente = nullptr;
    } else {
        nodo->anterior->siguiente = nodo->siguiente;
        nodo->siguiente->anterior = nodo->anterior;
    }

    delete nodo;
    tamano--;
    return true;
}

void ListaUniversidades::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "  (Lista de universidades vacia)\n";
        return;
    }

    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(15) << "ID Universidad"
              << std::setw(32) << "Nombre"
              << std::setw(20) << "Pais"
              << "Ranking Global" << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";

    NodoUniversidad* actual = cabeza;
    while (actual != nullptr) {
        std::cout << std::left << std::setw(15) << actual->idUniversidad
                  << std::setw(32) << actual->nombre
                  << std::setw(20) << actual->pais
                  << "#" << actual->ranking << "\n";
        actual = actual->siguiente;
    }
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "Total de universidades: " << tamano << "\n";
}
