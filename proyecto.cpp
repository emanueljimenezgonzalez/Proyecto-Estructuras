// ================================================================
// Sistema de Gestion de Produccion Cientifica y Metricas Academicas
// ================================================================

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// ==================== DECLARACIONES ====================

// ----- Area.h -----


// Nodo de la Lista Simple de Áreas de Investigación
struct NodoArea {
    std::string idArea;
    std::string nombre;
    std::string descripcion;
    NodoArea* siguiente;

    NodoArea(const std::string& id, const std::string& nom, const std::string& desc)
        : idArea(id), nombre(nom), descripcion(desc), siguiente(nullptr) {}
};

// Lista Simple de Áreas de Investigación
// Requisito: Inserción al final
class ListaAreas {
private:
    NodoArea* cabeza;
    int tamano;

public:
    ListaAreas();
    ~ListaAreas();

    // Operaciones requeridas
    bool insertarAlFinal(const std::string& id, const std::string& nom, const std::string& desc);
    NodoArea* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNombre, const std::string& nuevaDesc);
    bool eliminar(const std::string& id);
    void mostrar() const;
    
    // Validaciones y utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoArea* getCabeza() const { return cabeza; }
    void liberar();
};


// ----- Universidad.h -----


// Nodo de la Lista Doble de Universidades
struct NodoUniversidad {
    std::string idUniversidad;
    std::string nombre;
    std::string pais;
    int ranking;
    NodoUniversidad* siguiente;
    NodoUniversidad* anterior;

    NodoUniversidad(const std::string& id, const std::string& nom, const std::string& p, int rank)
        : idUniversidad(id), nombre(nom), pais(p), ranking(rank), siguiente(nullptr), anterior(nullptr) {}
};

// Lista Doble de Universidades
// Requisito: Inserción como guste (implementada al final manteniendo enlaces dobles)
class ListaUniversidades {
private:
    NodoUniversidad* cabeza;
    NodoUniversidad* cola;
    int tamano;

public:
    ListaUniversidades();
    ~ListaUniversidades();

    // Operaciones requeridas
    bool insertar(const std::string& id, const std::string& nom, const std::string& pais, int ranking);
    NodoUniversidad* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNombre, const std::string& nuevoPais, int nuevoRanking);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Utilidades y validaciones
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoUniversidad* getCabeza() const { return cabeza; }
    void liberar();
};


// ----- Coautor.h -----


// Nodo de la Lista Doble de Coautores (sublista dentro de Investigador)
struct NodoCoautor {
    std::string idCoautor;
    std::string nombre;
    std::string universidad;
    int publicacionesConjuntas;
    NodoCoautor* siguiente;
    NodoCoautor* anterior;

    NodoCoautor(const std::string& id, const std::string& nom, const std::string& uni, int pubConj)
        : idCoautor(id), nombre(nom), universidad(uni), publicacionesConjuntas(pubConj),
          siguiente(nullptr), anterior(nullptr) {}
};

// Lista Doble de Coautores
// Requisito: Inserción como guste
class ListaCoautores {
private:
    NodoCoautor* cabeza;
    NodoCoautor* cola;
    int tamano;

public:
    ListaCoautores();
    ~ListaCoautores();

    // Operaciones
    bool insertar(const std::string& id, const std::string& nom, const std::string& uni, int pubConj);
    NodoCoautor* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNom, const std::string& nuevaUni, int nuevasPubConj);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoCoautor* getCabeza() const { return cabeza; }
    void liberar();
};


// ----- Investigador.h -----


// Nodo de la Lista Simple de Investigadores
struct NodoInvestigador {
    std::string idInvestigador;
    std::string nombreCompleto;
    NodoUniversidad* universidad;  // Enlace a la universidad
    std::string pais;
    NodoArea* area;                // Enlace al area de investigacion
    std::string correo;
    int indiceH;
    ListaCoautores sublistaCoautores; // Sublista doble de coautores
    NodoInvestigador* siguiente;

    NodoInvestigador(const std::string& id, const std::string& nom,
                     NodoUniversidad* uni, const std::string& p,
                     NodoArea* ar, const std::string& email)
        : idInvestigador(id), nombreCompleto(nom), universidad(uni),
          pais(p), area(ar), correo(email), indiceH(0), siguiente(nullptr) {}
};

// Lista Simple de Investigadores
// Requisito: Inserción al final
class ListaInvestigadores {
private:
    NodoInvestigador* cabeza;
    int tamano;

public:
    ListaInvestigadores();
    ~ListaInvestigadores();

    // Operaciones principales
    bool insertarAlFinal(const std::string& id, const std::string& nom,
                         NodoUniversidad* uni, const std::string& pais,
                         NodoArea* ar, const std::string& email);
    NodoInvestigador* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNombre,
                   NodoUniversidad* nuevaUni, const std::string& nuevoPais,
                   NodoArea* nuevaArea, const std::string& nuevoCorreo);
    bool eliminar(const std::string& id);
    void mostrar() const;
    void mostrarConDetalles() const;

    // Métricas y utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoInvestigador* getCabeza() const { return cabeza; }
    void liberar();
};


// ----- Revista.h -----


// Nodo de la Lista Simple de Revistas Científicas
struct NodoRevista {
    std::string idRevista;
    std::string nombre;
    std::string editorial;
    std::string pais;
    double factorImpacto;
    std::string cuartil; // Q1, Q2, Q3, Q4
    NodoRevista* siguiente;

    NodoRevista(const std::string& id, const std::string& nom, const std::string& ed,
                const std::string& p, double fi, const std::string& q)
        : idRevista(id), nombre(nom), editorial(ed), pais(p),
          factorImpacto(fi), cuartil(q), siguiente(nullptr) {}
};

// Lista Simple de Revistas Científicas
// Requisito: Inserción ordenada por nombre
class ListaRevistas {
private:
    NodoRevista* cabeza;
    int tamano;

public:
    ListaRevistas();
    ~ListaRevistas();

    // Operaciones principales
    bool insertarOrdenado(const std::string& id, const std::string& nom, const std::string& ed,
                          const std::string& p, double fi, const std::string& q);
    NodoRevista* buscarPorId(const std::string& id) const;
    NodoRevista* buscarPorNombre(const std::string& nom) const;
    bool modificar(const std::string& id, const std::string& nuevoNom, const std::string& nuevaEd,
                   const std::string& nuevoPais, double nuevoFI, const std::string& nuevoCuartil);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Validaciones y utilidades
    static bool esCuartilValido(const std::string& q);
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoRevista* getCabeza() const { return cabeza; }
    void liberar();
};


// ----- Proyecto.h -----


// Nodo de la Lista Doble de Proyectos de Investigación
struct NodoProyecto {
    std::string idProyecto;
    std::string nombre;
    double financiamiento;
    int anioInicio;
    int anioFin;
    NodoInvestigador* investigadorResponsable; // Enlace al investigador responsable
    NodoProyecto* siguiente;
    NodoProyecto* anterior;

    NodoProyecto(const std::string& id, const std::string& nom, double fin,
                 int aIni, int aFin, NodoInvestigador* resp)
        : idProyecto(id), nombre(nom), financiamiento(fin),
          anioInicio(aIni), anioFin(aFin), investigadorResponsable(resp),
          siguiente(nullptr), anterior(nullptr) {}
};

// Lista Doble de Proyectos de Investigación
// Requisito: Inserción ordenada por fecha/año de inicio
class ListaProyectos {
private:
    NodoProyecto* cabeza;
    NodoProyecto* cola;
    int tamano;

public:
    ListaProyectos();
    ~ListaProyectos();

    // Operaciones principales
    bool insertarOrdenadoPorAnio(const std::string& id, const std::string& nom, double fin,
                                 int aIni, int aFin, NodoInvestigador* resp);
    NodoProyecto* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoNom, double nuevoFin,
                   int nuevoAIni, int nuevoAFin, NodoInvestigador* nuevoResp);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Validaciones y utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoProyecto* getCabeza() const { return cabeza; }
    void liberar();
};


// ----- Citacion.h -----


// Nodo de la Lista Doble de Citaciones (sublista dentro de Publicación)
struct NodoCitacion {
    std::string idCita;
    int anio;
    std::string publicacionCitante; // Nombre o título de la publicación que cita
    std::string autorCitante;       // Autor que realizó la cita
    NodoCitacion* siguiente;
    NodoCitacion* anterior;

    NodoCitacion(const std::string& id, int a, const std::string& pubCit, const std::string& autCit)
        : idCita(id), anio(a), publicacionCitante(pubCit), autorCitante(autCit),
          siguiente(nullptr), anterior(nullptr) {}
};

// Lista Doble de Citaciones
// Requisito: Inserción como guste
class ListaCitaciones {
private:
    NodoCitacion* cabeza;
    NodoCitacion* cola;
    int tamano;

public:
    ListaCitaciones();
    ~ListaCitaciones();

    // Operaciones principales
    bool insertar(const std::string& id, int a, const std::string& pubCit, const std::string& autCit);
    NodoCitacion* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, int nuevoAnio, const std::string& nuevaPubCit, const std::string& nuevoAutCit);
    bool eliminar(const std::string& id);
    void mostrar() const;

    // Utilidades
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoCitacion* getCabeza() const { return cabeza; }
    void liberar();
};


// ----- Publicacion.h -----


// Relacion de autores de una publicacion.
// Es una estructura auxiliar para representar que una publicacion
// puede tener varios autores sin utilizar STL.
struct NodoAutorPublicacion {
    std::string idAutor;
    std::string nombreAutor;
    bool esPrincipal;
    NodoInvestigador* investigador;
    NodoCoautor* coautor;
    NodoAutorPublicacion* siguiente;

    NodoAutorPublicacion(const std::string& id, const std::string& nom, bool principal,
                         NodoInvestigador* inv, NodoCoautor* coaut)
        : idAutor(id), nombreAutor(nom), esPrincipal(principal),
          investigador(inv), coautor(coaut), siguiente(nullptr) {}
};

class ListaAutoresPublicacion {
private:
    NodoAutorPublicacion* cabeza;
    NodoAutorPublicacion* cola;
    int tamano;

public:
    ListaAutoresPublicacion();
    ~ListaAutoresPublicacion();

    bool agregarInvestigador(NodoInvestigador* investigador);
    bool agregarCoautor(NodoCoautor* coautor);
    bool existeAutor(const std::string& idAutor) const;
    int getTamano() const { return tamano; }
    NodoAutorPublicacion* getCabeza() const { return cabeza; }
    void mostrar() const;
    void liberar();
};

// Nodo de la Lista Circular de Publicaciones
struct NodoPublicacion {
    std::string idPublicacion;
    std::string titulo;
    int anio;
    std::string tipo; // "Articulo", "Libro", "Conferencia"
    int cantidadCitas;
    std::string doi;
    NodoInvestigador* investigadorPrincipal; // Enlace al investigador principal
    NodoRevista* revista;                   // Enlace a revista (puede ser nullptr)
    NodoProyecto* proyecto;                 // Enlace a proyecto (puede ser nullptr)
    ListaAutoresPublicacion autores;        // Autores de esta publicacion
    ListaCitaciones sublistaCitaciones;     // Sublista doble de citaciones
    NodoPublicacion* siguiente;             // Puntero circular al siguiente

    NodoPublicacion(const std::string& id, const std::string& tit, int a,
                    const std::string& tip, int citas, const std::string& d,
                    NodoInvestigador* inv, NodoRevista* rev, NodoProyecto* proy)
        : idPublicacion(id), titulo(tit), anio(a), tipo(tip), cantidadCitas(citas),
          doi(d), investigadorPrincipal(inv), revista(rev), proyecto(proy),
          siguiente(nullptr) {}
};

// Lista Circular de Publicaciones
// Requisito: Inserción ordenada por año ascendente
class ListaPublicaciones {
private:
    NodoPublicacion* cabeza;
    int tamano;

public:
    ListaPublicaciones();
    ~ListaPublicaciones();

    // Operaciones principales
    bool insertarOrdenadoPorAnio(const std::string& id, const std::string& tit, int anio,
                                 const std::string& tipo, int citas, const std::string& doi,
                                 NodoInvestigador* inv, NodoRevista* rev, NodoProyecto* proy);
    NodoPublicacion* buscarPorId(const std::string& id) const;
    bool modificar(const std::string& id, const std::string& nuevoTit, int nuevoAnio,
                   const std::string& nuevoTipo, int nuevasCitas, const std::string& nuevoDoi,
                   NodoInvestigador* nuevoInv, NodoRevista* nuevaRev, NodoProyecto* nuevoProy);
    bool eliminar(const std::string& id);
    void mostrar() const;
    void mostrarConDetalles() const;

    // Métodos para relaciones de 
    void mostrarPublicacionesDeProyecto(const std::string& idProy) const;

    // Metodos para agregar autores a una publicacion
    bool agregarCoautorAPublicacion(const std::string& idPub, NodoInvestigador* investigadorPropietario,
                                    const std::string& idCoautor);

    // Metodos para agregar citas a una publicacion
    bool agregarCitaAPublicacion(const std::string& idPub, const std::string& idCita,
                                 int anioCita, const std::string& pubCit, const std::string& autCit);

    // Validaciones y utilidades
    static bool esTipoValido(const std::string& t);
    bool existeId(const std::string& id) const;
    int getTamano() const { return tamano; }
    NodoPublicacion* getCabeza() const { return cabeza; }
    void liberar();
};


// ----- Metricas.h -----


// Estructura de Métricas Académicas calculadas para un investigador
struct ResumenMetricas {
    int indiceH;
    int totalCitas;
    int produccionCientifica;        // Total de publicaciones
    double promedioCitasPorPub;
    int colaboracionCientifica;      // Cantidad de coautores
};

class MetricasAcademicas {
public:
    // Cálculos individuales para un investigador
    static int calcularIndiceH(NodoInvestigador* inv, const ListaPublicaciones& publicaciones);
    static int calcularTotalCitas(NodoInvestigador* inv, const ListaPublicaciones& publicaciones);
    static int calcularProduccionCientifica(NodoInvestigador* inv, const ListaPublicaciones& publicaciones);
    static double calcularPromedioCitas(NodoInvestigador* inv, const ListaPublicaciones& publicaciones);
    static int calcularColaboracionCientifica(NodoInvestigador* inv);

    // Resumen integral de métricas
    static ResumenMetricas obtenerMetricas(NodoInvestigador* inv, const ListaPublicaciones& publicaciones);

    // Actualizar los índices H de todos los investigadores en la lista
    static void actualizarIndicesHTodos(ListaInvestigadores& investigadores, const ListaPublicaciones& publicaciones);

    // Mostrar reporte detallado de métricas de un investigador
    static void mostrarMetricasInvestigador(NodoInvestigador* inv, const ListaPublicaciones& publicaciones);

    // Mostrar tabla comparativa de métricas de todos los investigadores
    static void mostrarTodasLasMetricas(const ListaInvestigadores& investigadores, const ListaPublicaciones& publicaciones);
};


// ----- Consultas.h -----


class GestorConsultas {
public:
    // Consulta 1: Investigador con mayor índice H
    static void consulta1_MayorIndiceH(const ListaInvestigadores& invs, const ListaPublicaciones& pubs);

    // Consulta 2: Investigador con más citas acumuladas
    static void consulta2_MasCitasAcumuladas(const ListaInvestigadores& invs, const ListaPublicaciones& pubs);

