#include "lista_estudiantes.h"
#include <assert.h>
#include <search.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Funcion: 
 * Retorna true o false dependiendo si el nombre del estudiante1 es alfabeticamente mayor que el nombre
 * del estudiante2
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes de la universidad
 * 		datos (*Datos): estructura de datos personales del alumno
 * 		historia_academica (*HistoriaAcademica): estructura de la historia academica del alumno
 * 
 * 		return (bool): true si el nombre del estudiante1 es mayor que el estudiante2, false en caso contrario
*/
bool comparador(EstudianteConectado *estudiante1, EstudianteConectado *estudiante2, bool orden)
{
    /* La funcion strcmp devuelve un numero positivo si la primer cadena es mayor que la segunda */
    bool mayor_a_menor = orden;
    EstudianteConectado *nodoNuevo1 = (mayor_a_menor) ? estudiante1 : estudiante2;
    EstudianteConectado *nodoNuevo2 = (mayor_a_menor) ? estudiante2 : estudiante1;

    return strcmp(nodoNuevo1->estudiante->datos_personales->nombre, nodoNuevo2->estudiante->datos_personales->nombre) > 0;
}

/**
 * Funcion: 
 * Agrega un estudiante a la lista de estudiantes
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes de la universidad
 * 		datos (*Datos): estructura de datos personales del alumno
 * 		historia_academica (*HistoriaAcademica): estructura de la historia academica del alumno
 * 
 * 		return (void)
*/
void agregarEstudiante(ListaEstudiantes *lista, Datos *datos, HistoriaAcademica *historia_academica)
{

    /* Asigno la memoria para el estudiante */
    EstudianteConectado *estudiante_nuevo = malloc(sizeof(EstudianteConectado));
    estudiante_nuevo->estudiante = malloc(sizeof(Estudiante));
    estudiante_nuevo->estudiante->datos_personales = malloc(sizeof(Datos));
    estudiante_nuevo->estudiante->historia_academica = malloc(sizeof(HistoriaAcademica));
    estudiante_nuevo->estudiante->historia_academica->materias_en_curso = malloc(sizeof(MateriaHistoria));
    estudiante_nuevo->estudiante->historia_academica->materias_aprobadas = malloc(sizeof(MateriaHistoria));
    estudiante_nuevo->estudiante->historia_academica->materias_desaprobadas = malloc(sizeof(MateriaHistoria));

    /* Seteo las variables correspondientes */
    estudiante_nuevo->estudiante->historia_academica->materias_en_curso = NULL;
    estudiante_nuevo->estudiante->historia_academica->materias_aprobadas = NULL;
    estudiante_nuevo->estudiante->historia_academica->materias_desaprobadas = NULL;
    *estudiante_nuevo->estudiante->datos_personales = *datos;
    if (historia_academica != NULL)
    {
        *estudiante_nuevo->estudiante->historia_academica = *historia_academica;
    }
    estudiante_nuevo->proximo = NULL;

    /* Si no hay ningun estudiante */
    if (lista->cabeza->proximo == NULL)
    {
        lista->cabeza->proximo = estudiante_nuevo;
    }
    /* Si ya existen estudiantes en la lista */
    else
    {
        /* Si tiene que ir primero con respecto al orden */
        if (comparador(estudiante_nuevo, lista->cabeza->proximo, lista->orden))
        {

            estudiante_nuevo->proximo = lista->cabeza->proximo;
            lista->cabeza->proximo = estudiante_nuevo;
        }
        /* Sino, busco el lugar donde le corresponde respecto al orden de la lista */
        else
        {
            EstudianteConectado *cursor = lista->cabeza->proximo;
            while ((cursor->proximo != NULL) && comparador(cursor->proximo, estudiante_nuevo, lista->orden))
            {
                cursor = cursor->proximo;
            }
            /* Si lo agrego al final */
            if (cursor->proximo == NULL)
            {
                cursor->proximo = estudiante_nuevo;
            }
            /* Si esta en el medio */
            else
            {
                estudiante_nuevo->proximo = cursor->proximo;
                cursor->proximo = estudiante_nuevo;
            }
        }
    }
}

