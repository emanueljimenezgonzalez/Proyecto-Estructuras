#include "Sistema.h"
#include <iostream>
#include <iomanip>
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

void SistemaAcademico::precargarDatos() {
    std::cout << "[SISTEMA] Iniciando precarga de datos academicos...\n";

    // 1. Precarga de Áreas de Investigación (Lista Simple, mínimo 5 -> 6 registros)
    listaAreas.insertarAlFinal("AR01", "Inteligencia Artificial", "Modelos de aprendizaje profundo, agentes autonomos y NLP.");
    listaAreas.insertarAlFinal("AR02", "Bioinformatica", "Algoritmos para analisis genomico y biologia computacional.");
    listaAreas.insertarAlFinal("AR03", "Ciberseguridad", "Criptografia aplicada, seguridad en redes y protocolos robustos.");
    listaAreas.insertarAlFinal("AR04", "Robotica y Autonomia", "Percepcion visual, navegacion de robots y control cinematico.");
    listaAreas.insertarAlFinal("AR05", "Ciencia de Datos", "Mineria de datos, analitica predictiva y big data.");
    listaAreas.insertarAlFinal("AR06", "Ingenieria de Software", "Arquitectura de sistemas complejos, grafos y algoritmos eficientes.");

    // 2. Precarga de Universidades (Lista Doble, mínimo 5 -> 6 registros)
    listaUniversidades.insertar("U01", "Instituto Tecnologico de CR", "Costa Rica", 1);
    listaUniversidades.insertar("U02", "Universidad de Costa Rica", "Costa Rica", 2);
    listaUniversidades.insertar("U03", "Massachusetts Inst. of Tech.", "Estados Unidos", 1);
    listaUniversidades.insertar("U04", "Stanford University", "Estados Unidos", 3);
    listaUniversidades.insertar("U05", "University of Oxford", "Reino Unido", 4);
    listaUniversidades.insertar("U06", "Universidad de Buenos Aires", "Argentina", 67);

    // 3. Precarga de Revistas Científicas (Lista Simple Ordenada por Nombre, mínimo 5 -> 7 registros)
    listaRevistas.insertarOrdenado("REV01", "Nature Machine Intelligence", "Nature Publishing", "Reino Unido", 25.898, "Q1");
    listaRevistas.insertarOrdenado("REV02", "IEEE Trans. Pattern Analysis", "IEEE", "Estados Unidos", 23.600, "Q1");
    listaRevistas.insertarOrdenado("REV03", "Science", "AAAS", "Estados Unidos", 44.700, "Q1");
    listaRevistas.insertarOrdenado("REV04", "Bioinformatics", "Oxford Univ Press", "Reino Unido", 5.800, "Q1");
    listaRevistas.insertarOrdenado("REV05", "ACM Computing Surveys", "ACM", "Estados Unidos", 16.600, "Q1");
    listaRevistas.insertarOrdenado("REV06", "Communications of the ACM", "ACM", "Estados Unidos", 14.100, "Q2");
    listaRevistas.insertarOrdenado("REV07", "Int. Journal of Robotics", "SAGE", "Estados Unidos", 7.500, "Q2");

    // 4. Precarga de Investigadores (Lista Simple, mínimo 5 -> 6 registros vinculados)
    NodoUniversidad* uTec = listaUniversidades.buscarPorId("U01");
    NodoUniversidad* uUcr = listaUniversidades.buscarPorId("U02");
    NodoUniversidad* uMit = listaUniversidades.buscarPorId("U03");
    NodoUniversidad* uStan = listaUniversidades.buscarPorId("U04");
    NodoUniversidad* uOx = listaUniversidades.buscarPorId("U05");

    NodoArea* arIA = listaAreas.buscarPorId("AR01");
    NodoArea* arBio = listaAreas.buscarPorId("AR02");
    NodoArea* arSeg = listaAreas.buscarPorId("AR03");
    NodoArea* arRob = listaAreas.buscarPorId("AR04");
    NodoArea* arSoft = listaAreas.buscarPorId("AR06");

    listaInvestigadores.insertarAlFinal("INV01", "Dr. Alan Turing", uMit, "Estados Unidos", arSeg, "turing@mit.edu");
    listaInvestigadores.insertarAlFinal("INV02", "Dra. Ada Lovelace", uOx, "Reino Unido", arSoft, "lovelace@oxford.ac.uk");
    listaInvestigadores.insertarAlFinal("INV03", "Dr. Geoffrey Hinton", uStan, "Estados Unidos", arIA, "hinton@stanford.edu");
    listaInvestigadores.insertarAlFinal("INV04", "Dra. Lorena Valerio", uTec, "Costa Rica", arIA, "lvalerio@itcr.ac.cr");
    listaInvestigadores.insertarAlFinal("INV05", "Dr. Carlos Alvarado", uUcr, "Costa Rica", arBio, "carlos.alvarado@ucr.ac.cr");
    listaInvestigadores.insertarAlFinal("INV06", "Dra. Fei-Fei Li", uStan, "Estados Unidos", arRob, "feifeili@stanford.edu");

    // 5. Precarga de Coautores (Lista Doble dentro de cada investigador, mínimo 5 global -> 13 registros)
    NodoInvestigador* invTuring = listaInvestigadores.buscarPorId("INV01");
    if (invTuring) {
        invTuring->sublistaCoautores.insertar("CO01", "John von Neumann", "Princeton University", 12);
        invTuring->sublistaCoautores.insertar("CO02", "Claude Shannon", "Bell Laboratories", 8);
    }

    NodoInvestigador* invLovelace = listaInvestigadores.buscarPorId("INV02");
    if (invLovelace) {
        invLovelace->sublistaCoautores.insertar("CO03", "Charles Babbage", "Cambridge University", 15);
        invLovelace->sublistaCoautores.insertar("CO04", "Michael Faraday", "Royal Institution", 4);
    }

    NodoInvestigador* invHinton = listaInvestigadores.buscarPorId("INV03");
    if (invHinton) {
        invHinton->sublistaCoautores.insertar("CO05", "Yann LeCun", "New York University", 24);
        invHinton->sublistaCoautores.insertar("CO06", "Yoshua Bengio", "Universite de Montreal", 22);
        invHinton->sublistaCoautores.insertar("CO07", "Ilya Sutskever", "OpenAI Research", 10);
    }

    NodoInvestigador* invValerio = listaInvestigadores.buscarPorId("INV04");
    if (invValerio) {
        invValerio->sublistaCoautores.insertar("CO08", "Ing. Roberto Solis", "Instituto Tecnologico de CR", 6);
        invValerio->sublistaCoautores.insertar("CO09", "Dra. Maria Chen", "Universidad de Costa Rica", 5);
    }

    NodoInvestigador* invAlvarado = listaInvestigadores.buscarPorId("INV05");
    if (invAlvarado) {
        invAlvarado->sublistaCoautores.insertar("CO10", "Dr. David Lipman", "NCBI / NIH", 9);
        invAlvarado->sublistaCoautores.insertar("CO11", "Dra. Sarah Gilbert", "University of Oxford", 3);
    }

    NodoInvestigador* invFeiFei = listaInvestigadores.buscarPorId("INV06");
    if (invFeiFei) {
        invFeiFei->sublistaCoautores.insertar("CO12", "Dr. Andrej Karpathy", "Stanford University", 11);
        invFeiFei->sublistaCoautores.insertar("CO13", "Dra. Olga Russakovsky", "Princeton University", 7);
    }

    // 6. Precarga de Proyectos de Investigación (Lista Doble Ordenada por Año de Inicio, mínimo 5 -> 6 registros)
    listaProyectos.insertarOrdenadoPorAnio("PRY01", "Deep Neural Foundations", 850000.0, 2017, 2021, invHinton);
    listaProyectos.insertarOrdenadoPorAnio("PRY02", "Algoritmos Cripto Distribuidos", 450000.0, 2018, 2022, invTuring);
    listaProyectos.insertarOrdenadoPorAnio("PRY03", "Genomica Predictiva Avanzada", 620000.0, 2019, 2023, invAlvarado);
    listaProyectos.insertarOrdenadoPorAnio("PRY04", "Grafos en Redes Complejas TEC", 280000.0, 2020, 2024, invValerio);
    listaProyectos.insertarOrdenadoPorAnio("PRY05", "Vision Medica y Robotica", 950000.0, 2021, 2025, invFeiFei);
    listaProyectos.insertarOrdenadoPorAnio("PRY06", "Modelos de Computacion Analitica", 530000.0, 2022, 2026, invLovelace);

    // 7. Precarga de Publicaciones (Lista Circular Ordenada por Año, mínimo 5 -> 12 registros)
    NodoRevista* revNat = listaRevistas.buscarPorId("REV01");
    NodoRevista* revIEEE = listaRevistas.buscarPorId("REV02");
    NodoRevista* revSci = listaRevistas.buscarPorId("REV03");
    NodoRevista* revBio = listaRevistas.buscarPorId("REV04");
    NodoRevista* revACM = listaRevistas.buscarPorId("REV05");
    NodoRevista* revCACM = listaRevistas.buscarPorId("REV06");
    NodoRevista* revRob = listaRevistas.buscarPorId("REV07");

    NodoProyecto* pry01 = listaProyectos.buscarPorId("PRY01");
    NodoProyecto* pry02 = listaProyectos.buscarPorId("PRY02");
    NodoProyecto* pry03 = listaProyectos.buscarPorId("PRY03");
    NodoProyecto* pry04 = listaProyectos.buscarPorId("PRY04");
    NodoProyecto* pry05 = listaProyectos.buscarPorId("PRY05");
    NodoProyecto* pry06 = listaProyectos.buscarPorId("PRY06");

    listaPublicaciones.insertarOrdenadoPorAnio("PUB01", "On Computable Numbers and Logic", 2018, "Articulo", 35, "10.1093/mind/436", invTuring, revIEEE, pry02);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB02", "Deep Residual Learning for Vision", 2018, "Articulo", 42, "10.1109/tpami.2018.1", invHinton, revIEEE, pry01);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB03", "Computational Genomic Assembly", 2019, "Articulo", 18, "10.1093/bioinf/2019", invAlvarado, revBio, pry03);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB04", "Foundations of Analytical Engines", 2019, "Libro", 12, "10.1145/acm.2019", invLovelace, nullptr, pry06);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB05", "Dropout in Deep Neural Architectures", 2020, "Articulo", 28, "10.1038/nature.2020", invHinton, revNat, pry01);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB06", "Estructuras Dinamicas en Grafos TEC", 2020, "Articulo", 15, "10.1016/j.tec.2020", invValerio, revCACM, pry04);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB07", "ImageNet Visual Recognition Challenge", 2021, "Articulo", 50, "10.1007/s11263.2021", invFeiFei, revSci, pry05);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB08", "Cryptographic Protocols in Computing", 2021, "Conferencia", 8, "10.1109/sp.2021", invTuring, nullptr, pry02);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB09", "Deep Learning via Attention Mechanisms", 2022, "Articulo", 31, "10.1038/s42256.2022", invHinton, revNat, pry01);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB10", "Algoritmos de Enrutamiento Eficiente", 2022, "Articulo", 9, "10.1145/surveys.2022", invValerio, revACM, pry04);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB11", "Variant Detection in Viral Outbreaks", 2023, "Articulo", 14, "10.1093/bioinf/2023", invAlvarado, revBio, pry03);
    listaPublicaciones.insertarOrdenadoPorAnio("PUB12", "Autonomous Robotic Terrain Navigation", 2023, "Articulo", 22, "10.1177/0278364923", invFeiFei, revRob, pry05);

    // 8. Precarga de Citaciones (Lista Doble dentro de publicaciones, mínimo 5 -> 18 registros)
    listaPublicaciones.agregarCitaAPublicacion("PUB01", "CIT01", 2019, "A Survey on Computability", "Prof. Martin Davis");
    listaPublicaciones.agregarCitaAPublicacion("PUB01", "CIT02", 2020, "Modern Cryptography Review", "Dra. Shafi Goldwasser");
    listaPublicaciones.agregarCitaAPublicacion("PUB01", "CIT03", 2021, "Quantum Turing Machines", "Dr. David Deutsch");

    listaPublicaciones.agregarCitaAPublicacion("PUB02", "CIT04", 2019, "Vision Transformers Survey", "Alexey Dosovitskiy");
    listaPublicaciones.agregarCitaAPublicacion("PUB02", "CIT05", 2020, "Backprop Evolution", "Andrew Ng");
    listaPublicaciones.agregarCitaAPublicacion("PUB02", "CIT06", 2021, "Convolutional Networks Review", "Yann LeCun");

    listaPublicaciones.agregarCitaAPublicacion("PUB03", "CIT07", 2020, "Genome Analysis in Plants", "Dr. Michael Eisen");
    listaPublicaciones.agregarCitaAPublicacion("PUB03", "CIT08", 2021, "Sequence Alignment Algorithms", "Gene Myers");

    listaPublicaciones.agregarCitaAPublicacion("PUB05", "CIT09", 2021, "Regularization Techniques", "Yoshua Bengio");
    listaPublicaciones.agregarCitaAPublicacion("PUB05", "CIT10", 2022, "Neural Architecture Search", "Quoc Le");

    listaPublicaciones.agregarCitaAPublicacion("PUB06", "CIT11", 2021, "Graph Theory in Computer Science", "Robert Tarjan");
    listaPublicaciones.agregarCitaAPublicacion("PUB06", "CIT12", 2022, "Data Structures for Networks", "Donald Knuth");

    listaPublicaciones.agregarCitaAPublicacion("PUB07", "CIT13", 2022, "Foundation Models Paradigm", "Percy Liang");
    listaPublicaciones.agregarCitaAPublicacion("PUB07", "CIT14", 2022, "Multimodal Machine Learning", "Kaiming He");
    listaPublicaciones.agregarCitaAPublicacion("PUB07", "CIT15", 2023, "Diffusion Models for Images", "Jonathan Ho");

    listaPublicaciones.agregarCitaAPublicacion("PUB09", "CIT16", 2023, "Attention is All You Need: Analysis", "Ashish Vaswani");
    listaPublicaciones.agregarCitaAPublicacion("PUB11", "CIT17", 2024, "Pandemic Computational Tracking", "Trevor Bedford");
    listaPublicaciones.agregarCitaAPublicacion("PUB12", "CIT18", 2024, "SLAM for Outdoor Exploration", "Sebastian Thrun");

    // Sincronizar índices H iniciales
    MetricasAcademicas::actualizarIndicesHTodos(listaInvestigadores, listaPublicaciones);

    std::cout << "[SISTEMA] Precarga completada exitosamente. Todas las 8 listas contienen datos estructurados.\n";
}

