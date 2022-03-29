#include "sistema_estudiantes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * Funcion: 
 * Crea un estudiante historia academica, almacena memoria y lo devuelve
 * 
 * 		return (*HistoriaAcademica): estudiante vacio
*/
HistoriaAcademica *crearHistoriaAcademica()
{
    HistoriaAcademica *historia_academica = malloc(sizeof(HistoriaAcademica));
    historia_academica->materias_en_curso = malloc(sizeof(MateriaHistoria));
    historia_academica->materias_aprobadas = malloc(sizeof(MateriaHistoria));
    historia_academica->materias_desaprobadas = malloc(sizeof(MateriaHistoria));

    historia_academica->materias_en_curso = NULL;
    historia_academica->materias_aprobadas = NULL;
    historia_academica->materias_desaprobadas = NULL;
}

/**
 * Funcion: DEBUG 
 * Agrega una materia a una de las 3 listas especificadas por el identificador de la
 * historia
 * SU UNICO PROPOSITO ES EL DEBUG Y LA CREACION MASIVA DE DATOS PARA PRUEBAS
 * 
 * 		return (void)
*/
void agregarMateriaHistoriaAcademica(HistoriaAcademica *historia, int id, int nota, int identificador)
{

    MateriaHistoria *nueva_materia = malloc(sizeof(MateriaHistoria));
    nueva_materia->id = id;
    nueva_materia->nota = nota;
    nueva_materia->proximo = NULL;

    MateriaHistoria **estudiante;

    if (identificador == 1)
    {
        estudiante = &(historia->materias_en_curso);
    }
    else if (identificador == 2)
    {
        estudiante = &(historia->materias_aprobadas);
    }
    else if (identificador == 3)
    {
        estudiante = &(historia->materias_desaprobadas);
    }
    else
    {
        printf("El identificador no es valido\n");
        return;
    }

    if ((*estudiante) == NULL)
    {
        (*estudiante) = nueva_materia;
    }
    else
    {
        while ((*estudiante)->proximo != NULL)
        {
            estudiante = &(*estudiante)->proximo;
        }
        (*estudiante)->proximo = nueva_materia;
    }
}

/**
 * Funcion: 
 * A partir de datos crea las estructuras necesarias para llamar al metodo
 * agregarEstudiante de lista_estudiantes_con_struct
 * 		
 * 		universidad (*Universidad): estudiante a struct universidad
 * 		nombre (*char): nombre del estudiante a crear
 * 		edad (int): edad del estudiante a crear
 * 		dni (*char): dni del estudiante a crear
 * 		legajo (int): legajo del estudiante a crear
 * 		historia (*Historia): estudiante a struct historia (deberia ser NULL en caso de 
 * 		que no se use para crear un estudiante ya anotado materias)
 * 
 * 		return (void)
*/
void crearEstudiante(Universidad *universidad, char *nombre, int edad, char *dni, int legajo, HistoriaAcademica *historia)
{
    Datos *datos = malloc(sizeof(Datos));
    datos->nombre = nombre;
    datos->edad = edad;
    datos->dni = dni;
    datos->legajo = legajo;

    agregarEstudiante(universidad->estudiantes, datos, historia);
}

/**
 * Funcion: 
 *  Crea la lista de estudiante y de correlatividades inicializando y devolviendo una 
 * struct Universidad
 * 		
 * 		ruta_archivo (*char): ruta del archivo .csv
 * 		orden_lista_estudiantes (bool): false = menor a mayor, true = mayor a menor
 *  
 * 		return (*Universidad): struct creada y cargada con datos
*/
Universidad *crearSistema(char *ruta_archivo, bool orden_lista_estudiantes)
{
    Universidad *universidad = malloc(sizeof(Universidad));
    universidad->estudiantes = crearLista(false);
    universidad->materias = obtenerMateriasCorrelativas("datos_completos.csv");
}

/**
 * Funcion: 
 *  Imprime la lista de estudiantes de la universidad
 * 		
 * 		universidad (*Universidad): puntero de tipo Universidad
 *  
 * 		return (void)
*/
void imprimirListaEstudiantes(Universidad *universidad)
{
    imprimirLista(universidad->estudiantes, universidad->materias);
    printf("\n\n");
}