/**
 * Funcion: 
 * Creo la lista de estudiantes y la devuelvo
 * 
 * 		orden (bool): orden de la lista
 * 
 * 		return (*ListaEstudiantes): lista de estudiantes creada y con memoria alojada
*/
ListaEstudiantes *crearLista(bool orden)
{
    ListaEstudiantes *lista = malloc(sizeof(ListaEstudiantes));
    lista->orden = orden;
    //nodo ficticio
    EstudianteConectado *estudiante_nuevo = malloc(sizeof(EstudianteConectado));

    estudiante_nuevo->estudiante = malloc(sizeof(Estudiante));
    estudiante_nuevo->estudiante->datos_personales = NULL;
    estudiante_nuevo->estudiante->historia_academica = NULL;
    estudiante_nuevo->proximo = NULL;
    lista->cabeza = estudiante_nuevo;
    return lista;
}

/**
 * Funcion: 
 * Devuelve si la lista no contiene elementos
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes de la universidad
 * 
 * 		return (bool): true si la cabeza de la lista es distinto de null, false en caso contrario
*/
bool estaVacia(ListaEstudiantes *lista)
{
    return lista->cabeza->proximo == NULL;
}

/**
 * Funcion: 
 * Devuelve la cantidad de elementos en lista
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes de la universidad
 * 
 * 		return (int): cantidad de estudiantes presentes en lista
*/
int obtenerLargoEstudiantes(ListaEstudiantes *lista)
{
    int nodos;

    if (estaVacia(lista))
    {
        nodos = 0;
    }
    else
    {
        nodos = 1;
        EstudianteConectado *cursor = lista->cabeza->proximo;
        while (cursor->proximo != NULL)
        {
            cursor = cursor->proximo;
            nodos += 1;
        }
    }
    return nodos;
}

/**
 * Funcion: 
 * Devuelve un puntero a puntero del estudiante que coincida con el legajo_estudiante
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes anotados en la universidad
 * 		legajo_estudiante (int): legajo del estudiante (5 digitos)
 * 
 * 		return (**Estudiante): estudiante cuyo legajo coincide con legajo_estudiante 
*/
Estudiante **buscarEstudiante(ListaEstudiantes *lista, int legajo_estudiante)
{
    Estudiante **estudiante_a_anotar;
    EstudianteConectado *cursor = lista->cabeza->proximo;

    while (cursor != NULL)
    {
        if (cursor->estudiante->datos_personales->legajo == legajo_estudiante)
        {
            estudiante_a_anotar = &cursor->estudiante;
            return estudiante_a_anotar;
        }
        cursor = cursor->proximo;
    }
    return NULL;
}

/**
 * Funcion: 
 * Devuelve el promedio del estudiante que coincida con el legajo_estudiante
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes anotados en la universidad
 * 		legajo_estudiante (int): legajo del estudiante (5 digitos)
 * 
 * 		return (float): promedio de materias aprobadas y desaprobadas
*/
float obtenerPromedio(ListaEstudiantes *lista, int legajo_estudiante)
{

    int suma_total = 0;
    int cantidad_materias = 0;

    Estudiante **estudiante = buscarEstudiante(lista, legajo_estudiante);

    MateriaHistoria *cursor_aprobadas = (*estudiante)->historia_academica->materias_aprobadas;
    MateriaHistoria *cursor_desaprobadas = (*estudiante)->historia_academica->materias_desaprobadas;

    if (cursor_aprobadas == NULL && cursor_desaprobadas == NULL)
    {
        return 0;
    }
    while (cursor_aprobadas != NULL)
    {
        suma_total += cursor_aprobadas->nota;
        cantidad_materias++;
        cursor_aprobadas = cursor_aprobadas->proximo;
    }

    while (cursor_desaprobadas != NULL)
    {
        suma_total += cursor_desaprobadas->nota;
        cantidad_materias++;
        cursor_desaprobadas = cursor_desaprobadas->proximo;
    }

    return (float)suma_total / cantidad_materias;
}

