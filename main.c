#include "sistema_estudiantes.h"

int main(int argc, char const *argv[])
{
    Universidad *universidad = crearSistema("datos_completos.csv", false);

    HistoriaAcademica *historia_pedro = crearHistoriaAcademica();
    agregarMateriaHistoriaAcademica(historia_pedro, 25, 2, 1);
    agregarMateriaHistoriaAcademica(historia_pedro, 15, 2, 1);

    HistoriaAcademica *historia_brayan = crearHistoriaAcademica();
    agregarMateriaHistoriaAcademica(historia_brayan, 25, 2, 1);
    agregarMateriaHistoriaAcademica(historia_brayan, 15, 2, 1);

    HistoriaAcademica *historia_apa = crearHistoriaAcademica();
    agregarMateriaHistoriaAcademica(historia_apa, 25, 2, 1);
    agregarMateriaHistoriaAcademica(historia_apa, 15, 2, 1);

    // generarDatosMasivos(universidad, 100001);

    crearEstudiante(universidad, "Pedro Godoy", 22, "41823376", 57267, NULL);
    crearEstudiante(universidad, "Jose Godoy", 58, "54718293", 20239, NULL);
    crearEstudiante(universidad, "Fiamma dennise", 22, "82819302", 20231, NULL);

    anotarEstudianteAMateria(universidad, 57267, 1);
    anotarEstudianteAMateria(universidad, 57267, 2);
    anotarEstudianteAMateria(universidad, 20239, 3);

    rendirUnaMateria(universidad, 57267, 1, 10);
    rendirUnaMateria(universidad, 57267, 2, 3);

    buscarPorNombre(universidad, "Godoy", false);
    buscarPorRangoEdad(universidad, 10, 30, true);

    mostrarMaterias(universidad, 1, -1);

    imprimirListaEstudiantes(universidad);

    free(universidad);
}