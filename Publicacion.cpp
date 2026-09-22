#include "Publicacion.h"
#include <iostream>
#include <iomanip>

ListaPublicaciones::ListaPublicaciones() : cabeza(nullptr), tamano(0) {}

ListaPublicaciones::~ListaPublicaciones() {
    liberar();
}

void ListaPublicaciones::liberar() {
    if (cabeza == nullptr) return;

    // Romper el ciclo circular para liberar ordenadamente
    NodoPublicacion* ultimo = cabeza;
    while (ultimo->siguiente != cabeza) {
        ultimo = ultimo->siguiente;
    }
    ultimo->siguiente = nullptr;

    NodoPublicacion* actual = cabeza;
    while (actual != nullptr) {
        NodoPublicacion* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }

    cabeza = nullptr;
    tamano = 0;
}

bool ListaPublicaciones::existeId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

bool ListaPublicaciones::esTipoValido(const std::string& t) {
    return (t == "Articulo" || t == "Libro" || t == "Conferencia" ||
            t == "Artículo" || t == "articulo" || t == "libro" || t == "conferencia");
}

bool ListaPublicaciones::insertarOrdenadoPorAnio(const std::string& id, const std::string& tit, int anio,
                                                 const std::string& tipo, int citas, const std::string& doi,
                                                 NodoInvestigador* inv, NodoRevista* rev, NodoProyecto* proy) {
    if (id.empty() || tit.empty()) {
        std::cout << "[ERROR] ID y titulo de la publicacion son obligatorios.\n";
        return false;
    }
    if (anio <= 0) {
        std::cout << "[ERROR] El ano de la publicacion debe ser valido.\n";
        return false;
    }
    if (citas < 0) citas = 0;
    if (existeId(id)) {
        std::cout << "[ERROR] Ya existe una publicacion con el ID: " << id << "\n";
        return false;
    }

    std::string tipoNormalizado = tipo;
    if (tipo == "Artículo" || tipo == "articulo") tipoNormalizado = "Articulo";
    else if (tipo == "libro") tipoNormalizado = "Libro";
    else if (tipo == "conferencia") tipoNormalizado = "Conferencia";

    NodoPublicacion* nuevo = new NodoPublicacion(id, tit, anio, tipoNormalizado, citas, doi, inv, rev, proy);

    if (cabeza == nullptr) {
        nuevo->siguiente = nuevo;
        cabeza = nuevo;
    } else if (anio < cabeza->anio) {
        // Insertar antes de la cabeza: nuevo nodo pasa a ser cabeza
        NodoPublicacion* ultimo = cabeza;
        while (ultimo->siguiente != cabeza) {
            ultimo = ultimo->siguiente;
        }
        nuevo->siguiente = cabeza;
        ultimo->siguiente = nuevo;
        cabeza = nuevo;
    } else {
        // Inserción intermedia o al final
        NodoPublicacion* actual = cabeza;
        while (actual->siguiente != cabeza && actual->siguiente->anio <= anio) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
    tamano++;
    return true;
}

NodoPublicacion* ListaPublicaciones::buscarPorId(const std::string& id) const {
    if (cabeza == nullptr) return nullptr;

    NodoPublicacion* actual = cabeza;
    do {
        if (actual->idPublicacion == id) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    return nullptr;
}

bool ListaPublicaciones::modificar(const std::string& id, const std::string& nuevoTit, int nuevoAnio,
                                  const std::string& nuevoTipo, int nuevasCitas, const std::string& nuevoDoi,
                                  NodoInvestigador* nuevoInv, NodoRevista* nuevaRev, NodoProyecto* nuevoProy) {
    NodoPublicacion* pub = buscarPorId(id);
    if (pub == nullptr) {
        std::cout << "[ERROR] Publicacion no encontrada con ID: " << id << "\n";
        return false;
    }

    if (nuevoAnio > 0 && nuevoAnio != pub->anio) {
        // Para preservar el ordenamiento por año en la lista circular, reinsertamos
        std::string titFinal = nuevoTit.empty() ? pub->titulo : nuevoTit;
        std::string tipFinal = nuevoTipo.empty() ? pub->tipo : nuevoTipo;
        int citFinal = (nuevasCitas >= 0) ? nuevasCitas : pub->cantidadCitas;
        std::string doiFinal = nuevoDoi.empty() ? pub->doi : nuevoDoi;
        NodoInvestigador* invFinal = (nuevoInv != nullptr) ? nuevoInv : pub->investigadorPrincipal;
        NodoRevista* revFinal = (nuevaRev != nullptr) ? nuevaRev : pub->revista;
        NodoProyecto* proyFinal = (nuevoProy != nullptr) ? nuevoProy : pub->proyecto;

        eliminar(id);
        return insertarOrdenadoPorAnio(id, titFinal, nuevoAnio, tipFinal, citFinal, doiFinal, invFinal, revFinal, proyFinal);
    }

    if (!nuevoTit.empty()) pub->titulo = nuevoTit;
    if (!nuevoTipo.empty()) pub->tipo = nuevoTipo;
    if (nuevasCitas >= 0) pub->cantidadCitas = nuevasCitas;
    if (!nuevoDoi.empty()) pub->doi = nuevoDoi;
    if (nuevoInv != nullptr) pub->investigadorPrincipal = nuevoInv;
    if (nuevaRev != nullptr) pub->revista = nuevaRev;
    if (nuevoProy != nullptr) pub->proyecto = nuevoProy;
    return true;
}

bool ListaPublicaciones::eliminar(const std::string& id) {
    if (cabeza == nullptr) return false;

    // Caso 1: Un solo nodo en la lista circular
    if (tamano == 1) {
        if (cabeza->idPublicacion == id) {
            delete cabeza;
            cabeza = nullptr;
            tamano = 0;
            return true;
        }
        return false;
    }

    // Caso 2: El nodo a eliminar es la cabeza
    if (cabeza->idPublicacion == id) {
        NodoPublicacion* ultimo = cabeza;
        while (ultimo->siguiente != cabeza) {
            ultimo = ultimo->siguiente;
        }
        NodoPublicacion* temp = cabeza;
        cabeza = cabeza->siguiente;
        ultimo->siguiente = cabeza;
        delete temp;
        tamano--;
        return true;
    }

    // Caso 3: Nodo intermedio o final
    NodoPublicacion* anterior = cabeza;
    NodoPublicacion* actual = cabeza->siguiente;
    while (actual != cabeza && actual->idPublicacion != id) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != cabeza) {
        anterior->siguiente = actual->siguiente;
        delete actual;
        tamano--;
        return true;
    }

    return false;
}

void ListaPublicaciones::mostrarPublicacionesDeProyecto(const std::string& idProy) const {
    if (cabeza == nullptr) {
        std::cout << "  (Lista de publicaciones vacia)\n";
        return;
    }

    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "PUBLICACIONES VINCULADAS AL PROYECTO ID: " << idProy << "\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    int cuenta = 0;
    NodoPublicacion* actual = cabeza;
    do {
        if (actual->proyecto != nullptr && actual->proyecto->idProyecto == idProy) {
            cuenta++;
            std::cout << "  [" << cuenta << "] \"" << actual->titulo << "\" (" << actual->anio << ")\n"
                      << "      ID Pub: " << actual->idPublicacion
                      << " | Tipo: " << actual->tipo
                      << " | Citas: " << actual->cantidadCitas << "\n"
                      << "      Investigador: "
                      << (actual->investigadorPrincipal ? actual->investigadorPrincipal->nombreCompleto : "N/A") << "\n"
                      << "      Revista: "
                      << (actual->revista ? actual->revista->nombre : "(Sin revista)") << "\n";
        }
        actual = actual->siguiente;
    } while (actual != cabeza);

    if (cuenta == 0) {
        std::cout << "  (No se encontraron publicaciones asociadas a este proyecto)\n";
    }
    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "Total de publicaciones en el proyecto: " << cuenta << "\n";
}

bool ListaPublicaciones::agregarCitaAPublicacion(const std::string& idPub, const std::string& idCita,
                                                int anioCita, const std::string& pubCit, const std::string& autCit) {
    NodoPublicacion* pub = buscarPorId(idPub);
    if (pub == nullptr) {
        std::cout << "[ERROR] Publicacion " << idPub << " no existe.\n";
        return false;
    }

    bool insertado = pub->sublistaCitaciones.insertar(idCita, anioCita, pubCit, autCit);
    if (insertado) {
        // Actualizar la cantidad de citas de la publicación
        if (pub->sublistaCitaciones.getTamano() > pub->cantidadCitas) {
            pub->cantidadCitas = pub->sublistaCitaciones.getTamano();
        } else {
            pub->cantidadCitas++;
        }
    }
    return insertado;
}

void ListaPublicaciones::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "  (Lista de publicaciones vacia)\n";
        return;
    }

    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(10) << "ID Pub"
              << std::setw(32) << "Titulo"
              << std::setw(6) << "Ano"
              << std::setw(14) << "Tipo"
              << std::setw(7) << "Citas"
              << std::setw(22) << "Investigador"
              << std::setw(20) << "Revista/Medio"
              << "DOI" << "\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";

    NodoPublicacion* actual = cabeza;
    do {
        std::string invNom = (actual->investigadorPrincipal != nullptr)
                             ? actual->investigadorPrincipal->nombreCompleto : "N/A";
        std::string revNom = (actual->revista != nullptr)
                             ? actual->revista->nombre : "(Sin revista)";

        // Truncar título visualmente si es demasiado largo para que la tabla quede prolija
        std::string titCorto = actual->titulo;
        if (titCorto.length() > 30) titCorto = titCorto.substr(0, 27) + "...";

        std::cout << std::left << std::setw(10) << actual->idPublicacion
                  << std::setw(32) << titCorto
                  << std::setw(6) << actual->anio
                  << std::setw(14) << actual->tipo
                  << std::setw(7) << actual->cantidadCitas
                  << std::setw(22) << invNom
                  << std::setw(20) << revNom
                  << actual->doi << "\n";

        actual = actual->siguiente;
    } while (actual != cabeza);

    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << "Total de publicaciones (Lista Circular): " << tamano << "\n";
}