/**
 * Funcion: 
 * Imprime en consola los datos de cada estudiante
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes de la universidad
 * 
 * 		return (void)
*/
void imprimirLista(ListaEstudiantes *lista, Materia *correlativas)
{

    if (estaVacia(lista))
    {
        printf("La lista esta vacia");
    }
    else
    {
        int largo = obtenerLargoEstudiantes(lista);
        EstudianteConectado *cursor = lista->cabeza->proximo;

        Datos *datos_puntero = malloc(sizeof(Datos));
        HistoriaAcademica *datos_historia = malloc(sizeof(HistoriaAcademica));
        for (int i = 0; i < largo; i++)
        {
            datos_puntero = cursor->estudiante->datos_personales;
            datos_historia = cursor->estudiante->historia_academica;
            printf("--------------------------------------\n");
            printf("------ Datos personales ------ \n");
            printf("Nombre: %s\n", datos_puntero->nombre);
            printf("Edad: %d\n", datos_puntero->edad);
            printf("DNI: %s\n", datos_puntero->dni);
            printf("Legajo: %d\n", datos_puntero->legajo);
            printf("Promedio: %.2f\n", obtenerPromedio(lista, datos_puntero->legajo));
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
                    printf("\tNombre: %s\n", correlativas[cursor_dentro->id - 1].nombre);
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
                    printf("\tNombre: %s\n", correlativas[cursor_dentro->id - 1].nombre);
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
                    printf("\tNombre: %s\n", correlativas[cursor_dentro->id - 1].nombre);
                    printf("\tId: %d\n", cursor_dentro->id);
                    printf("\tNota: %d\n\n", cursor_dentro->nota);
                    cursor_dentro = cursor_dentro->proximo;
                }
            }
            printf("--------------------------------------\n");
            cursor = cursor->proximo;
        }
    }
}

/**
 * Funcion: 
 * Devuelve una lista de estudiantes en la que las edades se encuentran dentro del rango de edades
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes de la universidad
 * 		rango_inicio (int): rango inicial de edad
 * 		rango_final (int): rango final de edad
 * 
 * 		return (*EstudianteConectado): lista de estudiantes cuya edad esta dentro del rango
*/
EstudianteConectado *buscarEstudiantesPorRangoEdad(ListaEstudiantes *lista, int rango_inicio, int rango_final)
{

    EstudianteConectado *cabeza_lista_a_devolver = malloc(sizeof(EstudianteConectado));
    cabeza_lista_a_devolver->estudiante = malloc(sizeof(Estudiante));
    cabeza_lista_a_devolver->proximo = NULL;

    EstudianteConectado **puntero_estudiante = &cabeza_lista_a_devolver;

    EstudianteConectado *cursor = lista->cabeza->proximo;

    while (cursor != NULL)
    {

        if (cursor->estudiante->datos_personales->edad <= rango_final && cursor->estudiante->datos_personales->edad >= rango_inicio)
        {

            *(*puntero_estudiante)->estudiante = *cursor->estudiante;
            EstudianteConectado *estudiante_proximo = malloc(sizeof(EstudianteConectado));
            estudiante_proximo->estudiante = malloc(sizeof(Estudiante));
            estudiante_proximo->proximo = NULL;
            (*puntero_estudiante)->proximo = estudiante_proximo;
            puntero_estudiante = &((*puntero_estudiante)->proximo);
        }

        cursor = cursor->proximo;
    }

    return cabeza_lista_a_devolver;
}

