#include "quidditch.h"
#include "sombrero.h"

int main(){
	char casa;
	casa=obtener_casa();
	char movimiento;
	char campo[MAX_FILAS][MAX_COLUMNAS];
	juego_t juego;
	coordenada_t jugador;
	inicializar_juego(campo,casa,&juego);
	jugador.fila=juego.posicion_jugador.fila;
	jugador.columna=juego.posicion_jugador.columna;
	bool movimiento_hufflepuff=true;
	do{
		movimiento=pedir_movimiento(jugador);
		mover_jugador(campo,movimiento,&juego);
		jugador.fila=juego.posicion_jugador.fila;
		jugador.columna=juego.posicion_jugador.columna;
		if(casa!=HUFFLEPUFF || movimiento_hufflepuff==false){
			mover_bludgers(campo,&juego);
			mover_snitch(campo,&juego);
			movimiento_hufflepuff=true;
		}else{
			movimiento_hufflepuff=false;
		}
		imprimir_campo(campo,&juego);
	}while(!finalizo_juego(&juego));
	if(finalizo_juego(&juego)){
		mostrar_resultado(juego);
	}
	return 0;
}