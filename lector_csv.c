#include "lector_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1000

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
int calcularTamanioLineaAEscribir(int *arreglo, int tamanio)
{
    int digitos = 0;
    int numero;

    for (int i = 0; i < tamanio - 1; i++)
    {
        numero = arreglo[i];
        while (numero != 0)
        {
            numero /= 10;
            digitos++;
        }
    }
    return digitos + 6;
}

/**
 * Funcion: 
 * Calculo y devuelvo el tamanio maximo que va a ocupar cada campo del archivo
 * 
 * 		ruta_archivo (*char): ruta del archivo .csv
 *  
 * 		return (*int): arreglo de 6 posiciones con los tamanios de cada campo
*/
int *calcularTamanioMaximo(char *ruta_archivo)
{
    char buff[1024];
    int indice_array_materias = 0;
    int contador_campo = 0;

    int *arreglo_tamanios = malloc(sizeof(int) * 6);

    FILE *fp = fopen(ruta_archivo, "r");
    if (!fp)
        return NULL;

    fgets(buff, 1024, fp);

    int cantidad_materias = 0;
    int len_nombre_maximo = 0;
    int len_id_maximo = 0;
    int len_requiere_maximo = 0;
    int len_es_requerido_maximo = 0;

    while (fgets(buff, 1024, fp))
    {
        contador_campo = 0;

        char *campo = strtok(buff, ",");
        while (campo)
        {
            if (contador_campo == 0)
            {
                if (strlen(campo) > len_nombre_maximo)
                {
                    len_nombre_maximo = strlen(campo);
                }
            }
            else if (contador_campo == 1)
            {
                if (strlen(campo) > len_id_maximo)
                {
                    len_id_maximo = strlen(campo);
                }
            }
            else if (contador_campo == 2)
            {
                if (strlen(campo) > len_requiere_maximo)
                {
                    len_requiere_maximo = strlen(campo);
                }
            }
            else if (contador_campo == 3)
            {
                if (strlen(campo) > len_es_requerido_maximo)
                {
                    len_es_requerido_maximo = strlen(campo);
                }
                cantidad_materias++;
            }

            contador_campo = (contador_campo + 1 == 4) ? 0 : contador_campo + 1;

            campo = strtok(NULL, ",");
        }
    }
    fclose(fp);

    arreglo_tamanios[0] = cantidad_materias;
    arreglo_tamanios[1] = len_nombre_maximo;
    arreglo_tamanios[2] = len_id_maximo;
    arreglo_tamanios[3] = len_requiere_maximo;
    arreglo_tamanios[4] = len_es_requerido_maximo;
    arreglo_tamanios[5] = calcularTamanioLineaAEscribir(arreglo_tamanios, 6);

    return arreglo_tamanios;
}

/**
 * Funcion: 
 * Modifica el archivo .csv agregandole en la 1er linea los tamanios maximos
 * de cada campo
 * 
 * 		ruta_archivo (*char): ruta del archivo .csv
 * 		arreglo_tamanios (*int): arreglo con los tamanios maximos de cada campo
 *  
 * 		return (void)
*/
void modificarArchivo(char *ruta_archivo_csv, int *arreglo_tamanios)
{
    FILE *puntero_archivo_original;
    FILE *puntero_archivo_temporal;
    char *ruta_archivo = ruta_archivo_csv;

    char buffer[BUFFER_SIZE];
    char *linea_a_escribir = malloc(sizeof(char) * arreglo_tamanios[5]);

    sprintf(linea_a_escribir, "%d,%d,%d,%d,%d\n", arreglo_tamanios[0], arreglo_tamanios[1], arreglo_tamanios[2], arreglo_tamanios[3], arreglo_tamanios[4]);
    int linea;

    puntero_archivo_original = fopen(ruta_archivo, "r");
    puntero_archivo_temporal = fopen("archivo_tempora.tmp", "w");

    if (puntero_archivo_original == NULL || puntero_archivo_temporal == NULL)
    {
        printf("\nNo se pudo encontrar el archivo\n");
        exit(EXIT_SUCCESS);
    }

    linea = 0;
    while ((fgets(buffer, BUFFER_SIZE, puntero_archivo_original)) != NULL)
    {
        linea++;

        if (linea == 1)
            fputs(linea_a_escribir, puntero_archivo_temporal);
        else
            fputs(buffer, puntero_archivo_temporal);
    }

    fclose(puntero_archivo_original);
    fclose(puntero_archivo_temporal);

    remove(ruta_archivo);

    rename("archivo_tempora.tmp", ruta_archivo);

    free(linea_a_escribir);
}