/**
 * Funcion: 
 * Devuelve una lista de estudiantes en la que los nombres contengan el nombre a buscar
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes de la universidad
 * 		nombre_a_buscar (*char): nombre de estudiante a buscar
 * 
 * 		return (*EstudianteConectado): lista de estudiantes cuyo nombre contiene nombre_a_buscar
*/
EstudianteConectado *buscarEstudiantesPorNombre(ListaEstudiantes *lista, char *nombre_a_buscar)
{
    /* Creo el nodo que voy a devolver */
    EstudianteConectado *cabeza_lista_a_devolver = malloc(sizeof(EstudianteConectado));
    cabeza_lista_a_devolver->estudiante = malloc(sizeof(Estudiante));
    cabeza_lista_a_devolver->proximo = NULL;

    /* Trabajo con un puntero a puntero para ir agregando nodos a la cabeza_lista_a_devolver */
    EstudianteConectado **puntero_estudiante = &cabeza_lista_a_devolver;

    EstudianteConectado *cursor = lista->cabeza->proximo;

    bool nombre_encontrado_principio = false;
    bool nombre_encontrado_final = false;

    /* Recorro la lista hasta que encuentro el ultimo nombre que coincide (me aprovecho de esto porque la lista esta ordenada por nombre)*/
    while (!nombre_encontrado_final && cursor != NULL)
    {
        if (strstr(cursor->estudiante->datos_personales->nombre, nombre_a_buscar) != NULL)
        {
            nombre_encontrado_principio = true;
            *(*puntero_estudiante)->estudiante = *cursor->estudiante;
            EstudianteConectado *estudiante_proximo = malloc(sizeof(EstudianteConectado));
            estudiante_proximo->estudiante = malloc(sizeof(Estudiante));
            estudiante_proximo->proximo = NULL;
            (*puntero_estudiante)->proximo = estudiante_proximo;
            puntero_estudiante = &((*puntero_estudiante)->proximo);
        }
        else if (nombre_encontrado_principio)
        {
            nombre_encontrado_final = true;
        }

        cursor = cursor->proximo;
    }

    return cabeza_lista_a_devolver;
}

/**
 * Funcion: 
 * Elimina de la lista pasada por parametro, la materia que coincida con id_materia
 * 
 * 		lista_a_borrar_materia (*MateriaHistoria): lista de materias donde se va a eliminar un elemento
 * 		id_materia (int): id de la materia a buscar
 * 
 * 		return (void)
*/
void borrarMateria(MateriaHistoria **lista_a_borrar_materia, int id_materia)
{

    MateriaHistoria **cursor = lista_a_borrar_materia;

    if ((*cursor)->id == id_materia)
    {

        if ((*cursor)->proximo == NULL)
        {
            (*cursor) = NULL;
        }
        else
        {
            MateriaHistoria *nodoTemporal = malloc(sizeof(MateriaHistoria));
            nodoTemporal->proximo = (*cursor);
            *cursor = (*cursor)->proximo;
            free(nodoTemporal);
            nodoTemporal = NULL;
        }
    }
    else
    {
        while ((*cursor)->proximo->id != id_materia)
        {
            cursor = &(*cursor)->proximo;
        }
        MateriaHistoria *nodoTemporal = malloc(sizeof(MateriaHistoria));
        nodoTemporal = (*cursor)->proximo;
        (*cursor)->proximo = (*cursor)->proximo->proximo;
        free(nodoTemporal);
        nodoTemporal = NULL;
    }
}

/**
 * Funcion: 
 * Devuelve false si el id_materia existe dentro de la lista_en_curso o dentro de la lista_rendidas
 * Si no existe el id_materia dentro de las mismas, retorna true
 * 
 * 		lista_en_curso (*MateriaHistoria): lista de materias en curso del estudiante
 * 		lista_rendidas (*MateriaHistoria): lista de materias rendidas del estudiante
 * 		id_materia (int): id de la materia a buscar
 * 
 * 		return (bool): true si no se encuentra la materia, false si la encuentra
*/
bool noEstoyAnotado(MateriaHistoria *lista_en_curso, MateriaHistoria *lista_rendidas, int id_materia)
{

    MateriaHistoria *cursor = lista_en_curso;

    while (cursor != NULL)
    {
        if (cursor->id == id_materia)
        {
            return false;
        }
        cursor = cursor->proximo;
    }

    cursor = lista_rendidas;

    while (cursor != NULL)
    {
        if (cursor->id == id_materia)
        {
            return false;
        }
        cursor = cursor->proximo;
    }

    return true;
}

