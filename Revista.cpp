#include "Revista.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

ListaRevistas::ListaRevistas() : cabeza(nullptr), tamano(0) {}

ListaRevistas::~ListaRevistas() {
    liberar();
}

void ListaRevistas::liberar() {
    NodoRevista* actual = cabeza;
    while (actual != nullptr) {
        NodoRevista* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    tamano = 0;
}

bool ListaRevistas::existeId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

bool ListaRevistas::esCuartilValido(const std::string& q) {
    return (q == "Q1" || q == "Q2" || q == "Q3" || q == "Q4");
}

bool ListaRevistas::insertarOrdenado(const std::string& id, const std::string& nom, const std::string& ed,
                                    const std::string& p, double fi, const std::string& q) {
    if (id.empty() || nom.empty()) {
        std::cout << "[ERROR] ID y nombre de revista son obligatorios.\n";
        return false;
    }
    if (fi < 0.0) {
        std::cout << "[ERROR] El factor de impacto no puede ser negativo.\n";
        return false;
    }
    if (!esCuartilValido(q)) {
        std::cout << "[ERROR] Cuartil invalido. Debe ser Q1, Q2, Q3 o Q4.\n";
        return false;
    }
    if (existeId(id)) {
        std::cout << "[ERROR] Ya existe una revista con el ID: " << id << "\n";
        return false;
    }

    NodoRevista* nuevo = new NodoRevista(id, nom, ed, p, fi, q);

    // Inserción ordenada alfabéticamente por nombre
    if (cabeza == nullptr || nom < cabeza->nombre) {
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
    } else {
        NodoRevista* actual = cabeza;
        while (actual->siguiente != nullptr && actual->siguiente->nombre < nom) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
    tamano++;
    return true;
}

NodoRevista* ListaRevistas::buscarPorId(const std::string& id) const {
    NodoRevista* actual = cabeza;
    while (actual != nullptr) {
        if (actual->idRevista == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

NodoRevista* ListaRevistas::buscarPorNombre(const std::string& nom) const {
    NodoRevista* actual = cabeza;
    while (actual != nullptr) {
        if (actual->nombre == nom) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ListaRevistas::modificar(const std::string& id, const std::string& nuevoNom, const std::string& nuevaEd,
                             const std::string& nuevoPais, double nuevoFI, const std::string& nuevoCuartil) {
    NodoRevista* rev = buscarPorId(id);
    if (rev == nullptr) {
        std::cout << "[ERROR] Revista no encontrada con ID: " << id << "\n";
        return false;
    }
    if (!nuevoNom.empty() && nuevoNom != rev->nombre) {
        // Si cambia el nombre, para preservar el orden debemos reinsertar
        std::string edFinal = nuevaEd.empty() ? rev->editorial : nuevaEd;
        std::string paisFinal = nuevoPais.empty() ? rev->pais : nuevoPais;
        double fiFinal = (nuevoFI >= 0.0) ? nuevoFI : rev->factorImpacto;
        std::string qFinal = esCuartilValido(nuevoCuartil) ? nuevoCuartil : rev->cuartil;

        eliminar(id);
        return insertarOrdenado(id, nuevoNom, edFinal, paisFinal, fiFinal, qFinal);
    }
    if (!nuevaEd.empty()) rev->editorial = nuevaEd;
    if (!nuevoPais.empty()) rev->pais = nuevoPais;
    if (nuevoFI >= 0.0) rev->factorImpacto = nuevoFI;
    if (esCuartilValido(nuevoCuartil)) rev->cuartil = nuevoCuartil;
    return true;
}

bool ListaRevistas::eliminar(const std::string& id) {
    if (cabeza == nullptr) return false;

    if (cabeza->idRevista == id) {
        NodoRevista* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        tamano--;
        return true;
    }

    NodoRevista* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->idRevista != id) {
        actual = actual->siguiente;
    }

    if (actual->siguiente != nullptr) {
        NodoRevista* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        tamano--;
        return true;
    }

    return false;
}

void ListaRevistas::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "  (Lista de revistas vacia)\n";
        return;
    }

    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(12) << "ID Revista"
              << std::setw(30) << "Nombre"
              << std::setw(20) << "Editorial"
              << std::setw(16) << "Pais"
              << std::setw(12) << "Factor Imp."
              << "Cuartil" << "\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    NodoRevista* actual = cabeza;
    while (actual != nullptr) {
        std::cout << std::left << std::setw(12) << actual->idRevista
                  << std::setw(30) << actual->nombre
                  << std::setw(20) << actual->editorial
                  << std::setw(16) << actual->pais
                  << std::setw(12) << std::fixed << std::setprecision(3) << actual->factorImpacto
                  << actual->cuartil << "\n";
        actual = actual->siguiente;
    }
    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "Total de revistas registradas: " << tamano << "\n";
}
