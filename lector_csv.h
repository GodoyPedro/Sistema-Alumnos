
typedef struct MateriaConectada
{
    int id;
    struct MateriaConectada *proximo;
} MateriaConectada;

typedef struct estructuraMateria
{
    char *nombre;
    int id;
    struct MateriaConectada *requiere;
    struct MateriaConectada *es_requerido;
} Materia;

typedef struct datosCrudosArray
{
    char *nombre;
    char *id;
    char *requiere;
    char *es_requerido;
} MateriaDatos;

typedef struct estructuraDatosCuatriAnios
{
    int cantidad_cuatrimestres;
    int cantidad_anios;
    int *cuatrimestres;
    int *anios;
} datosCuatriAnios;

int calcularTamanioLineaAEscribir(int *arreglo, int tamanio);
int *calcularTamanioMaximo(char *ruta_archivo);
void modificarArchivo(char *ruta_archivo_csv, int *arreglo_tamanios);
MateriaDatos *parsearArchivo(char *nombre_archivo);
int compararCadenas(const char *cadena1, const char *cadena2);
Materia *crearCorrelatividades(MateriaDatos *array, int cantidad_materias);
Materia *obtenerMateriasCorrelativas(char *ruta_archivo);
datosCuatriAnios *cargarArchivoConfiguracionMaterias(char *ruta_archivo);
