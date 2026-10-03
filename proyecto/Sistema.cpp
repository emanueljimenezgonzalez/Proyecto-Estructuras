#include "Sistema.h"
#include "Metricas.h"
#include "Consultas.h"
#include "Reportes.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

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

void SistemaAcademico::sincronizar() {
    MetricasAcademicas::actualizarIndicesHTodos(listaInvestigadores, listaPublicaciones);
    listaPublicaciones.actualizarEnlaces(listaInvestigadores, listaRevistas);
}

void SistemaAcademico::limpiarReferenciasInvestigador(NodoInvestigador* inv) {
    NodoProyecto* proy = listaProyectos.getCabeza();
    while (proy != nullptr) {
        if (proy->investigadorResponsable == inv) proy->investigadorResponsable = nullptr;
        proy = proy->siguiente;
    }
    if (listaPublicaciones.getCabeza() == nullptr) return;
    NodoPublicacion* pub = listaPublicaciones.getCabeza();
    do {
        if (pub->investigadorPrincipal == inv) pub->investigadorPrincipal = nullptr;
        NodoCitacion* c = pub->sublistaCitaciones.getCabeza();
        while (c != nullptr) {
            if (c->autorCitante == inv) c->autorCitante = nullptr;
            c = c->siguiente;
        }
        pub = pub->siguiente;
    } while (pub != listaPublicaciones.getCabeza());
}

void SistemaAcademico::limpiarReferenciasUniversidad(NodoUniversidad* uni) {
    NodoInvestigador* inv = listaInvestigadores.getCabeza();
    while (inv != nullptr) {
        if (inv->universidad == uni) inv->universidad = nullptr;
        NodoCoautor* co = inv->sublistaCoautores.getCabeza();
        while (co != nullptr) {
            if (co->universidad == uni) co->universidad = nullptr;
            co = co->siguiente;
        }
        inv = inv->siguiente;
    }
    if (listaPublicaciones.getCabeza() == nullptr) return;
    NodoPublicacion* pub = listaPublicaciones.getCabeza();
    do {
        NodoCoautor* co = pub->sublistaCoautores.getCabeza();
        while (co != nullptr) {
            if (co->universidad == uni) co->universidad = nullptr;
            co = co->siguiente;
        }
        pub = pub->siguiente;
    } while (pub != listaPublicaciones.getCabeza());
}

void SistemaAcademico::limpiarReferenciasArea(NodoArea* ar) {
    NodoInvestigador* inv = listaInvestigadores.getCabeza();
    while (inv != nullptr) {
        if (inv->area == ar) inv->area = nullptr;
        inv = inv->siguiente;
    }
}

void SistemaAcademico::limpiarReferenciasRevista(NodoRevista* rev) {
    if (listaPublicaciones.getCabeza() == nullptr) return;
    NodoPublicacion* pub = listaPublicaciones.getCabeza();
    do {
        if (pub->revista == rev) pub->revista = nullptr;
        pub = pub->siguiente;
    } while (pub != listaPublicaciones.getCabeza());
}

