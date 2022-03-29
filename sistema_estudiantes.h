// #include "lector_csv.h"
#include "lista_estudiantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HistoriaAcademica *crearHistoriaAcademica();
void agregarMateriaHistoriaAcademica(HistoriaAcademica *historia, int id, int nota, int identificador);
void crearEstudiante(Universidad *universidad, char *nombre, int edad, char *dni, int legajo, HistoriaAcademica *historia);
Universidad *crearSistema(char *ruta_archivo, bool orden_lista_estudiantes);
void imprimirListaEstudiantes(Universidad *universidad);
void anotarEstudianteAMateria(Universidad *universidad, int legajo_estudiante, int id_materia);
void rendirUnaMateria(Universidad *universidad, int legajo_estudiante, int id_materia, int nota);
void imprimirListaRecibida(Universidad *universidad, EstudianteConectado *estudiantes);
void imprimirDatosSimples(EstudianteConectado *estudiantes);
void buscarPorNombre(Universidad *universidad, char *nombre_a_buscar, bool especificaciones);
void buscarPorRangoEdad(Universidad *universidad, int rango_inicio, int rango_final, bool especificaciones);
void imprimirRangoListaMaterias(Materia *materias, int rango_inicio, int rango_final);
void mostrarMaterias(Universidad *universidad, int cuatrimestre, int anio);
void generarDatosMasivos(Universidad *universidad, int cantidad);