#include "objeto.h"
#include "estructuras.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct objeto *objeto_crear_desde_string(const char *string)
{
	char nombre[MAX_NOMBRE];
	char descripcion[MAX_TEXTO];
	char asibilidad[6];

	if(!string || strcmp(string, "") == 0){
		printf("El string está vacío\n");
		return NULL;
	}

	int elementos_leidos = sscanf(string, "%[^;];%[^;];%[^\n]", nombre, descripcion, asibilidad);

	if (elementos_leidos != 3){
		printf("Formato incorrecto de string\n");
		return NULL;
	}

	if (strcmp(asibilidad, "true") != 0 && strcmp(asibilidad, "false") != 0){
		printf("Formato incorrecto de string\n");
		return NULL;
	}

	if (strcmp(nombre, "") == 0 || strcmp(descripcion, "") == 0){
		printf("Formato incorrecto de string\n");
		return NULL;
	}	

	struct objeto *objeto = malloc(sizeof(struct objeto));
	if(!objeto){
		printf("Error de memoria\n");
		return NULL;
	}

	strcpy(objeto->nombre, nombre);
	strcpy(objeto->descripcion, descripcion);
	if(strcmp(asibilidad,"true") == 0)
		objeto->es_asible = true;
	else
		objeto->es_asible = false;

	return objeto;
}
