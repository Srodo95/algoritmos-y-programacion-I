#include "quidditch.h"
#include "sombrero.h"

bool posicion_invalida(int fila,int columna){
	return (fila>=MAX_FILAS || columna>=MAX_COLUMNAS || fila<0 || columna<0);
}

bool movimiento_valido(char movimiento_jugador){
	if(movimiento_jugador==ARRIBA || movimiento_jugador==ABAJO || movimiento_jugador==IZQUIERDA || movimiento_jugador==DERECHA)
		return true;
	return false;
}

char pedir_movimiento(coordenada_t jugador){
	char movimiento;
	printf("ingrese el movimiento al cual quiera moverse\n");
	scanf(" %c", &movimiento);
	while(!movimiento_valido(movimiento)){
		printf("por favor ingrese un movimiento valido\n");
		scanf(" %c", &movimiento);
	}
	while(movimiento==ARRIBA && jugador.fila-1<0){
		printf("FUERA DE RANGO, por favor ingrese un movimiento valido\n");
		scanf(" %c", &movimiento);
	}
	while(movimiento==ABAJO && jugador.fila+1==MAX_FILAS){
		printf("FUERA DE RANGO, por favor ingrese un movimiento valido\n");
		scanf(" %c", &movimiento);
	}
	while(movimiento==DERECHA && jugador.columna+1==MAX_COLUMNAS){
		printf("FUERA DE RANGO, por favor ingrese un movimiento valido\n");
		scanf(" %c", &movimiento);
	}
	while(movimiento==IZQUIERDA && jugador.columna-1<0){
		printf("FUERA DE RANGO, por favor ingrese un movimiento valido\n");
		scanf(" %c", &movimiento);
	}
	return movimiento;
}

coordenada_t posicion_inicial_snitch(){
	coordenada_t posicion;
	srand((unsigned int)clock());
	posicion.columna=rand()%MAX_COLUMNAS;
	posicion.fila=rand()%MAX_FILAS;
	return posicion;
}

int calcular_distancia(int fila_snitch, int columna_snitch, int fila_jugador, int columna_jugador){
	return abs(fila_snitch-fila_jugador)+abs(columna_snitch-columna_jugador);
}

void imprimir_campo(char campo[MAX_FILAS][MAX_COLUMNAS], juego_t* juego){
	int i;
  	int j;

	campo[(*juego).posicion_snitch.fila][(*juego).posicion_snitch.columna]=SNITCH;
	for(i=0;i<(*juego).bludgers_en_juego;i++){
		campo[(*juego).posicion_bludgers[i].fila][(*juego).posicion_bludgers[i].columna]=BLUDGER;
	}

	for(i=0;i<(*juego).dementores_en_juego;i++){
		campo[(*juego).posicion_dementores[i].fila][(*juego).posicion_dementores[i].columna]=DEMENTOR;
	}
	for(i=0;i<MAX_FILAS;i++){
		printf("\n| ");
		for (j = 0;j<MAX_COLUMNAS;j++){
			if(campo[i][j]!=JUGADOR && campo[i][j]!=BLUDGER && campo[i][j]!=DEMENTOR && campo[i][j]!=SNITCH){
				printf("%c ", NADA);
			}
			else if(campo[i][j]==SNITCH){
				printf("%c ", SNITCH);
			}
			else if(campo[i][j]==JUGADOR){
				printf("%c ", JUGADOR);
			}
			else if(campo[i][j]==BLUDGER){
				printf("%c ", BLUDGER);
			}
			else if(campo[i][j]==DEMENTOR){
				printf("%c ", DEMENTOR);
			}
		}
	}
	printf("\n");
	printf("RESISTENCIA ACTUAL DEL JUGADOR: %d\n", (*juego).resistencia);
}

