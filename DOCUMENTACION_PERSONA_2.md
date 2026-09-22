# INSTITUTO TECNOLÓGICO DE COSTA RICA
## Escuela de Computación
### Curso IC2001 - Estructuras de Datos
**Prof. Lorena Valerio Solís**  
**Semestre II - 2026**

---

# INFORME TÉCNICO Y MANUAL DE USUARIO
## MÓDULO DE LA PERSONA 2: REVISTAS, PROYECTOS Y RELACIONES CIENTÍFICAS

**Integrantes del Proyecto:**
- **Persona 2:** Responsable de Revistas Científicas, Proyectos de Investigación y Relaciones
- **Persona 1:** Investigadores, Universidades, Áreas y Coautores
- **Persona 3:** Publicaciones (Lista Circular), Citaciones, Métricas e Integración General

---

## ÍNDICE DEL MÓDULO DE LA PERSONA 2
1. [Descripción de Responsabilidades y Alcance](#1-descripción-de-responsabilidades-y-alcance)
2. [Estructuras de Datos Implementadas (Manual sin STL)](#2-estructuras-de-datos-implementadas)
   - 2.1. Lista Simple: Revistas Científicas (Ordenada por Nombre)
   - 2.2. Lista Doble: Proyectos de Investigación (Ordenada por Año de Inicio)
   - 2.3. Coordinación de Relaciones con Publicaciones (Persona 2 & Persona 3)
3. [Diagrama de Clases y Relaciones de la Persona 2](#3-diagrama-de-clases-y-relaciones-de-la-persona-2)
4. [Consultas Asignadas a la Persona 2](#4-consultas-asignadas-a-la-persona-2)
   - Consulta 4: Revista con mayor factor de impacto
   - Consulta 8: Año con mayor producción científica
   - Consulta 10: Investigador con más artículos en revistas Q1
5. [Reportes Asignados a la Persona 2](#5-reportes-asignados-a-la-persona-2)
   - Reporte 2: Publicaciones ordenadas por año ascendente
   - Reporte 4: Revistas y sus factores de impacto
   - Reporte 6: Publicaciones de una revista indicada
   - Reporte 7: Publicaciones de un área determinada
6. [Manual de Usuario con Evidencias de Ejecución](#6-manual-de-usuario-con-evidencias-de-ejecución)
7. [Análisis de Resultados y Pruebas de Integridad](#7-análisis-de-resultados-y-pruebas-de-integridad)
8. [Conclusiones del Módulo](#8-conclusiones-del-módulo)

---

## 1. DESCRIPCIÓN DE RESPONSABILIDADES Y ALCANCE

A la **Persona 2** le corresponde la administración de las revistas indexadas donde se divulga el conocimiento y de los proyectos que financian las investigaciones científicas. Asimismo, coordina las relaciones bidireccionales con las publicaciones (que se gestionan en la lista circular de la Persona 3) y con los investigadores líderes (Persona 1).

### Objetivos Específicos de la Persona 2:
1. Diseñar e implementar la **Lista Simple de Revistas Científicas**, asegurando que toda inserción se realice en **orden alfabético por nombre**.
2. Diseñar e implementar la **Lista Doble de Proyectos de Investigación**, garantizando la **inserción ordenada por fecha/año de inicio**.
3. Implementar las operaciones CRUD requeridas (Insertar, Modificar, Eliminar en lista doble, Buscar y Mostrar) sin emplear contenedores STL.
4. Establecer las relaciones dinámicas por punteros:
   - $\text{Publicación} \rightarrow \text{Revista}$
   - $\text{Publicación} \rightarrow \text{Proyecto}$
   - $\text{Proyecto} \rightarrow \text{Investigador Responsable}$
   - $\text{Revista} \rightarrow \text{Publicaciones vinculadas}$
5. Resolver y presentar las consultas (4, 8, 10) y los reportes (2, 4, 6, 7).

---

## 2. ESTRUCTURAS DE DATOS IMPLEMENTADAS

### 2.1. Lista Simple: Revistas Científicas (`Revista.h` / `Revista.cpp`)
- **Tipo de Estructura:** Lista Simplemente Enlazada (`NodoRevista* siguiente`).
- **Criterio de Inserción Obligatorio:** **Ordenada alfabéticamente por nombre**.
- **Atributos:**
  - `idRevista` (std::string): Código alfanumérico único (ej. `REV01`).
  - `nombre` (std::string): Nombre oficial de la revista (clave de ordenación).
  - `editorial` (std::string): Casa editorial (ej. *Nature Publishing*, *IEEE*, *ACM*).
  - `pais` (std::string): País de origen.
  - `factorImpacto` (double): Factor de impacto JCR/Scopus (debe ser $\ge 0.0$).
  - `cuartil` (std::string): Cuartil de impacto internacional (`Q1`, `Q2`, `Q3`, `Q4`).
- **Algoritmo de Inserción Ordenada:**
  - Se valida no duplicidad de ID y que el cuartil sea válido.
  - Si la lista está vacía o el nombre es menor lexicográficamente que el de la cabeza:
    ```cpp
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    ```
  - Si no, se recorre con punteros hasta encontrar la posición exacta:
    ```cpp
    while (actual->siguiente != nullptr && actual->siguiente->nombre < nom) {
        actual = actual->siguiente;
    }
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
    ```

### 2.2. Lista Doble: Proyectos de Investigación (`Proyecto.h` / `Proyecto.cpp`)
- **Tipo de Estructura:** Lista Doblemente Enlazada (`anterior` y `siguiente`).
- **Criterio de Inserción Obligatorio:** **Ordenada por fecha/año de inicio ascendente**.
- **Atributos:**
  - `idProyecto` (std::string): Código único (ej. `PRY01`).
  - `nombre` (std::string): Nombre del proyecto de investigación.
  - `financiamiento` (double): Presupuesto en dólares (USD).
  - `anioInicio` (int): Año de inicio (criterio de ordenación).
  - `anioFin` (int): Año de finalización (debe ser $\ge \text{anioInicio}$).
  - `investigadorResponsable` (`NodoInvestigador*`): Puntero directo al investigador principal.
- **Operación de Eliminación en Lista Doble:**
  Cumple el requisito del curso de implementar al menos una eliminación en lista doble:
  ```cpp
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
  ```

### 2.3. Coordinación de Relaciones
- **Revista $\rightarrow$ Publicaciones:** Desde cualquier revista es posible obtener y listar todas las publicaciones arbitradas en ella mediante un recorrido en la lista circular (`pub->revista == rev`).
- **Proyecto $\rightarrow$ Publicaciones:** Se implementó el método `mostrarPublicacionesDeProyecto(idProy)` que extrae las publicaciones financiadas por dicho proyecto.
- **Proyecto $\rightarrow$ Investigador Responsable:** Acceso directo en tiempo constante $O(1)$ a través del puntero `investigadorResponsable`.

---

## 3. DIAGRAMA DE CLASES Y RELACIONES DE LA PERSONA 2

```
+------------------------------------+
|            NodoRevista             |
+------------------------------------+
| - idRevista: string                |
| - nombre: string                   |
| - editorial: string                |
| - pais: string                     |
| - factorImpacto: double            |
| - cuartil: string (Q1-Q4)          |
| - siguiente: NodoRevista*          |
+------------------------------------+
                  ^
                  | 1
                  |
                  | *
+------------------------------------+          1           1 +------------------------------------+
|           NodoPublicacion          |----------------------->|             NodoProyecto           |
+------------------------------------+                        +------------------------------------+
| - idPublicacion: string            |                        | - idProyecto: string               |
| - titulo: string                   |                        | - nombre: string                   |
| - anio: int                        |                        | - financiamiento: double           |
| - tipo: string                     |                        | - anioInicio: int                  |
| - cantidadCitas: int               |                        | - anioFin: int                     |
| - revista: NodoRevista*            |                        | - investigadorResponsable: Nodo*   |
| - proyecto: NodoProyecto*          |                        | - anterior: NodoProyecto*          |
+------------------------------------+                        | - siguiente: NodoProyecto*         |
                                                              +------------------------------------+
                                                                                | 1
                                                                                v
                                                                      NodoInvestigador (P1)
```

---

## 4. CONSULTAS ASIGNADAS A LA PERSONA 2

### Consulta 4: Revista con mayor factor de impacto
- **Objetivo:** Recorrer la lista simple de revistas y encontrar el valor máximo de `factorImpacto`.
- **Manejo de Empates:** Si dos o más revistas empatan en el factor de impacto máximo, se imprimen todas con su respectivo cuartil y editorial.
- **Resultado en Precarga:** `Science` con factor de impacto `44.700` (Q1).

### Consulta 8: Año con mayor producción científica
- **Objetivo:** Determinar qué año calendario registra la mayor cantidad de publicaciones.
- **Algoritmo Manual:** Sin usar `std::map`, se utiliza un conteo dinámico manual que agrupa las publicaciones de la lista circular según el atributo `anio`.
- **Resultado en Precarga:** Años con mayor producción científica empatados (2018, 2020, 2021, 2022 con 2 publicaciones cada uno).

### Consulta 10: Investigador con más artículos en revistas Q1
- **Objetivo:** Identificar al científico que ha publicado mayor cantidad de artículos en revistas catalogadas como `Q1`.
- **Algoritmo:** Para cada investigador, se recorre la lista circular de publicaciones y se contabilizan aquellas donde `pub->revista != nullptr` y `pub->revista->cuartil == "Q1"`.
- **Resultado en Precarga:** `Dr. Geoffrey Hinton` (3 artículos en Q1: dos en *Nature Machine Intelligence* y uno en *IEEE TPAMI*).

---

## 5. REPORTES ASIGNADOS A LA PERSONA 2

### Reporte 2: Publicaciones ordenadas por año ascendente
- **Funcionamiento:** Aprovecha el invariante de la lista circular de publicaciones, la cual se mantiene ordenada cronológicamente en cada inserción. Se recorre desde la cabeza circular imprimiendo año, título, tipo, citas y revista asociada.

### Reporte 4: Mostrar todas las revistas y sus factores de impacto
- **Funcionamiento:** Despliega en formato tabular todas las revistas en estricto orden alfabético:
  ```
  ID Revista   Nombre                         Editorial            Pais            Factor Imp.  Cuartil
  ----------------------------------------------------------------------------------------------------
  REV05        ACM Computing Surveys          ACM                  Estados Unidos  16.600       Q1
  REV04        Bioinformatics                 Oxford Univ Press    Reino Unido     5.800        Q1
  REV06        Communications of the ACM      ACM                  Estados Unidos  14.100       Q2
  REV02        IEEE Trans. Pattern Analysis   IEEE                 Estados Unidos  23.600       Q1
  REV07        Int. Journal of Robotics       SAGE                 Estados Unidos  7.500        Q2
  REV01        Nature Machine Intelligence    Nature Publishing    Reino Unido     25.898       Q1
  REV03        Science                        AAAS                 Estados Unidos  44.700       Q1
  ```

### Reporte 6: Publicaciones de una revista indicada por el usuario
- **Funcionamiento:** El usuario ingresa el ID o nombre de la revista (ej. `REV04` o `Bioinformatics`) y el sistema lista todas las publicaciones contenidas en esa revista.

### Reporte 7: Publicaciones de un área determinada
- **Funcionamiento:** Permite filtrar y visualizar todas las publicaciones cuyos autores principales pertenecen a un área de investigación específica (ej. `AR01: Inteligencia Artificial`).

---

## 6. MANUAL DE USUARIO CON EVIDENCIAS DE EJECUCIÓN

Para comodidad y facilidad durante la evaluación o defensa, la Persona 2 cuenta con el **submenú dedicado (Opción [12])** en el menú general:

```
================================================================================
                 MODULO DE LA PERSONA 2: REVISTAS Y PROYECTOS                   
================================================================================
  [1]  Gestion de Revistas Cientificas (Lista Simple Ordenada por Nombre)
  [2]  Gestion de Proyectos de Investigacion (Lista Doble Ordenada por Fecha)
  [3]  Relacion: Ver publicaciones de una Revista indicada (Reporte 6)
  [4]  Relacion: Ver publicaciones asociadas a un Proyecto indicado
  [5]  Relacion: Ver proyectos asociados a su Investigador Responsable
  [6]  Consulta P2 (No. 4): Revista con mayor factor de impacto
  [7]  Consulta P2 (No. 8): Ano con mayor produccion cientifica
  [8]  Consulta P2 (No. 10): Investigador con mas articulos en revistas Q1
  [9]  Reporte P2 (No. 2): Publicaciones ordenadas por ano ascendente
  [10] Reporte P2 (No. 4): Mostrar todas las revistas y sus factores de impacto
  [11] Reporte P2 (No. 7): Mostrar todas las publicaciones de un area
  [0]  Volver al menu principal
================================================================================
```

### Ejemplo de Ejecución: Consulta 4 (Revista con Mayor Factor de Impacto)
```
================================================================================
  CONSULTA 4: REVISTA(S) CON EL MAYOR FACTOR DE IMPACTO
================================================================================
  Factor de impacto maximo: 44.700

  [1] Science (ID: REV03)
      Editorial: AAAS | Pais: Estados Unidos
      Factor de Impacto: 44.700 | Cuartil: Q1
```

### Ejemplo de Ejecución: Consulta 10 (Investigador con más artículos en revistas Q1)
```
================================================================================
  CONSULTA 10: INVESTIGADOR(ES) CON MAS ARTICULOS EN REVISTAS Q1
================================================================================
  Maximo de articulos en revistas Q1: 3

  [1] Dr. Geoffrey Hinton (ID: INV03)
      Universidad: Stanford University
      Total Articulos Q1: 3
      Detalle de publicaciones Q1:
        - "Deep Residual Learning for Vision" (2018) en IEEE Trans. Pattern Analysis (FI: 23.600)
        - "Dropout in Deep Neural Architectures" (2020) en Nature Machine Intelligence (FI: 25.898)
        - "Deep Learning via Attention Mechanisms" (2022) en Nature Machine Intelligence (FI: 25.898)
```

---

## 7. ANÁLISIS DE RESULTADOS Y PRUEBAS DE INTEGRIDAD

1. **Ordenamiento de Revistas por Nombre:**
   - Se probó la inserción de revistas con nombres variados (`ACM...`, `Bioinformatics`, `Nature...`, `Science`). La lista mantiene la relación de orden alfabético ascendente en todo momento sin requerir llamadas posteriores a funciones de ordenamiento.
2. **Ordenamiento Cronológico de Proyectos:**
   - La inserción en la lista doble coloca cada proyecto según su año de inicio (`2017, 2018, 2019, 2020, 2021, 2022`), permitiendo un análisis temporal de los fondos de financiamiento.
3. **Consistencia de Enlaces entre Módulos:**
   - Los punteros entre `Publicacion -> Revista` y `Publicacion -> Proyecto` fueron comprobados en memoria. No existen punteros nulos no controlados (*null dereference*).

---

## 8. CONCLUSIONES DEL MÓDULO

1. La implementación de la lista simple de revistas con inserción alfabética garantiza búsquedas rápidas y un reporte de factor de impacto organizado por defecto.
2. La lista doble de proyectos proporciona una estructura robusta con navegación bidireccional y eliminación eficiente de nodos mediante reasignación de punteros dobles (`anterior` y `siguiente`).
3. El módulo se integra limpiamente con el trabajo de la Persona 1 y la Persona 3, logrando un sistema unificado, robusto y 100% libre de bibliotecas de contenedores STL.
