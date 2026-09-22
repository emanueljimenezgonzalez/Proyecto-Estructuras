#include "Reportes.h"
#include <iostream>
#include <iomanip>

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

// Reporte 3: Mostrar publicaciones ordenadas por cantidad de citas descendente (Persona 3)
void GestorReportes::reporte3_PublicacionesPorCitasDescendente(const ListaPublicaciones& pubs) {
    std::cout << "\n====================================================================================================\n";
    std::cout << "         REPORTE 3: PUBLICACIONES ORDENADAS POR CANTIDAD DE CITAS DESCENDENTE (Persona 3)           \n";
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
