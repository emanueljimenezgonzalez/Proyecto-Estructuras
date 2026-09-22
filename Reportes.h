#ifndef REPORTES_H
#define REPORTES_H

#include "Investigador.h"
#include "Universidad.h"
#include "Area.h"
#include "Revista.h"
#include "Proyecto.h"
#include "Publicacion.h"
#include "Metricas.h"

class GestorReportes {
public:
    // Reporte 1: Mostrar todos los investigadores con sus publicaciones
    static void reporte1_InvestigadoresConPublicaciones(const ListaInvestigadores& invs, const ListaPublicaciones& pubs);

    // Reporte 2: Mostrar publicaciones ordenadas por año ascendente
    static void reporte2_PublicacionesPorAnioAscendente(const ListaPublicaciones& pubs);

    // Reporte 3: Mostrar publicaciones ordenadas por cantidad de citas descendente (Persona 3)
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

#endif // REPORTES_H