/**
 * Funcion: 
 * Abro el archuvo .csv ya modificado con la 1er linea, leo esa linea e inicializo
 * un arreglo de MateriaDatos que voy a ir cargando a medida que se lee el archivo 
 * 
 * 		ruta_archivo (*char): ruta del archivo .csv
 *  
 * 		return (*MateriaDatos): Arreglo de MateriaDatos
*/
MateriaDatos *parsearArchivo(char *nombre_archivo)
{

    char buff[1024];
    int indice_array_materias = 0;
    int fila = 0;
    int contador_campo = 0;

    int tamanio_arreglo;
    int tamanio_nombre;
    int tamanio_id;
    int tamanio_requiere;
    int tamanio_es_requerido;

    FILE *fp = fopen(nombre_archivo, "r");
    if (!fp)
        return NULL;

    fgets(buff, 1024, fp);

    char *campo = strtok(buff, ",");

    while (campo)
    {
        if (contador_campo == 0)
        {
            tamanio_arreglo = atoi(campo);
        }
        else if (contador_campo == 1)
        {
            tamanio_nombre = atoi(campo);
        }
        else if (contador_campo == 2)
        {
            tamanio_id = atoi(campo);
        }
        else if (contador_campo == 3)
        {
            tamanio_requiere = atoi(campo);
        }
        else if (contador_campo == 4)
        {
            tamanio_es_requerido = atoi(campo);
        }
        contador_campo++;
        campo = strtok(NULL, ",");
    }

    contador_campo = 0;

    MateriaDatos *materias = malloc(sizeof(MateriaDatos) * tamanio_arreglo);
    for (int i = 0; i < tamanio_arreglo; i++)
    {
        materias[i].nombre = malloc(tamanio_nombre * sizeof(char));
        materias[i].id = malloc(tamanio_id * sizeof(char));
        materias[i].requiere = malloc(tamanio_requiere * sizeof(char));
        materias[i].es_requerido = malloc(tamanio_es_requerido * sizeof(char));
    }

    while (fgets(buff, 1024, fp))
    {

        fila++;
        contador_campo = 0;

        char datos[4][1000];

        campo = strtok(buff, ",");
        while (campo)
        {

            if (contador_campo < 4)
            {
                strcpy(datos[contador_campo], campo);
            }
            contador_campo++;
            if (contador_campo == 4)
            {

                strcpy(materias[indice_array_materias].nombre, datos[0]);
                strcpy(materias[indice_array_materias].id, datos[1]);
                strcpy(materias[indice_array_materias].requiere, datos[2]);
                strcpy(materias[indice_array_materias].es_requerido, datos[3]);
                indice_array_materias++;
            }

            campo = strtok(NULL, ",");
        }
    }
    fclose(fp);

    return materias;
}

/**
 * Funcion: 
 * Compara dos strings sin importar los saltos de linea que contenga
 * 		string1 (*char): string 1 a comparar
 * 		string2 (*char): string 2 a comparar
 *  
 * 		return (*MateriaDatos): Arreglo de MateriaDatos
*/
int compararCadenas(const char *cadena1, const char *cadena2)
{
    char cadena1_cursor;
    char cadena2_cursor;
    do
    {
        cadena1_cursor = *(cadena1++);
        cadena2_cursor = *(cadena2++);
        if (cadena1_cursor == '\n')
            cadena1_cursor = 0;
        if (cadena2_cursor == '\n')
            cadena2_cursor = 0;
        if (cadena1_cursor != cadena2_cursor)
            return 1;
    } while (cadena1_cursor);
    return 0;
}

