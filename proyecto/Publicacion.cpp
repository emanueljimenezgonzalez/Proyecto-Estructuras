#include "Publicacion.h"
#include <iostream>
#include <iomanip>

// ----- Publicaciones (Lista Circular) -----

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

// Devuelve el tipo con el formato oficial, o "" si no es valido
static std::string normalizarTipo(const std::string& t) {
    if (t == "Articulo" || t == "Artículo" || t == "articulo" || t == "artículo") return "Articulo";
    if (t == "Libro" || t == "libro") return "Libro";
    if (t == "Conferencia" || t == "conferencia") return "Conferencia";
    return "";
}

bool ListaPublicaciones::insertarOrdenadoPorAnio(const std::string& id, const std::string& tit, int anio,
                                                 const std::string& tipo, int citas, const std::string& doi,
                                                 NodoInvestigador* inv, NodoRevista* rev, NodoProyecto* proy) {
    if (id.empty() || tit.empty()) {
        std::cout << "[ERROR] ID y titulo de la publicacion son obligatorios.\n";
        return false;
    }
    if (anio < 1900 || anio > 2100) {
        std::cout << "[ERROR] El ano de la publicacion debe estar entre 1900 y 2100.\n";
        return false;
    }
    if (citas < 0) citas = 0;
    if (existeId(id)) {
        std::cout << "[ERROR] Ya existe una publicacion con el ID: " << id << "\n";
        return false;
    }

    std::string tipoNormalizado = normalizarTipo(tipo);
    if (tipoNormalizado.empty()) {
        std::cout << "[ERROR] Tipo invalido. Debe ser Articulo, Libro o Conferencia.\n";
        return false;
    }

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

    // Validar y normalizar el tipo si se provee
    std::string tipoNorm = "";
    if (!nuevoTipo.empty()) {
        tipoNorm = normalizarTipo(nuevoTipo);
        if (tipoNorm.empty()) {
            std::cout << "[ERROR] Tipo invalido. Debe ser Articulo, Libro o Conferencia.\n";
            return false;
        }
    }

    if (nuevoAnio > 0 && (nuevoAnio < 1900 || nuevoAnio > 2100)) {
        std::cout << "[ERROR] El ano de la publicacion debe estar entre 1900 y 2100.\n";
        return false;
    }

    if (nuevoAnio > 0 && nuevoAnio != pub->anio) {
        // Se mueve el mismo nodo (sin borrarlo) para que sigan validos los
        // punteros de las citaciones y se conserven coautores y citaciones.
        desenlazar(pub);
        pub->anio = nuevoAnio;
        enlazarOrdenado(pub);
    }

    // Se modifican los demas campos en su lugar
    if (!nuevoTit.empty()) pub->titulo = nuevoTit;
    if (!tipoNorm.empty()) pub->tipo = tipoNorm;
    if (nuevasCitas >= 0) pub->cantidadCitas = nuevasCitas;
    if (!nuevoDoi.empty()) pub->doi = nuevoDoi;
    if (nuevoInv != nullptr) pub->investigadorPrincipal = nuevoInv;
    if (nuevaRev != nullptr) pub->revista = nuevaRev;
    if (nuevoProy != nullptr) pub->proyecto = nuevoProy;
    return true;
}

void ListaPublicaciones::desenlazar(NodoPublicacion* nodo) {
    if (cabeza == nullptr || nodo == nullptr) return;
    if (tamano == 1) {
        cabeza = nullptr;
        nodo->siguiente = nullptr;
        tamano = 0;
        return;
    }
    NodoPublicacion* previo = cabeza;
    while (previo->siguiente != nodo) {
        previo = previo->siguiente;
    }
    previo->siguiente = nodo->siguiente;
    if (nodo == cabeza) cabeza = nodo->siguiente;
    nodo->siguiente = nullptr;
    tamano--;
}