void inicializar_juego(char campo[MAX_FILAS][MAX_COLUMNAS], char casa, juego_t* juego){
	(*juego).estado=EN_EJECUCION;
	(*juego).casa=casa;
	(*juego).bludgers_en_juego=MAX_BLUDGERS;
	(*juego).direccion=DERECHA_BLUDGER;
	(*juego).dementores_en_juego=MAX_DEMENTORES;
	(*juego).resistencia=RESISTENCIA_INICIAL;
	(*juego).posicion_jugador.fila=FILA_JUGADOR;
	(*juego).posicion_jugador.columna=COLUMNA_JUGADOR;
  	(*juego).posicion_snitch=posicion_inicial_snitch();
  	int i;
  	int j;
	for(i=0;i<MAX_FILAS;i++){
        for (j = 0; j < MAX_COLUMNAS; j++){
          	campo[i][j]=NADA;
        }
    }

	while(calcular_distancia((*juego).posicion_snitch.fila,(*juego).posicion_snitch.columna,FILA_JUGADOR,COLUMNA_JUGADOR)<DISTANCIA_MINIMA){
		if(campo[(*juego).posicion_snitch.fila][(*juego).posicion_snitch.columna]==NADA){
			(*juego).posicion_snitch=posicion_inicial_snitch();
		}
	}
	campo[FILA_JUGADOR][COLUMNA_JUGADOR]=JUGADOR;
	campo[(*juego).posicion_snitch.fila][(*juego).posicion_snitch.columna]=SNITCH;

	for(i=0;i<MAX_BLUDGERS;i++){
		(*juego).posicion_bludgers[i].fila=filas_bludger[i];
		(*juego).posicion_bludgers[i].columna=columnas_bludger[i];
		campo[filas_bludger[i]][columnas_bludger[i]]=BLUDGER;
	}

	for(i=0;i<MAX_DEMENTORES;i++){
		(*juego).posicion_dementores[i].fila=filas_dementores[i];
		(*juego).posicion_dementores[i].columna=columnas_dementores[i];
		campo[filas_dementores[i]][columnas_dementores[i]]=DEMENTOR;
	}
	imprimir_campo(campo,juego);
}

void buscar_snitch(char campo[MAX_FILAS][MAX_COLUMNAS],juego_t* juego){
	int i;
	int j;
	for(i=-RADIO_RAVENCLAW;i<RADIO_RAVENCLAW;i++){
		for(j=-RADIO_RAVENCLAW;j<RADIO_RAVENCLAW;j++){
			if(!posicion_invalida((*juego).posicion_jugador.fila+i,(*juego).posicion_jugador.columna+j)){
				if(campo[(*juego).posicion_jugador.fila+i][(*juego).posicion_jugador.columna+j]==SNITCH){
					(*juego).estado=GANO;
				}
			}
		}
	}
}

void eliminar(coordenada_t vector[], int fila_elemento, int columna_elemento, int* tope_vector){
	bool esta=false;
	int i=0;
	int posicion=0;
	while((i<(*tope_vector)) && (!esta)){
		if(vector[i].fila==fila_elemento && vector[i].columna==columna_elemento){
			esta=true;
			posicion=i;
		}
		i++;
	}
	if(esta){
		for(i=posicion;i<(*tope_vector)-1;i++){
			vector[i]=vector[i+1];
		}
		(*tope_vector)--;
	}
}

void jugador_toca_dementor(juego_t* juego){
	(*juego).resistencia=0;
	(*juego).estado=PERDIO;
}

void jugador_toca_bludger(juego_t* juego){
	(*juego).resistencia-=10;
}

void realizar_movimiento(char campo[MAX_FILAS][MAX_COLUMNAS], char movimiento, juego_t* juego){
	campo[(*juego).posicion_jugador.fila][(*juego).posicion_jugador.columna]=NADA;
	if(movimiento==ARRIBA ){
		(*juego).posicion_jugador.fila--;
	}else if(movimiento==ABAJO){
		(*juego).posicion_jugador.fila++;
	}else if(movimiento==IZQUIERDA){
		(*juego).posicion_jugador.columna--;
	}else if(movimiento==DERECHA){
		(*juego).posicion_jugador.columna++;
	}
	if((*juego).casa==RAVENCLAW){
		buscar_snitch(campo,juego);
	}
	(*juego).resistencia--;
}