    // Consulta 3: Publicación con mayor cantidad de citas
    static void consulta3_PublicacionMasCitada(const ListaPublicaciones& pubs);

    // Consulta 4: Revista con mayor factor de impacto
    static void consulta4_RevistaMayorImpacto(const ListaRevistas& revs);

    // Consulta 5: Investigador con más coautores
    static void consulta5_InvestigadorMasCoautores(const ListaInvestigadores& invs);

    // Consulta 6: Universidad con más investigadores registrados
    static void consulta6_UniversidadMasInvestigadores(const ListaUniversidades& unis, const ListaInvestigadores& invs);

    // Consulta 7: Área de investigación que genera más publicaciones
    static void consulta7_AreaMasPublicaciones(const ListaAreas& areas, const ListaPublicaciones& pubs);

    // Consulta 8: Año con mayor producción científica
    static void consulta8_AnioMayorProduccion(const ListaPublicaciones& pubs);

    // Consulta 9: Publicación con mayor cantidad de autores
    static void consulta9_PublicacionMasAutores(const ListaPublicaciones& pubs);

    // Consulta 10: Investigador con más artículos en revistas Q1
    static void consulta10_InvestigadorMasArticulosQ1(const ListaInvestigadores& invs, const ListaPublicaciones& pubs);
};


// ----- Reportes.h -----


class GestorReportes {
public:
    // Reporte 1: Mostrar todos los investigadores con sus publicaciones
    static void reporte1_InvestigadoresConPublicaciones(const ListaInvestigadores& invs, const ListaPublicaciones& pubs);

    // Reporte 2: Mostrar publicaciones ordenadas por año ascendente
    static void reporte2_PublicacionesPorAnioAscendente(const ListaPublicaciones& pubs);

    // Reporte 3: Mostrar publicaciones ordenadas por cantidad de citas descendente
    static void reporte3_PublicacionesPorCitasDescendente(const ListaPublicaciones& pubs);

    // Reporte 4: Mostrar todas las revistas y sus factores de impacto
    static void reporte4_RevistasYFactoresImpacto(const ListaRevistas& revs);

    // Reporte 5: Imprimir la red de coautoría de un investigador específico
    static void reporte5_RedCoautoriaInvestigador(const ListaInvestigadores& invs, const std::string& idInv);

    // Reporte 6: Mostrar todas las publicaciones de una revista indicada por el usuario
    static void reporte6_PublicacionesDeRevista(const ListaRevistas& revs, const ListaPublicaciones& pubs, const std::string& idRevista);

    // Reporte 7: Mostrar todas las publicaciones de un área determinada
    static void reporte7_PublicacionesDeArea(const ListaAreas& areas, const ListaPublicaciones& pubs, const std::string& idArea);

    // Reporte 8: Mostrar los investigadores agrupados por universidad
    static void reporte8_InvestigadoresAgrupadosPorUniversidad(const ListaUniversidades& unis, const ListaInvestigadores& invs);

    // Reporte 9: Mostrar los investigadores ordenados por índice H
    static void reporte9_InvestigadoresOrdenadosPorIndiceH(ListaInvestigadores& invs, const ListaPublicaciones& pubs);
};


// ----- Sistema.h -----


class SistemaAcademico {
private:
    ListaAreas listaAreas;
    ListaUniversidades listaUniversidades;
    ListaRevistas listaRevistas;
    ListaInvestigadores listaInvestigadores;
    ListaProyectos listaProyectos;
    ListaPublicaciones listaPublicaciones;

public:
    SistemaAcademico();
    ~SistemaAcademico();

    // Carga de datos iniciales (>5 registros por cada una de las 8 listas)
    void precargarDatos();

    // Getters de las listas
    ListaAreas& getAreas() { return listaAreas; }
    ListaUniversidades& getUniversidades() { return listaUniversidades; }
    ListaRevistas& getRevistas() { return listaRevistas; }
    ListaInvestigadores& getInvestigadores() { return listaInvestigadores; }
    ListaProyectos& getProyectos() { return listaProyectos; }
    ListaPublicaciones& getPublicaciones() { return listaPublicaciones; }

    // Módulos interactivos de menús
    void menuPrincipal();
    void menuInvestigadores();
    void menuUniversidades();
    void menuAreas();
    void menuRevistas();
    void menuProyectos();
    void menuPublicaciones();
    void menuCitaciones();
    void menuMetricas();
    void menuConsultas();
    void menuReportes();
    void menu();

    // Prueba demostrativa del ejemplo de Índice H = 5 del enunciado oficial
    void ejecutarPruebaEjemploIndiceH();
};


// ==================== IMPLEMENTACIONES ====================

// ----- Area.cpp -----

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

// ----- Universidad.cpp -----

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

// ----- Coautor.cpp -----

ListaCoautores::ListaCoautores() : cabeza(nullptr), cola(nullptr), tamano(0) {}

ListaCoautores::~ListaCoautores() {
    liberar();
}

void ListaCoautores::liberar() {
    NodoCoautor* actual = cabeza;
    while (actual != nullptr) {
        NodoCoautor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}

bool ListaCoautores::existeId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

bool ListaCoautores::insertar(const std::string& id, const std::string& nom, const std::string& uni, int pubConj) {
    if (id.empty() || nom.empty()) {
        std::cout << "    [ERROR] ID y nombre de coautor son requeridos.\n";
        return false;
    }
    if (existeId(id)) {
        std::cout << "    [ERROR] Ya existe un coautor con ID: " << id << "\n";
        return false;
    }
    if (pubConj < 0) {
        pubConj = 0;
    }

    NodoCoautor* nuevo = new NodoCoautor(id, nom, uni, pubConj);
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

NodoCoautor* ListaCoautores::buscarPorId(const std::string& id) const {
    NodoCoautor* actual = cabeza;
    while (actual != nullptr) {
        if (actual->idCoautor == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

bool ListaCoautores::modificar(const std::string& id, const std::string& nuevoNom, const std::string& nuevaUni, int nuevasPubConj) {
    NodoCoautor* nodo = buscarPorId(id);
    if (nodo == nullptr) return false;
    if (!nuevoNom.empty()) nodo->nombre = nuevoNom;
    if (!nuevaUni.empty()) nodo->universidad = nuevaUni;
    if (nuevasPubConj >= 0) nodo->publicacionesConjuntas = nuevasPubConj;
    return true;
}

bool ListaCoautores::eliminar(const std::string& id) {
    NodoCoautor* nodo = buscarPorId(id);
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

void ListaCoautores::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "    (Sin coautores registrados)\n";
        return;
    }

    NodoCoautor* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "    * [" << actual->idCoautor << "] " << actual->nombre
                  << " (" << actual->universidad << ") - Pub. conjuntas: "
                  << actual->publicacionesConjuntas << "\n";
        actual = actual->siguiente;
    }
}

// ----- Investigador.cpp -----

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

// ----- Revista.cpp -----

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

// ----- Proyectok.cpp -----

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

// ----- Citacion.cpp -----

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

// ----- Autores de Publicacion -----

ListaAutoresPublicacion::ListaAutoresPublicacion()
    : cabeza(nullptr), cola(nullptr), tamano(0) {}

ListaAutoresPublicacion::~ListaAutoresPublicacion() {
    liberar();
}

void ListaAutoresPublicacion::liberar() {
    NodoAutorPublicacion* actual = cabeza;
    while (actual != nullptr) {
        NodoAutorPublicacion* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamano = 0;
}

bool ListaAutoresPublicacion::existeAutor(const std::string& idAutor) const {
    NodoAutorPublicacion* actual = cabeza;
    while (actual != nullptr) {
        if (actual->idAutor == idAutor) return true;
        actual = actual->siguiente;
    }
    return false;
}

bool ListaAutoresPublicacion::agregarInvestigador(NodoInvestigador* investigador) {
    if (investigador == nullptr || existeAutor(investigador->idInvestigador)) return false;

    NodoAutorPublicacion* nuevo = new NodoAutorPublicacion(
        investigador->idInvestigador, investigador->nombreCompleto, true, investigador, nullptr);

    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        cola = nuevo;
    }
    tamano++;
    return true;
}

bool ListaAutoresPublicacion::agregarCoautor(NodoCoautor* coautor) {
    if (coautor == nullptr || existeAutor(coautor->idCoautor)) return false;

    NodoAutorPublicacion* nuevo = new NodoAutorPublicacion(
        coautor->idCoautor, coautor->nombre, false, nullptr, coautor);

    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->siguiente = nuevo;
        cola = nuevo;
    }
    tamano++;
    return true;
}

void ListaAutoresPublicacion::mostrar() const {
    if (cabeza == nullptr) {
        std::cout << "  (Sin autores registrados)\n";
        return;
    }

    NodoAutorPublicacion* actual = cabeza;
    int posicion = 1;
    while (actual != nullptr) {
        std::cout << "  " << posicion << ". " << actual->nombreAutor
                  << " [ID: " << actual->idAutor << "]"
                  << (actual->esPrincipal ? " (Investigador principal)" : " (Coautor)") << "\n";
        actual = actual->siguiente;
        posicion++;
    }
}

// ----- Publicacion.cpp -----

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
    if (inv != nullptr) {
        nuevo->autores.agregarInvestigador(inv);
    }

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
        // Para conservar el orden por año se guarda temporalmente la relacion de autores.
        std::string titFinal = nuevoTit.empty() ? pub->titulo : nuevoTit;
        std::string tipFinal = nuevoTipo.empty() ? pub->tipo : nuevoTipo;
        int citFinal = (nuevasCitas >= 0) ? nuevasCitas : pub->cantidadCitas;
        std::string doiFinal = nuevoDoi.empty() ? pub->doi : nuevoDoi;
        NodoInvestigador* invFinal = (nuevoInv != nullptr) ? nuevoInv : pub->investigadorPrincipal;
        NodoRevista* revFinal = (nuevaRev != nullptr) ? nuevaRev : pub->revista;
        NodoProyecto* proyFinal = (nuevoProy != nullptr) ? nuevoProy : pub->proyecto;

        int cantidadAutores = pub->autores.getTamano();
        NodoAutorPublicacion** autores = nullptr;
        if (cantidadAutores > 0) {
            autores = new NodoAutorPublicacion*[cantidadAutores];
            NodoAutorPublicacion* autorActual = pub->autores.getCabeza();
            int i = 0;
            while (autorActual != nullptr && i < cantidadAutores) {
                autores[i++] = autorActual;
                autorActual = autorActual->siguiente;
            }
        }

        eliminar(id);
        bool resultado = insertarOrdenadoPorAnio(id, titFinal, nuevoAnio, tipFinal, citFinal, doiFinal, invFinal, revFinal, proyFinal);
        if (resultado) {
            NodoPublicacion* nuevaPub = buscarPorId(id);
            for (int i = 0; i < cantidadAutores; ++i) {
                if (autores[i]->esPrincipal) continue;
                if (autores[i]->coautor != nullptr) {
                    nuevaPub->autores.agregarCoautor(autores[i]->coautor);
                }
            }
        }
        delete[] autores;
        return resultado;
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

    if (!pub->autores.agregarCoautor(coautor)) {
        std::cout << "[ERROR] El coautor ya esta asociado a esta publicacion.\n";
        return false;
    }
    return true;
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
        std::cout << "Autores (" << actual->autores.getTamano() << "):\n";
        actual->autores.mostrar();
        std::cout << "Sublista de Citaciones Detalladas (" << actual->sublistaCitaciones.getTamano() << "):\n";
        actual->sublistaCitaciones.mostrar();

        actual = actual->siguiente;
    } while (actual != cabeza);
    std::cout << "========================================================================================\n";
}

// ----- Metricas.cpp -----

int MetricasAcademicas::calcularProduccionCientifica(NodoInvestigador* inv, const ListaPublicaciones& publicaciones) {
    if (inv == nullptr || publicaciones.getCabeza() == nullptr) return 0;

    int total = 0;
    NodoPublicacion* actual = publicaciones.getCabeza();
    do {
        if (actual->investigadorPrincipal == inv) {
            total++;
        }
        actual = actual->siguiente;
    } while (actual != publicaciones.getCabeza());

    return total;
}

int MetricasAcademicas::calcularTotalCitas(NodoInvestigador* inv, const ListaPublicaciones& publicaciones) {
    if (inv == nullptr || publicaciones.getCabeza() == nullptr) return 0;

    int totalCitas = 0;
    NodoPublicacion* actual = publicaciones.getCabeza();
    do {
        if (actual->investigadorPrincipal == inv) {
            totalCitas += actual->cantidadCitas;
        }
        actual = actual->siguiente;
    } while (actual != publicaciones.getCabeza());

    return totalCitas;
}

int MetricasAcademicas::calcularColaboracionCientifica(NodoInvestigador* inv) {
    if (inv == nullptr) return 0;
    return inv->sublistaCoautores.getTamano();
}

double MetricasAcademicas::calcularPromedioCitas(NodoInvestigador* inv, const ListaPublicaciones& publicaciones) {
    int totalPub = calcularProduccionCientifica(inv, publicaciones);
    if (totalPub == 0) return 0.0;
    int totalCitas = calcularTotalCitas(inv, publicaciones);
    return static_cast<double>(totalCitas) / totalPub;
}

int MetricasAcademicas::calcularIndiceH(NodoInvestigador* inv, const ListaPublicaciones& publicaciones) {
    if (inv == nullptr || publicaciones.getCabeza() == nullptr) {
        if (inv != nullptr) inv->indiceH = 0;
        return 0;
    }

    int totalPub = calcularProduccionCientifica(inv, publicaciones);
    if (totalPub == 0) {
        inv->indiceH = 0;
        return 0;
    }

    // Alocar arreglo dinámico manual para almacenar las citas de sus publicaciones
    int* citas = new int[totalPub];
    int idx = 0;

    NodoPublicacion* actual = publicaciones.getCabeza();
    do {
        if (actual->investigadorPrincipal == inv) {
            citas[idx++] = actual->cantidadCitas;
        }
        actual = actual->siguiente;
    } while (actual != publicaciones.getCabeza());

    // Ordenar de mayor a menor manualmente (ordenamiento por inserción/burbuja sin STL)
    for (int i = 0; i < totalPub - 1; ++i) {
        for (int j = i + 1; j < totalPub; ++j) {
            if (citas[j] > citas[i]) {
                int temp = citas[i];
                citas[i] = citas[j];
                citas[j] = temp;
            }
        }
    }

    // Cálculo del índice H según la definición formal del enunciado:
    // "h publicaciones que tienen al menos h citas cada una"
    int h = 0;
    for (int i = 0; i < totalPub; ++i) {
        int posicion = i + 1; // Posición 1-indexed
        if (citas[i] >= posicion) {
            h = posicion;
        } else {
            break;
        }
    }

    delete[] citas;
    inv->indiceH = h;
    return h;
}

ResumenMetricas MetricasAcademicas::obtenerMetricas(NodoInvestigador* inv, const ListaPublicaciones& publicaciones) {
    ResumenMetricas res;
    res.produccionCientifica = calcularProduccionCientifica(inv, publicaciones);
    res.totalCitas = calcularTotalCitas(inv, publicaciones);
    res.promedioCitasPorPub = calcularPromedioCitas(inv, publicaciones);
    res.colaboracionCientifica = calcularColaboracionCientifica(inv);
    res.indiceH = calcularIndiceH(inv, publicaciones);
    return res;
}

