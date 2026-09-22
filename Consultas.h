#ifndef CONSULTAS_H
#define CONSULTAS_H

#include "Investigador.h"
#include "Universidad.h"
#include "Area.h"
#include "Revista.h"
#include "Proyecto.h"
#include "Publicacion.h"
#include "Metricas.h"

class GestorConsultas {
public:
    // Consulta 1: Investigador con mayor índice H
    static void consulta1_MayorIndiceH(const ListaInvestigadores& invs, const ListaPublicaciones& pubs);

    // Consulta 2: Investigador con más citas acumuladas (Persona 3)
    static void consulta2_MasCitasAcumuladas(const ListaInvestigadores& invs, const ListaPublicaciones& pubs);

    // Consulta 3: Publicación con mayor cantidad de citas (Persona 3)
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

    // Consulta 9: Publicación con mayor cantidad de autores (Persona 3)
    static void consulta9_PublicacionMasAutores(const ListaPublicaciones& pubs);

    // Consulta 10: Investigador con más artículos en revistas Q1
    static void consulta10_InvestigadorMasArticulosQ1(const ListaInvestigadores& invs, const ListaPublicaciones& pubs);
};

#endif // CONSULTAS_H