/**
 * Funcion: 
 *  Anota a estudiante dentro de la universidad cuyo legajo coincida con legajo_estudiante
 * 	a la materia que coincida con id_materia, siempre que cumpla los requerimientos
 * 
 * 		universidad (*Universidad): puntero de tipo Universidad
 * 		legajo_estudiante (int): legajo del estudiante (5 digitos)
 * 		id_materia (int): id de la materia (2 digitos)
 *  
 * 		return (void)
*/
void anotarEstudianteAMateria(Universidad *universidad, int legajo_estudiante, int id_materia)
{
    anotarAMateria(universidad->estudiantes, legajo_estudiante, id_materia, universidad->materias);
}

/**
 * Funcion: 
 *  Rinde una materia que coincida con el id_materia de un estudiante cuyo legajo coincida con legajo_estudiante
 * 	siempre que este anotado a ella o la haya desaprobado previamente
 * 
 * 		universidad (*Universidad): puntero de tipo Universidad
 * 		legajo_estudiante (int): legajo del estudiante (5 digitos)
 * 		id_materia (int): id de la materia (2 digitos)
 * 		nota (int): nota con la que rinde la materia (2 digitos)
 *  
 * 		return (void)
*/
void rendirUnaMateria(Universidad *universidad, int legajo_estudiante, int id_materia, int nota)
{
    rendirMateria(universidad->estudiantes, legajo_estudiante, id_materia, nota);
}

/**
 * Funcion: 
 *  Imprime una lista detallada de EstudianteConectado pasada por parametro
 * 
 * 		universidad (*Universidad): puntero de tipo Universidad
 * 		estudiantes (*EstudianteConectado): lista de estudiantes a imprimir
 *  
 * 		return (void)
*/
void imprimirListaRecibida(Universidad *universidad, EstudianteConectado *estudiantes)
{
    EstudianteConectado *estudiante = estudiantes;

    Datos *datos_puntero = malloc(sizeof(Datos));
    HistoriaAcademica *datos_historia = malloc(sizeof(HistoriaAcademica));

    while (estudiante->proximo != NULL)
    {
        datos_puntero = estudiante->estudiante->datos_personales;
        datos_historia = estudiante->estudiante->historia_academica;
        printf("--------------------------------------\n");
        printf("------ Datos personales ------ \n");
        printf("Nombre: %s\n", estudiante->estudiante->datos_personales->nombre);
        printf("Edad: %d\n", datos_puntero->edad);
        printf("DNI: %s\n", datos_puntero->dni);
        printf("Legajo: %d\n", datos_puntero->legajo);
        printf("Promedio: %.2f\n", obtenerPromedio(universidad->estudiantes, datos_puntero->legajo));
        printf("----- Historia Academica -----\n");
        printf("Materias en curso:\n");

        MateriaHistoria *cursor_dentro = datos_historia->materias_en_curso;

        if (cursor_dentro == NULL)
        {
            printf("\tNo hay materias en curso\n");
        }
        else
        {
            while (cursor_dentro != NULL)
            {
                printf("\tNombre: %s\n", universidad->materias[cursor_dentro->id - 1].nombre);
                printf("\tId: %d\n\n", cursor_dentro->id);
                cursor_dentro = cursor_dentro->proximo;
            }
        }

        printf("Materias aprobadas:\n");

        cursor_dentro = datos_historia->materias_aprobadas;

        if (cursor_dentro == NULL)
        {
            printf("\tNo hay materias aprobadas\n");
        }
        else
        {
            while (cursor_dentro != NULL)
            {
                printf("\tNombre: %s\n", universidad->materias[cursor_dentro->id - 1].nombre);
                printf("\tId: %d\n", cursor_dentro->id);
                printf("\tNota: %d\n\n", cursor_dentro->nota);
                cursor_dentro = cursor_dentro->proximo;
            }
        }

        printf("Materias desaprobadas:\n");

        cursor_dentro = datos_historia->materias_desaprobadas;
        if (cursor_dentro == NULL)
        {
            printf("\tNo hay materias desaprobadas\n");
        }
        else
        {
            while (cursor_dentro != NULL)
            {
                printf("\tNombre: %s\n", universidad->materias[cursor_dentro->id - 1].nombre);
                printf("\tId: %d\n", cursor_dentro->id);
                printf("\tNota: %d\n\n", cursor_dentro->nota);
                cursor_dentro = cursor_dentro->proximo;
            }
        }
        printf("--------------------------------------\n");
        estudiante = estudiante->proximo;
    }
}

