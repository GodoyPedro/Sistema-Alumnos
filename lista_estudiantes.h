// #include "sistema_estudiantes.h"
#include "lector_csv.h"
#include <stdbool.h>

typedef struct estructuraMateriaRendida
{
    int id;
    int nota;
    struct estructuraMateriaRendida *proximo;
} MateriaHistoria;

typedef struct estructuraHistoriaAcademica
{
    MateriaHistoria *materias_en_curso;
    MateriaHistoria *materias_aprobadas;
    MateriaHistoria *materias_desaprobadas;
} HistoriaAcademica;

typedef struct estructuraDatos
{
    char *nombre;
    int edad;
    char *dni;
    int legajo;
} Datos;

typedef struct estructuraUniversidad
{
    struct estructuraListaEnlazada *estudiantes;
    Materia *materias;
} Universidad;

typedef struct estructuraEstudiante
{
    Datos *datos_personales;
    HistoriaAcademica *historia_academica;
} Estudiante;

typedef struct estructuraEstudianteConectado
{
    Estudiante *estudiante;
    struct estructuraEstudianteConectado *proximo;
} EstudianteConectado;

typedef struct estructuraListaEnlazada
{
    bool orden;
    EstudianteConectado *cabeza;
} ListaEstudiantes;

bool comparador(EstudianteConectado *estudiante1, EstudianteConectado *estudiante2, bool orden);
void agregarEstudiante(ListaEstudiantes *lista, Datos *datos, HistoriaAcademica *historia_academica);
ListaEstudiantes *crearLista(bool orden);
bool estaVacia(ListaEstudiantes *lista);
int obtenerLargoEstudiantes(ListaEstudiantes *lista);
void imprimirLista(ListaEstudiantes *lista, Materia *correlativas);
EstudianteConectado *buscarEstudiantesPorNombre(ListaEstudiantes *lista, char *nombre_a_buscar);
EstudianteConectado *buscarEstudiantesPorRangoEdad(ListaEstudiantes *lista, int rango_inicio, int rango_final);
void borrarMateria(MateriaHistoria **lista_a_borrar_materia, int id_materia);
bool noEstoyAnotado(MateriaHistoria *lista_en_curso, MateriaHistoria *lista_rendidas, int id_materia);
bool puedoAnotarme(MateriaConectada *lista_requiere_materia, MateriaHistoria *lista_rendidas);
Estudiante **buscarEstudiante(ListaEstudiantes *lista, int legajo_estudiante);
void anotarAMateria(ListaEstudiantes *lista, int legajo_estudiante, int id_materia, Materia *lista_materias);
bool buscarMateriaDesaprobada(MateriaHistoria *lista_desaprobadas, int id_materia);
void rendirMateria(ListaEstudiantes *lista, int legajo_estudiante, int id_materia, int nota);
float obtenerPromedio(ListaEstudiantes *lista, int legajo_estudiante);