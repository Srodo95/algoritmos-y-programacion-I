#include "admin.h"

int main(int argc, char* argv[]){
	if(!strcmp(argv[1],"ayuda")){
		printf("hola bienvenido al administrador de archivos de hogwarts!\n");
		
		printf("el programa solo puede recibir 4 comandos para su funcionamiento:\n");

		printf("para poder ejecutar el programa se requiere poner primero  './hogwadin ' seguido de los argumentos que se explicaran a continuacion\n");
		
		printf("comando 'aplicar':toma el archivo de un anio, elimina los alumnos del ultimo anio(7) e incrementa en 1 el anio de todos los alumnos de anios anteriores.luego de poner la palabra 'aplicar' se debe poner primero la ruta de alumnos y luego la ruta de las actualizaciones\n");

		printf("comando 'limpiar': aplica las actualizaciones del archivo de actualizaciones al archivo de alumnos, incorporando a dicho padron a todos los ingresantes.luego de poner la palabra 'limpiar' se debe poner primero la ruta de origen y luego la ruta de alumnos.\n");

		printf("comando actualizar: paras cada entrada del archivo de bitacora, modifica la cantidad de puntos. acumulada durante el anio por el alumnos indicado en dicha entrada. luego de poner la palabra 'actualizar' se debe poner primero la ruta de alumnos y luego la ruta de bitacora\n");

		printf("comando resumir: muestra por pantalla un resumen de cantidad de puntos por cada anio dentro de una casa, y por cada casa. Incluye al final del resumen la casa con la  maxima cantidad de puntos(el nombre), los puntos acumulados, y para el integrante de la casa que mas puntos gano para esa casa ese anio y los puntos que ese alumno sumo. luego de poner la palabra 'resumir' se debe poner primero la ruta de alumnos y luego la de canal de impresion\n");
		
		printf("EJEMPLO: Si quiero actualizar el archivo de alumnos y agregar a los ingresantes del anio en el que estoy:");
		printf("archivo de alumno: alumnos.dat,  archivo de ingresantes:ingresantes.txt");
		printf("en la linea de comando debo poner:  ./hogwadin actualizar alumnos.dat ingresantes.txt");
	}else if(!strcmp(argv[1],"aplicar")){
		aplicar(argv[2],argv[3]);
	}else if(!strcmp(argv[1],"limpiar")){
		pasar_de_anio(argv[2],argv[3]);
	}else if(!strcmp(argv[1],"actualizar")){
		actualizar_alumnos(argv[2],argv[3]);
	}else if(!strcmp(argv[1],"resumir")){
		resumir_puntos(argv[2],stdout);
	}else{
		printf("argumentos invalidos, por favor ingreselos nuevamente\n");
	}

	return 0;
}