#include "Consultas.h"
#include <iostream>
#include <iomanip>

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

// 2. ¿Cuál investigador tiene más citas acumuladas? (Persona 3)
void GestorConsultas::consulta2_MasCitasAcumuladas(const ListaInvestigadores& invs, const ListaPublicaciones& pubs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 2: INVESTIGADOR(ES) CON MAS CITAS ACUMULADAS (Modulo Persona 3)\n";
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

// 3. ¿Cuál publicación recibió mayor cantidad de citas? (Persona 3)
void GestorConsultas::consulta3_PublicacionMasCitada(const ListaPublicaciones& pubs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 3: PUBLICACION(ES) CON MAYOR CANTIDAD DE CITAS (Modulo Persona 3)\n";
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

// 9. ¿Cuál publicación tiene mayor cantidad de autores? (Persona 3)
void GestorConsultas::consulta9_PublicacionMasAutores(const ListaPublicaciones& pubs) {
    std::cout << "\n================================================================================\n";
    std::cout << "  CONSULTA 9: PUBLICACION(ES) CON MAYOR CANTIDAD DE AUTORES (Modulo Persona 3)\n";
    std::cout << "================================================================================\n";

    if (pubs.getCabeza() == nullptr) {
        std::cout << "  No hay publicaciones registradas.\n";
        return;
    }

    int maxAutores = -1;
    NodoPublicacion* pub = pubs.getCabeza();
    do {
        // Total autores = Autor Principal (1) + Coautores en la red del autor principal
        int autores = 0;
        if (pub->investigadorPrincipal != nullptr) {
            autores = 1 + pub->investigadorPrincipal->sublistaCoautores.getTamano();
        }
        if (autores > maxAutores) {
            maxAutores = autores;
        }
        pub = pub->siguiente;
    } while (pub != pubs.getCabeza());

    std::cout << "  Cantidad maxima de autores por publicacion: " << maxAutores << "\n\n";
    pub = pubs.getCabeza();
    int count = 0;
    do {
        int autores = (pub->investigadorPrincipal != nullptr)
                      ? (1 + pub->investigadorPrincipal->sublistaCoautores.getTamano()) : 0;
        if (autores == maxAutores) {
            count++;
            std::cout << "  [" << count << "] \"" << pub->titulo << "\" (" << pub->anio << ")\n"
                      << "      ID: " << pub->idPublicacion << " | Total Autores: " << autores << "\n"
                      << "      Investigador Principal: "
                      << (pub->investigadorPrincipal ? pub->investigadorPrincipal->nombreCompleto : "N/A") << "\n"
                      << "      Equipo de Coautores:\n";
            if (pub->investigadorPrincipal) {
                pub->investigadorPrincipal->sublistaCoautores.mostrar();
            }
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
