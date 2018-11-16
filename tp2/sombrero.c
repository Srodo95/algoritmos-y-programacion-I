#include <stdio.h>
#include "sombrero.h"

char obtener_casa(){
	char casa;
	int fuerza;
	int valor;
	int inteligencia;
	int ingenio;
	int dedicacion;
	int cantidad_superatributos=0;
	printf("----------BIENVENIDO AL SOMBRERO SELECCIONADOR!!---------\n");
	printf("ingrese su fuerza\n");
	scanf("%d", &fuerza);
	while(fuerza>VALOR_MAXIMO || fuerza<VALOR_MINIMO){
		printf("por favor, ingrese de nuevo un valor que no este fuera del rango\n");
		scanf("%d", &fuerza);
	}
	if(fuerza>VALOR_MINIMO_SUPER_ATRIBUTO){
		cantidad_superatributos++;
	}
	printf("ingrese su valor\n");
	scanf("%d", &valor);
	while(valor>VALOR_MAXIMO || valor<VALOR_MINIMO){
		printf("por favor, ingrese de nuevo un valor que no este fuera del rango\n");
		scanf("%d", &valor);
	}
	if(valor>VALOR_MINIMO_SUPER_ATRIBUTO){
		cantidad_superatributos++;
	}
	printf("ingrese su inteligencia\n");
	scanf("%d", &inteligencia);
	while(inteligencia>VALOR_MAXIMO || inteligencia<VALOR_MINIMO){
		printf("por favor, ingrese de nuevo un valor que no este fuera del rango\n");
		scanf("%d", &inteligencia);
	}
	if(inteligencia>VALOR_MINIMO_SUPER_ATRIBUTO){
		cantidad_superatributos++;
	}
	printf("ingrese su ingenio\n");
	scanf("%d", &ingenio);
	while(ingenio>VALOR_MAXIMO || ingenio<VALOR_MINIMO){
		printf("por favor, ingrese de nuevo un valor que no este fuera del rango\n");
		scanf("%d", &ingenio);
	}
	if(ingenio>VALOR_MINIMO_SUPER_ATRIBUTO){
		cantidad_superatributos++;
	}
	printf("ingrese su dedicacion\n");
	scanf("%d", &dedicacion);
	while(dedicacion>VALOR_MAXIMO || dedicacion<VALOR_MINIMO){
		printf("por favor, ingrese de nuevo un valor que no este fuera del rango\n");
		scanf("%d", &dedicacion);
	}
	if(dedicacion>VALOR_MINIMO_SUPER_ATRIBUTO){
		cantidad_superatributos++;
	}
	while(cantidad_superatributos>2){
		cantidad_superatributos=0;
		printf("no esta permitido tener mas de 2 superatributos\n");
		printf("ingrese su fuerza\n");
		scanf("%d", &fuerza);
		while(fuerza>VALOR_MAXIMO || fuerza<VALOR_MINIMO){
		printf("por favor, ingrese de nuevo un valor que no este fuera del rango\n");
		scanf("%d", &fuerza);
		}
		printf("ingrese su valor\n");
		scanf("%d", &valor);
		while(valor>VALOR_MAXIMO || valor<VALOR_MINIMO){
		printf("por favor, ingrese de nuevo un valor que no este fuera del rango\n");
		scanf("%d", &valor);
		}
		printf("ingrese su inteligencia\n");
		scanf("%d", &inteligencia);
		while(inteligencia>VALOR_MAXIMO || inteligencia<VALOR_MINIMO){
		printf("por favor, ingrese de nuevo un valor que no este fuera del rango\n");
		scanf("%d", &inteligencia);
		}
		printf("ingrese su ingenio\n");
		scanf("%d", &ingenio);
		while(ingenio>VALOR_MAXIMO || ingenio<VALOR_MINIMO){
		printf("por favor, ingrese de nuevo un valor que no este fuera del rango\n");
		scanf("%d", &ingenio);
		}
		printf("ingrese su dedicacion\n");
		scanf("%d", &dedicacion);
		while(dedicacion>VALOR_MAXIMO || dedicacion<VALOR_MINIMO){
		printf("por favor, ingrese de nuevo un valor que no este fuera del rango\n");
		scanf("%d", &dedicacion);
		}
	}
	if(fuerza>FUERZA_ALTA && valor>VALOR_ALTO && ingenio<INGENIO_BAJO){
		casa=GRYFFINDOR;
	}
	else if(inteligencia>INTELIGENCIA_ALTA && ingenio>INGENIO_ALTO){
		casa=RAVENCLAW;
	}
	else if(inteligencia>INTELIGENCIA_BAJA && inteligencia<INTELIGENCIA_ALTA && ingenio>INGENIO_BAJO){
		casa=SLYTHERIN;
	}
	else{
		casa=HUFFLEPUFF;
	}
	return casa;
}