/**
 * Funcion: 
 * Recibo un arreglo con los datos leidos del archivo .csv y conformo un arreglo de Materia
 * 		
 * 		array (*MateriaDatos): Arreglo de MateriaDatos
 * 		cantidad_materias (int): Longitud del arreglo array
 *  
 * 		return (*Materia): Arreglo de Materia completo con la estructura final
*/
Materia *crearCorrelatividades(MateriaDatos *array, int cantidad_materias)
{

    Materia *arreglo = malloc(sizeof(Materia) * cantidad_materias);

    for (int i = 0; i < cantidad_materias; i++)
    {
        Materia *materia_general = malloc(sizeof(Materia));
        materia_general->nombre = array[i].nombre;
        materia_general->id = atoi(array[i].id);

        MateriaConectada *materia_requiere = malloc(sizeof(MateriaConectada));
        materia_requiere->id = -1;
        materia_requiere->proximo = NULL;

        MateriaConectada *materia_es_requerida = malloc(sizeof(MateriaConectada));
        materia_es_requerida->id = -1;
        materia_es_requerida->proximo = NULL;

        MateriaConectada **puntero_requiere = &materia_requiere;
        MateriaConectada **puntero_es_requerida = &materia_es_requerida;

        materia_general->requiere = *puntero_requiere;
        materia_general->es_requerido = *puntero_es_requerida;

        char *dato = strtok(array[i].requiere, "-");

        while (dato && compararCadenas("-1", array[i].requiere))
        {
            (*puntero_requiere)->id = atoi(dato);
            MateriaConectada *materia_requiere_proximo = malloc(sizeof(MateriaConectada));
            materia_requiere_proximo->proximo = NULL;
            (*puntero_requiere)->proximo = materia_requiere_proximo;
            puntero_requiere = &((*puntero_requiere)->proximo);
            dato = strtok(NULL, "-");
        }

        dato = strtok(array[i].es_requerido, "-");

        while (dato && compararCadenas("-1", array[i].es_requerido))
        {
            (*puntero_es_requerida)->id = atoi(dato);
            MateriaConectada *materia_es_requerida_proximo = malloc(sizeof(MateriaConectada));
            materia_es_requerida_proximo->proximo = NULL;
            (*puntero_es_requerida)->proximo = materia_es_requerida_proximo;
            puntero_es_requerida = &((*puntero_es_requerida)->proximo);
            dato = strtok(NULL, "-");
        }

        arreglo[i] = *materia_general;
    }

    return arreglo;
}

/**
 * Funcion: 
 * Metodo general para obtener el arreglo de Materia
 * 		
 * 		ruta_archivo (*char): ruta del archivo .csv
 *  
 * 		return (*Materia): Arreglo de Materia completo con la estructura final
*/
Materia *obtenerMateriasCorrelativas(char *ruta_archivo)
{
    int *tamanio_campos = calcularTamanioMaximo(ruta_archivo);
    modificarArchivo(ruta_archivo, tamanio_campos);
    MateriaDatos *datos_campos = parsearArchivo(ruta_archivo);
    Materia *materias_correlativas = crearCorrelatividades(datos_campos, tamanio_campos[0]);
    free(tamanio_campos);

    return materias_correlativas;
}

/**
 * Funcion: 
 *  Abre un archivo de configuracion ubicado en ruta_archivo, lo carga en una struct datosCuatriAnios
 *  y lo devuelve
 * 
 * 		ruta_archivo (*char): ubicacion del archivo
 *  
 * 		return (*datosCuatriAnios): estructura cargada con los rangos de id de cada cuatrimestre y anio
*/
datosCuatriAnios *cargarArchivoConfiguracionMaterias(char *ruta_archivo)
{

    char buff[1024];
    int contador_campo = 0;
    int cantidad_cuatrimestres, cantidad_anios;
    int fila = 0;
    int indice_cuatrimestres = 0;
    int indice_anios = 0;

    FILE *fp = fopen(ruta_archivo, "r");
    if (!fp)
        return NULL;

    fgets(buff, 1024, fp);
    char *campo = strtok(buff, ",");

    while (campo)
    {
        if (contador_campo == 0)
        {
            cantidad_cuatrimestres = atoi(campo);
        }
        else if (contador_campo == 1)
        {
            cantidad_anios = atoi(campo);
        }
        contador_campo++;
        campo = strtok(NULL, ",");
    }

    int *cuatrimestres = malloc(sizeof(int) * cantidad_cuatrimestres);
    int *anios = malloc(sizeof(int) * cantidad_anios);

    datosCuatriAnios *datos = malloc(sizeof(datosCuatriAnios));

    while (fgets(buff, 1024, fp))
    {
        campo = strtok(buff, ",");
        while (campo)
        {
            if (fila == 0)
            {
                cuatrimestres[indice_cuatrimestres] = atoi(campo);
                indice_cuatrimestres++;
            }
            else if (fila == 1)
            {
                anios[indice_anios] = atoi(campo);
                indice_anios++;
            }
            campo = strtok(NULL, ",");
        }
        fila++;
    }

    datos->cuatrimestres = cuatrimestres;
    datos->anios = anios;
    datos->cantidad_cuatrimestres = cantidad_cuatrimestres;
    datos->cantidad_anios = cantidad_anios;

    return datos;
}