void SistemaAcademico::menuPrincipal() {
    int opcion = -1;
    do {
        std::cout << "\n================================================================================\n";
        std::cout << "     SISTEMA DE GESTION DE PRODUCCION CIENTIFICA Y METRICAS ACADEMICAS          \n";
        std::cout << "                 IC2001 ESTRUCTURA DE DATOS - TEC COSTA RICA                    \n";
        std::cout << "                 MODULO RESPONSABLE: PERSONA 3 (INTEGRACION TOTAL)              \n";
        std::cout << "================================================================================\n";
        std::cout << "  [1]  Gestion de Publicaciones Cientificas (Lista Circular - Persona 3)\n";
        std::cout << "  [2]  Gestion de Citaciones (Lista Doble / Sublistas - Persona 3)\n";
        std::cout << "  [3]  Modulo de Metricas Academicas e Indice H (Persona 3)\n";
        std::cout << "  [4]  Consultas del Sistema (10 consultas - Enfoque Persona 3 en 2, 3, 9)\n";
        std::cout << "  [5]  Reportes del Sistema (9 reportes - Enfoque Persona 3 en Reporte 3)\n";
        std::cout << "  [6]  Gestion de Investigadores (Lista Simple y Sublista Coautores)\n";
        std::cout << "  [7]  Gestion de Universidades (Lista Doble)\n";
        std::cout << "  [8]  Gestion de Areas de Investigacion (Lista Simple)\n";
        std::cout << "  [9]  Gestion de Revistas Cientificas (Lista Simple Ordenada)\n";
        std::cout << "  [10] Gestion de Proyectos de Investigacion (Lista Doble Ordenada)\n";
        std::cout << "  [11] Demostracion del Ejemplo Oficial de Indice H = 5 (PDF)\n";
        std::cout << "  [12] SUBMENU DEDICADO: TODO EL MODULO DE LA PERSONA 2\n";
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
            case 12: menuPersona2(); break;
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
// MÓDULOS PERSONA 3: PUBLICACIONES (Lista Circular)
// -------------------------------------------------------------------------------------
void SistemaAcademico::menuPublicaciones() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "        GESTION DE PUBLICACIONES CIENTIFICAS (LISTA CIRCULAR - PERSONA 3)       \n";
        std::cout << "--------------------------------------------------------------------------------\n";
        std::cout << "  1. Insertar publicacion (ordenada por ano ascendente)\n";
        std::cout << "  2. Buscar publicacion por ID\n";
        std::cout << "  3. Modificar publicacion\n";
        std::cout << "  4. Eliminar publicacion (Eliminacion en Lista Circular)\n";
        std::cout << "  5. Mostrar todas las publicaciones\n";
        std::cout << "  6. Mostrar publicaciones con detalle completo (incluye citaciones)\n";
        std::cout << "  0. Volver al menu principal\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        op = leerEntero("Seleccione una opcion [0-6]: ");

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
        }
    } while (op != 0);
}