void MetricasAcademicas::actualizarIndicesHTodos(ListaInvestigadores& investigadores, const ListaPublicaciones& publicaciones) {
    NodoInvestigador* actual = investigadores.getCabeza();
    while (actual != nullptr) {
        calcularIndiceH(actual, publicaciones);
        actual = actual->siguiente;
    }
}

void MetricasAcademicas::mostrarMetricasInvestigador(NodoInvestigador* inv, const ListaPublicaciones& publicaciones) {
    if (inv == nullptr) {
        std::cout << "[ERROR] Investigador invalido.\n";
        return;
    }

    ResumenMetricas m = obtenerMetricas(inv, publicaciones);

    std::cout << "================================================================================\n";
    std::cout << "                    METRICAS ACADEMICAS DEL INVESTIGADOR                        \n";
    std::cout << "================================================================================\n";
    std::cout << "Investigador:            " << inv->nombreCompleto << " (ID: " << inv->idInvestigador << ")\n";
    std::cout << "Universidad:             " << (inv->universidad ? inv->universidad->nombre : "N/A") << "\n";
    std::cout << "Area de Investigacion:   " << (inv->area ? inv->area->nombre : "N/A") << "\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "  * Indice H:                   " << m.indiceH << "\n";
    std::cout << "  * Total de Citas Recibidas:   " << m.totalCitas << "\n";
    std::cout << "  * Produccion Cientifica:      " << m.produccionCientifica << " publicaciones\n";
    std::cout << "  * Promedio de Citas por Pub.: " << std::fixed << std::setprecision(2) << m.promedioCitasPorPub << "\n";
    std::cout << "  * Colaboracion Cientifica:    " << m.colaboracionCientifica << " coautores distintos\n";
    std::cout << "================================================================================\n";
}

void MetricasAcademicas::mostrarTodasLasMetricas(const ListaInvestigadores& investigadores, const ListaPublicaciones& publicaciones) {
    if (investigadores.getCabeza() == nullptr) {
        std::cout << "  (No hay investigadores registrados)\n";
        return;
    }

    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(10) << "ID"
              << std::setw(28) << "Investigador"
              << std::setw(10) << "Indice H"
              << std::setw(14) << "Total Citas"
              << std::setw(15) << "Publicaciones"
              << std::setw(14) << "Prom. Citas"
              << "Coautores" << "\n";
    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";

    NodoInvestigador* actual = investigadores.getCabeza();
    while (actual != nullptr) {
        ResumenMetricas m = obtenerMetricas(actual, publicaciones);
        std::cout << std::left << std::setw(10) << actual->idInvestigador
                  << std::setw(28) << actual->nombreCompleto
                  << std::setw(10) << m.indiceH
                  << std::setw(14) << m.totalCitas
                  << std::setw(15) << m.produccionCientifica
                  << std::setw(14) << std::fixed << std::setprecision(2) << m.promedioCitasPorPub
                  << m.colaboracionCientifica << "\n";
        actual = actual->siguiente;
    }
    std::cout << "------------------------------------------------------------------------------------------------------------------------\n";
}

// ----- Consultas.cpp -----

// 1. ¿Cuál investigador posee el mayor índice H?
void GestorConsultas::consulta1_MayorIndiceH(const ListaInvestigadores& invs, const ListaPublicaciones& pubs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 1: INVESTIGADOR(ES) CON EL MAYOR INDICE H\n";
    std::cout << "================================================================================\n";

    if (invs.getCabeza() == nullptr) {
        std::cout << "  No hay investigadores registrados en el sistema.\n";
        return;
    }

    int maxH = -1;
    NodoInvestigador* act = invs.getCabeza();
    while (act != nullptr) {
        int h = MetricasAcademicas::calcularIndiceH(act, pubs);
        if (h > maxH) {
            maxH = h;
        }
        act = act->siguiente;
    }

    std::cout << "  Indice H maximo encontrado: " << maxH << "\n\n";
    std::cout << "  Investigadores lideres:\n";
    act = invs.getCabeza();
    int count = 0;
    while (act != nullptr) {
        if (act->indiceH == maxH) {
            count++;
            std::cout << "  [" << count << "] " << act->nombreCompleto
                      << " (ID: " << act->idInvestigador << ")\n"
                      << "      Universidad: " << (act->universidad ? act->universidad->nombre : "N/A") << "\n"
                      << "      Area: " << (act->area ? act->area->nombre : "N/A") << "\n"
                      << "      Indice H: " << act->indiceH << "\n";
        }
        act = act->siguiente;
    }
}

// 2. ¿Cuál investigador tiene más citas acumuladas?
void GestorConsultas::consulta2_MasCitasAcumuladas(const ListaInvestigadores& invs, const ListaPublicaciones& pubs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 2: INVESTIGADOR(ES) CON MAS CITAS ACUMULADAS \n";
    std::cout << "================================================================================\n";

    if (invs.getCabeza() == nullptr) {
        std::cout << "  No hay investigadores registrados en el sistema.\n";
        return;
    }

    int maxCitas = -1;
    NodoInvestigador* act = invs.getCabeza();
    while (act != nullptr) {
        int c = MetricasAcademicas::calcularTotalCitas(act, pubs);
        if (c > maxCitas) {
            maxCitas = c;
        }
        act = act->siguiente;
    }

    std::cout << "  Maximo de citas acumuladas: " << maxCitas << "\n\n";
    std::cout << "  Investigador(es) con mayor impacto en citas:\n";
    act = invs.getCabeza();
    int count = 0;
    while (act != nullptr) {
        int c = MetricasAcademicas::calcularTotalCitas(act, pubs);
        if (c == maxCitas) {
            count++;
            std::cout << "  [" << count << "] " << act->nombreCompleto
                      << " (ID: " << act->idInvestigador << ")\n"
                      << "      Universidad: " << (act->universidad ? act->universidad->nombre : "N/A") << "\n"
                      << "      Total Citas Acumuladas: " << c << "\n"
                      << "      Produccion: " << MetricasAcademicas::calcularProduccionCientifica(act, pubs) << " publicaciones\n";
        }
        act = act->siguiente;
    }
}

// 3. ¿Cuál publicación recibió mayor cantidad de citas?
void GestorConsultas::consulta3_PublicacionMasCitada(const ListaPublicaciones& pubs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 3: PUBLICACION(ES) CON MAYOR CANTIDAD DE CITAS \n";
    std::cout << "================================================================================\n";

    if (pubs.getCabeza() == nullptr) {
        std::cout << "  No hay publicaciones registradas en la lista circular.\n";
        return;
    }

    int maxCitas = -1;
    NodoPublicacion* act = pubs.getCabeza();
    do {
        if (act->cantidadCitas > maxCitas) {
            maxCitas = act->cantidadCitas;
        }
        act = act->siguiente;
    } while (act != pubs.getCabeza());

    std::cout << "  Citas maximas registradas en una publicacion: " << maxCitas << "\n\n";
    act = pubs.getCabeza();
    int count = 0;
    do {
        if (act->cantidadCitas == maxCitas) {
            count++;
            std::cout << "  [" << count << "] \"" << act->titulo << "\" (" << act->anio << ")\n"
                      << "      ID: " << act->idPublicacion << " | Tipo: " << act->tipo << " | DOI: " << act->doi << "\n"
                      << "      Citas: " << act->cantidadCitas << "\n"
                      << "      Autor Principal: " << (act->investigadorPrincipal ? act->investigadorPrincipal->nombreCompleto : "N/A") << "\n"
                      << "      Revista: " << (act->revista ? act->revista->nombre : "(Sin revista)") << "\n";
        }
        act = act->siguiente;
    } while (act != pubs.getCabeza());
}

// 4. ¿Cuál revista posee el mayor factor de impacto?
void GestorConsultas::consulta4_RevistaMayorImpacto(const ListaRevistas& revs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 4: REVISTA(S) CON EL MAYOR FACTOR DE IMPACTO\n";
    std::cout << "================================================================================\n";

    if (revs.getCabeza() == nullptr) {
        std::cout << "  No hay revistas registradas en el sistema.\n";
        return;
    }

    double maxFI = -1.0;
    NodoRevista* act = revs.getCabeza();
    while (act != nullptr) {
        if (act->factorImpacto > maxFI) {
            maxFI = act->factorImpacto;
        }
        act = act->siguiente;
    }

    std::cout << "  Factor de impacto maximo: " << std::fixed << std::setprecision(3) << maxFI << "\n\n";
    act = revs.getCabeza();
    int count = 0;
    while (act != nullptr) {
        if (act->factorImpacto == maxFI) {
            count++;
            std::cout << "  [" << count << "] " << act->nombre << " (ID: " << act->idRevista << ")\n"
                      << "      Editorial: " << act->editorial << " | Pais: " << act->pais << "\n"
                      << "      Factor de Impacto: " << act->factorImpacto << " | Cuartil: " << act->cuartil << "\n";
        }
        act = act->siguiente;
    }
}

// 5. ¿Cuál investigador tiene más coautores?
void GestorConsultas::consulta5_InvestigadorMasCoautores(const ListaInvestigadores& invs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 5: INVESTIGADOR(ES) CON MAS COAUTORES\n";
    std::cout << "================================================================================\n";

    if (invs.getCabeza() == nullptr) {
        std::cout << "  No hay investigadores registrados.\n";
        return;
    }

    int maxCoaut = -1;
    NodoInvestigador* act = invs.getCabeza();
    while (act != nullptr) {
        int c = act->sublistaCoautores.getTamano();
        if (c > maxCoaut) {
            maxCoaut = c;
        }
        act = act->siguiente;
    }

    std::cout << "  Cantidad maxima de coautores: " << maxCoaut << "\n\n";
    act = invs.getCabeza();
    int count = 0;
    while (act != nullptr) {
        if (act->sublistaCoautores.getTamano() == maxCoaut) {
            count++;
            std::cout << "  [" << count << "] " << act->nombreCompleto << " (ID: " << act->idInvestigador << ")\n"
                      << "      Universidad: " << (act->universidad ? act->universidad->nombre : "N/A") << "\n"
                      << "      Coautores registrados: " << act->sublistaCoautores.getTamano() << "\n"
                      << "      Listado de Coautores:\n";
            act->sublistaCoautores.mostrar();
        }
        act = act->siguiente;
    }
}

// 6. ¿Cuál universidad tiene más investigadores registrados?
void GestorConsultas::consulta6_UniversidadMasInvestigadores(const ListaUniversidades& unis, const ListaInvestigadores& invs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 6: UNIVERSIDAD(ES) CON MAS INVESTIGADORES REGISTRADOS\n";
    std::cout << "================================================================================\n";

    if (unis.getCabeza() == nullptr) {
        std::cout << "  No hay universidades registradas.\n";
        return;
    }

    int maxReg = -1;
    NodoUniversidad* uni = unis.getCabeza();
    while (uni != nullptr) {
        int cuenta = 0;
        NodoInvestigador* inv = invs.getCabeza();
        while (inv != nullptr) {
            if (inv->universidad == uni) {
                cuenta++;
            }
            inv = inv->siguiente;
        }
        if (cuenta > maxReg) {
            maxReg = cuenta;
        }
        uni = uni->siguiente;
    }

    std::cout << "  Maximo de investigadores por universidad: " << maxReg << "\n\n";
    uni = unis.getCabeza();
    int count = 0;
    while (uni != nullptr) {
        int cuenta = 0;
        NodoInvestigador* inv = invs.getCabeza();
        while (inv != nullptr) {
            if (inv->universidad == uni) cuenta++;
            inv = inv->siguiente;
        }
        if (cuenta == maxReg) {
            count++;
            std::cout << "  [" << count << "] " << uni->nombre << " (ID: " << uni->idUniversidad
                      << ", Pais: " << uni->pais << ", Ranking: #" << uni->ranking << ")\n"
                      << "      Total investigadores: " << cuenta << "\n"
                      << "      Investigadores afiliados:\n";
            inv = invs.getCabeza();
            while (inv != nullptr) {
                if (inv->universidad == uni) {
                    std::cout << "        - " << inv->nombreCompleto << " (ID: " << inv->idInvestigador << ")\n";
                }
                inv = inv->siguiente;
            }
        }
        uni = uni->siguiente;
    }
}

// 7. ¿Cuál área de investigación genera más publicaciones?
void GestorConsultas::consulta7_AreaMasPublicaciones(const ListaAreas& areas, const ListaPublicaciones& pubs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 7: AREA(S) DE INVESTIGACION QUE GENERA MAS PUBLICACIONES\n";
    std::cout << "================================================================================\n";

    if (areas.getCabeza() == nullptr) {
        std::cout << "  No hay areas registradas.\n";
        return;
    }

    int maxPubs = -1;
    NodoArea* ar = areas.getCabeza();
    while (ar != nullptr) {
        int cuenta = 0;
        if (pubs.getCabeza() != nullptr) {
            NodoPublicacion* pub = pubs.getCabeza();
            do {
                if (pub->investigadorPrincipal != nullptr && pub->investigadorPrincipal->area == ar) {
                    cuenta++;
                }
                pub = pub->siguiente;
            } while (pub != pubs.getCabeza());
        }
        if (cuenta > maxPubs) {
            maxPubs = cuenta;
        }
        ar = ar->siguiente;
    }

    std::cout << "  Maximo de publicaciones por area: " << maxPubs << "\n\n";
    ar = areas.getCabeza();
    int count = 0;
    while (ar != nullptr) {
        int cuenta = 0;
        if (pubs.getCabeza() != nullptr) {
            NodoPublicacion* pub = pubs.getCabeza();
            do {
                if (pub->investigadorPrincipal != nullptr && pub->investigadorPrincipal->area == ar) {
                    cuenta++;
                }
                pub = pub->siguiente;
            } while (pub != pubs.getCabeza());
        }
        if (cuenta == maxPubs) {
            count++;
            std::cout << "  [" << count << "] " << ar->nombre << " (ID: " << ar->idArea << ")\n"
                      << "      Descripcion: " << ar->descripcion << "\n"
                      << "      Total publicaciones generadas: " << cuenta << "\n";
        }
        ar = ar->siguiente;
    }
}

// 8. ¿Qué año tuvo la mayor producción científica?
void GestorConsultas::consulta8_AnioMayorProduccion(const ListaPublicaciones& pubs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 8: ANO(S) CON LA MAYOR PRODUCCION CIENTIFICA\n";
    std::cout << "================================================================================\n";

    if (pubs.getCabeza() == nullptr) {
        std::cout << "  No hay publicaciones registradas.\n";
        return;
    }

    int n = pubs.getTamano();
    int* anios = new int[n];
    int* cuentas = new int[n];
    int numAnios = 0;

    NodoPublicacion* pub = pubs.getCabeza();
    do {
        int a = pub->anio;
        int idx = -1;
        for (int i = 0; i < numAnios; ++i) {
            if (anios[i] == a) {
                idx = i;
                break;
            }
        }
        if (idx != -1) {
            cuentas[idx]++;
        } else {
            anios[numAnios] = a;
            cuentas[numAnios] = 1;
            numAnios++;
        }
        pub = pub->siguiente;
    } while (pub != pubs.getCabeza());

    int maxProd = 0;
    for (int i = 0; i < numAnios; ++i) {
        if (cuentas[i] > maxProd) {
            maxProd = cuentas[i];
        }
    }

    std::cout << "  Mayor cantidad de publicaciones en un ano: " << maxProd << "\n\n";
    int count = 0;
    for (int i = 0; i < numAnios; ++i) {
        if (cuentas[i] == maxProd) {
            count++;
            std::cout << "  [" << count << "] Ano " << anios[i] << ": "
                      << cuentas[i] << " publicaciones registradas\n";
        }
    }

    delete[] anios;
    delete[] cuentas;
}

