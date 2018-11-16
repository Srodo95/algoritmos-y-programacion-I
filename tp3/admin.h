#ifndef ADMIN_H
#define ADMIN_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static const int ULTIMO_ANIO=7;
static const int ERROR=-1;
static const int MAX_PADRON=9;
static const int MAX_CASA=16;
static const int MAX_NOMBRE=32;
static const int MAX_FECHA=10;
static const int MAX_COMENTARIO=257;

typedef struct resumen_casa{
	char casa[16];
	unsigned long puntos_casa;
	char padron[9];
	unsigned long puntos_alumno;
} resumen_casa_t;

typedef struct alumnos{
	char padron_alumno[9];
	char nombre_alumno[32];
	char casa_alumno[16];
	int anio;
	int puntos;
} alumnos_t;

typedef struct bitacora{
    char padron_bitacora[9];
    char fecha[10];
    int puntos;
    char comentario[257];
} bitacora_t;

/*
	toma el archivo de un anio, elimina los alumnos del ultimo anio(7)
	e incrementa en 1 el anio de todos los alumnos de anios anteriores.
	post: devuelve la cantidad de alumnos que quedaron en el archivo destino.
*/
int pasar_de_anio(char* ruta_origen, char* ruta_destino);
/*
	aplica las actualizaciones del archivo de actualizaciones al archivo de
	alumnos, incorporando a dicho padron a todos los ingresantes.
	post: devuelve la cantidad de alumnos ingresados al padron de alumnos.
	queda a criterio del alumno el uso de valores negativos para informar
	errores.
*/
int actualizar_alumnos(char* ruta_alumnos, char* ruta_actualizaciones);
/*
	para cada entrada del archivo de bitacora, modifica la cantidad de puntos
	acumulada durante el anio por el alumnos indicado en dicha entrada.
	devuelve la cantidad de entradas de la bitacora procesadas.
*/
int aplicar(char* ruta_alumnos, char* ruta_bitacora);
/*
	muestra por pantalla un resumen de cantidad de puntos por cada anio dentro
	de una casa, y por cada casa. Incluye al final del resumen la casa con la 
	maxima cantidad de puntos(el nombre), los puntos acumulados, y para el
	integrante de la casa que mas puntos gano para esa casa ese anio y los puntos
	que ese alumno sumo.
	devuelve:
		-casa ganadora.
		-Puntos.
		-padron de alumno con mas puntos
		-puntos obtenidos por el alumno.
	se asume que no hay empates.
*/
resumen_casa_t resumir_puntos(char* ruta_alumnos, FILE* canal_impresion);

#endif /* ADMIN_H */
