#include "Metricas.h"
#include <iostream>
#include <iomanip>

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
