#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#ifndef QUIDDITCH_H
#define QUIDDITCH_H

static const char JUGADOR='J';
static const char DEMENTOR='D';
static const char SNITCH='S';
static const char BLUDGER='B';
static const char NADA=' ';
static const char ARRIBA='w';
static const char ABAJO='s';
static const char DERECHA='d';
static const char IZQUIERDA='a';
static const char DERECHA_BLUDGER='D';
static const char IZQUIERDA_BLUDGER='I';


static const int MAX_FILAS=25;
static const int MAX_COLUMNAS=15;
static const int RESISTENCIA_INICIAL=50;
static const int filas_dementores[4]={5,5,19,19};
static const int columnas_dementores[4]={3,11,3,11};
static const int filas_bludger[5]={2,7,12,17,22};
static const int columnas_bludger[5]={0,0,0,0,0};
static const int DISTANCIA_MINIMA=5;
static const int DISTANCIA_LEJANA=10;
static const int FILA_JUGADOR=12;
static const int COLUMNA_JUGADOR=7;
static const int PERDIO=2;
static const int GANO=1;
static const int EN_EJECUCION=0;
static const int MAX_BLUDGERS=5;
static const int MAX_DEMENTORES=4;
static const int RADIO_RAVENCLAW=1;
static const int TOPE_DIAGONALES_SNITCH=4;

typedef struct coordenada {
	int fila;
	int columna;
} coordenada_t;

typedef struct juego {
	coordenada_t posicion_jugador;
	char casa;
	int resistencia;
	coordenada_t posicion_snitch;

	int bludgers_en_juego; // tope del vector posicion_bludgers
	coordenada_t posicion_bludgers[6];
	char direccion; // 'D': derecha – 'I': izquierda

	int dementores_en_juego; // tope del vector posicion_dementores
	coordenada_t posicion_dementores[5];

	int estado; // 0: en ejecucion – 1: jugador gano – 2: jugador perdio
} juego_t;

/*pre condiciones: debe ingresar los valores del jugador para saber a que casa pertenece.
 *post condicion: inicializa el campo del juego.
 */
void inicializar_juego(char campo[MAX_FILAS][MAX_COLUMNAS], char casa, juego_t *juego);

/*
 * pre:mueve al jugador y segun la casa a la que pertenece con ciertos atributos al moverlo
 	post condicion: debe tener una resistencia mayor a 0 para mover al jugador, sino, se termina el juego.
 */
void mover_jugador(char campo[MAX_FILAS][MAX_COLUMNAS], char direccion, juego_t *juego);

/*
 * pre:debera actualizarse los datos del registro y el estado de juego.
   post condicion: debe ser un movimiento valido.
 */
void mover_snitch(char campo[MAX_FILAS][MAX_COLUMNAS], juego_t *juego);


bool posicion_invalida(int fila,int columna);

bool movimiento_valido(char movimiento_jugador);

/*
  pre: pide al usuario que ingrese un movimiento para mover al jugador.
  post condicion: si no ingresa un movimiento valido, lo debe volver a ingresar.
 */

char pedir_movimiento(coordenada_t jugador);

int calcular_distancia(int fila_snitch, int columna_snitch, int fila_jugador, int columna_jugador);

void eliminar(coordenada_t vector[], int fila_elemento, int columna_elemento, int* tope_vector);

void jugador_toca_dementor(juego_t* juego);

void jugador_toca_bludger(juego_t* juego);

void verificar_bludgers(char campo[MAX_FILAS][MAX_COLUMNAS],juego_t* juego);

void verificar_dementores(char campo[MAX_FILAS][MAX_COLUMNAS],juego_t* juego);

void verificar_snitch(char campo[MAX_FILAS][MAX_COLUMNAS],juego_t* juego);

void verificar_estado_juego(juego_t* juego);

/*
 *  post condicion: actualizara el campo del juego, moviendo todas las bludgers
 */
void mover_bludgers(char campo[MAX_FILAS][MAX_COLUMNAS], juego_t *juego);

/*
 * pre: debe cumplir con la posicion aleatoria y distancia mayor o igual a 5 hacia el jugador
   post condicion: devolvera la posicion de la snitch en el campo
 */
coordenada_t posicion_inicial_snitch();

/*pre: el juego debe inicializarse
 * post condicion: devolvera el estado del juego
 */
bool finalizo_juego(juego_t *juego);

/* pre: para mostrar el resultado final, debe finalizar el juego, perdiendo o ganandolo.
 * post condicion: imprime por pantalla el campo del juego.
 */
void mostrar_resultado(juego_t juego);

/*
 * pre: debe existir el campo con los elementos del juego.
   post condicion: imprime el campo del juego.
 */

void imprimir_campo(char campo[MAX_FILAS][MAX_COLUMNAS], juego_t* juego);

#endif /* QUIDDITCH_H */
