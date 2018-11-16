#ifndef SOMBRERO_H
#define SOMBRERO_H

#define VALOR_MINIMO 0
#define VALOR_MAXIMO 10
#define VALOR_MINIMO_SUPER_ATRIBUTO 8
#define FUERZA_ALTA 8
#define FUERZA_BAJA 5
#define VALOR_ALTO 8
#define VALOR_BAJO 5
#define INTELIGENCIA_ALTA 8
#define INTELIGENCIA_BAJA 5
#define INGENIO_ALTO 8
#define INGENIO_BAJO 5
static const char GRYFFINDOR='G';
static const char SLYTHERIN='S';
static const char RAVENCLAW='R';
static const char HUFFLEPUFF='H';


char obtener_casa();
	/* pre condicion: 
		post condicion: devuelve la inicial del nombre de la casa a la que pertenece el jugador.
	*/



#endif /* SOMBRERO_H */