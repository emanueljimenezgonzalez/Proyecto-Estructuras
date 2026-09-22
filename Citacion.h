#ifndef CITACION_H
#define CITACION_H

#include <string>
#include <iostream>

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

#endif // CITACION_H
