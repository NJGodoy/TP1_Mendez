#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	//Los archivos deben venir como parámetros del main

	if(!argv[1] || !argv[2]){
		printf("No se pasaron parámetros correctos\n");
		return -1;
	}

	char *archivo_objeto = argv[1];
	char *archivo_interaccion = argv[2];

	sala_t *sala = sala_crear_desde_archivos(archivo_objeto, archivo_interaccion);

	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}

	//Mostrar todos los objetos en la sala

	printf("Objetos...\n");

	int cantidad_objetos = 0;
	char **nombres = sala_obtener_nombre_objetos(sala, &cantidad_objetos);

	for(int i = 0; i < cantidad_objetos; i++){
		printf("%i: %s\n", i, nombres[i]);
	}
	
	free(nombres);

	//Mostrar si son válidas las siguientes interacciones
	//1. examinar habitacion
	//2. abrir pokebola
	//3. usar llave cajon
	//4. quemar mesa
	printf("\n");
	printf("Interacciones...\n");
	printf("Examinar la habitacion: ");
	if(sala_es_interaccion_valida(sala, "examinar", "habitacion", ""))
		printf("Válido\n");
	else
		printf("Inválido\n");
	
	printf("Abrir pokebola: ");
	if(sala_es_interaccion_valida(sala, "abrir", "pokebola", ""))
		printf("Válido\n");
	else
		printf("Inválido\n");

	printf("Usar llave cajon: ");
	if(sala_es_interaccion_valida(sala, "usar", "llave", "cajon"))
		printf("Válido\n");
	else
		printf("Inválido\n");

	printf("Quemar mesa: ");
	if(sala_es_interaccion_valida(sala, "quemar", "mesa", ""))
		printf("Válido\n");
	else
		printf("Inválido\n");

	//Destruir la sala
	sala_destruir(sala);

	return 0;
}