// -------------------------------------------------------------------------------------
// MÓDULOS PERSONA 3: CITACIONES (Lista Doble)
// -------------------------------------------------------------------------------------
void SistemaAcademico::menuCitaciones() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "        GESTION DE CITACIONES (LISTA DOBLE / SUBLISTAS - PERSONA 3)             \n";
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
// MÓDULOS PERSONA 3: MÉTRICAS ACADÉMICAS
// -------------------------------------------------------------------------------------
void SistemaAcademico::menuMetricas() {
    int op = -1;
    do {
        std::cout << "\n--------------------------------------------------------------------------------\n";
        std::cout << "          MODULO DE METRICAS ACADEMICAS E INDICE H (PERSONA 3)                  \n";
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
        std::cout << "  2.  Investigador con mas citas acumuladas (Persona 3)\n";
        std::cout << "  3.  Publicacion que recibio mayor cantidad de citas (Persona 3)\n";
        std::cout << "  4.  Revista con mayor factor de impacto\n";
        std::cout << "  5.  Investigador con mas coautores\n";
        std::cout << "  6.  Universidad con mas investigadores registrados\n";
        std::cout << "  7.  Area de investigacion que genera mas publicaciones\n";
        std::cout << "  8.  Ano que tuvo la mayor produccion cientifica\n";
        std::cout << "  9.  Publicacion con mayor cantidad de autores (Persona 3)\n";
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
        std::cout << "  3. Mostrar publicaciones ordenadas por cantidad de citas descendente (Persona 3)\n";
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
// MÓDULO EXCLUSIVO Y COMPLETO: PERSONA 2 (REVISTAS Y PROYECTOS)
// -------------------------------------------------------------------------------------
void SistemaAcademico::menuPersona2() {
    int op = -1;
    do {
        std::cout << "\n================================================================================\n";
        std::cout << "                 MODULO DE LA PERSONA 2: REVISTAS Y PROYECTOS                   \n";
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
