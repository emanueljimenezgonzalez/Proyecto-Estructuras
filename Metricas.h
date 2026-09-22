#ifndef METRICAS_H
#define METRICAS_H

#include "Investigador.h"
#include "Publicacion.h"

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

#endif // METRICAS_H