void ListaPublicaciones::enlazarOrdenado(NodoPublicacion* nuevo) {
    if (cabeza == nullptr) {
        nuevo->siguiente = nuevo;
        cabeza = nuevo;
    } else if (nuevo->anio < cabeza->anio) {
        NodoPublicacion* ultimo = cabeza;
        while (ultimo->siguiente != cabeza) {
            ultimo = ultimo->siguiente;
        }
        nuevo->siguiente = cabeza;
        ultimo->siguiente = nuevo;
        cabeza = nuevo;
    } else {
        NodoPublicacion* actual = cabeza;
        while (actual->siguiente != cabeza && actual->siguiente->anio <= nuevo->anio) {
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
    tamano++;
}

// Evita punteros colgantes: las citaciones que apuntan a la publicacion borrada quedan en nullptr
void ListaPublicaciones::anularCitasHacia(NodoPublicacion* objetivo) {
    if (cabeza == nullptr) return;
    NodoPublicacion* p = cabeza;
    do {
        NodoCitacion* c = p->sublistaCitaciones.getCabeza();
        while (c != nullptr) {
            if (c->publicacionCitante == objetivo) c->publicacionCitante = nullptr;
            c = c->siguiente;
        }
        p = p->siguiente;
    } while (p != cabeza);
}

bool ListaPublicaciones::eliminar(const std::string& id) {
    if (cabeza == nullptr) return false;

    NodoPublicacion* objetivo = buscarPorId(id);
    if (objetivo == nullptr) return false;
    anularCitasHacia(objetivo);

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

bool ListaPublicaciones::agregarCoautorAPublicacion(const std::string& idPub,
                                                    NodoInvestigador* investigadorPropietario,
                                                    const std::string& idCoautor) {
    NodoPublicacion* pub = buscarPorId(idPub);
    if (pub == nullptr) {
        std::cout << "[ERROR] Publicacion no encontrada: " << idPub << "\n";
        return false;
    }
    if (investigadorPropietario == nullptr) {
        std::cout << "[ERROR] Investigador propietario no encontrado.\n";
        return false;
    }

    NodoCoautor* coautor = investigadorPropietario->sublistaCoautores.buscarPorId(idCoautor);
    if (coautor == nullptr) {
        std::cout << "[ERROR] El coautor " << idCoautor
                  << " no pertenece a la sublista del investigador indicado.\n";
        return false;
    }

    if (!pub->sublistaCoautores.agregarCoautorExistente(coautor)) {
        std::cout << "[ERROR] El coautor ya esta asociado a esta publicacion.\n";
        return false;
    }
    return true;
}

bool ListaPublicaciones::agregarCitaAPublicacion(const std::string& idPub, const std::string& idCita,
                                                int anioCita, NodoPublicacion* pubCitante, NodoInvestigador* autCitante) {
    NodoPublicacion* pub = buscarPorId(idPub);
    if (pub == nullptr) {
        std::cout << "[ERROR] Publicacion " << idPub << " no existe.\n";
        return false;
    }

    if (pubCitante == pub) {
        std::cout << "[ERROR] Una publicacion no puede citarse a si misma.\n";
        return false;
    }
    if (anioCita < pub->anio) {
        std::cout << "[ERROR] El ano de la cita no puede ser menor al ano de la publicacion citada ("
                  << pub->anio << ").\n";
        return false;
    }

    bool insertado = pub->sublistaCitaciones.insertar(idCita, anioCita, pubCitante, autCitante);
    if (insertado) {
        // Cada cita agregada incrementa en 1 el contador total de citas.
        // La sublista de citaciones es un registro detallado, 'cantidadCitas' es el
        // total acumulado (que puede incluir citas historicas no registradas una a una).
        pub->cantidadCitas++;
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
        std::cout << "Coautores de esta publicacion (" << actual->sublistaCoautores.getTamano() << "):\n";
        actual->sublistaCoautores.mostrar();
        std::cout << "Sublista de Citaciones Detalladas (" << actual->sublistaCitaciones.getTamano() << "):\n";
        actual->sublistaCitaciones.mostrar();

        actual = actual->siguiente;
    } while (actual != cabeza);
    std::cout << "========================================================================================\n";
}

void ListaPublicaciones::actualizarEnlaces(ListaInvestigadores& invs, ListaRevistas& revs) const {
    NodoInvestigador* inv = invs.getCabeza();
    while (inv != nullptr) {
        inv->publicacion = nullptr;
        inv = inv->siguiente;
    }
    NodoRevista* rev = revs.getCabeza();
    while (rev != nullptr) {
        rev->publicacion = nullptr;
        rev = rev->siguiente;
    }
    if (cabeza == nullptr) return;

    NodoPublicacion* p = cabeza;
    do {
        if (p->investigadorPrincipal != nullptr && p->investigadorPrincipal->publicacion == nullptr) {
            p->investigadorPrincipal->publicacion = p;
        }
        if (p->revista != nullptr && p->revista->publicacion == nullptr) {
            p->revista->publicacion = p;
        }
        p = p->siguiente;
    } while (p != cabeza);
}