void verificar_bludgers(char campo[MAX_FILAS][MAX_COLUMNAS],juego_t* juego){
	if(campo[(*juego).posicion_jugador.fila][(*juego).posicion_jugador.columna]==BLUDGER && (*juego).casa!=SLYTHERIN){
		jugador_toca_bludger(juego);
		eliminar((*juego).posicion_bludgers,(*juego).posicion_jugador.fila,(*juego).posicion_jugador.columna,&(*juego).bludgers_en_juego);
	}
}

void verificar_dementores(char campo[MAX_FILAS][MAX_COLUMNAS],juego_t* juego){
	if(campo[(*juego).posicion_jugador.fila][(*juego).posicion_jugador.columna]==DEMENTOR && (*juego).casa!=GRYFFINDOR){
		jugador_toca_dementor(juego);
	}else if(campo[(*juego).posicion_jugador.fila][(*juego).posicion_jugador.columna]==DEMENTOR && (*juego).casa==GRYFFINDOR){
		eliminar((*juego).posicion_dementores,(*juego).posicion_jugador.fila,(*juego).posicion_jugador.columna,&(*juego).dementores_en_juego);
	}
}

void verificar_snitch(char campo[MAX_FILAS][MAX_COLUMNAS],juego_t* juego){
	if(campo[(*juego).posicion_jugador.fila][(*juego).posicion_jugador.columna]==SNITCH){
		(*juego).estado=GANO;
	}
}

void verificar_estado_juego(juego_t* juego){
	if((*juego).resistencia<=0){
		(*juego).estado=PERDIO;
	}else if((*juego).estado!=GANO && (*juego).resistencia>0){
		(*juego).estado=EN_EJECUCION;
	}
}

void mover_jugador(char campo[MAX_FILAS][MAX_COLUMNAS], char direccion, juego_t *juego){
	realizar_movimiento(campo,direccion,juego);
	verificar_bludgers(campo,juego);
	verificar_dementores(campo,juego);
	verificar_snitch(campo,juego);
	verificar_estado_juego(juego);
	campo[(*juego).posicion_jugador.fila][(*juego).posicion_jugador.columna]=JUGADOR;
}

bool posicion_ocupada(char campo[MAX_FILAS][MAX_COLUMNAS],int fila, int columna){
	return(campo[fila][columna]!=NADA);
}




coordenada_t nueva_coordenada_snitch(char campo[MAX_FILAS][MAX_COLUMNAS], juego_t* juego){
	coordenada_t coordenada_elegida;
	coordenada_t coordenada_original;
	coordenada_original.fila=juego->posicion_snitch.fila;
	coordenada_original.columna=juego->posicion_snitch.columna;
	coordenada_t vector_diagonales[TOPE_DIAGONALES_SNITCH];
	vector_diagonales[0].fila=(*juego).posicion_snitch.fila-1;
	vector_diagonales[0].columna=(*juego).posicion_snitch.columna-1;
	vector_diagonales[1].fila=(*juego).posicion_snitch.fila-1;
	vector_diagonales[1].columna=(*juego).posicion_snitch.columna+1;
	vector_diagonales[2].fila=(*juego).posicion_snitch.fila+1;
	vector_diagonales[2].columna=(*juego).posicion_snitch.columna-1;
	vector_diagonales[3].fila=(*juego).posicion_snitch.fila+1;
	vector_diagonales[3].columna=(*juego).posicion_snitch.columna+1;
	int i;
	int mayor=-1;
	int posicion=-1;
	for(i=0;i<TOPE_DIAGONALES_SNITCH;i++){
		if(!posicion_invalida(vector_diagonales[i].fila,vector_diagonales[i].columna) && !posicion_ocupada(campo,vector_diagonales[i].fila,vector_diagonales[i].columna)){
				if(calcular_distancia(vector_diagonales[i].fila,vector_diagonales[i].columna,(*juego).posicion_jugador.fila,(*juego).posicion_jugador.columna)>mayor){
					mayor=calcular_distancia(vector_diagonales[i].fila,vector_diagonales[i].columna,(*juego).posicion_jugador.fila,(*juego).posicion_jugador.columna);
					posicion=i;
				}
		}
	}

	if (posicion<0)
		return coordenada_original;

	coordenada_elegida.fila=vector_diagonales[posicion].fila;
	coordenada_elegida.columna=vector_diagonales[posicion].columna;
	return coordenada_elegida;
}