/**
 * Funcion: 
 * Comprueba si los requerimientos de una cierta materia son cumplidos por el estudiante
 * 
 * 		lista_requiere_materia (*MateriaConectada): lista de requerimientos de la materia
 * 		lista_rendidas (*MateriaHistoria): lista de materias rendidas del estudiante
 * 
 * 		return (bool): true si todas las materias dentro de lista_requiere_materia se encuentran dentro de lista_rendidas false en caso de que no se cumpla esto
*/
bool puedoAnotarme(MateriaConectada *lista_requiere_materia, MateriaHistoria *lista_rendidas)
{
    bool continuar_buscando = true;
    bool id_encontrado = false;

    MateriaConectada *puntero_conectada = lista_requiere_materia;
    MateriaHistoria *puntero_rendida = lista_rendidas;

    /* Recorro toda la lista de materias rendidas por cada elemento de la lista de requerimientos de la materia
	 * En el momento que una materia no se encuentra, la iteracion termina y la funcion retorna false */
    while (continuar_buscando && puntero_conectada != NULL && puntero_conectada != NULL)
    {
        puntero_rendida = lista_rendidas;

        while (!id_encontrado && puntero_rendida != NULL)
        {
            id_encontrado = (puntero_conectada->id == puntero_rendida->id);
            puntero_rendida = puntero_rendida->proximo;
        }
        continuar_buscando = id_encontrado;
        puntero_conectada = puntero_conectada->proximo;
    }

    return continuar_buscando;
}

/**
 * Funcion: 
 * Agrega una materia a la lista de materias_en_curso del estudiante que coincida con el legajo_estudiante
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes anotados en la universidad
 * 		legajo_estudiante (int): legajo del estudiante (5 digitos)
 * 		id_materia (int): id de la materia (2 digitos maximo)
 * 		lista_materias (*Materia): lista de materias posibles para anotarse
 * 
 * 		return (void) 
*/
void anotarAMateria(ListaEstudiantes *lista, int legajo_estudiante, int id_materia, Materia *lista_materias)
{
    /* Busco el estudiante  */
    Estudiante **estudiante_a_anotar = buscarEstudiante(lista, legajo_estudiante);

    /* si existe el estudiante */
    if (estudiante_a_anotar != NULL)
    {
        /*Si el estudiante no esta anotado y si no la aprobo previamente*/
        if (noEstoyAnotado((*estudiante_a_anotar)->historia_academica->materias_en_curso, (*estudiante_a_anotar)->historia_academica->materias_aprobadas, id_materia))
        {
            /* Requisitos para inscripcion, si la materia no requiere ninguna otra previa aprobada
			 * O si la materia requiere materias previas, comprobar que esas esten en aprobadas por el estudiante */
            if (lista_materias[id_materia - 1].requiere->id == -1 || puedoAnotarme(lista_materias[id_materia - 1].requiere, (*estudiante_a_anotar)->historia_academica->materias_aprobadas))
            {
                MateriaHistoria *materia_nueva = malloc(sizeof(MateriaHistoria));
                materia_nueva->id = id_materia;
                materia_nueva->proximo = NULL;

                /* Si no hay materias anotadas */
                if ((*estudiante_a_anotar)->historia_academica->materias_en_curso == NULL)
                {
                    (*estudiante_a_anotar)->historia_academica->materias_en_curso = materia_nueva;
                }
                /* Si existen materias anotadas, se agrego al final */
                else
                {
                    MateriaHistoria *puntero = (*estudiante_a_anotar)->historia_academica->materias_en_curso;

                    while (puntero->proximo != NULL)
                    {
                        puntero = puntero->proximo;
                    }
                    puntero->proximo = materia_nueva;
                }
            }
            /* Si no se cumplen los requerimientos de una materia, no se puede anotar al estudiante */
            else
            {
                printf("No podes anotarte a la materia con Id: %d, te faltan las siguientes materias\n", id_materia);
                MateriaConectada *cursor = lista_materias[id_materia - 1].requiere;
                while (cursor->proximo != NULL)
                {
                    printf("\tNombre: %s Id: %d\n", lista_materias[cursor->id - 1].nombre, cursor->id);
                    cursor = cursor->proximo;
                }
            }
        }
        else
        {
            printf("No podes anotarte a esta materia porque ya estas anotado o ya la rendiste\n");
        }
    }
    else
    {
        printf("No existe el estudiante\n");
    }
}