/**
 * Funcion: 
 *  Imprime una lista con datos siemples, de EstudianteConectado pasada por parametro
 * 
 * 		universidad (*Universidad): puntero de tipo Universidad
 * 		estudiantes (*EstudianteConectado): lista de estudiantes a imprimir
 *  
 * 		return (void)
*/
void imprimirDatosSimples(EstudianteConectado *estudiantes)
{
    EstudianteConectado *cursor = estudiantes;

    while (cursor->proximo != NULL)
    {
        printf("------ Datos personales ------ \n");
        printf("Nombre: %s\n", cursor->estudiante->datos_personales->nombre);
        printf("Edad: %d\n", cursor->estudiante->datos_personales->edad);
        printf("DNI: %s\n", cursor->estudiante->datos_personales->dni);
        printf("Legajo: %d\n", cursor->estudiante->datos_personales->legajo);
        cursor = cursor->proximo;
    }
}

/**
 * Funcion: 
 *  Imprime una lista de estudiantes que contengan en su nombre el nombre_a_buscar, se puede elegir entre
 *  imprimir la lista detallada o solo los datos personales
 * 
 * 		universidad (*Universidad): puntero de tipo Universidad
 * 		nombre_a_buscar (*char): nombre a buscar de estudiante
 * 		especificaciones (bool): false si se quiere datos siemples, true en caso contrario
 *  
 * 		return (void)
*/
void buscarPorNombre(Universidad *universidad, char *nombre_a_buscar, bool especificaciones)
{
    if (especificaciones)
    {
        imprimirListaRecibida(universidad, buscarEstudiantesPorNombre(universidad->estudiantes, nombre_a_buscar));
    }
    else
    {
        imprimirDatosSimples(buscarEstudiantesPorNombre(universidad->estudiantes, nombre_a_buscar));
    }
}

/**
 * Funcion: 
 *  Imprime una lista de estudiantes que se encuentren dentro del rango rango_inicio - rango_final, se puede elegir entre
 *  imprimir la lista detallada o solo los datos personales
 * 
 * 		universidad (*Universidad): puntero de tipo Universidad
 * 		rango_inicio (int): rango inicial de edad
 * 		rango_final (int): rango final de edad
 * 		especificaciones (bool): false si se quiere datos siemples, true en caso contrario
 *  
 * 		return (void)
*/
void buscarPorRangoEdad(Universidad *universidad, int rango_inicio, int rango_final, bool especificaciones)
{
    if (especificaciones)
    {
        imprimirListaRecibida(universidad, buscarEstudiantesPorRangoEdad(universidad->estudiantes, rango_inicio, rango_final));
    }
    else
    {
        imprimirDatosSimples(buscarEstudiantesPorRangoEdad(universidad->estudiantes, rango_inicio, rango_final));
    }
}

/**
 * Funcion: 
 *  Imprime la porcion de la lista de materias correlativas que se pase por parametro
 * 
 * 		materias (*Materia): lista de materias correlativas
 * 		rango_inicio (int): rango inicial de impresion
 * 		rango_final (int): rango final de impresion
 *  
 * 		return (void)
*/
void imprimirRangoListaMaterias(Materia *materias, int rango_inicio, int rango_final)
{
    for (int h = rango_inicio; h < rango_final + 1; h++)
    {
        printf("--------------------------------------\n");
        printf("Nombre: %s\n", materias[h].nombre);
        printf("Id: %d\n", materias[h].id);

        printf("Requiere: ");
        MateriaConectada *estudiante = materias[h].requiere;
        if (estudiante->id == -1)
        {
            printf("No requiere ninguna materia previa para ser cursada");
        }
        else
        {
            while (estudiante->proximo != NULL)
            {
                printf("\tId: %d", estudiante->id);
                estudiante = estudiante->proximo;
            }
        }
        printf("\n");

        printf("Es requerida: ");
        estudiante = materias[h].es_requerido;
        if (estudiante->id == -1)
        {
            printf("No es requerida por ninguna materia posterior");
        }
        else
        {
            while (estudiante->proximo != NULL)
            {
                printf("\tId es requerido: %d", estudiante->id);
                estudiante = estudiante->proximo;
            }
        }
        printf("\n");
        printf("--------------------------------------\n");
    }
}

