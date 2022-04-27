#include "estructuras.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct interaccion *interaccion_crear_desde_string(const char *string)
{
	char objeto[MAX_NOMBRE];
	char verbo[MAX_VERBO];
	char objeto_2[MAX_NOMBRE];
	char accion_s[MAX_TEXTO];

    	char tipo;
	char nombre_objeto[MAX_NOMBRE];
    	char mensaje[MAX_TEXTO];

	if(!string || strcmp(string, "") == 0){
		printf("Cadena vacía\n");
		return NULL;
	}

	int elementos_leidos_interaccion = sscanf(string, "%[^;];%[^;];%[^;];%[^\n]", objeto, verbo, objeto_2, accion_s);

	if(strcmp(objeto, "") == 0 || strcmp(verbo, "") == 0){
		printf("Formato incorrecto de string\n");
		return NULL;
	}

	if(strcmp(objeto_2, "_") == 0){
		strcpy(objeto_2, "");
	}

	if (elementos_leidos_interaccion != 4){
		printf("Formato incorrecto de string\n");
		return NULL;
	}

	int elementos_leidos_accion = sscanf(accion_s, "%c:%[^:]:%[^\n]", &tipo, nombre_objeto, mensaje);

	if (elementos_leidos_accion != 3){
		printf("Formato incorrecto de string\n");
		return NULL;
	}

	if(strcmp(nombre_objeto, "_") == 0){
		strcpy(nombre_objeto, "");
	}

	struct interaccion *interaccion = malloc(sizeof(struct interaccion));

	if(!interaccion){
		printf("Error de memoria\n");
		return NULL;
	}

	strcpy(interaccion->objeto, objeto);
	strcpy(interaccion->verbo, verbo);
	strcpy(interaccion->objeto_parametro, objeto_2);

	switch(tipo){
		case 'd':
		interaccion->accion.tipo = DESCUBRIR_OBJETO;
		break;
		case 'r':
		interaccion->accion.tipo = REEMPLAZAR_OBJETO;
		break;
		case 'm':
		interaccion->accion.tipo = MOSTRAR_MENSAJE;
		break;
		case 'e':
		interaccion->accion.tipo = ELIMINAR_OBJETO;
		break;
		default:
		interaccion->accion.tipo = ACCION_INVALIDA;

	}

	strcpy(interaccion->accion.objeto, nombre_objeto);
	strcpy(interaccion->accion.mensaje, mensaje);

	return interaccion;
}