// 9. ¿Cuál publicación tiene mayor cantidad de autores?
void GestorConsultas::consulta9_PublicacionMasAutores(const ListaPublicaciones& pubs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 9: PUBLICACION(ES) CON MAYOR CANTIDAD DE AUTORES\n";
    std::cout << "================================================================================\n";

    if (pubs.getCabeza() == nullptr) {
        std::cout << "  No hay publicaciones registradas.\n";
        return;
    }

    int maxAutores = -1;
    NodoPublicacion* pub = pubs.getCabeza();
    do {
        int autores = pub->autores.getTamano();
        if (autores > maxAutores) {
            maxAutores = autores;
        }
        pub = pub->siguiente;
    } while (pub != pubs.getCabeza());

    std::cout << "  Cantidad maxima de autores por publicacion: " << maxAutores << "\n\n";

    pub = pubs.getCabeza();
    int count = 0;
    do {
        if (pub->autores.getTamano() == maxAutores) {
            count++;
            std::cout << "  [" << count << "] \"" << pub->titulo << "\" (" << pub->anio << ")\n"
                      << "      ID: " << pub->idPublicacion
                      << " | Total Autores: " << pub->autores.getTamano() << "\n"
                      << "      Autores:\n";
            pub->autores.mostrar();
            std::cout << "\n";
        }
        pub = pub->siguiente;
    } while (pub != pubs.getCabeza());
}

// 10. ¿Qué investigador posee más artículos en revistas Q1?
void GestorConsultas::consulta10_InvestigadorMasArticulosQ1(const ListaInvestigadores& invs, const ListaPublicaciones& pubs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 10: INVESTIGADOR(ES) CON MAS ARTICULOS EN REVISTAS Q1\n";
    std::cout << "================================================================================\n";

    if (invs.getCabeza() == nullptr) {
        std::cout << "  No hay investigadores registrados.\n";
        return;
    }

    int maxQ1 = -1;
    NodoInvestigador* inv = invs.getCabeza();
    while (inv != nullptr) {
        int cuentaQ1 = 0;
        if (pubs.getCabeza() != nullptr) {
            NodoPublicacion* pub = pubs.getCabeza();
            do {
                if (pub->investigadorPrincipal == inv && pub->revista != nullptr && pub->revista->cuartil == "Q1") {
                    cuentaQ1++;
                }
                pub = pub->siguiente;
            } while (pub != pubs.getCabeza());
        }
        if (cuentaQ1 > maxQ1) {
            maxQ1 = cuentaQ1;
        }
        inv = inv->siguiente;
    }

    std::cout << "  Maximo de articulos en revistas Q1: " << maxQ1 << "\n\n";
    inv = invs.getCabeza();
    int count = 0;
    while (inv != nullptr) {
        int cuentaQ1 = 0;
        if (pubs.getCabeza() != nullptr) {
            NodoPublicacion* pub = pubs.getCabeza();
            do {
                if (pub->investigadorPrincipal == inv && pub->revista != nullptr && pub->revista->cuartil == "Q1") {
                    cuentaQ1++;
                }
                pub = pub->siguiente;
            } while (pub != pubs.getCabeza());
        }
        if (cuentaQ1 == maxQ1) {
            count++;
            std::cout << "  [" << count << "] " << inv->nombreCompleto << " (ID: " << inv->idInvestigador << ")\n"
                      << "      Universidad: " << (inv->universidad ? inv->universidad->nombre : "N/A") << "\n"
                      << "      Total Articulos Q1: " << cuentaQ1 << "\n"
                      << "      Detalle de publicaciones Q1:\n";
            if (pubs.getCabeza() != nullptr) {
                NodoPublicacion* pub = pubs.getCabeza();
                do {
                    if (pub->investigadorPrincipal == inv && pub->revista != nullptr && pub->revista->cuartil == "Q1") {
                        std::cout << "        - \"" << pub->titulo << "\" (" << pub->anio << ") en "
                                  << pub->revista->nombre << " (FI: " << pub->revista->factorImpacto << ")\n";
                    }
                    pub = pub->siguiente;
                } while (pub != pubs.getCabeza());
            }
        }
        inv = inv->siguiente;
    }
}

// ----- Reportes.cpp -----

// Reporte 1: Mostrar todos los investigadores con sus publicaciones
void GestorReportes::reporte1_InvestigadoresConPublicaciones(const ListaInvestigadores& invs, const ListaPublicaciones& pubs) {
    std::cout << "\n====================================================================================================\n";
    std::cout << "                 REPORTE 1: INVESTIGADORES Y SU PRODUCCION CIENTIFICA COMPLETA                       \n";
    std::cout << "====================================================================================================\n";

    if (invs.getCabeza() == nullptr) {
        std::cout << "  No hay investigadores registrados.\n";
        return;
    }

    NodoInvestigador* inv = invs.getCabeza();
    while (inv != nullptr) {
        std::cout << "\n----------------------------------------------------------------------------------------------------\n";
        std::cout << "INVESTIGADOR: " << inv->nombreCompleto << " (ID: " << inv->idInvestigador << ")\n";
        std::cout << "Universidad:  " << (inv->universidad ? inv->universidad->nombre : "N/A")
                  << " | Pais: " << inv->pais
                  << " | Area: " << (inv->area ? inv->area->nombre : "N/A") << "\n";
        std::cout << "Indice H:     " << inv->indiceH
                  << " | Coautores: " << inv->sublistaCoautores.getTamano() << "\n";
        std::cout << "PUBLICACIONES ASOCIADAS:\n";

        int cuenta = 0;
        if (pubs.getCabeza() != nullptr) {
            NodoPublicacion* pub = pubs.getCabeza();
            do {
                if (pub->investigadorPrincipal == inv) {
                    cuenta++;
                    std::cout << "  [" << cuenta << "] \"" << pub->titulo << "\" (" << pub->anio << ")\n"
                              << "      Tipo: " << pub->tipo
                              << " | Citas: " << pub->cantidadCitas
                              << " | DOI: " << pub->doi << "\n"
                              << "      Revista: " << (pub->revista ? (pub->revista->nombre + " [" + pub->revista->cuartil + "]") : "(Sin revista)")
                              << " | Proyecto: " << (pub->proyecto ? pub->proyecto->nombre : "(Ninguno)") << "\n";
                }
                pub = pub->siguiente;
            } while (pub != pubs.getCabeza());
        }

        if (cuenta == 0) {
            std::cout << "  (Sin publicaciones registradas para este investigador)\n";
        }
        inv = inv->siguiente;
    }
    std::cout << "====================================================================================================\n";
}

// Reporte 2: Mostrar publicaciones ordenadas por año ascendente
void GestorReportes::reporte2_PublicacionesPorAnioAscendente(const ListaPublicaciones& pubs) {
    std::cout << "\n====================================================================================================\n";
    std::cout << "             REPORTE 2: PUBLICACIONES ORDENADAS POR ANO ASCENDENTE (LISTA CIRCULAR)                 \n";
    std::cout << "====================================================================================================\n";

    if (pubs.getCabeza() == nullptr) {
        std::cout << "  No hay publicaciones registradas.\n";
        return;
    }

    std::cout << std::left << std::setw(6) << "Ano"
              << std::setw(10) << "ID Pub"
              << std::setw(34) << "Titulo"
              << std::setw(14) << "Tipo"
              << std::setw(8) << "Citas"
              << std::setw(24) << "Investigador Principal"
              << "Revista" << "\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    NodoPublicacion* pub = pubs.getCabeza();
    do {
        std::string titCorto = pub->titulo;
        if (titCorto.length() > 32) titCorto = titCorto.substr(0, 29) + "...";

        std::string invNom = pub->investigadorPrincipal ? pub->investigadorPrincipal->nombreCompleto : "N/A";
        std::string revNom = pub->revista ? pub->revista->nombre : "(Sin revista)";

        std::cout << std::left << std::setw(6) << pub->anio
                  << std::setw(10) << pub->idPublicacion
                  << std::setw(34) << titCorto
                  << std::setw(14) << pub->tipo
                  << std::setw(8) << pub->cantidadCitas
                  << std::setw(24) << invNom
                  << revNom << "\n";
        pub = pub->siguiente;
    } while (pub != pubs.getCabeza());

    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "Total de publicaciones: " << pubs.getTamano() << "\n";
}

// Reporte 3: Mostrar publicaciones ordenadas por cantidad de citas descendente
void GestorReportes::reporte3_PublicacionesPorCitasDescendente(const ListaPublicaciones& pubs) {
    std::cout << "\n====================================================================================================\n";
    std::cout << "         REPORTE 3: PUBLICACIONES ORDENADAS POR CANTIDAD DE CITAS DESCENDENTE           \n";
    std::cout << "====================================================================================================\n";

    if (pubs.getCabeza() == nullptr) {
        std::cout << "  No hay publicaciones registradas.\n";
        return;
    }

    int n = pubs.getTamano();
    NodoPublicacion** arr = new NodoPublicacion*[n];
    int idx = 0;

    NodoPublicacion* act = pubs.getCabeza();
    do {
        arr[idx++] = act;
        act = act->siguiente;
    } while (act != pubs.getCabeza());

    // Ordenar de mayor a menor citas sin STL
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[j]->cantidadCitas > arr[i]->cantidadCitas) {
                NodoPublicacion* tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }

    std::cout << std::left << std::setw(8) << "Citas"
              << std::setw(10) << "ID Pub"
              << std::setw(6) << "Ano"
              << std::setw(34) << "Titulo"
              << std::setw(24) << "Investigador Principal"
              << "Revista / Cuartil" << "\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; ++i) {
        std::string titCorto = arr[i]->titulo;
        if (titCorto.length() > 32) titCorto = titCorto.substr(0, 29) + "...";

        std::string invNom = arr[i]->investigadorPrincipal ? arr[i]->investigadorPrincipal->nombreCompleto : "N/A";
        std::string revInfo = arr[i]->revista ? (arr[i]->revista->nombre + " (" + arr[i]->revista->cuartil + ")") : "(Sin revista)";

        std::cout << std::left << std::setw(8) << arr[i]->cantidadCitas
                  << std::setw(10) << arr[i]->idPublicacion
                  << std::setw(6) << arr[i]->anio
                  << std::setw(34) << titCorto
                  << std::setw(24) << invNom
                  << revInfo << "\n";
    }

    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "Total de publicaciones analizadas: " << n << "\n";

    delete[] arr;
}

// Reporte 4: Mostrar todas las revistas y sus factores de impacto
void GestorReportes::reporte4_RevistasYFactoresImpacto(const ListaRevistas& revs) {
    std::cout << "\n====================================================================================================\n";
    std::cout << "                       REPORTE 4: REVISTAS Y SUS FACTORES DE IMPACTO                                \n";
    std::cout << "====================================================================================================\n";
    revs.mostrar();
}

// Reporte 5: Imprimir la red de coautoría de un investigador específico
void GestorReportes::reporte5_RedCoautoriaInvestigador(const ListaInvestigadores& invs, const std::string& idInv) {
    std::cout << "\n====================================================================================================\n";
    std::cout << "                  REPORTE 5: RED DE COAUTORIA DE UN INVESTIGADOR ESPECIFICO                         \n";
    std::cout << "====================================================================================================\n";

    NodoInvestigador* inv = invs.buscarPorId(idInv);
    if (inv == nullptr) {
        std::cout << "  [ERROR] No existe ningun investigador con ID: " << idInv << "\n";
        return;
    }

    std::cout << "INVESTIGADOR: " << inv->nombreCompleto << " (ID: " << inv->idInvestigador << ")\n";
    std::cout << "Universidad:  " << (inv->universidad ? inv->universidad->nombre : "N/A") << "\n";
    std::cout << "Pais:         " << inv->pais << "\n";
    std::cout << "Area:         " << (inv->area ? inv->area->nombre : "N/A") << "\n";
    std::cout << "Total Coautores en Red: " << inv->sublistaCoautores.getTamano() << "\n\n";
    std::cout << "SUBRED DE COLABORACIONES CIENTIFICAS (Lista Doble):\n";
    inv->sublistaCoautores.mostrar();
    std::cout << "====================================================================================================\n";
}

// Reporte 6: Mostrar todas las publicaciones de una revista indicada por el usuario
void GestorReportes::reporte6_PublicacionesDeRevista(const ListaRevistas& revs, const ListaPublicaciones& pubs, const std::string& idRevista) {
    std::cout << "\n====================================================================================================\n";
    std::cout << "                  REPORTE 6: PUBLICACIONES DE UNA REVISTA DETERMINADA                               \n";
    std::cout << "====================================================================================================\n";

    NodoRevista* rev = revs.buscarPorId(idRevista);
    if (rev == nullptr) {
        rev = revs.buscarPorNombre(idRevista);
    }
    if (rev == nullptr) {
        std::cout << "  [ERROR] No se encontro la revista indicada: " << idRevista << "\n";
        return;
    }

    std::cout << "Revista:           " << rev->nombre << " (ID: " << rev->idRevista << ")\n";
    std::cout << "Editorial:         " << rev->editorial << " | Pais: " << rev->pais << "\n";
    std::cout << "Factor de Impacto: " << rev->factorImpacto << " | Cuartil: " << rev->cuartil << "\n\n";
    std::cout << "Articulos / Publicaciones en esta revista:\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    int cuenta = 0;
    if (pubs.getCabeza() != nullptr) {
        NodoPublicacion* pub = pubs.getCabeza();
        do {
            if (pub->revista == rev) {
                cuenta++;
                std::cout << "  [" << cuenta << "] \"" << pub->titulo << "\" (" << pub->anio << ")\n"
                          << "      ID: " << pub->idPublicacion << " | Citas: " << pub->cantidadCitas
                          << " | DOI: " << pub->doi << "\n"
                          << "      Investigador Principal: "
                          << (pub->investigadorPrincipal ? pub->investigadorPrincipal->nombreCompleto : "N/A") << "\n";
            }
            pub = pub->siguiente;
        } while (pub != pubs.getCabeza());
    }

    if (cuenta == 0) {
        std::cout << "  (No hay publicaciones registradas en esta revista actualmente)\n";
    }
    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "Total publicaciones encontradas: " << cuenta << "\n";
}

// Reporte 7: Mostrar todas las publicaciones de un área determinada
void GestorReportes::reporte7_PublicacionesDeArea(const ListaAreas& areas, const ListaPublicaciones& pubs, const std::string& idArea) {
    std::cout << "\n====================================================================================================\n";
    std::cout << "               REPORTE 7: PUBLICACIONES DE UN AREA DE INVESTIGACION DETERMINADA                     \n";
    std::cout << "====================================================================================================\n";

    NodoArea* ar = areas.buscarPorId(idArea);
    if (ar == nullptr) {
        std::cout << "  [ERROR] No se encontro el area con ID: " << idArea << "\n";
        return;
    }

    std::cout << "Area de Investigacion: " << ar->nombre << " (ID: " << ar->idArea << ")\n";
    std::cout << "Descripcion:           " << ar->descripcion << "\n\n";
    std::cout << "Publicaciones generadas en esta area:\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    int cuenta = 0;
    if (pubs.getCabeza() != nullptr) {
        NodoPublicacion* pub = pubs.getCabeza();
        do {
            if (pub->investigadorPrincipal != nullptr && pub->investigadorPrincipal->area == ar) {
                cuenta++;
                std::cout << "  [" << cuenta << "] \"" << pub->titulo << "\" (" << pub->anio << ")\n"
                          << "      ID: " << pub->idPublicacion << " | Citas: " << pub->cantidadCitas << " | Tipo: " << pub->tipo << "\n"
                          << "      Investigador: " << pub->investigadorPrincipal->nombreCompleto << "\n"
                          << "      Revista: " << (pub->revista ? pub->revista->nombre : "(Sin revista)") << "\n";
            }
            pub = pub->siguiente;
        } while (pub != pubs.getCabeza());
    }

    if (cuenta == 0) {
        std::cout << "  (No hay publicaciones registradas para esta area actualmente)\n";
    }
    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "Total publicaciones en el area: " << cuenta << "\n";
}

