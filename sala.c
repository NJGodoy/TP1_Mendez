#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	FILE *archivo_objeto = fopen(objetos, "r");

	if(!archivo_objeto){
		perror("Error de archivos: ");
		return NULL;
	}

    	char string_objeto[MAX_TEXTO];
	int cantidad_objetos = 0;
	struct objeto **vector_objetos = NULL;

	while (fgets(string_objeto, MAX_TEXTO, archivo_objeto)){
		cantidad_objetos++;
        	vector_objetos = realloc(vector_objetos, (unsigned long)cantidad_objetos * sizeof(struct objeto));
		vector_objetos[cantidad_objetos - 1] = objeto_crear_desde_string(string_objeto);
	}

	fclose(archivo_objeto);

	if(cantidad_objetos == 0){
		return NULL;
	}

	FILE *archivo_interaccion = fopen(interacciones, "r");

	if(!archivo_interaccion){
		perror("Error de archivos: ");
		for(int i = cantidad_objetos; i>0; i--)
			free(vector_objetos[i - 1]);
		free(vector_objetos);
		return NULL;
	}

	char string_interaccion[MAX_TEXTO];
	int cantidad_interacciones = 0;
	struct interaccion **vector_interacciones = NULL;

	while (fgets(string_interaccion, MAX_TEXTO, archivo_interaccion)){
        	cantidad_interacciones++;
        	vector_interacciones = realloc(vector_interacciones, (unsigned long)cantidad_interacciones * sizeof(struct interaccion));
		vector_interacciones[cantidad_interacciones - 1] = interaccion_crear_desde_string(string_interaccion);

		if(vector_interacciones[cantidad_interacciones - 1] == NULL){
			for(int i = cantidad_objetos; i>0; i--)
				free(vector_objetos[i - 1]);
			free(vector_objetos);
			return NULL;
		}
	}

	fclose(archivo_interaccion);

	if(cantidad_interacciones == 0){
		for(int i = cantidad_objetos; i>0; i--)
			free(vector_objetos[i - 1]);
		free(vector_objetos);
		return NULL;
	}

	sala_t *sala = malloc(sizeof(sala_t));
	sala->objetos = vector_objetos;
	sala->cantidad_objetos = cantidad_objetos;
	sala->interacciones = vector_interacciones;
	sala->cantidad_interacciones = cantidad_interacciones;

	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if(!sala){
		if(cantidad != NULL)
			*cantidad = -1;
		return NULL;
	}

	if(cantidad != NULL && cantidad < 0){
		printf("ERROR DE PARAMETRO CANTIDAD\n");
		if(cantidad != NULL)
			*cantidad = -1;
		return NULL;
	}

	char **nombres;
	int iter = sala->cantidad_objetos;
	nombres = malloc((unsigned long)iter * sizeof(char *));
	if(!nombres){
		printf("ERROR DE MEMORIA\n");
		if(cantidad != NULL)
			*cantidad = -1;
		return NULL;
	}

	int cont_objetos = 0;
	for(int i = 0; i < iter; i++){
		nombres[i] = sala->objetos[i]->nombre;
		cont_objetos++;
	}

	if(cantidad != NULL){
		*cantidad = cont_objetos;
	}
	return nombres;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	char verbo_sala[MAX_VERBO];
	char objeto1_sala[MAX_NOMBRE];
	char objeto2_sala[MAX_NOMBRE];

	if(!sala || !verbo || !objeto1){
		return NULL;
	}

	for(int i=0; i<(sala->cantidad_interacciones); i++){
		strcpy(verbo_sala, sala->interacciones[i]->verbo);
		strcpy(objeto1_sala, sala->interacciones[i]->objeto);
		strcpy(objeto2_sala, sala->interacciones[i]->objeto_parametro);

		if(strcmp(objeto1_sala, objeto1) == 0 && strcmp(verbo_sala, verbo) == 0 && strcmp(objeto2_sala, objeto2) == 0){
			return true;
		}
	}
	return false;
}

void sala_destruir(sala_t *sala)
{
	for(int i = sala->cantidad_objetos; i>0; i--){
		free(sala->objetos[i - 1]);
	}
	free(sala->objetos);
	for(int j = sala->cantidad_interacciones; j>0; j--){
		free(sala->interacciones[j - 1]);
	}
	free(sala->interacciones);
	free(sala);
	return;
}
