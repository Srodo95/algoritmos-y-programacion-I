#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct alumnos{
	char padron_alumno[9];
	char nombre_alumno[32];
	char casa_alumno[16];
	int anio;
	int puntos;
} alumnos_t;


int main(){
	FILE* archivo=fopen("alumnos.dat","r");
	alumnos_t alumno;
	/*strcpy(alumno.padron_alumno,"EEEEE");
	strcpy(alumno.nombre_alumno,"Ernesto");
	strcpy(alumno.casa_alumno,"Gryffindor");
	alumno.anio=5;
	alumno.puntos=10;*/

	fread(&alumno,sizeof(alumnos_t),1,archivo);
	while(!feof(archivo)){
		printf("%s;%s;%s;%d;%d\n",alumno.padron_alumno,alumno.nombre_alumno,alumno.casa_alumno,alumno.anio,alumno.puntos);
		fread(&alumno,sizeof(alumnos_t),1,archivo);
	}
	fclose(archivo);
	return 0;
}


/*K3114GTO;Juan Cesar Rodo;Gryffindor;1
K3115GTO;Jorge Cessi;Gryffindor;1
K3116GTO;Julio Velez;Gryffindor;1
L5224GTO;Juan Cesar Rodo;Gryffindor;2

T3333RAD;Un nombre particularmente largo;Slytherin;3
I6443CAT;Un nombre particularmente largo;Slytherin;4
A2553CBG;Un nombre particularmente largo;Slytherin;5*/