/**
 * Funcion: 
 *  Muestra un listado reducido de materias, se puede seleccionar un cuatrimestre o un anio especifico
 * En caso de querer imprimir solo materias por cuatrimestre, anio debe ser -1 y lo mismo en caso contrario para
 * cuatrimestre
 * 
 * 		universidad (*Materia): puntero de tipo Universidad
 * 		cuatrimestre (int): cuatrimestre a imprimir
 * 		anio (int): anio a imprimir
 *  
 * 		return (void)
*/
void mostrarMaterias(Universidad *universidad, int cuatrimestre, int anio)
{
    datosCuatriAnios *datos = cargarArchivoConfiguracionMaterias("configuracion_materias.csv");

    if (cuatrimestre >= 0 && cuatrimestre <= datos->cantidad_cuatrimestres)
    {

        if (cuatrimestre == 0)
        {
            printf("\n\nImprimiendo todas las materias\n\n");
            imprimirRangoListaMaterias(universidad->materias, 0, datos->cuatrimestres[datos->cantidad_cuatrimestres - 1]);
        }
        else if (cuatrimestre == 1)
        {
            printf("\n\nImprimiendo las materias del cuatrimestre %d\n\n \n", cuatrimestre);
            imprimirRangoListaMaterias(universidad->materias, 0, datos->cuatrimestres[cuatrimestre - 1]);
        }
        else
        {
            printf("\n\nImprimiendo las materias del cuatrimestre %d\n\n \n", cuatrimestre);
            imprimirRangoListaMaterias(universidad->materias, datos->cuatrimestres[cuatrimestre - 2] + 1, datos->cuatrimestres[cuatrimestre - 1]);
        }
    }

    if (anio >= 0 && anio <= datos->cantidad_anios)
    {

        if (anio == 0)
        {
            printf("\n\nImprimiendo todas las materias\n\n");
            imprimirRangoListaMaterias(universidad->materias, 0, datos->anios[datos->cantidad_anios - 1]);
        }
        else if (anio == 1)
        {
            printf("\n\nImprimiendo las materias del anio %d\n\n", anio);
            imprimirRangoListaMaterias(universidad->materias, 0, datos->anios[anio - 1]);
        }
        else
        {
            printf("\n\nImprimiendo las materias del anio %d\n\n", anio);
            imprimirRangoListaMaterias(universidad->materias, datos->anios[anio - 2] + 1, datos->anios[anio - 1]);
        }
    }
}

/**
 * Funcion: 
 * 	Aniade tantos estudiantes a la lista de estudiantes de la universidad como 
 *  sea cantidad
 * 
 * 		universidad (*Materia): puntero de tipo Universidad
 * 		cantidad (int): cantidad de alumnos a agregar
 *  
 * 		return (void)
*/
void generarDatosMasivos(Universidad *universidad, int cantidad)
{
    srand(time(NULL));

    char *arreglo_nombre[10] = {
        "pedro godoy",
        "martin perez",
        "joaquin gomez",
        "alejo via",
        "marcelo gutierrez",
        "manuel eche",
        "lucas ivaldi",
        "braian gaza",
        "pablo carmuchi",
        "jose godoy"};

    int valor_random = rand();
    for (int i = 0; i < cantidad; i++)
    {
        crearEstudiante(universidad, arreglo_nombre[valor_random % 10], valor_random % 100, "dni", (valor_random % 10) * 1000, NULL);
        valor_random = rand();
    }

    printf("Se completo la generacion de datos\n");
}