// Reporte 8: Mostrar los investigadores agrupados por universidad
void GestorReportes::reporte8_InvestigadoresAgrupadosPorUniversidad(const ListaUniversidades& unis, const ListaInvestigadores& invs) {
    std::cout << "\n====================================================================================================\n";
    std::cout << "                    REPORTE 8: INVESTIGADORES AGRUPADOS POR UNIVERSIDAD                              \n";
    std::cout << "====================================================================================================\n";

    if (unis.getCabeza() == nullptr) {
        std::cout << "  No hay universidades registradas.\n";
        return;
    }

    NodoUniversidad* uni = unis.getCabeza();
    while (uni != nullptr) {
        std::cout << "\n>>> UNIVERSIDAD: " << uni->nombre << " (ID: " << uni->idUniversidad << ")\n";
        std::cout << "    Pais: " << uni->pais << " | Ranking Global: #" << uni->ranking << "\n";
        std::cout << "    Investigadores Afiliados:\n";

        int cuenta = 0;
        NodoInvestigador* inv = invs.getCabeza();
        while (inv != nullptr) {
            if (inv->universidad == uni) {
                cuenta++;
                std::cout << "      " << cuenta << ". " << inv->nombreCompleto << " (ID: " << inv->idInvestigador << ")\n"
                          << "         Area: " << (inv->area ? inv->area->nombre : "N/A")
                          << " | Correo: " << inv->correo
                          << " | Indice H: " << inv->indiceH << "\n";
            }
            inv = inv->siguiente;
        }

        if (cuenta == 0) {
            std::cout << "      (Sin investigadores afiliados registrados)\n";
        }
        std::cout << "    Total en esta institucion: " << cuenta << "\n";

        uni = uni->siguiente;
    }
    std::cout << "====================================================================================================\n";
}

// Reporte 9: Mostrar los investigadores ordenados por índice H
void GestorReportes::reporte9_InvestigadoresOrdenadosPorIndiceH(ListaInvestigadores& invs, const ListaPublicaciones& pubs) {
    std::cout << "\n====================================================================================================\n";
    std::cout << "             REPORTE 9: INVESTIGADORES ORDENADOS POR INDICE H DESCENDENTE                            \n";
    std::cout << "====================================================================================================\n";

    if (invs.getCabeza() == nullptr) {
        std::cout << "  No hay investigadores registrados.\n";
        return;
    }

    // Actualizar previamente los índices H
    MetricasAcademicas::actualizarIndicesHTodos(invs, pubs);

    int n = invs.getTamano();
    NodoInvestigador** arr = new NodoInvestigador*[n];
    int idx = 0;

    NodoInvestigador* act = invs.getCabeza();
    while (act != nullptr) {
        arr[idx++] = act;
        act = act->siguiente;
    }

    // Ordenar de mayor a menor por índice H sin STL
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[j]->indiceH > arr[i]->indiceH) {
                NodoInvestigador* tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }

    std::cout << std::left << std::setw(10) << "Indice H"
              << std::setw(10) << "ID"
              << std::setw(28) << "Investigador"
              << std::setw(32) << "Universidad"
              << std::setw(14) << "Total Citas"
              << "Publicaciones" << "\n";
    std::cout << "----------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; ++i) {
        int totCitas = MetricasAcademicas::calcularTotalCitas(arr[i], pubs);
        int totPubs = MetricasAcademicas::calcularProduccionCientifica(arr[i], pubs);
        std::string uniNom = arr[i]->universidad ? arr[i]->universidad->nombre : "N/A";

        std::cout << std::left << std::setw(10) << arr[i]->indiceH
                  << std::setw(10) << arr[i]->idInvestigador
                  << std::setw(28) << arr[i]->nombreCompleto
                  << std::setw(32) << uniNom
                  << std::setw(14) << totCitas
                  << totPubs << "\n";
    }

    std::cout << "----------------------------------------------------------------------------------------------------\n";
    std::cout << "Total investigadores listados: " << n << "\n";

    delete[] arr;
}

// ----- Sistema.cpp -----

// Función utilitaria para leer cadenas con espacios de forma segura
static std::string leerLinea(const std::string& prompt) {
    std::cout << prompt;
    std::string linea;
    if (!std::getline(std::cin, linea)) return "";
    // Remover BOM de UTF-8 si PowerShell lo inyectó al inicio del pipe
    if (linea.size() >= 3 && (unsigned char)linea[0] == 0xEF && (unsigned char)linea[1] == 0xBB && (unsigned char)linea[2] == 0xBF) {
        linea = linea.substr(3);
    }
    // Remover retorno de carro '\r' común en Windows
    if (!linea.empty() && linea.back() == '\r') {
        linea.pop_back();
    }
    return linea;
}

// Función utilitaria para leer enteros de forma segura
static int leerEntero(const std::string& prompt) {
    while (true) {
        std::string linea = leerLinea(prompt);
        if (linea.empty()) {
            if (std::cin.eof()) return 0;
            continue;
        }
        try {
            size_t idx;
            int valor = std::stoi(linea, &idx);
            return valor;
        } catch (...) {
            std::cout << "  [ERROR] Entrada invalida. Ingrese un numero entero.\n";
            if (std::cin.eof()) return 0;
        }
    }
}

// Función utilitaria para leer doubles de forma segura
static double leerDouble(const std::string& prompt) {
    while (true) {
        std::string linea = leerLinea(prompt);
        if (linea.empty()) {
            if (std::cin.eof()) return 0.0;
            continue;
        }
        try {
            size_t idx;
            double valor = std::stod(linea, &idx);
            return valor;
        } catch (...) {
            std::cout << "  [ERROR] Entrada invalida. Ingrese un numero decimal.\n";
            if (std::cin.eof()) return 0.0;
        }
    }
}

SistemaAcademico::SistemaAcademico() {
    precargarDatos();
}

SistemaAcademico::~SistemaAcademico() {}

void SistemaAcademico::precargarDatos() {
    std::cout << "[SISTEMA] Iniciando precarga de datos academicos...\n";

    // ================================================================
    // Datos iniciales de revistas y proyectos.
    // Se conservan los datos y la organizacion de la implementacion original.
    // ================================================================

    // 1. Universidades. En el proyecto unificado se mantiene como lista doble.
    listaUniversidades.insertar("1", "TEC", "Costa Rica", 1);
    listaUniversidades.insertar("2", "UCR", "Costa Rica", 2);
    listaUniversidades.insertar("3", "UNA", "Costa Rica", 3);
    listaUniversidades.insertar("4", "MIT", "USA", 1);
    listaUniversidades.insertar("5", "Stanford", "USA", 2);

    // 2. Areas de investigacion.
    listaAreas.insertarAlFinal("1", "Inteligencia Artificial", "IA y Machine Learning");
    listaAreas.insertarAlFinal("2", "Ciberseguridad", "Seguridad informatica");
    listaAreas.insertarAlFinal("3", "Redes", "Redes de computadoras");
    listaAreas.insertarAlFinal("4", "Software", "Ingenieria de software");
    listaAreas.insertarAlFinal("5", "Datos", "Bases de datos y Big Data");

    NodoUniversidad* uTec = listaUniversidades.buscarPorId("1");
    NodoUniversidad* uUcr = listaUniversidades.buscarPorId("2");
    NodoUniversidad* uMit = listaUniversidades.buscarPorId("4");
    NodoUniversidad* uStan = listaUniversidades.buscarPorId("5");

    NodoArea* arIA = listaAreas.buscarPorId("1");
    NodoArea* arSeg = listaAreas.buscarPorId("2");
    NodoArea* arRedes = listaAreas.buscarPorId("3");
    NodoArea* arSoft = listaAreas.buscarPorId("4");

    // 3. Investigadores. Se conservan los cinco registros originales.
    listaInvestigadores.insertarAlFinal("1", "Ana Perez", uTec, "Costa Rica", arIA, "ana@tec.ac.cr");
    listaInvestigadores.insertarAlFinal("2", "Carlos Lopez", uUcr, "Costa Rica", arSeg, "carlos@ucr.ac.cr");
    listaInvestigadores.insertarAlFinal("3", "Maria Ruiz", uTec, "Costa Rica", arRedes, "maria@tec.ac.cr");
    listaInvestigadores.insertarAlFinal("4", "John Doe", uMit, "USA", arIA, "john@mit.edu");
    listaInvestigadores.insertarAlFinal("5", "Elena Gomez", uStan, "USA", arSoft, "elena@stanford.edu");

    // 4. Coautores. Se conservan los registros de las sublistas originales.
    NodoInvestigador* inv1 = listaInvestigadores.buscarPorId("1");
    NodoInvestigador* inv3 = listaInvestigadores.buscarPorId("3");
    NodoInvestigador* inv5 = listaInvestigadores.buscarPorId("5");

    if (inv1) {
        inv1->sublistaCoautores.insertar("101", "Luis Solis", "UCR", 3);
        inv1->sublistaCoautores.insertar("102", "Sara Mora", "TEC", 5);
    }
    if (inv3) {
        inv3->sublistaCoautores.insertar("103", "Pedro Picapiedra", "UNA", 2);
        inv3->sublistaCoautores.insertar("104", "Rocio Perez", "TEC", 4);
        inv3->sublistaCoautores.insertar("105", "Marta Vega", "MIT", 1);
    }
    if (inv5) {
        inv5->sublistaCoautores.insertar("106", "Albert Einstein", "Princeton", 10);
    }

    // ================================================================
    // Datos iniciales de revistas y proyectos.
    // Revistas y proyectos.
    // ================================================================

    listaRevistas.insertarOrdenado("REV01", "Nature Machine Intelligence", "Nature Publishing", "Reino Unido", 25.898, "Q1");
    listaRevistas.insertarOrdenado("REV02", "IEEE Trans. Pattern Analysis", "IEEE", "Estados Unidos", 23.600, "Q1");
    listaRevistas.insertarOrdenado("REV03", "Science", "AAAS", "Estados Unidos", 44.700, "Q1");
    listaRevistas.insertarOrdenado("REV04", "Bioinformatics", "Oxford Univ Press", "Reino Unido", 5.800, "Q1");
    listaRevistas.insertarOrdenado("REV05", "ACM Computing Surveys", "ACM", "Estados Unidos", 16.600, "Q1");
    listaRevistas.insertarOrdenado("REV06", "Communications of the ACM", "ACM", "Estados Unidos", 14.100, "Q2");
    listaRevistas.insertarOrdenado("REV07", "Int. Journal of Robotics", "SAGE", "Estados Unidos", 7.500, "Q2");

    listaProyectos.insertarOrdenadoPorAnio("PRY01", "Proyecto de Inteligencia Artificial", 850000.0, 2019, 2023, inv1);
    listaProyectos.insertarOrdenadoPorAnio("PRY02", "Proyecto de Ciberseguridad", 450000.0, 2020, 2024, listaInvestigadores.buscarPorId("2"));
    listaProyectos.insertarOrdenadoPorAnio("PRY03", "Proyecto de Redes", 620000.0, 2021, 2025, inv3);
    listaProyectos.insertarOrdenadoPorAnio("PRY04", "Proyecto de Software", 280000.0, 2022, 2025, inv5);
    listaProyectos.insertarOrdenadoPorAnio("PRY05", "Proyecto de Datos", 950000.0, 2023, 2026, listaInvestigadores.buscarPorId("4"));
    listaProyectos.insertarOrdenadoPorAnio("PRY06", "Proyecto de Sistemas Inteligentes", 530000.0, 2024, 2027, inv1);

    // ================================================================
    // Datos iniciales de revistas y proyectos.
    // Publicaciones y citaciones.
    // ================================================================

    NodoRevista* revNat = listaRevistas.buscarPorId("REV01");
    NodoRevista* revIEEE = listaRevistas.buscarPorId("REV02");
    NodoRevista* revSci = listaRevistas.buscarPorId("REV03");
    NodoRevista* revBio = listaRevistas.buscarPorId("REV04");
    NodoRevista* revACM = listaRevistas.buscarPorId("REV05");
    NodoRevista* revCACM = listaRevistas.buscarPorId("REV06");

    NodoProyecto* pry01 = listaProyectos.buscarPorId("PRY01");
    NodoProyecto* pry02 = listaProyectos.buscarPorId("PRY02");
    NodoProyecto* pry03 = listaProyectos.buscarPorId("PRY03");
    NodoProyecto* pry04 = listaProyectos.buscarPorId("PRY04");
    NodoProyecto* pry05 = listaProyectos.buscarPorId("PRY05");
    NodoProyecto* pry06 = listaProyectos.buscarPorId("PRY06");

    NodoInvestigador* inv2 = listaInvestigadores.buscarPorId("2");
    NodoInvestigador* inv4 = listaInvestigadores.buscarPorId("4");

    listaPublicaciones.insertarOrdenadoPorAnio("PUB01", "Sistemas inteligentes aplicados", 2020, "Articulo", 35, "doi1", inv1, revIEEE, pry01);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB02", "Modelos de datos", 2020, "Articulo", 12, "doi2", inv1, revNat, pry06);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB03", "Software educativo", 2021, "Articulo", 8, "doi3", inv2, revACM, pry04);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB04", "Redes universitarias", 2021, "Articulo", 5, "doi4", inv2, revCACM, pry02);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB05", "Analisis de datos", 2022, "Articulo", 22, "doi5", inv3, revSci, pry03);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB06", "Sistemas inteligentes", 2022, "Articulo", 14, "doi6", inv4, revNat, pry05);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB07", "Bases de datos modernas", 2023, "Articulo", 7, "doi7", inv5, revBio, pry04);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB08", "IA y educacion", 2023, "Articulo", 10, "doi8", inv1, revIEEE, pry01);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB09", "Ciberseguridad en redes", 2024, "Articulo", 18, "doi9", inv2, revSci, pry02);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB10", "Arquitecturas de software", 2024, "Articulo", 16, "doi10", inv5, revACM, pry04);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB11", "Mineria de datos", 2025, "Articulo", 9, "doi11", inv3, revBio, pry05);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB12", "Redes y sistemas", 2025, "Articulo", 11, "doi12", inv4, revCACM, pry03);

    // Asociacion de autores por publicacion. Cada publicacion conserva al investigador principal
    // y, cuando corresponde, los coautores concretos que participaron en ella.
    listaPublicaciones.agregarCoautorAPublicacion("PUB01", inv1, "101");
    listaPublicaciones.agregarCoautorAPublicacion("PUB01", inv1, "102");
    listaPublicaciones.agregarCoautorAPublicacion("PUB02", inv1, "101");
    listaPublicaciones.agregarCoautorAPublicacion("PUB05", inv3, "103");
    listaPublicaciones.agregarCoautorAPublicacion("PUB05", inv3, "104");
    listaPublicaciones.agregarCoautorAPublicacion("PUB07", inv5, "106");
    listaPublicaciones.agregarCoautorAPublicacion("PUB10", inv5, "106");

    listaPublicaciones.agregarCitaAPublicacion("PUB01", "CIT01", 2021, "Trabajo relacionado 1", "Autor 1");
    listaPublicaciones.agregarCitaAPublicacion("PUB01", "CIT02", 2022, "Trabajo relacionado 2", "Autor 2");
    listaPublicaciones.agregarCitaAPublicacion("PUB02", "CIT03", 2021, "Trabajo relacionado 3", "Autor 3");
    listaPublicaciones.agregarCitaAPublicacion("PUB03", "CIT04", 2022, "Trabajo relacionado 4", "Autor 4");
    listaPublicaciones.agregarCitaAPublicacion("PUB03", "CIT05", 2023, "Trabajo relacionado 5", "Autor 5");
    listaPublicaciones.agregarCitaAPublicacion("PUB05", "CIT06", 2023, "Trabajo relacionado 6", "Autor 6");
    listaPublicaciones.agregarCitaAPublicacion("PUB06", "CIT07", 2023, "Trabajo relacionado 7", "Autor 7");
    listaPublicaciones.agregarCitaAPublicacion("PUB06", "CIT08", 2024, "Trabajo relacionado 8", "Autor 8");
    listaPublicaciones.agregarCitaAPublicacion("PUB07", "CIT09", 2024, "Trabajo relacionado 9", "Autor 9");
    listaPublicaciones.agregarCitaAPublicacion("PUB08", "CIT10", 2024, "Trabajo relacionado 10", "Autor 10");
    listaPublicaciones.agregarCitaAPublicacion("PUB09", "CIT11", 2025, "Trabajo relacionado 11", "Autor 11");
    listaPublicaciones.agregarCitaAPublicacion("PUB10", "CIT12", 2025, "Trabajo relacionado 12", "Autor 12");
    listaPublicaciones.agregarCitaAPublicacion("PUB11", "CIT13", 2025, "Trabajo relacionado 13", "Autor 13");
    listaPublicaciones.agregarCitaAPublicacion("PUB12", "CIT14", 2026, "Trabajo relacionado 14", "Autor 14");

    // Calculo de H a partir de las publicaciones, en lugar de dejarlo fijo.
    MetricasAcademicas::actualizarIndicesHTodos(listaInvestigadores, listaPublicaciones);

    std::cout << "[SISTEMA] Precarga completada. Se cargaron los datos iniciales y las relaciones del sistema.\n";
}

