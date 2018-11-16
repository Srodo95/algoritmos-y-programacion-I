#include "admin.h"


void cerrar_archivo(FILE* archivo){
	fclose(archivo);
}

bool son_iguales(char primer_cadena,char segunda_cadena){
	return(strcmp(primer_cadena,segunda_cadena)==0);
}

int pasar_de_anio(char* ruta_origen, char* ruta_destino){
	FILE* archivo_origen=fopen(ruta_origen,"rb");
	if(!archivo_origen){
		printf("error al abrir el archivo");
		return ERROR;
	}
	FILE* archivo_destino=fopen(ruta_destino,"wb");

	alumnos_t alumnos;
	int contador_alumnos=0;
	int cantidad_alumnos_egresados=0;

	fread(&alumnos,sizeof(alumnos_t),1,archivo_origen);
	while(!feof(archivo_origen)){
		if(alumnos.anio<ULTIMO_ANIO){
			alumnos.anio++;
			alumnos.puntos=0;
			contador_alumnos++;
			fwrite(&alumnos,sizeof(alumnos_t),1,archivo_destino);
		}
		else if(alumnos.anio==ULTIMO_ANIO){
			cantidad_alumnos_egresados++;
		}
		fread(&alumnos,sizeof(alumnos_t),1,archivo_origen);
	}
	cerrar_archivo(archivo_origen);
	cerrar_archivo(archivo_destino);
	return contador_alumnos-cantidad_alumnos_egresados;
}


int actualizar_alumnos(char* ruta_alumnos, char* ruta_actualizaciones){
	FILE* archivo_alumnos=fopen(ruta_alumnos,"w+b");
	if(!archivo_alumnos){
		return ERROR;
	}
	FILE* archivo_actualizaciones=fopen(ruta_actualizaciones,"rt");
	if(!archivo_actualizaciones){
		cerrar_archivo(archivo_alumnos);
		return ERROR;
	}
	FILE* archivo_union_alumnos=fopen("union.dat","wb");

	alumnos_t alumnos;
	alumnos_t alumnos_ingresados;

	int contador_alumnos_ingresados=0;
	fscanf(archivo_actualizaciones,"%[^;];%[^;];%[^;];%d\n",alumnos_ingresados.padron_alumno,alumnos_ingresados.nombre_alumno,alumnos_ingresados.casa_alumno,&alumnos_ingresados.anio);
	fread(&alumnos,sizeof(alumnos_t),1,archivo_alumnos);
	while(!feof(archivo_alumnos) && !feof(archivo_actualizaciones)){
		if(strcmp(alumnos.casa_alumno,alumnos_ingresados.casa_alumno)==0){
			if(alumnos.anio==alumnos_ingresados.anio){
				if(strcmp(alumnos_ingresados.padron_alumno,alumnos.padron_alumno)>0){
					alumnos_ingresados.puntos=0;
					fwrite(&alumnos_ingresados,sizeof(alumnos_t),1,archivo_union_alumnos);
					fscanf(archivo_actualizaciones,"%[^;];%[^;];%[^;];%d\n",alumnos_ingresados.padron_alumno,alumnos_ingresados.nombre_alumno,alumnos_ingresados.casa_alumno,&alumnos_ingresados.anio);
					contador_alumnos_ingresados++;
				}else{
					fwrite(&alumnos,sizeof(alumnos_t),1,archivo_union_alumnos);
					fread(&alumnos,sizeof(alumnos_t),1,archivo_alumnos);
				}
			}else if(alumnos.anio<alumnos_ingresados.anio){
				fwrite(&alumnos,sizeof(alumnos_t),1,archivo_union_alumnos);
				fread(&alumnos,sizeof(alumnos_t),1,archivo_alumnos);
			}else{
				alumnos_ingresados.puntos=0;
				fwrite(&alumnos_ingresados,sizeof(alumnos_t),1,archivo_union_alumnos);
				fscanf(archivo_actualizaciones,"%[^;];%[^;];%[^;];%d\n",alumnos_ingresados.padron_alumno,alumnos_ingresados.nombre_alumno,alumnos_ingresados.casa_alumno,&alumnos_ingresados.anio);
				contador_alumnos_ingresados++;
			}
		}else if(strcmp(alumnos.casa_alumno,alumnos_ingresados.casa_alumno)>0){
			fwrite(&alumnos,sizeof(alumnos_t),1,archivo_union_alumnos);
			fread(&alumnos,sizeof(alumnos_t),1,archivo_alumnos);
		}else{
			alumnos_ingresados.puntos=0;
			fwrite(&alumnos_ingresados,sizeof(alumnos_t),1,archivo_union_alumnos);
			fscanf(archivo_actualizaciones,"%[^;];%[^;];%[^;];%d\n",alumnos_ingresados.padron_alumno,alumnos_ingresados.nombre_alumno,alumnos_ingresados.casa_alumno,&alumnos_ingresados.anio);
			contador_alumnos_ingresados++;
		}
	}
	while(!feof(archivo_actualizaciones)){
		alumnos_ingresados.puntos=0;
		fwrite(&alumnos_ingresados,sizeof(alumnos_t),1,archivo_union_alumnos);
		fscanf(archivo_actualizaciones,"%[^;];%[^;];%[^;];%d\n",alumnos_ingresados.padron_alumno,alumnos_ingresados.nombre_alumno,alumnos_ingresados.casa_alumno,&alumnos_ingresados.anio);
		contador_alumnos_ingresados++;
	}
	while(!feof(archivo_alumnos)){
		fwrite(&alumnos,sizeof(alumnos_t),1,archivo_union_alumnos);
		fread(&alumnos,sizeof(alumnos_t),1,archivo_alumnos);
	}
	remove(ruta_alumnos);
	rename("union.dat",ruta_alumnos);
	cerrar_archivo(archivo_alumnos);
	cerrar_archivo(archivo_actualizaciones);
	cerrar_archivo(archivo_union_alumnos);

	return contador_alumnos_ingresados;
}

