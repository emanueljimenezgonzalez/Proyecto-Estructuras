#include "Area.h"
#include <iostream>
#include <iomanip>

ListaAreas::ListaAreas() : cabeza(nullptr), tamano(0) {}

ListaAreas::~ListaAreas() {
    liberar();
}

void ListaAreas::liberar() {
    NodoArea* actual = cabeza;
    while (actual != nullptr) {
        NodoArea* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    tamano = 0;
}

bool ListaAreas::existeId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

bool ListaAreas::insertarAlFinal(const std::string& id, const std::string& nom, const std::string& desc) {
    if (id.empty() || nom.empty()) {
        std::cout << "[ERROR] El ID y el nombre del area no pueden estar vacios.\n";
        return false;
    }
    if (existeId(id)) {
        std::cout << "[ERROR] Ya existe un area con el ID: " << id << "\n";
        return false;
    }

    NodoArea* nuevo = new NodoArea(id, nom, desc);
    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        NodoArea* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    tamano++;
    return true;
}

NodoArea* ListaAreas::buscarPorId(const std::string& id) const {
    NodoArea* actual = cabeza;
    while (actual != nullptr) {
        if (actual->idArea == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ListaAreas::modificar(const std::string& id, const std::string& nuevoNombre, const std::string& nuevaDesc) {
    NodoArea* nodo = buscarPorId(id);
    if (nodo == nullptr) {
        std::cout << "[ERROR] No se encontro el area con ID: " << id << "\n";
        return false;
    }
    if (!nuevoNombre.empty()) nodo->nombre = nuevoNombre;
    if (!nuevaDesc.empty()) nodo->descripcion = nuevaDesc;
    return true;
}

bool ListaAreas::eliminar(const std::string& id) {
    if (cabeza == nullptr) return false;

    if (cabeza->idArea == id) {
        NodoArea* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        tamano--;
        return true;
    }

    NodoArea* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->idArea != id) {
        actual = actual->siguiente;
    }

    if (actual->siguiente != nullptr) {
        NodoArea* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        tamano--;
        return true;
    }

    return false;
}

void ListaAreas::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "  (Lista de areas vacia)\n";
        return;
    }

    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(12) << "ID Area"
              << std::setw(28) << "Nombre del Area"
              << "Descripcion" << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";

    NodoArea* actual = cabeza;
    while (actual != nullptr) {
        std::cout << std::left << std::setw(12) << actual->idArea
                  << std::setw(28) << actual->nombre
                  << actual->descripcion << "\n";
        actual = actual->siguiente;
    }
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "Total de areas registradas: " << tamano << "\n";
}