void SistemaAcademico::menuPrincipal() {
    int opcion = -1;
    do {
        std::cout << "\n================================================================================\n";
        std::cout << "     SISTEMA DE GESTION DE PRODUCCION CIENTIFICA Y METRICAS ACADEMICAS          \n";
        std::cout << "                 IC2001 ESTRUCTURA DE DATOS - TEC COSTA RICA                    \n";
        std::cout << "                 INTEGRACION TOTAL\n";
        std::cout << "================================================================================\n";
        std::cout << "  [1]  Gestion de Publicaciones Cientificas (Lista Circular)\n";
        std::cout << "  [2]  Gestion de Citaciones (Lista Doble / Sublistas)\n";
        std::cout << "  [3]  Modulo de Metricas Academicas e Indice H\n";
        std::cout << "  [4]  Consultas del Sistema (10 consultas)\n";
        std::cout << "  [5]  Reportes del Sistema (9 reportes)\n";
        std::cout << "  [6]  Gestion de Investigadores (Lista Simple y Sublista Coautores)\n";
        std::cout << "  [7]  Gestion de Universidades (Lista Doble)\n";
        std::cout << "  [8]  Gestion de Areas de Investigacion (Lista Simple)\n";
        std::cout << "  [9]  Gestion de Revistas Cientificas (Lista Simple Ordenada)\n";
        std::cout << "  [10] Gestion de Proyectos de Investigacion (Lista Doble Ordenada)\n";
        std::cout << "  [11] Demostracion del Ejemplo Oficial de Indice H = 5 (PDF)\n";
        std::cout << "  [12] Gestion de Revistas y Proyectos\n";
        std::cout << "  [0]  Salir del Sistema\n";
        std::cout << "================================================================================\n";
        opcion = leerEntero("Seleccione una opcion [0-12]: ");

        switch (opcion) {
            case 1:  menuPublicaciones(); break;
            case 2:  menuCitaciones(); break;
            case 3:  menuMetricas(); break;
            case 4:  menuConsultas(); break;
            case 5:  menuReportes(); break;
            case 6:  menuInvestigadores(); break;
            case 7:  menuUniversidades(); break;
            case 8:  menuAreas(); break;
            case 9:  menuRevistas(); break;
            case 10: menuProyectos(); break;
            case 11: ejecutarPruebaEjemploIndiceH(); break;
            case 12: menu(); break;
            case 0:
                std::cout << "\nGracias por utilizar el Sistema de Produccion Cientifica y Metricas Academicas.\n";
                break;
            default:
                std::cout << "  [ERROR] Opcion no valida. Intente de nuevo.\n";
                break;
        }
    } while (opcion != 0);
}

// -------------------------------------------------------------------------------------
// GESTION DE PUBLICACIONES (Lista Circular)
// -------------------------------------------------------------------------------------
void SistemaAcademico::menuPublicaciones() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "        GESTION DE PUBLICACIONES CIENTIFICAS (LISTA CIRCULAR)       \n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1. Insertar publicacion (ordenada por ano ascendente)\n";
        std::cout << "  2. Buscar publicacion por ID\n";
        std::cout << "  3. Modificar publicacion\n";
        std::cout << "  4. Eliminar publicacion (Eliminacion en Lista Circular)\n";
        std::cout << "  5. Mostrar todas las publicaciones\n";
        std::cout << "  6. Mostrar publicaciones con detalle completo (incluye autores y citaciones)\n";
        std::cout << "  7. Agregar coautor a una publicacion\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-7]: ");

        if (op == 1) {
            std::cout << "\n--- INSERTAR PUBLICACION ---\n";
            std::string id = leerLinea("ID de la publicacion (ej. PUB13): ");
            if (listaPublicaciones.existeId(id)) {
                std::cout << "  [ERROR] El ID " << id << " ya existe en el sistema.\n";
                continue;
            }
            std::string tit = leerLinea("Titulo de la publicacion: ");
            int anio = leerEntero("Ano de publicacion: ");
            std::string tipo = leerLinea("Tipo (Articulo, Libro, Conferencia): ");
            int citas = leerEntero("Cantidad inicial de citas: ");
            std::string doi = leerLinea("DOI (ej. 10.1145/example.2024): ");

            std::string idInv = leerLinea("ID del investigador principal: ");
            NodoInvestigador* inv = listaInvestigadores.buscarPorId(idInv);
            if (inv == nullptr) {
                std::cout << "  [AVISO] No se encontro el investigador " << idInv << ". Se asignara nullptr.\n";
            }

            std::string idRev = leerLinea("ID de la revista (dejar vacio si es Libro/Conferencia): ");
            NodoRevista* rev = idRev.empty() ? nullptr : listaRevistas.buscarPorId(idRev);

            std::string idProy = leerLinea("ID del proyecto asociado (dejar vacio si no aplica): ");
            NodoProyecto* proy = idProy.empty() ? nullptr : listaProyectos.buscarPorId(idProy);

            if (listaPublicaciones.insertarOrdenadoPorAnio(id, tit, anio, tipo, citas, doi, inv, rev, proy)) {
                std::cout << "  [EXITO] Publicacion insertada correctamente en la lista circular.\n";
                MetricasAcademicas::actualizarIndicesHTodos(listaInvestigadores, listaPublicaciones);
            }
        } else if (op == 2) {
            std::string id = leerLinea("Ingrese ID de la publicacion a buscar: ");
            NodoPublicacion* p = listaPublicaciones.buscarPorId(id);
            if (p != nullptr) {
                std::cout << "  [ENCONTRADA]\n";
                std::cout << "  Titulo: " << p->titulo << " (" << p->anio << ") | Tipo: " << p->tipo << "\n";
                std::cout << "  Citas: " << p->cantidadCitas << " | DOI: " << p->doi << "\n";
                std::cout << "  Investigador: " << (p->investigadorPrincipal ? p->investigadorPrincipal->nombreCompleto : "N/A") << "\n";
                std::cout << "  Revista: " << (p->revista ? p->revista->nombre : "N/A") << "\n";
            } else {
                std::cout << "  [ERROR] No se encontro publicacion con ID: " << id << "\n";
            }
        } else if (op == 3) {
            std::string id = leerLinea("Ingrese ID de la publicacion a modificar: ");
            NodoPublicacion* p = listaPublicaciones.buscarPorId(id);
            if (p == nullptr) {
                std::cout << "  [ERROR] No se encontro la publicacion con ID: " << id << "\n";
                continue;
            }
            std::cout << "  (Deje el campo vacio o valor -1 para conservar el valor actual)\n";
            std::string nuevoTit = leerLinea("Nuevo titulo [" + p->titulo + "]: ");
            int nuevoAnio = leerEntero("Nuevo ano (" + std::to_string(p->anio) + "): ");
            std::string nuevoTipo = leerLinea("Nuevo tipo [" + p->tipo + "]: ");
            int nuevasCitas = leerEntero("Nuevas citas (" + std::to_string(p->cantidadCitas) + "): ");
            std::string nuevoDoi = leerLinea("Nuevo DOI [" + p->doi + "]: ");

            if (listaPublicaciones.modificar(id, nuevoTit, nuevoAnio, nuevoTipo, nuevasCitas, nuevoDoi,
                                             p->investigadorPrincipal, p->revista, p->proyecto)) {
                std::cout << "  [EXITO] Publicacion modificada exitosamente.\n";
                MetricasAcademicas::actualizarIndicesHTodos(listaInvestigadores, listaPublicaciones);
            }
        } else if (op == 4) {
            std::string id = leerLinea("Ingrese ID de la publicacion a eliminar (Lista Circular): ");
            if (listaPublicaciones.eliminar(id)) {
                std::cout << "  [EXITO] Publicacion eliminada de la lista circular correctamente.\n";
                MetricasAcademicas::actualizarIndicesHTodos(listaInvestigadores, listaPublicaciones);
            } else {
                std::cout << "  [ERROR] No se encontro la publicacion con ID: " << id << "\n";
            }
        } else if (op == 5) {
            listaPublicaciones.mostrar();
        } else if (op == 6) {
            listaPublicaciones.mostrarConDetalles();
        } else if (op == 7) {
            std::string idPub = leerLinea("ID de la publicacion: ");
            NodoPublicacion* pub = listaPublicaciones.buscarPorId(idPub);
            if (pub == nullptr) {
                std::cout << "  [ERROR] Publicacion no encontrada.\n";
                continue;
            }

            std::string idInv = leerLinea("ID del investigador propietario del coautor: ");
            NodoInvestigador* invPropietario = listaInvestigadores.buscarPorId(idInv);
            if (invPropietario == nullptr) {
                std::cout << "  [ERROR] Investigador no encontrado.\n";
                continue;
            }

            std::string idCoautor = leerLinea("ID del coautor: ");
            if (listaPublicaciones.agregarCoautorAPublicacion(idPub, invPropietario, idCoautor)) {
                std::cout << "  [EXITO] Coautor asociado correctamente a la publicacion.\n";
            }
        }
    } while (op != 0);
}

// -------------------------------------------------------------------------------------
// GESTION DE CITACIONES (Lista Doble)
// -------------------------------------------------------------------------------------
void SistemaAcademico::menuCitaciones() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "        GESTION DE CITACIONES (LISTA DOBLE / SUBLISTAS)             \n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1. Agregar citacion a una publicacion especifica\n";
        std::cout << "  2. Buscar citacion dentro de una publicacion\n";
        std::cout << "  3. Modificar citacion en una publicacion\n";
        std::cout << "  4. Eliminar citacion de una publicacion (Eliminacion en Lista Doble)\n";
        std::cout << "  5. Mostrar todas las citaciones de una publicacion\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-5]: ");

        if (op == 1) {
            std::string idPub = leerLinea("ID de la publicacion que recibe la cita: ");
            NodoPublicacion* pub = listaPublicaciones.buscarPorId(idPub);
            if (pub == nullptr) {
                std::cout << "  [ERROR] Publicacion no encontrada.\n";
                continue;
            }
            std::string idCita = leerLinea("ID de la cita (ej. CIT19): ");
            int anio = leerEntero("Ano de la citacion: ");
            std::string pubCit = leerLinea("Titulo/Articulo citante: ");
            std::string autCit = leerLinea("Autor(es) citante(s): ");

            if (listaPublicaciones.agregarCitaAPublicacion(idPub, idCita, anio, pubCit, autCit)) {
                std::cout << "  [EXITO] Citacion agregada exitosamente a la sublista de " << idPub << ".\n";
                MetricasAcademicas::actualizarIndicesHTodos(listaInvestigadores, listaPublicaciones);
            }
        } else if (op == 2) {
            std::string idPub = leerLinea("ID de la publicacion: ");
            NodoPublicacion* pub = listaPublicaciones.buscarPorId(idPub);
            if (pub == nullptr) {
                std::cout << "  [ERROR] Publicacion no encontrada.\n";
                continue;
            }
            std::string idCita = leerLinea("ID de la cita a buscar: ");
            NodoCitacion* c = pub->sublistaCitaciones.buscarPorId(idCita);
            if (c != nullptr) {
                std::cout << "  [ENCONTRADA] Cita " << c->idCita << " (" << c->anio << "): \""
                          << c->publicacionCitante << "\" por " << c->autorCitante << "\n";
            } else {
                std::cout << "  [ERROR] No se encontro la cita en esta publicacion.\n";
            }
        } else if (op == 3) {
            std::string idPub = leerLinea("ID de la publicacion: ");
            NodoPublicacion* pub = listaPublicaciones.buscarPorId(idPub);
            if (pub == nullptr) {
                std::cout << "  [ERROR] Publicacion no encontrada.\n";
                continue;
            }
            std::string idCita = leerLinea("ID de la cita a modificar: ");
            NodoCitacion* c = pub->sublistaCitaciones.buscarPorId(idCita);
            if (c == nullptr) {
                std::cout << "  [ERROR] No se encontro la cita.\n";
                continue;
            }
            int nuevoAnio = leerEntero("Nuevo ano: ");
            std::string nuevaPub = leerLinea("Nuevo titulo citante: ");
            std::string nuevoAut = leerLinea("Nuevo autor citante: ");
            if (pub->sublistaCitaciones.modificar(idCita, nuevoAnio, nuevaPub, nuevoAut)) {
                std::cout << "  [EXITO] Citacion modificada con exito.\n";
            }
        } else if (op == 4) {
            std::string idPub = leerLinea("ID de la publicacion: ");
            NodoPublicacion* pub = listaPublicaciones.buscarPorId(idPub);
            if (pub == nullptr) {
                std::cout << "  [ERROR] Publicacion no encontrada.\n";
                continue;
            }
            std::string idCita = leerLinea("ID de la cita a eliminar (Lista Doble): ");
            if (pub->sublistaCitaciones.eliminar(idCita)) {
                std::cout << "  [EXITO] Citacion eliminada de la sublista doble.\n";
                if (pub->cantidadCitas > 0) pub->cantidadCitas--;
                MetricasAcademicas::actualizarIndicesHTodos(listaInvestigadores, listaPublicaciones);
            } else {
                std::cout << "  [ERROR] No se encontro la cita.\n";
            }
        } else if (op == 5) {
            std::string idPub = leerLinea("ID de la publicacion: ");
            NodoPublicacion* pub = listaPublicaciones.buscarPorId(idPub);
            if (pub == nullptr) {
                std::cout << "  [ERROR] Publicacion no encontrada.\n";
                continue;
            }
            std::cout << "Citaciones registradas para: \"" << pub->titulo << "\":\n";
            pub->sublistaCitaciones.mostrar();
        }
    } while (op != 0);
}