void ListaPublicaciones::mostrarConDetalles() const {
    if (cabeza == nullptr) {
        std::cout << "  (Lista de publicaciones vacia)\n";
        return;
    }

    NodoPublicacion* actual = cabeza;
    do {
        std::cout << "========================================================================================\n";
        std::cout << "ID: " << actual->idPublicacion << " | Titulo: " << actual->titulo << "\n";
        std::cout << "Ano: " << actual->anio << " | Tipo: " << actual->tipo
                  << " | Citas registradas: " << actual->cantidadCitas << "\n";
        std::cout << "DOI: " << actual->doi << "\n";
        std::cout << "Investigador Principal: "
                  << (actual->investigadorPrincipal ? actual->investigadorPrincipal->nombreCompleto : "N/A") << "\n";
        std::cout << "Revista: "
                  << (actual->revista ? (actual->revista->nombre + " (" + actual->revista->cuartil + ")") : "N/A") << "\n";
        std::cout << "Proyecto Asociado: "
                  << (actual->proyecto ? actual->proyecto->nombre : "Ninguno") << "\n";
        std::cout << "Sublista de Citaciones Detalladas (" << actual->sublistaCitaciones.getTamano() << "):\n";
        actual->sublistaCitaciones.mostrar();

        actual = actual->siguiente;
    } while (actual != cabeza);
    std::cout << "========================================================================================\n";
}
