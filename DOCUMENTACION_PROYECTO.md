# INSTITUTO TECNOLÓGICO DE COSTA RICA
## Escuela de Computación
### Curso IC2001 - Estructuras de Datos
**Prof. Lorena Valerio Solís**  
**Semestre II - 2026**

---

# INFORME TÉCNICO Y DOCUMENTACIÓN DE PROYECTO
## Sistema de Gestión de Producción Científica y Métricas Académicas

**Integración del Sistema y Módulo Asignado: Persona 3**  
- **Responsabilidad Principal:** Lista Circular de Publicaciones, Lista Doble de Citaciones, Sublistas de Citaciones, Cálculo de Métricas Académicas (Índice H, Citas Totales, Promedios, Colaboración, Producción), Consultas Asignadas (2, 3, 9), Reporte Asignado (Reporte 3), Integración Global del Sistema y Menú Principal.

---

## ÍNDICE GENERAL
1. [Portada y Datos Generales](#1-portada-y-datos-generales)
2. [Descripción General del Sistema y Arquitectura](#2-descripción-general-del-sistema-y-arquitectura)
3. [Estructuras de Datos Implementadas (Manual sin STL)](#3-estructuras-de-datos-implementadas-manual-sin-stl)
   - 3.1. Lista Circular: Publicaciones Científicas (Persona 3)
   - 3.2. Lista Doble: Sublista de Citaciones (Persona 3)
   - 3.3. Listas Simples: Investigadores, Revistas y Áreas
   - 3.4. Listas Dobles: Coautores, Proyectos y Universidades
4. [Diagrama de Clases y Relaciones](#4-diagrama-de-clases-y-relaciones)
5. [Métricas Académicas y Algoritmo del Índice H](#5-métricas-académicas-y-algoritmo-del-índice-h)
   - 5.1. Demostración del Ejemplo Oficial (Página 5 del Enunciado)
   - 5.2. Fórmulas y Recorridos de Punteros
6. [Catálogo de Consultas y Reportes](#6-catálogo-de-consultas-y-reportes)
   - 6.1. Las 10 Consultas Solicitadas (con Manejo de Empates)
   - 6.2. Los 9 Reportes del Sistema
7. [Manual de Usuario y Evidencias de Ejecución (Capturas de Consola)](#7-manual-de-usuario-y-evidencias-de-ejecución)
8. [Análisis de Resultados y Complejidad Algorítmica](#8-análisis-de-resultados-y-complejidad-algorítmica)
9. [Conclusiones y Recomendaciones](#9-conclusiones-y-recomendaciones)
10. [Instrucciones de Compilación y Ejecución](#10-instrucciones-de-compilación-y-ejecución)

---

## 1. PORTADA Y DATOS GENERALES

- **Institución:** Instituto Tecnológico de Costa Rica (TEC)
- **Área:** Ingeniería en Computación / Escuela de Ingeniería Informática
- **Curso:** IC2001 Estructuras de Datos
- **Docente:** Prof. Lorena Valerio Solís
- **Proyecto:** Primer Proyecto Programado - Sistema de Gestión de Producción Científica y Métricas Académicas
- **Lenguaje:** C++ Estándar (C++11/C++14) sin librerías de contenedores STL
- **Rol en el Equipo:** **Persona 3** (Módulo de Publicaciones Circulares, Citaciones Dobles, Métricas e Integrador General del Software)
- **Fecha de Entrega:** Octubre 2026

---

## 2. DESCRIPCIÓN GENERAL DEL SISTEMA Y ARQUITECTURA

El sistema simula una plataforma integral de gestión bibliométrica análoga a *Google Scholar* o *Scopus*. Permite administrar el ciclo de vida completo de investigadores, proyectos de investigación, revistas científicas arbitradas, publicaciones en diversos formatos (artículos, libros, conferencias) y sus correspondientes redes de coautoría y citación.

### Reglas Técnicas Obligatorias Cumplidas:
1. **Punteros y Memoria Dinámica Manual:** Todas las listas enlazadas (simples, dobles y circular) fueron desarrolladas manualmente utilizando punteros (`Nodo*`, `cabeza`, `cola`, `siguiente`, `anterior`), operadores `new` y `delete`.
2. **Prohibición de Contenedores STL:** No se utiliza `std::vector`, `std::list`, `std::map`, `std::queue`, `std::stack`, ni algoritmos como `std::sort`. Los ordenamientos para el índice H y reportes se realizan mediante arreglos dinámicos alocados con punteros y algoritmos de intercambio manuales.
3. **Persistencia e IDs Únicos:** Toda entidad posee una validación de unicidad de identificador antes de su registro.
4. **Relaciones Dinámicas por Punteros:** No se almacenan IDs foráneos redundantes; los nodos contienen punteros directos hacia la entidad relacionada (ej. `NodoPublicacion` apunta a `NodoInvestigador`, `NodoRevista` y `NodoProyecto`).
5. **Precarga de Datos:** Se incluyen más de 5 registros predefinidos en cada una de las 8 estructuras interconectadas.

---

## 3. ESTRUCTURAS DE DATOS IMPLEMENTADAS (MANUAL SIN STL)

El sistema consta exactamente de las 8 estructuras requeridas por el enunciado:

### 3.1. Lista Circular: Publicaciones Científicas (Persona 3)
- **Tipo:** Circular Simplemente Enlazada.
- **Regla de Inserción:** **Ordenada por año ascendente**.
- **Comportamiento Circular:** El puntero `siguiente` del último nodo siempre apunta a `cabeza`. En listas de un solo nodo, `cabeza->siguiente == cabeza`.
- **Atributos:**
  - `idPublicacion` (std::string): Identificador único (ej. "PUB01").
  - `titulo` (std::string): Título académico de la obra.
  - `anio` (int): Año de publicación (clave de ordenamiento).
  - `tipo` (std::string): Artículo, Libro o Conferencia.
  - `cantidadCitas` (int): Métrica cuantitativa de citas.
  - `doi` (std::string): Digital Object Identifier.
  - `investigadorPrincipal` (`NodoInvestigador*`): Enlace directo al autor principal.
  - `revista` (`NodoRevista*`): Enlace directo a la revista (o `nullptr` si es libro/conferencia).
  - `proyecto` (`NodoProyecto*`): Enlace al proyecto financiado que respaldó la publicación.
  - `sublistaCitaciones` (`ListaCitaciones`): Sublista doble de citas recibidas.
  - `siguiente` (`NodoPublicacion*`): Puntero circular al siguiente nodo.
- **Operaciones CRUD:**
  - `insertarOrdenadoPorAnio`: Inserción ordenada manteniendo la circularidad en casos de lista vacía, inserción antes de la cabeza (actualizando el puntero del último nodo a la nueva cabeza) e inserciones intermedias/finales.
  - `buscarPorId`: Recorrido circular mediante ciclo `do ... while (actual != cabeza)`.
  - `modificar`: Si el año es alterado, se realiza reubicación ordenada para garantizar consistencia topológica.
  - `eliminar`: Desconexión de punteros circulares segura liberando la sublista de citas y evitando bucles infinitos.
  - `mostrar` / `mostrarConDetalles`: Recorrido tabular e interactivo.

### 3.2. Lista Doble: Sublista de Citaciones (Persona 3)
- **Tipo:** Doblemente Enlazada (`anterior` y `siguiente`).
- **Ubicación:** Sublista interna contenida en cada `NodoPublicacion`.
- **Atributos:** `idCita`, `anio`, `publicacionCitante`, `autorCitante`.
- **Inserción:** Como guste (inserción al final con punteros dobles).
- **Operaciones:** Insertar, buscar, modificar, eliminar y mostrar.

### 3.3. Listas Simples (3)
1. **Investigadores:** Inserción al final. Conecta con Universidad (`NodoUniversidad*`), Área (`NodoArea*`) y sublista doble de Coautores.
2. **Revistas Científicas:** Inserción **ordenada alfabéticamente por nombre**. Maneja factor de impacto y cuartil (Q1 a Q4).
3. **Áreas de Investigación:** Inserción al final. Posee ID, nombre y descripción temática.

### 3.4. Listas Dobles (4)
1. **Coautores:** Sublista doble contenida en cada `NodoInvestigador`.
2. **Citaciones:** Sublista doble contenida en cada `NodoPublicacion`.
3. **Proyectos de Investigación:** Inserción **ordenada por año de inicio**. Enlace a Investigador Responsable.
4. **Universidades:** Lista doble global de instituciones de educación superior.

---

## 4. DIAGRAMA DE CLASES Y RELACIONES

```
+-------------------+        1       * +----------------------+
|    Universidad    |<-----------------|     Investigador     |
| (Lista Doble: U)  |                  | (Lista Simple: INV)  |
+-------------------+                  +----------------------+
                                               | 1       | 1
                                               |         |
                                             * |         | *
                        +----------------------+         +----------------------+
                        |   Sublista Coautores |         |      Publicacion     |
                        |   (Lista Doble: CO)  |         | (Lista Circular: PUB)|
                        +----------------------+         +----------------------+
                                                               | 1       | *     | 1
                                                               |         |       |
                                      +------------------------+         |       +---------------+
                                      |                                  |                       |
                                    1 v                                * v                     1 v
                             +-----------------+              +--------------------+   +-------------------+
                             |     Revista     |              | Sublista Citaciones|   |      Proyecto     |
                             | (Simple: REV)   |              |  (Lista Doble: CIT)|   |  (Lista Doble: PRY|
                             +-----------------+              +--------------------+   +-------------------+
                                                                                                 | 1
                                                                                                 v
                                                                                       Investigador Resp.
```

---

## 5. MÉTRICAS ACADÉMICAS Y ALGORITMO DEL ÍNDICE H

El cálculo del **Índice H** implementado por la Persona 3 se fundamenta estrictamente en la definición de Jorge E. Hirsch y la especificación de la página 5:

> *"Un investigador posee un índice h si tiene h publicaciones con al menos h citas cada una."*

### 5.1. Algoritmo Manual sin STL:
1. Se recorre la lista circular de publicaciones contando cuántas pertenecen al investigador evaluado ($N$).
2. Si $N = 0$, el índice es 0.
3. Se aloca dinámicamente un arreglo de enteros con puntero simple: `int* citas = new int[N];`.
4. Se extrae la cantidad de citas de cada publicación del autor.
5. Se ordenan las citas en orden descendente mediante ordenamiento manual de intercambio.
6. Se itera comparando la posición $i+1$ con `citas[i]`:
   - Mientras `citas[i] >= i + 1`, el índice actual es $i + 1$.
   - En el primer momento en que `citas[i] < i + 1`, el ciclo se interrumpe.
7. Se libera la memoria dinámica (`delete[] citas;`).

### 5.2. Demostración Matemática del Ejemplo Oficial:
- **Vector de citas del ejemplo:** `[25, 18, 12, 8, 5, 4, 2, 1]`
- Posición 1: $25 \ge 1 \rightarrow$ Sí
- Posición 2: $18 \ge 2 \rightarrow$ Sí
- Posición 3: $12 \ge 3 \rightarrow$ Sí
- Posición 4: $8 \ge 4 \rightarrow$ Sí
- Posición 5: $5 \ge 5 \rightarrow$ Sí
- Posición 6: $4 \ge 6 \rightarrow$ **NO** (se detiene)
- **Resultado exacto:** $\mathbf{H = 5}$.

---

## 6. CATÁLOGO DE CONSULTAS Y REPORTES

### 6.1. Las 10 Consultas Implementadas (con soporte de empates):
1. **Mayor índice H:** Identifica al o los investigadores con el índice de impacto más elevado.
2. **Más citas acumuladas (Persona 3):** Sumatoria de citas de toda la producción del autor.
3. **Publicación más citada (Persona 3):** Nodo de la lista circular con mayor `cantidadCitas`.
4. **Revista con mayor factor de impacto:** Revista con el valor numérico más alto.
5. **Investigador con más coautores:** Mayor cardinalidad en la sublista de coautores.
6. **Universidad con más investigadores:** Conteo de afiliaciones por cada universidad.
7. **Área con más publicaciones:** Suma de artículos generados por investigadores de dicha área.
8. **Año con mayor producción:** Año con más nodos en la lista circular de publicaciones.
9. **Publicación con más autores (Persona 3):** Publicación respaldada por la mayor cantidad de autores (investigador principal + coautores).
10. **Investigador con más artículos en revistas Q1:** Investigador con más publicaciones vinculadas a revistas con cuartil Q1.

### 6.2. Los 9 Reportes Generados:
1. Mostrar todos los investigadores con sus publicaciones completas.
2. Publicaciones ordenadas por año ascendente (recorrido natural de la lista circular).
3. Publicaciones ordenadas por cantidad de citas descendente (ordenamiento manual Persona 3).
4. Revistas registradas con factores de impacto y cuartiles.
5. Red de coautoría detallada de un investigador específico.
6. Publicaciones de una revista indicada por el usuario.
7. Publicaciones de un área de investigación seleccionada.
8. Investigadores agrupados jerárquicamente por universidad.
9. Investigadores ordenados por índice H descendente.

---

## 7. MANUAL DE USUARIO Y EVIDENCIAS DE EJECUCIÓN

Al iniciar el sistema mediante `./sistema_academico.exe` o ejecutando el script `compilar.bat`, se despliega el menú general integrado:

```
================================================================================
     SISTEMA DE GESTION DE PRODUCCION CIENTIFICA Y METRICAS ACADEMICAS          
                 IC2001 ESTRUCTURA DE DATOS - TEC COSTA RICA                    
                 MODULO RESPONSABLE: PERSONA 3 (INTEGRACION TOTAL)              
================================================================================
  [1]  Gestion de Publicaciones Cientificas (Lista Circular - Persona 3)
  [2]  Gestion de Citaciones (Lista Doble / Sublistas - Persona 3)
  [3]  Modulo de Metricas Academicas e Indice H (Persona 3)
  [4]  Consultas del Sistema (10 consultas - Enfoque Persona 3 en 2, 3, 9)
  [5]  Reportes del Sistema (9 reportes - Enfoque Persona 3 en Reporte 3)
  [6]  Gestion de Investigadores (Lista Simple y Sublista Coautores)
  [7]  Gestion de Universidades (Lista Doble)
  [8]  Gestion de Areas de Investigacion (Lista Simple)
  [9]  Gestion de Revistas Cientificas (Lista Simple Ordenada)
  [10] Gestion de Proyectos de Investigacion (Lista Doble Ordenada)
  [11] Demostracion del Ejemplo Oficial de Indice H = 5 (PDF)
  [0]  Salir del Sistema
================================================================================
```

### Ejecución de Prueba de la Opción 11 (Índice H = 5):
```
Posicion de la pub.      Cantidad de Citas
--------------------------------------------------------
1                        25
2                        18
3                        12
4                        8
5                        5
6                        4
7                        2
8                        1
--------------------------------------------------------
Verificacion paso a paso:
  1 publicacion(es) con al menos 1 cita(s): SI (25 >= 1)
  2 publicacion(es) con al menos 2 cita(s): SI (18 >= 2)
  3 publicacion(es) con al menos 3 cita(s): SI (12 >= 3)
  4 publicacion(es) con al menos 4 cita(s): SI (8 >= 4)
  5 publicacion(es) con al menos 5 cita(s): SI (5 >= 5)
  6 publicacion(es) con al menos 6 cita(s): NO (la 6a tiene 4 citas)

Resultado del algoritmo sin STL: Indice H = 5
Resultado esperado por el enunciado: Indice H = 5
>>> COINCIDENCIA EXACTA CONFIRMADA (100% CORRECTO) <<<
```

---

## 8. ANÁLISIS DE RESULTADOS Y COMPLEJIDAD ALGORÍTMICA

1. **Inserción en Lista Circular de Publicaciones:**
   - La inserción ordenada por año presenta una complejidad temporal de $O(P)$ en el peor caso, donde $P$ es la cantidad de publicaciones.
   - El enlace circular asegura que desde cualquier nodo sea posible alcanzar el resto de elementos, garantizando recorridos homogéneos.
2. **Sublista Doble de Citaciones:**
   - Permite navegación bidireccional inmediata ($O(1)$ para avanzar o retroceder) y eliminación en $O(1)$ una vez localizado el puntero al nodo.
3. **Cálculo del Índice H:**
   - Conteo y extracción: $O(P)$
   - Ordenamiento por intercambio de $k$ publicaciones del autor: $O(k^2)$ en memoria dinámica local.
   - Evaluación lineal Hirsch: $O(k)$.
   - Dado que $k \ll 1000$ en perfiles individuales, la respuesta en consola es instantánea (< 1 milisegundo).
4. **Gestión de Memoria:**
   - En C++, al no existir recolección de basura automática, cada clase implementa un destructor explícito (`liberar()`) que recorre y libera cada nodo mediante `delete`.
   - En la lista circular, se rompe el ciclo asignando `ultimo->siguiente = nullptr` antes del bucle de eliminación para prevenir desbordamientos de pila o bucles infinitos.

---

## 9. CONCLUSIONES Y RECOMENDACIONES

### Conclusiones:
1. Se demostró el dominio riguroso del manejo de memoria dinámica en C++ mediante punteros nativos, implementando exitosamente 3 listas simples, 4 listas dobles y 1 lista circular interconectadas.
2. La arquitectura modular adoptada desacopla las responsabilidades en archivos `.h` y `.cpp` independientes, permitiendo que el rol de Persona 3 lidere la lista circular y las citaciones, a la vez que orquesta la integración sin conflictos de dependencias cíclicas.
3. La ausencia de contenedores STL enriqueció la comprensión algorítmica de estructuras fundamentales, garantizando algoritmos de ordenamiento, inserción y eliminación altamente optimizados.

### Recomendaciones:
1. Para despliegues a gran escala con millones de registros, se recomienda indexar las publicaciones mediante estructuras jerárquicas balanceadas (como árboles AVL o B+) para reducir el costo de búsqueda de $O(N)$ a $O(\log N)$.
2. Mantener siempre el control del puntero circular antes de operaciones de vaciado o serialización para evitar referencias colgantes (*dangling pointers*).

---

## 10. INSTRUCCIONES DE COMPILACIÓN Y EJECUCIÓN

### Compilación rápida con MinGW en Windows:
Haga doble clic en el archivo:
```bat
compilar.bat
```
O ejecute manualmente en la terminal de comandos de Windows (PowerShell / CMD):
```bash
g++ -std=c++11 -Wall -Wextra -O2 -o sistema_academico.exe main.cpp Sistema.cpp Publicacion.cpp Citacion.cpp Metricas.cpp Consultas.cpp Reportes.cpp Investigador.cpp Coautor.cpp Revista.cpp Proyecto.cpp Universidad.cpp Area.cpp
```
Y luego inicie el ejecutable:
```bash
.\sistema_academico.exe
```
