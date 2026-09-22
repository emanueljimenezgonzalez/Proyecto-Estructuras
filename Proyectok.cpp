#include "Proyecto.h"
#include <iostream>
#include <iomanip>

ListaProyectos::ListaProyectos() : cabeza(nullptr), cola(nullptr), tamano(0) {}

ListaProyectos::~ListaProyectos() {
    liberar();
}

void ListaProyectos::liberar() {
    NodoProyecto* actual = cabeza;
    while (actual != nullptr) {
        NodoProyecto* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}

bool ListaProyectos::existeId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

bool ListaProyectos::insertarOrdenadoPorAnio(const std::string& id, const std::string& nom, double fin,
                                            int aIni, int aFin, NodoInvestigador* resp) {
    if (id.empty() || nom.empty()) {
        std::cout << "[ERROR] ID y nombre del proyecto son obligatorios.\n";
        return false;
    }
    if (aFin < aIni) {
        std::cout << "[ERROR] El ano de finalizacion no puede ser menor al de inicio.\n";
        return false;
    }
    if (fin < 0.0) {
        std::cout << "[ERROR] El financiamiento no puede ser negativo.\n";
        return false;
    }
    if (existeId(id)) {
        std::cout << "[ERROR] Ya existe un proyecto con el ID: " << id << "\n";
        return false;
    }

    NodoProyecto* nuevo = new NodoProyecto(id, nom, fin, aIni, aFin, resp);

    if (cabeza == nullptr) {
        cabeza = cola = nuevo;
    } else if (aIni < cabeza->anioInicio) {
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
        cabeza = nuevo;
    } else if (aIni >= cola->anioInicio) {
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    } else {
        NodoProyecto* actual = cabeza;
        while (actual != nullptr && actual->anioInicio <= aIni) {
            actual = actual->siguiente;
        }
        // Insertar nuevo antes de actual
        nuevo->siguiente = actual;
        nuevo->anterior = actual->anterior;
        actual->anterior->siguiente = nuevo;
        actual->anterior = nuevo;
    }
    tamano++;
    return true;
}

NodoProyecto* ListaProyectos::buscarPorId(const std::string& id) const {
    NodoProyecto* actual = cabeza;
    while (actual != nullptr) {
        if (actual->idProyecto == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ListaProyectos::modificar(const std::string& id, const std::string& nuevoNom, double nuevoFin,
                              int nuevoAIni, int nuevoAFin, NodoInvestigador* nuevoResp) {
    NodoProyecto* p = buscarPorId(id);
    if (p == nullptr) {
        std::cout << "[ERROR] Proyecto no encontrado con ID: " << id << "\n";
        return false;
    }

    if (nuevoAIni > 0 && nuevoAIni != p->anioInicio) {
        // Si cambia año de inicio, para preservar el orden eliminamos y reinsertamos
        std::string nomFinal = nuevoNom.empty() ? p->nombre : nuevoNom;
        double finFinal = (nuevoFin >= 0.0) ? nuevoFin : p->financiamiento;
        int aIniFinal = nuevoAIni;
        int aFinFinal = (nuevoAFin >= aIniFinal) ? nuevoAFin : p->anioFin;
        NodoInvestigador* respFinal = (nuevoResp != nullptr) ? nuevoResp : p->investigadorResponsable;

        eliminar(id);
        return insertarOrdenadoPorAnio(id, nomFinal, finFinal, aIniFinal, aFinFinal, respFinal);
    }

    if (!nuevoNom.empty()) p->nombre = nuevoNom;
    if (nuevoFin >= 0.0) p->financiamiento = nuevoFin;
    if (nuevoAFin >= p->anioInicio) p->anioFin = nuevoAFin;
    if (nuevoResp != nullptr) p->investigadorResponsable = nuevoResp;
    return true;
}

bool ListaProyectos::eliminar(const std::string& id) {
    NodoProyecto* nodo = buscarPorId(id);
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

void ListaProyectos::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "  (Lista de proyectos vacia)\n";
        return;
    }

    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(12) << "ID Proy"
              << std::setw(30) << "Nombre del Proyecto"
              << std::setw(16) << "Financiamiento"
              << std::setw(12) << "Periodo"
              << "Investigador Resp." << "\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    NodoProyecto* actual = cabeza;
    while (actual != nullptr) {
        std::string periodo = std::to_string(actual->anioInicio) + "-" + std::to_string(actual->anioFin);
        std::string resp = (actual->investigadorResponsable != nullptr)
                           ? actual->investigadorResponsable->nombreCompleto
                           : "Sin asignar";

        std::cout << std::left << std::setw(12) << actual->idProyecto
                  << std::setw(30) << actual->nombre
                  << "$" << std::setw(15) << std::fixed << std::setprecision(2) << actual->financiamiento
                  << std::setw(12) << periodo
                  << resp << "\n";
        actual = actual->siguiente;
    }
    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "Total de proyectos registrados: " << tamano << "\n";
}
