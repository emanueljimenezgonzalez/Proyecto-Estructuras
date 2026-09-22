#include "Citacion.h"
#include <iostream>
#include <iomanip>

ListaCitaciones::ListaCitaciones() : cabeza(nullptr), cola(nullptr), tamano(0) {}

ListaCitaciones::~ListaCitaciones() {
    liberar();
}

void ListaCitaciones::liberar() {
    NodoCitacion* actual = cabeza;
    while (actual != nullptr) {
        NodoCitacion* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}

bool ListaCitaciones::existeId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

bool ListaCitaciones::insertar(const std::string& id, int a, const std::string& pubCit, const std::string& autCit) {
    if (id.empty()) {
        std::cout << "    [ERROR] El ID de la citacion es requerido.\n";
        return false;
    }
    if (a <= 0) {
        std::cout << "    [ERROR] El ano de la citacion debe ser valido.\n";
        return false;
    }
    if (existeId(id)) {
        std::cout << "    [ERROR] Ya existe una cita con ID: " << id << "\n";
        return false;
    }

    NodoCitacion* nuevo = new NodoCitacion(id, a, pubCit, autCit);
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

NodoCitacion* ListaCitaciones::buscarPorId(const std::string& id) const {
    NodoCitacion* actual = cabeza;
    while (actual != nullptr) {
        if (actual->idCita == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ListaCitaciones::modificar(const std::string& id, int nuevoAnio, const std::string& nuevaPubCit, const std::string& nuevoAutCit) {
    NodoCitacion* nodo = buscarPorId(id);
    if (nodo == nullptr) return false;
    if (nuevoAnio > 0) nodo->anio = nuevoAnio;
    if (!nuevaPubCit.empty()) nodo->publicacionCitante = nuevaPubCit;
    if (!nuevoAutCit.empty()) nodo->autorCitante = nuevoAutCit;
    return true;
}

bool ListaCitaciones::eliminar(const std::string& id) {
    NodoCitacion* nodo = buscarPorId(id);
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

void ListaCitaciones::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "    (Sin citas registradas en la sublista)\n";
        return;
    }

    NodoCitacion* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "    * [" << actual->idCita << "] (" << actual->anio << ") "
                  << "\"" << actual->publicacionCitante << "\" por " << actual->autorCitante << "\n";
        actual = actual->siguiente;
    }
}