void SistemaAcademico::limpiarReferenciasProyecto(NodoProyecto* proy) {
    if (listaPublicaciones.getCabeza() == nullptr) return;
    NodoPublicacion* pub = listaPublicaciones.getCabeza();
    do {
        if (pub->proyecto == proy) pub->proyecto = nullptr;
        pub = pub->siguiente;
    } while (pub != listaPublicaciones.getCabeza());
}

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
        inv1->sublistaCoautores.insertar("101", "Luis Solis", uUcr, 3);
        inv1->sublistaCoautores.insertar("102", "Sara Mora", uTec, 5);
    }
    if (inv3) {
        inv3->sublistaCoautores.insertar("103", "Pedro Picapiedra", listaUniversidades.buscarPorId("3"), 2);
        inv3->sublistaCoautores.insertar("104", "Rocio Perez", uTec, 4);
        inv3->sublistaCoautores.insertar("105", "Marta Vega", uMit, 1);
    }
    if (inv5) {
        inv5->sublistaCoautores.insertar("106", "Albert Einstein", listaUniversidades.buscarPorId("5"), 10);
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

    listaPublicaciones.agregarCitaAPublicacion("PUB01", "CIT01", 2021, listaPublicaciones.buscarPorId("PUB02"), inv2);
    listaPublicaciones.agregarCitaAPublicacion("PUB01", "CIT02", 2022, listaPublicaciones.buscarPorId("PUB05"), inv3);
    listaPublicaciones.agregarCitaAPublicacion("PUB02", "CIT03", 2021, listaPublicaciones.buscarPorId("PUB03"), inv2);
    listaPublicaciones.agregarCitaAPublicacion("PUB03", "CIT04", 2022, listaPublicaciones.buscarPorId("PUB04"), inv4);
    listaPublicaciones.agregarCitaAPublicacion("PUB03", "CIT05", 2023, listaPublicaciones.buscarPorId("PUB05"), inv3);
    listaPublicaciones.agregarCitaAPublicacion("PUB05", "CIT06", 2023, listaPublicaciones.buscarPorId("PUB06"), inv4);
    listaPublicaciones.agregarCitaAPublicacion("PUB06", "CIT07", 2023, listaPublicaciones.buscarPorId("PUB07"), inv5);
    listaPublicaciones.agregarCitaAPublicacion("PUB06", "CIT08", 2024, listaPublicaciones.buscarPorId("PUB08"), inv1);
    listaPublicaciones.agregarCitaAPublicacion("PUB07", "CIT09", 2024, listaPublicaciones.buscarPorId("PUB09"), inv2);
    listaPublicaciones.agregarCitaAPublicacion("PUB08", "CIT10", 2024, listaPublicaciones.buscarPorId("PUB10"), inv5);
    listaPublicaciones.agregarCitaAPublicacion("PUB09", "CIT11", 2025, listaPublicaciones.buscarPorId("PUB11"), inv3);
    listaPublicaciones.agregarCitaAPublicacion("PUB10", "CIT12", 2025, listaPublicaciones.buscarPorId("PUB12"), inv4);
    listaPublicaciones.agregarCitaAPublicacion("PUB11", "CIT13", 2025, listaPublicaciones.buscarPorId("PUB01"), inv1);
    listaPublicaciones.agregarCitaAPublicacion("PUB12", "CIT14", 2026, listaPublicaciones.buscarPorId("PUB02"), inv2);

    // Calculo de H a partir de las publicaciones, en lugar de dejarlo fijo.
    sincronizar();

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
        std::cout << "  8. Buscar coautor dentro de una publicacion\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-8]: ");

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
                sincronizar();
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
            std::cout << "  (Deje los textos vacios y escriba -1 en los numeros para conservar el valor actual)\n";
            std::string nuevoTit = leerLinea("Nuevo titulo [" + p->titulo + "]: ");
            int nuevoAnio = leerEntero("Nuevo ano (" + std::to_string(p->anio) + "): ");
            std::string nuevoTipo = leerLinea("Nuevo tipo [" + p->tipo + "]: ");
            int nuevasCitas = leerEntero("Nuevas citas (" + std::to_string(p->cantidadCitas) + "): ");
            std::string nuevoDoi = leerLinea("Nuevo DOI [" + p->doi + "]: ");

            if (listaPublicaciones.modificar(id, nuevoTit, nuevoAnio, nuevoTipo, nuevasCitas, nuevoDoi,
                                             p->investigadorPrincipal, p->revista, p->proyecto)) {
                std::cout << "  [EXITO] Publicacion modificada exitosamente.\n";
                sincronizar();
            }
        } else if (op == 4) {
            std::string id = leerLinea("Ingrese ID de la publicacion a eliminar (Lista Circular): ");
            if (listaPublicaciones.eliminar(id)) {
                std::cout << "  [EXITO] Publicacion eliminada de la lista circular correctamente.\n";
                sincronizar();
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
        } else if (op == 8) {
            std::string idPub = leerLinea("ID de la publicacion: ");
            NodoPublicacion* pub = listaPublicaciones.buscarPorId(idPub);
            if (pub == nullptr) {
                std::cout << "  [ERROR] Publicacion no encontrada.\n";
                continue;
            }
            std::string idCo = leerLinea("ID del coautor a buscar: ");
            NodoCoautor* co = pub->sublistaCoautores.buscarPorId(idCo);
            if (co != nullptr) {
                std::cout << "  [ENCONTRADO] " << co->nombre << " | Universidad: "
                          << (co->universidad ? co->universidad->nombre : "N/A")
                          << " | Pub. conjuntas: " << co->publicacionesConjuntas << "\n";
            } else {
                std::cout << "  [ERROR] Ese coautor no esta asociado a la publicacion.\n";
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
            std::string idCita = leerLinea("ID de la cita (ej. CIT15): ");
            int anio = leerEntero("Ano de la citacion: ");
            std::string idPubCit = leerLinea("ID de la publicacion citante: ");
            NodoPublicacion* pubCit = listaPublicaciones.buscarPorId(idPubCit);
            if (pubCit == nullptr) {
                std::cout << "  [AVISO] No se encontro la publicacion citante. Se asignara nullptr.\n";
            }
            std::string idAutCit = leerLinea("ID del investigador citante: ");
            NodoInvestigador* autCit = listaInvestigadores.buscarPorId(idAutCit);
            if (autCit == nullptr) {
                std::cout << "  [AVISO] No se encontro el investigador citante. Se asignara nullptr.\n";
            }

            if (listaPublicaciones.agregarCitaAPublicacion(idPub, idCita, anio, pubCit, autCit)) {
                std::cout << "  [EXITO] Citacion agregada exitosamente a la sublista de " << idPub << ".\n";
                sincronizar();
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
                          << (c->publicacionCitante ? c->publicacionCitante->titulo : "N/A") << "\" por "
                          << (c->autorCitante ? c->autorCitante->nombreCompleto : "N/A") << "\n";
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
            int nuevoAnio = leerEntero("Nuevo ano (-1 conserva): ");
            std::string idNuevaPub = leerLinea("ID de la nueva publicacion citante (vacio para conservar): ");
            NodoPublicacion* nuevaPub = idNuevaPub.empty() ? nullptr : listaPublicaciones.buscarPorId(idNuevaPub);
            std::string idNuevoAut = leerLinea("ID del nuevo investigador citante (vacio para conservar): ");
            NodoInvestigador* nuevoAut = idNuevoAut.empty() ? nullptr : listaInvestigadores.buscarPorId(idNuevoAut);
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
                sincronizar();
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
            std::string idInv = leerLinea("Ingrese ID del investigador (ej. 1): ");
            NodoInvestigador* inv = listaInvestigadores.buscarPorId(idInv);
            if (inv != nullptr) {
                MetricasAcademicas::mostrarMetricasInvestigador(inv, listaPublicaciones);
            } else {
                std::cout << "  [ERROR] Investigador no encontrado con ID: " << idInv << "\n";
            }
        } else if (op == 2) {
            MetricasAcademicas::mostrarTodasLasMetricas(listaInvestigadores, listaPublicaciones);
        } else if (op == 3) {
            sincronizar();
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
                std::string idInv = leerLinea("Ingrese el ID del investigador (ej. 1, 3): ");
                GestorReportes::reporte5_RedCoautoriaInvestigador(listaInvestigadores, idInv);
                break;
            }
            case 6: {
                std::string idRev = leerLinea("Ingrese el ID o nombre de la revista (ej. REV01, Nature Machine Intelligence): ");
                GestorReportes::reporte6_PublicacionesDeRevista(listaRevistas, listaPublicaciones, idRev);
                break;
            }
            case 7: {
                std::string idArea = leerLinea("Ingrese el ID del area de investigacion (ej. 1, 2): ");
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
        std::cout << "  8. Buscar coautor en la red de un investigador\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-8]: ");

        if (op == 1) {
            std::string id = leerLinea("ID del investigador (ej. 6): ");
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
            NodoInvestigador* invDel = listaInvestigadores.buscarPorId(id);
            if (invDel != nullptr) limpiarReferenciasInvestigador(invDel);
            if (listaInvestigadores.eliminar(id)) {
                sincronizar();
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
            std::string idCo = leerLinea("ID del coautor (ej. 107): ");
            std::string nomCo = leerLinea("Nombre del coautor: ");
            std::string idUniCo = leerLinea("ID de la universidad del coautor: ");
            NodoUniversidad* uniCo = listaUniversidades.buscarPorId(idUniCo);
            int pubC = leerEntero("Cantidad de publicaciones conjuntas: ");
            if (inv->sublistaCoautores.insertar(idCo, nomCo, uniCo, pubC)) {
                std::cout << "  [EXITO] Coautor agregado a la red de " << inv->nombreCompleto << ".\n";
            }
        } else if (op == 8) {
            std::string idInv = leerLinea("ID del investigador: ");
            NodoInvestigador* inv = listaInvestigadores.buscarPorId(idInv);
            if (inv == nullptr) {
                std::cout << "  [ERROR] Investigador no encontrado.\n";
                continue;
            }
            std::string idCo = leerLinea("ID del coautor a buscar: ");
            NodoCoautor* co = inv->sublistaCoautores.buscarPorId(idCo);
            if (co != nullptr) {
                std::cout << "  [ENCONTRADO] " << co->nombre << " | Universidad: "
                          << (co->universidad ? co->universidad->nombre : "N/A")
                          << " | Pub. conjuntas: " << co->publicacionesConjuntas << "\n";
            } else {
                std::cout << "  [ERROR] Ese coautor no esta en la red del investigador.\n";
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
            std::string id = leerLinea("ID de la universidad (ej. 6): ");
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
            int nuevoRank = leerEntero("Nuevo ranking (-1 conserva) [" + std::to_string(u->ranking) + "]: ");
            if (listaUniversidades.modificar(id, nuevoNom, nuevoPais, nuevoRank)) {
                std::cout << "  [EXITO] Universidad modificada con exito.\n";
            }
        } else if (op == 4) {
            std::string id = leerLinea("ID de la universidad a eliminar (Lista Doble): ");
            NodoUniversidad* uniDel = listaUniversidades.buscarPorId(id);
            if (uniDel != nullptr) limpiarReferenciasUniversidad(uniDel);
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
            std::string id = leerLinea("ID del area (ej. 6): ");
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
            NodoArea* areaDel = listaAreas.buscarPorId(id);
            if (areaDel != nullptr) limpiarReferenciasArea(areaDel);
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
                std::cout << "  Publicacion enlazada: " << (r->publicacion ? r->publicacion->titulo : "Ninguna") << "\n";
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
            double nuevoFI = leerDouble("Nuevo factor de impacto (-1 conserva) [" + std::to_string(r->factorImpacto) + "]: ");
            std::string nuevoQ = leerLinea("Nuevo cuartil [" + r->cuartil + "]: ");
            if (listaRevistas.modificar(id, nuevoNom, nuevaEd, nuevoPais, nuevoFI, nuevoQ)) {
                std::cout << "  [EXITO] Revista modificada con exito.\n";
            }
        } else if (op == 5) {
            std::string id = leerLinea("ID de la revista a eliminar: ");
            NodoRevista* revDel = listaRevistas.buscarPorId(id);
            if (revDel != nullptr) limpiarReferenciasRevista(revDel);
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
            double nuevoFin = leerDouble("Nuevo financiamiento (-1 conserva): ");
            int nuevoAIni = leerEntero("Nuevo ano inicio (-1 conserva): ");
            int nuevoAFin = leerEntero("Nuevo ano fin (-1 conserva): ");
            if (listaProyectos.modificar(id, nuevoNom, nuevoFin, nuevoAIni, nuevoAFin, p->investigadorResponsable)) {
                std::cout << "  [EXITO] Proyecto modificado correctamente.\n";
            }
        } else if (op == 4) {
            std::string id = leerLinea("ID del proyecto a eliminar (Lista Doble): ");
            NodoProyecto* proyDel = listaProyectos.buscarPorId(id);
            if (proyDel != nullptr) limpiarReferenciasProyecto(proyDel);
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
                std::string idArea = leerLinea("Ingrese ID del area de investigacion (ej. 1, 2): ");
                GestorReportes::reporte7_PublicacionesDeArea(listaAreas, listaPublicaciones, idArea);
                break;
            }
            case 0: break;
            default: std::cout << "  [ERROR] Opcion invalida.\n"; break;
        }
    } while (op != 0);
}