void mover_snitch(char campo[MAX_FILAS][MAX_COLUMNAS], juego_t* juego){
	int distancia_contra_jugador=calcular_distancia((*juego).posicion_snitch.fila,(*juego).posicion_snitch.columna,(*juego).posicion_jugador.fila,(*juego).posicion_jugador.columna);

	if(distancia_contra_jugador<=DISTANCIA_LEJANA){
		coordenada_t nueva_coordenada=nueva_coordenada_snitch(campo,juego);

		campo[(*juego).posicion_snitch.fila][(*juego).posicion_snitch.columna]=NADA;
		(*juego).posicion_snitch.fila=nueva_coordenada.fila;
		(*juego).posicion_snitch.columna=nueva_coordenada.columna;
		campo[(*juego).posicion_snitch.fila][(*juego).posicion_snitch.columna]=SNITCH;
	}
}

void choca_jugador(char campo[MAX_FILAS][MAX_COLUMNAS], juego_t* juego, int bludger){
	if(campo[(*juego).posicion_bludgers[bludger].fila][(*juego).posicion_bludgers[bludger].columna]==JUGADOR){
		if((*juego).casa==GRYFFINDOR || (*juego).casa==RAVENCLAW || (*juego).casa==HUFFLEPUFF){
			jugador_toca_bludger(juego);
			eliminar((*juego).posicion_bludgers,(*juego).posicion_bludgers[bludger].fila,(*juego).posicion_bludgers[bludger].columna,&(*juego).bludgers_en_juego);
			campo[(*juego).posicion_bludgers[bludger].fila][(*juego).posicion_bludgers[bludger].columna]=NADA;
			if((*juego).direccion==DERECHA_BLUDGER){
				(*juego).posicion_bludgers[bludger].columna++;
			}else if((*juego).direccion==IZQUIERDA_BLUDGER){
				(*juego).posicion_bludgers[bludger].columna--;
			}
		}
 	}
}

void actualizar_direccion(juego_t* juego, int bludger){
	if(bludger==(*juego).bludgers_en_juego-1 && (*juego).posicion_bludgers[bludger].columna==MAX_COLUMNAS-1){
		(*juego).direccion=IZQUIERDA_BLUDGER;
	}if(bludger==(*juego).bludgers_en_juego-1 && (*juego).posicion_bludgers[bludger].columna==0){
		(*juego).direccion=DERECHA_BLUDGER;
	}
}

void mover_bludgers(char campo[MAX_FILAS][MAX_COLUMNAS], juego_t* juego){
	for(int i=0;i<(*juego).bludgers_en_juego;i++){
		campo[(*juego).posicion_bludgers[i].fila][(*juego).posicion_bludgers[i].columna]=NADA;
		if((*juego).direccion==DERECHA_BLUDGER){
			(*juego).posicion_bludgers[i].columna++;
		}else if((*juego).direccion==IZQUIERDA_BLUDGER){
			(*juego).posicion_bludgers[i].columna--;
		}
		choca_jugador(campo,juego,i);
		actualizar_direccion(juego,i);
		campo[(*juego).posicion_bludgers[i].fila][(*juego).posicion_bludgers[i].columna]=BLUDGER;
	}
	verificar_estado_juego(juego);
}

bool finalizo_juego(juego_t *juego){
	if((*juego).estado==GANO || (*juego).estado==PERDIO){
		return true;
	}else if((*juego).estado==EN_EJECUCION);
		return false;
}

void mostrar_resultado(juego_t juego){
	printf("RESISTENCIA DEL JUGADOR: %i\n", juego.resistencia);
	if(juego.estado==GANO){
		printf("GANASTE LA PARTIDA\n");
	}else if(juego.estado==PERDIO){
        printf("PERDISTE LA PARTIDA\n");
    }
}