// -------------------------------------------------------------------------------------
// GESTION DE METRICAS ACADEMICAS
// -------------------------------------------------------------------------------------
void SistemaAcademico::menuMetricas() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "          MODULO DE METRICAS ACADEMICAS E INDICE H\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1. Consultar metricas academicas de un investigador especifico\n";
        std::cout << "  2. Mostrar tabla comparativa de metricas de todos los investigadores\n";
        std::cout << "  3. Recalcular y sincronizar indices H en todo el sistema\n";
        std::cout << "  4. Ejecutar prueba del ejemplo teorico de Indice H = 5 del enunciado\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-4]: ");

        if (op == 1) {
            std::string idInv = leerLinea("Ingrese ID del investigador (ej. INV01): ");
            NodoInvestigador* inv = listaInvestigadores.buscarPorId(idInv);
            if (inv != nullptr) {
                MetricasAcademicas::mostrarMetricasInvestigador(inv, listaPublicaciones);
            } else {
                std::cout << "  [ERROR] Investigador no encontrado con ID: " << idInv << "\n";
            }
        } else if (op == 2) {
            MetricasAcademicas::mostrarTodasLasMetricas(listaInvestigadores, listaPublicaciones);
        } else if (op == 3) {
            MetricasAcademicas::actualizarIndicesHTodos(listaInvestigadores, listaPublicaciones);
            std::cout << "  [EXITO] Indices H recalculados y sincronizados correctamente.\n";
        } else if (op == 4) {
            ejecutarPruebaEjemploIndiceH();
        }
    } while (op != 0);
}

void SistemaAcademico::ejecutarPruebaEjemploIndiceH() {
    std::cout << "\n================================================================================\n";
    std::cout << "       DEMOSTRACION DEL EJEMPLO OFICIAL DE INDICE H DEL ENUNCIADO (PAG. 5)      \n";
    std::cout << "================================================================================\n";
    std::cout << "Enunciado oficial:\n";
    std::cout << "Suponga que un investigador tiene las siguientes citas por publicacion:\n";
    std::cout << "25, 18, 12, 8, 5, 4, 2, 1\n\n";

    int citasEjemplo[] = {25, 18, 12, 8, 5, 4, 2, 1};
    int totalPub = 8;

    std::cout << std::left << std::setw(25) << "Posicion de la pub." << "Cantidad de Citas" << "\n";
    std::cout << "--------------------------------------------------------\n";
    for (int i = 0; i < totalPub; ++i) {
        std::cout << std::left << std::setw(25) << (i + 1) << citasEjemplo[i] << "\n";
    }
    std::cout << "--------------------------------------------------------\n";
    std::cout << "Verificacion paso a paso:\n";
    int hCalculado = 0;
    for (int i = 0; i < totalPub; ++i) {
        int pos = i + 1;
        if (citasEjemplo[i] >= pos) {
            std::cout << "  " << pos << " publicacion(es) con al menos " << pos << " cita(s): SI ("
                      << citasEjemplo[i] << " >= " << pos << ")\n";
            hCalculado = pos;
        } else {
            std::cout << "  " << pos << " publicacion(es) con al menos " << pos << " cita(s): NO (la "
                      << pos << "a tiene " << citasEjemplo[i] << " citas)\n";
            break;
        }
    }
    std::cout << "\nResultado del algoritmo sin STL: Indice H = " << hCalculado << "\n";
    std::cout << "Resultado esperado por el enunciado: Indice H = 5\n";
    if (hCalculado == 5) {
        std::cout << ">>> COINCIDENCIA EXACTA CONFIRMADA (100% CORRECTO) <<<\n";
    }
    std::cout << "================================================================================\n";
}

// -------------------------------------------------------------------------------------
// CONSULTAS DEL SISTEMA (10 Consultas)
// -------------------------------------------------------------------------------------
void SistemaAcademico::menuConsultas() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "                         CONSULTAS DEL SISTEMA ACADEMICO                        \n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1.  Investigador con mayor indice H\n";
        std::cout << "  2.  Investigador con mas citas acumuladas\n";
        std::cout << "  3.  Publicacion que recibio mayor cantidad de citas\n";
        std::cout << "  4.  Revista con mayor factor de impacto\n";
        std::cout << "  5.  Investigador con mas coautores\n";
        std::cout << "  6.  Universidad con mas investigadores registrados\n";
        std::cout << "  7.  Area de investigacion que genera mas publicaciones\n";
        std::cout << "  8.  Ano que tuvo la mayor produccion cientifica\n";
        std::cout << "  9.  Publicacion con mayor cantidad de autores\n";
        std::cout << "  10. Investigador con mas articulos en revistas Q1\n";
        std::cout << "  11. Ejecutar TODAS las consultas de forma integral\n";
        std::cout << "  0.  Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una consulta [0-11]: ");

        switch (op) {
            case 1: GestorConsultas::consulta1_MayorIndiceH(listaInvestigadores, listaPublicaciones); break;
            case 2: GestorConsultas::consulta2_MasCitasAcumuladas(listaInvestigadores, listaPublicaciones); break;
            case 3: GestorConsultas::consulta3_PublicacionMasCitada(listaPublicaciones); break;
            case 4: GestorConsultas::consulta4_RevistaMayorImpacto(listaRevistas); break;
            case 5: GestorConsultas::consulta5_InvestigadorMasCoautores(listaInvestigadores); break;
            case 6: GestorConsultas::consulta6_UniversidadMasInvestigadores(listaUniversidades, listaInvestigadores); break;
            case 7: GestorConsultas::consulta7_AreaMasPublicaciones(listaAreas, listaPublicaciones); break;
            case 8: GestorConsultas::consulta8_AnioMayorProduccion(listaPublicaciones); break;
            case 9: GestorConsultas::consulta9_PublicacionMasAutores(listaPublicaciones); break;
            case 10: GestorConsultas::consulta10_InvestigadorMasArticulosQ1(listaInvestigadores, listaPublicaciones); break;
            case 11:
                GestorConsultas::consulta1_MayorIndiceH(listaInvestigadores, listaPublicaciones);
                GestorConsultas::consulta2_MasCitasAcumuladas(listaInvestigadores, listaPublicaciones);
                GestorConsultas::consulta3_PublicacionMasCitada(listaPublicaciones);
                GestorConsultas::consulta4_RevistaMayorImpacto(listaRevistas);
                GestorConsultas::consulta5_InvestigadorMasCoautores(listaInvestigadores);
                GestorConsultas::consulta6_UniversidadMasInvestigadores(listaUniversidades, listaInvestigadores);
                GestorConsultas::consulta7_AreaMasPublicaciones(listaAreas, listaPublicaciones);
                GestorConsultas::consulta8_AnioMayorProduccion(listaPublicaciones);
                GestorConsultas::consulta9_PublicacionMasAutores(listaPublicaciones);
                GestorConsultas::consulta10_InvestigadorMasArticulosQ1(listaInvestigadores, listaPublicaciones);
                break;
            case 0: break;
            default: std::cout << "  [ERROR] Opcion invalida.\n"; break;
        }
    } while (op != 0);
}

// -------------------------------------------------------------------------------------
// REPORTES DEL SISTEMA (9 Reportes)
// -------------------------------------------------------------------------------------
void SistemaAcademico::menuReportes() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "                          REPORTES DEL SISTEMA ACADEMICO                        \n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1. Mostrar todos los investigadores con sus publicaciones\n";
        std::cout << "  2. Mostrar publicaciones ordenadas por ano ascendente (Lista Circular)\n";
        std::cout << "  3. Mostrar publicaciones ordenadas por cantidad de citas descendente\n";
        std::cout << "  4. Mostrar todas las revistas y sus factores de impacto\n";
        std::cout << "  5. Imprimir la red de coautoria de un investigador especifico\n";
        std::cout << "  6. Mostrar todas las publicaciones de una revista indicada\n";
        std::cout << "  7. Mostrar todas las publicaciones de un area determinada\n";
        std::cout << "  8. Mostrar los investigadores agrupados por universidad\n";
        std::cout << "  9. Mostrar los investigadores ordenados por indice H\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione un reporte [0-9]: ");

        switch (op) {
            case 1:
                GestorReportes::reporte1_InvestigadoresConPublicaciones(listaInvestigadores, listaPublicaciones);
                break;
            case 2:
                GestorReportes::reporte2_PublicacionesPorAnioAscendente(listaPublicaciones);
                break;
            case 3:
                GestorReportes::reporte3_PublicacionesPorCitasDescendente(listaPublicaciones);
                break;
            case 4:
                GestorReportes::reporte4_RevistasYFactoresImpacto(listaRevistas);
                break;
            case 5: {
                std::string idInv = leerLinea("Ingrese el ID del investigador (ej. INV01, INV03): ");
                GestorReportes::reporte5_RedCoautoriaInvestigador(listaInvestigadores, idInv);
                break;
            }
            case 6: {
                std::string idRev = leerLinea("Ingrese el ID o nombre de la revista (ej. REV01, Nature Machine Intelligence): ");
                GestorReportes::reporte6_PublicacionesDeRevista(listaRevistas, listaPublicaciones, idRev);
                break;
            }
            case 7: {
                std::string idArea = leerLinea("Ingrese el ID del area de investigacion (ej. AR01, AR02): ");
                GestorReportes::reporte7_PublicacionesDeArea(listaAreas, listaPublicaciones, idArea);
                break;
            }
            case 8:
                GestorReportes::reporte8_InvestigadoresAgrupadosPorUniversidad(listaUniversidades, listaInvestigadores);
                break;
            case 9:
                GestorReportes::reporte9_InvestigadoresOrdenadosPorIndiceH(listaInvestigadores, listaPublicaciones);
                break;
            case 0: break;
            default: std::cout << "  [ERROR] Opcion invalida.\n"; break;
        }
    } while (op != 0);
}

// -------------------------------------------------------------------------------------
// OTROS MÓDULOS DEL SISTEMA: INVESTIGADORES, UNIVERSIDADES, ÁREAS, REVISTAS, PROYECTOS
// -------------------------------------------------------------------------------------
void SistemaAcademico::menuInvestigadores() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "             GESTION DE INVESTIGADORES (LISTA SIMPLE / COAUTORES)               \n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1. Insertar investigador (al final de la lista simple)\n";
        std::cout << "  2. Buscar investigador por ID\n";
        std::cout << "  3. Modificar investigador (Modificacion en Lista Simple)\n";
        std::cout << "  4. Eliminar investigador (Eliminacion en Lista Simple)\n";
        std::cout << "  5. Mostrar investigadores (resumen tabular)\n";
        std::cout << "  6. Mostrar investigadores con detalle completo de coautores\n";
        std::cout << "  7. Agregar coautor a la red de un investigador\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-7]: ");

        if (op == 1) {
            std::string id = leerLinea("ID del investigador (ej. INV07): ");
            if (listaInvestigadores.existeId(id)) {
                std::cout << "  [ERROR] Ya existe un investigador con ese ID.\n";
                continue;
            }
            std::string nom = leerLinea("Nombre completo: ");
            std::string idUni = leerLinea("ID de la universidad: ");
            NodoUniversidad* uni = listaUniversidades.buscarPorId(idUni);
            std::string pais = leerLinea("Pais: ");
            std::string idArea = leerLinea("ID del area de investigacion: ");
            NodoArea* ar = listaAreas.buscarPorId(idArea);
            std::string email = leerLinea("Correo electronico: ");

            if (listaInvestigadores.insertarAlFinal(id, nom, uni, pais, ar, email)) {
                std::cout << "  [EXITO] Investigador registrado con exito.\n";
            }
        } else if (op == 2) {
            std::string id = leerLinea("Ingrese ID del investigador a buscar: ");
            NodoInvestigador* inv = listaInvestigadores.buscarPorId(id);
            if (inv != nullptr) {
                std::cout << "  [ENCONTRADO] " << inv->nombreCompleto << " | Uni: "
                          << (inv->universidad ? inv->universidad->nombre : "N/A")
                          << " | Area: " << (inv->area ? inv->area->nombre : "N/A")
                          << " | Correo: " << inv->correo << "\n";
            } else {
                std::cout << "  [ERROR] No se encontro el investigador.\n";
            }
        } else if (op == 3) {
            std::string id = leerLinea("ID del investigador a modificar: ");
            NodoInvestigador* inv = listaInvestigadores.buscarPorId(id);
            if (inv == nullptr) {
                std::cout << "  [ERROR] No se encontro el investigador.\n";
                continue;
            }
            std::string nuevoNom = leerLinea("Nuevo nombre [" + inv->nombreCompleto + "]: ");
            std::string nuevoPais = leerLinea("Nuevo pais [" + inv->pais + "]: ");
            std::string nuevoCorreo = leerLinea("Nuevo correo [" + inv->correo + "]: ");
            if (listaInvestigadores.modificar(id, nuevoNom, inv->universidad, nuevoPais, inv->area, nuevoCorreo)) {
                std::cout << "  [EXITO] Investigador modificado exitosamente.\n";
            }
        } else if (op == 4) {
            std::string id = leerLinea("ID del investigador a eliminar (Lista Simple): ");
            if (listaInvestigadores.eliminar(id)) {
                std::cout << "  [EXITO] Investigador eliminado de la lista simple.\n";
            } else {
                std::cout << "  [ERROR] No se encontro el investigador con ID: " << id << "\n";
            }
        } else if (op == 5) {
            listaInvestigadores.mostrar();
        } else if (op == 6) {
            listaInvestigadores.mostrarConDetalles();
        } else if (op == 7) {
            std::string idInv = leerLinea("ID del investigador: ");
            NodoInvestigador* inv = listaInvestigadores.buscarPorId(idInv);
            if (inv == nullptr) {
                std::cout << "  [ERROR] Investigador no encontrado.\n";
                continue;
            }
            std::string idCo = leerLinea("ID del coautor (ej. CO14): ");
            std::string nomCo = leerLinea("Nombre del coautor: ");
            std::string uniCo = leerLinea("Universidad del coautor: ");
            int pubC = leerEntero("Cantidad de publicaciones conjuntas: ");
            if (inv->sublistaCoautores.insertar(idCo, nomCo, uniCo, pubC)) {
                std::cout << "  [EXITO] Coautor agregado a la red de " << inv->nombreCompleto << ".\n";
            }
        }
    } while (op != 0);
}