int aplicar(char* ruta_alumnos, char* ruta_bitacora){
	FILE* archivo_alumnos=fopen(ruta_alumnos,"r+b");
	if(!archivo_alumnos){
		printf("error al abrir el archivo");
		return ERROR;
	}
	FILE* archivo_bitacora=fopen(ruta_bitacora,"rt");
	if(!archivo_bitacora){
		cerrar_archivo(archivo_alumnos);
		return ERROR;
	}

	int entradas_bitacora=0;
	alumnos_t alumno;
	bitacora_t alumno_bitacora;

	fread(&alumno,sizeof(alumnos_t),1,archivo_alumnos);
	fscanf(archivo_bitacora,"%[^;];%[^;];%d;%s",alumno_bitacora.padron_bitacora,alumno_bitacora.fecha,&alumno_bitacora.puntos,alumno_bitacora.comentario);
	while(!feof(archivo_alumnos)){
		while(!feof(archivo_bitacora)){
			if(strcmp(alumno.padron_alumno,alumno_bitacora.padron_bitacora)==0){
				alumno.puntos+=alumno_bitacora.puntos;
				entradas_bitacora++;
			}
			fscanf(archivo_bitacora,"%[^;];%[^;];%d;%s",alumno_bitacora.padron_bitacora,alumno_bitacora.fecha,&alumno_bitacora.puntos,alumno_bitacora.comentario);
		}
		fseek(archivo_alumnos,-1*(int)sizeof(alumnos_t),SEEK_CUR);
		fwrite(&alumno,sizeof(alumnos_t),1,archivo_alumnos);
		fseek(archivo_alumnos,0L,SEEK_CUR);
		fseek(archivo_bitacora,0L,SEEK_SET);
		fscanf(archivo_bitacora,"%[^;];%[^;];%d;%s",alumno_bitacora.padron_bitacora,alumno_bitacora.fecha,&alumno_bitacora.puntos,alumno_bitacora.comentario);
		fread(&alumno,sizeof(alumnos_t),1,archivo_alumnos);
	}
	cerrar_archivo(archivo_alumnos);
	cerrar_archivo(archivo_bitacora);
	return entradas_bitacora;
	
}

resumen_casa_t resumir_puntos(char* ruta_alumnos, FILE* canal_impresion){
	FILE* archivo_alumnos=fopen(ruta_alumnos,"rb");

	alumnos_t alumno;
	resumen_casa_t resumen_anio;

	char casa_actual[MAX_CASA];
	int anio_actual;
	unsigned long total_puntos_anio;
	unsigned long total_puntos_casa;
	resumen_anio.puntos_alumno=0;
	unsigned long mayor_puntaje_casa=0;

	fread(&alumno,sizeof(alumnos_t),1,archivo_alumnos);
	while(!feof(archivo_alumnos)){
		strcpy(casa_actual,alumno.casa_alumno);
		total_puntos_casa=0;
		fprintf(canal_impresion,"Casa: %s\n",casa_actual);
		while(!feof(archivo_alumnos) && strcmp(casa_actual,alumno.casa_alumno)==0){
			total_puntos_anio=0;
			anio_actual=alumno.anio;
			fprintf(canal_impresion,"-----anio: %d\n", alumno.anio);
			while(!feof(archivo_alumnos) && strcmp(casa_actual,alumno.casa_alumno)==0 && anio_actual==alumno.anio){
				fprintf(canal_impresion,"-------puntaje del padron %s\n :  %d\n",alumno.padron_alumno,alumno.puntos);
				total_puntos_anio+=(unsigned long)alumno.puntos; 
				if((unsigned long)alumno.puntos>resumen_anio.puntos_alumno){
					resumen_anio.puntos_alumno=(unsigned long)alumno.puntos;
					strcpy(resumen_anio.padron,alumno.padron_alumno);		
				}
				fread(&alumno,sizeof(alumnos_t),1,archivo_alumnos);
			}
			fprintf(canal_impresion,"--------puntaje total del anio: %lu\n",total_puntos_anio);
			fread(&alumno,sizeof(alumnos_t),1,archivo_alumnos);
			total_puntos_casa+=total_puntos_anio;
		}
		if(total_puntos_casa>mayor_puntaje_casa){
			mayor_puntaje_casa=total_puntos_casa;
			strcpy(resumen_anio.casa,casa_actual);
			resumen_anio.puntos_casa=mayor_puntaje_casa;
		}
		fread(&alumno,sizeof(alumnos_t),1,archivo_alumnos);
	}
	fprintf(canal_impresion,"Casa ganadora: %s\n",resumen_anio.casa);
	fprintf(canal_impresion,"puntaje de la casa: %lu\n",resumen_anio.puntos_casa);
	fprintf(canal_impresion,"padron del alumno con mayor puntaje: %s\n",resumen_anio.padron);
	fprintf(canal_impresion,"puntaje: %lu\n",resumen_anio.puntos_alumno);
	cerrar_archivo(archivo_alumnos);
	cerrar_archivo(canal_impresion);
	return resumen_anio;
}