/**
 * Funcion: 
 * Retorna si existe la materia dentro de la lista de materias desaprobadas
 * 
 * 		lista_desaprobadas (*MateriaHistoria): lista de materias desaprobadas por el estudiante
 * 		id_materia (int): id de la materia (2 digitos maximo)
 * 
 * 		return (bool): Retorna true si la materia se encuentra, false en caso de que no 
*/
bool buscarMateriaDesaprobada(MateriaHistoria *lista_desaprobadas, int id_materia)
{
    MateriaHistoria *cursor = lista_desaprobadas;

    while (cursor != NULL)
    {
        if (cursor->id == id_materia)
        {
            return true;
        }
        cursor = cursor->proximo;
    }

    return false;
}

/**
 * Funcion: 
 * Agrega una materia nueva a la lista de aprobadas o desaprobadas, de acuerdo la nota del estudiante que coincida
 * con el legajo_estudiante
 * 
 * 		lista (*ListaEstudiantes): lista de estudiantes anotados en la universidad
 * 		legajo_estudiante (int): legajo del estudiante (5 digitos)
 * 		id_materia (int): id de la materia (2 digitos maximo)
 * 		nota (int): nota obtenida al rendir la materia en cuestion
 * 
 * 		return (void)
*/
void rendirMateria(ListaEstudiantes *lista, int legajo_estudiante, int id_materia, int nota)
{
    /* Busco el estudiante  */
    Estudiante **estudiante_a_anotar = buscarEstudiante(lista, legajo_estudiante);

    bool estoy_anotado = !noEstoyAnotado((*estudiante_a_anotar)->historia_academica->materias_en_curso, NULL, id_materia);
    bool rindo_de_nuevo = buscarMateriaDesaprobada((*estudiante_a_anotar)->historia_academica->materias_desaprobadas, id_materia);

    /* Si estoy anotado a la materia que quiero rendir 
	O la materia esta desaprobada*/
    if (estoy_anotado || rindo_de_nuevo)
    {

        MateriaHistoria **lista_a_borrar_materia = (rindo_de_nuevo) ? &((*estudiante_a_anotar)->historia_academica->materias_desaprobadas) : &((*estudiante_a_anotar)->historia_academica->materias_en_curso);

        /* Elimino la materia de la lista de materias_en_curso
		O de la lista de materias_desaprobadas si es el caso de que estoy rindiendo nuevamente*/
        borrarMateria(lista_a_borrar_materia, id_materia);

        /* Creo la materia que voy a guardar en la lista de aprobadas o desaprobadas */
        MateriaHistoria *cursor_dentro = (*estudiante_a_anotar)->historia_academica->materias_en_curso;
        MateriaHistoria *materia_rendida = malloc(sizeof(MateriaHistoria));
        materia_rendida->id = id_materia;
        materia_rendida->nota = nota;
        materia_rendida->proximo = NULL;

        /* Puntero que va a apuntar a la lista de aprobadas o desaprobadas de acuerdo a la nota con la que se rinde */
        MateriaHistoria **cursor_rendido = (nota >= 4) ? &((*estudiante_a_anotar)->historia_academica->materias_aprobadas) : &((*estudiante_a_anotar)->historia_academica->materias_desaprobadas);

        /* Si todavia no se rindio ninguna */
        if ((*cursor_rendido) == NULL)
        {
            *cursor_rendido = materia_rendida;
        }
        /* Si ya hay materias rendidas, la agrego al final */
        else
        {
            while ((*cursor_rendido)->proximo != NULL)
            {
                cursor_rendido = &(*cursor_rendido)->proximo;
            }
            (*cursor_rendido)->proximo = materia_rendida;
        }
    }
    else
    {
        printf("No estas anotado a esa materia o ya la rendiste");
    }
}