void SistemaAcademico::menuUniversidades() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "                   GESTION DE UNIVERSIDADES (LISTA DOBLE)                       \n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1. Insertar universidad\n";
        std::cout << "  2. Buscar universidad por ID\n";
        std::cout << "  3. Modificar universidad\n";
        std::cout << "  4. Eliminar universidad (Lista Doble)\n";
        std::cout << "  5. Mostrar universidades\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-5]: ");

        if (op == 1) {
            std::string id = leerLinea("ID de la universidad (ej. U07): ");
            std::string nom = leerLinea("Nombre de la universidad: ");
            std::string pais = leerLinea("Pais: ");
            int rank = leerEntero("Ranking global: ");
            if (listaUniversidades.insertar(id, nom, pais, rank)) {
                std::cout << "  [EXITO] Universidad registrada correctamente en la lista doble.\n";
            }
        } else if (op == 2) {
            std::string id = leerLinea("ID de la universidad a buscar: ");
            NodoUniversidad* u = listaUniversidades.buscarPorId(id);
            if (u != nullptr) {
                std::cout << "  [ENCONTRADA] " << u->nombre << " (" << u->pais << ") - Ranking #" << u->ranking << "\n";
            } else {
                std::cout << "  [ERROR] No se encontro universidad con ID: " << id << "\n";
            }
        } else if (op == 3) {
            std::string id = leerLinea("ID de la universidad a modificar: ");
            NodoUniversidad* u = listaUniversidades.buscarPorId(id);
            if (u == nullptr) {
                std::cout << "  [ERROR] No se encontro la universidad.\n";
                continue;
            }
            std::string nuevoNom = leerLinea("Nuevo nombre [" + u->nombre + "]: ");
            std::string nuevoPais = leerLinea("Nuevo pais [" + u->pais + "]: ");
            int nuevoRank = leerEntero("Nuevo ranking (" + std::to_string(u->ranking) + "): ");
            if (listaUniversidades.modificar(id, nuevoNom, nuevoPais, nuevoRank)) {
                std::cout << "  [EXITO] Universidad modificada con exito.\n";
            }
        } else if (op == 4) {
            std::string id = leerLinea("ID de la universidad a eliminar (Lista Doble): ");
            if (listaUniversidades.eliminar(id)) {
                std::cout << "  [EXITO] Universidad eliminada de la lista doble.\n";
            } else {
                std::cout << "  [ERROR] No se encontro la universidad con ID: " << id << "\n";
            }
        } else if (op == 5) {
            listaUniversidades.mostrar();
        }
    } while (op != 0);
}

void SistemaAcademico::menuAreas() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "             GESTION DE AREAS DE INVESTIGACION (LISTA SIMPLE)                   \n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1. Insertar area (al final)\n";
        std::cout << "  2. Buscar area por ID\n";
        std::cout << "  3. Modificar area\n";
        std::cout << "  4. Eliminar area\n";
        std::cout << "  5. Mostrar todas las areas\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-5]: ");

        if (op == 1) {
            std::string id = leerLinea("ID del area (ej. AR07): ");
            std::string nom = leerLinea("Nombre del area: ");
            std::string desc = leerLinea("Descripcion: ");
            if (listaAreas.insertarAlFinal(id, nom, desc)) {
                std::cout << "  [EXITO] Area insertada al final de la lista simple.\n";
            }
        } else if (op == 2) {
            std::string id = leerLinea("ID del area a buscar: ");
            NodoArea* a = listaAreas.buscarPorId(id);
            if (a != nullptr) {
                std::cout << "  [ENCONTRADA] " << a->nombre << ": " << a->descripcion << "\n";
            } else {
                std::cout << "  [ERROR] No se encontro area con ID: " << id << "\n";
            }
        } else if (op == 3) {
            std::string id = leerLinea("ID del area a modificar: ");
            NodoArea* a = listaAreas.buscarPorId(id);
            if (a == nullptr) {
                std::cout << "  [ERROR] No se encontro el area.\n";
                continue;
            }
            std::string nuevoNom = leerLinea("Nuevo nombre [" + a->nombre + "]: ");
            std::string nuevaDesc = leerLinea("Nueva descripcion: ");
            if (listaAreas.modificar(id, nuevoNom, nuevaDesc)) {
                std::cout << "  [EXITO] Area modificada con exito.\n";
            }
        } else if (op == 4) {
            std::string id = leerLinea("ID del area a eliminar: ");
            if (listaAreas.eliminar(id)) {
                std::cout << "  [EXITO] Area eliminada correctamente.\n";
            } else {
                std::cout << "  [ERROR] No se encontro el area con ID: " << id << "\n";
            }
        } else if (op == 5) {
            listaAreas.mostrar();
        }
    } while (op != 0);
}

void SistemaAcademico::menuRevistas() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "           GESTION DE REVISTAS CIENTIFICAS (LISTA SIMPLE ORDENADA)              \n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1. Insertar revista (ordenada alfabeticamente por nombre)\n";
        std::cout << "  2. Buscar revista por ID\n";
        std::cout << "  3. Buscar revista por nombre\n";
        std::cout << "  4. Modificar revista\n";
        std::cout << "  5. Eliminar revista\n";
        std::cout << "  6. Mostrar todas las revistas\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-6]: ");

        if (op == 1) {
            std::string id = leerLinea("ID de la revista (ej. REV08): ");
            std::string nom = leerLinea("Nombre de la revista: ");
            std::string ed = leerLinea("Editorial: ");
            std::string pais = leerLinea("Pais: ");
            double fi = leerDouble("Factor de impacto (ej. 12.5): ");
            std::string q = leerLinea("Cuartil (Q1, Q2, Q3, Q4): ");
            if (listaRevistas.insertarOrdenado(id, nom, ed, pais, fi, q)) {
                std::cout << "  [EXITO] Revista insertada en orden alfabetico en la lista simple.\n";
            }
        } else if (op == 2) {
            std::string id = leerLinea("ID de la revista a buscar: ");
            NodoRevista* r = listaRevistas.buscarPorId(id);
            if (r != nullptr) {
                std::cout << "  [ENCONTRADA] " << r->nombre << " | Editorial: " << r->editorial
                          << " | FI: " << r->factorImpacto << " | Cuartil: " << r->cuartil << "\n";
            } else {
                std::cout << "  [ERROR] No se encontro la revista con ID: " << id << "\n";
            }
        } else if (op == 3) {
            std::string nom = leerLinea("Nombre de la revista a buscar: ");
            NodoRevista* r = listaRevistas.buscarPorNombre(nom);
            if (r != nullptr) {
                std::cout << "  [ENCONTRADA] ID: " << r->idRevista << " | " << r->nombre
                          << " | FI: " << r->factorImpacto << " | Cuartil: " << r->cuartil << "\n";
            } else {
                std::cout << "  [ERROR] No se encontro la revista con ese nombre.\n";
            }
        } else if (op == 4) {
            std::string id = leerLinea("ID de la revista a modificar: ");
            NodoRevista* r = listaRevistas.buscarPorId(id);
            if (r == nullptr) {
                std::cout << "  [ERROR] No se encontro la revista.\n";
                continue;
            }
            std::string nuevoNom = leerLinea("Nuevo nombre [" + r->nombre + "]: ");
            std::string nuevaEd = leerLinea("Nueva editorial [" + r->editorial + "]: ");
            std::string nuevoPais = leerLinea("Nuevo pais [" + r->pais + "]: ");
            double nuevoFI = leerDouble("Nuevo factor de impacto (" + std::to_string(r->factorImpacto) + "): ");
            std::string nuevoQ = leerLinea("Nuevo cuartil [" + r->cuartil + "]: ");
            if (listaRevistas.modificar(id, nuevoNom, nuevaEd, nuevoPais, nuevoFI, nuevoQ)) {
                std::cout << "  [EXITO] Revista modificada con exito.\n";
            }
        } else if (op == 5) {
            std::string id = leerLinea("ID de la revista a eliminar: ");
            if (listaRevistas.eliminar(id)) {
                std::cout << "  [EXITO] Revista eliminada correctamente.\n";
            } else {
                std::cout << "  [ERROR] No se encontro la revista con ID: " << id << "\n";
            }
        } else if (op == 6) {
            listaRevistas.mostrar();
        }
    } while (op != 0);
}

void SistemaAcademico::menuProyectos() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "         GESTION DE PROYECTOS DE INVESTIGACION (LISTA DOBLE ORDENADA)           \n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1. Insertar proyecto (ordenado por ano de inicio en lista doble)\n";
        std::cout << "  2. Buscar proyecto por ID\n";
        std::cout << "  3. Modificar proyecto (Modificacion en Lista Doble)\n";
        std::cout << "  4. Eliminar proyecto (Eliminacion en Lista Doble)\n";
        std::cout << "  5. Mostrar todos los proyectos\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-5]: ");

        if (op == 1) {
            std::string id = leerLinea("ID del proyecto (ej. PRY07): ");
            std::string nom = leerLinea("Nombre del proyecto: ");
            double fin = leerDouble("Financiamiento (USD): ");
            int aIni = leerEntero("Ano de inicio: ");
            int aFin = leerEntero("Ano de finalizacion: ");
            std::string idResp = leerLinea("ID del investigador responsable: ");
            NodoInvestigador* resp = listaInvestigadores.buscarPorId(idResp);
            if (listaProyectos.insertarOrdenadoPorAnio(id, nom, fin, aIni, aFin, resp)) {
                std::cout << "  [EXITO] Proyecto insertado en orden cronologico en la lista doble.\n";
            }
        } else if (op == 2) {
            std::string id = leerLinea("ID del proyecto a buscar: ");
            NodoProyecto* p = listaProyectos.buscarPorId(id);
            if (p != nullptr) {
                std::cout << "  [ENCONTRADO] " << p->nombre << " (" << p->anioInicio << "-" << p->anioFin << ")\n";
                std::cout << "  Financiamiento: $" << p->financiamiento
                          << " | Responsable: " << (p->investigadorResponsable ? p->investigadorResponsable->nombreCompleto : "N/A") << "\n";
            } else {
                std::cout << "  [ERROR] No se encontro el proyecto con ID: " << id << "\n";
            }
        } else if (op == 3) {
            std::string id = leerLinea("ID del proyecto a modificar: ");
            NodoProyecto* p = listaProyectos.buscarPorId(id);
            if (p == nullptr) {
                std::cout << "  [ERROR] No se encontro el proyecto.\n";
                continue;
            }
            std::string nuevoNom = leerLinea("Nuevo nombre [" + p->nombre + "]: ");
            double nuevoFin = leerDouble("Nuevo financiamiento: ");
            int nuevoAIni = leerEntero("Nuevo ano inicio: ");
            int nuevoAFin = leerEntero("Nuevo ano fin: ");
            if (listaProyectos.modificar(id, nuevoNom, nuevoFin, nuevoAIni, nuevoAFin, p->investigadorResponsable)) {
                std::cout << "  [EXITO] Proyecto modificado correctamente.\n";
            }
        } else if (op == 4) {
            std::string id = leerLinea("ID del proyecto a eliminar (Lista Doble): ");
            if (listaProyectos.eliminar(id)) {
                std::cout << "  [EXITO] Proyecto eliminado de la lista doble exitosamente.\n";
            } else {
                std::cout << "  [ERROR] No se encontro el proyecto con ID: " << id << "\n";
            }
        } else if (op == 5) {
            listaProyectos.mostrar();
        }
    } while (op != 0);
}

// -------------------------------------------------------------------------------------
// GESTION DE REVISTAS Y PROYECTOS
// -------------------------------------------------------------------------------------
void SistemaAcademico::menu() {
    int op = -1;
    do {
        std::cout << "\n================================================================================\n";
        std::cout << "                 MODULO DE REVISTAS Y PROYECTOS                   \n";
        std::cout << "================================================================================\n";
        std::cout << "  [1]  Gestion de Revistas Cientificas (Lista Simple Ordenada por Nombre)\n";
        std::cout << "  [2]  Gestion de Proyectos de Investigacion (Lista Doble Ordenada por Fecha)\n";
        std::cout << "  [3]  Relacion: Ver publicaciones de una Revista indicada (Reporte 6)\n";
        std::cout << "  [4]  Relacion: Ver publicaciones asociadas a un Proyecto indicado\n";
        std::cout << "  [5]  Relacion: Ver proyectos asociados a su Investigador Responsable\n";
        std::cout << "  [6]  Consulta P2 (No. 4): Revista con mayor factor de impacto\n";
        std::cout << "  [7]  Consulta P2 (No. 8): Ano con mayor produccion cientifica\n";
        std::cout << "  [8]  Consulta P2 (No. 10): Investigador con mas articulos en revistas Q1\n";
        std::cout << "  [9]  Reporte P2 (No. 2): Publicaciones ordenadas por ano ascendente\n";
        std::cout << "  [10] Reporte P2 (No. 4): Mostrar todas las revistas y sus factores de impacto\n";
        std::cout << "  [11] Reporte P2 (No. 7): Mostrar todas las publicaciones de un area\n";
        std::cout << "  [0]  Volver al menu principal\n";
        std::cout << "================================================================================\n";
        op = leerEntero("Seleccione una opcion [0-11]: ");

        switch (op) {
            case 1: menuRevistas(); break;
            case 2: menuProyectos(); break;
            case 3: {
                std::string rev = leerLinea("Ingrese ID o nombre de la revista (ej. REV01, Nature Machine Intelligence): ");
                GestorReportes::reporte6_PublicacionesDeRevista(listaRevistas, listaPublicaciones, rev);
                break;
            }
            case 4: {
                std::string idProy = leerLinea("Ingrese ID del proyecto (ej. PRY01, PRY02): ");
                listaPublicaciones.mostrarPublicacionesDeProyecto(idProy);
                break;
            }
            case 5: {
                std::cout << "\n--- PROYECTOS Y SUS INVESTIGADORES RESPONSABLES ---\n";
                listaProyectos.mostrar();
                break;
            }
            case 6: GestorConsultas::consulta4_RevistaMayorImpacto(listaRevistas); break;
            case 7: GestorConsultas::consulta8_AnioMayorProduccion(listaPublicaciones); break;
            case 8: GestorConsultas::consulta10_InvestigadorMasArticulosQ1(listaInvestigadores, listaPublicaciones); break;
            case 9: GestorReportes::reporte2_PublicacionesPorAnioAscendente(listaPublicaciones); break;
            case 10: GestorReportes::reporte4_RevistasYFactoresImpacto(listaRevistas); break;
            case 11: {
                std::string idArea = leerLinea("Ingrese ID del area de investigacion (ej. AR01, AR02): ");
                GestorReportes::reporte7_PublicacionesDeArea(listaAreas, listaPublicaciones, idArea);
                break;
            }
            case 0: break;
            default: std::cout << "  [ERROR] Opcion invalida.\n"; break;
        }
    } while (op != 0);
}

// ==================== PROGRAMA PRINCIPAL ====================



int main() {
    // Configurar salida de consola de Windows

    std::cout << "================================================================================\n";
    std::cout << "                 INSTITUTO TECNOLOGICO DE COSTA RICA                            \n";
    std::cout << "               CURSO IC2001 - ESTRUCTURAS DE DATOS                              \n";
    std::cout << "                   PROF. LORENA VALERIO SOLIS                                   \n";
    std::cout << "  SISTEMA DE GESTION DE PRODUCCION CIENTIFICA Y METRICAS ACADEMICAS\n";
    std::cout << "================================================================================\n";
    std::cout << "PROYECTO INTEGRADO  \n";
    std::cout << "================================================================================\n\n";

    SistemaAcademico sistema;
    sistema.menuPrincipal();

    return 0;
}
