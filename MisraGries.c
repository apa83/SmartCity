#include <stdio.h>

typedef struct ficha_enlace{			//A partir de ahora declarar una variable de esta estructura será con: ficha_enlace_t [nombre variable]
	int nodo_origen;
	int nodo_destino;
	int color;							// Color del enlace
	int estado;							// 1 = Enlace con color fijo  0 = enlace sin color
}ficha_enlace_t;

ficha_enlace_t enlaces [100];			//conjunto de lista de las que dispongo

void leer_fichero(FILE *fichero, ficha_enlace_t enlaces[],int *numero_nodos,int *grado,int colores[],int *numero_enlaces){			//Función que unicamente lee el fichero e integra el los datos en las estructuras
	int trush,aux1,aux2=0;
	int i,k=1,j=0,l=0;
	fscanf(fichero,"%i",&aux1);
	for(i=1;(fscanf(fichero,"%i %i %i",&enlaces[i].nodo_origen , &enlaces[i].nodo_destino, &trush ))==3;i++){	//Lectura correcta de los datos y guardadas en sus respectivos huecos
		//printf("Enlace directo entre: %i  y  %i \n\n\n",enlaces[i].nodo_origen,enlaces[i].nodo_destino );
		enlaces[i].color=0;							//Todos los colores arrancan a 0 que no a NULL ¡OJO!
		enlaces[i].estado=0;
		(*numero_nodos) = i;						//Todos los estados arrancan a 0 qie no a NULL ¡OJO!
		if(k!=enlaces[i].nodo_origen){				//alculo el grado máximo del grafo		¡¡¡SOLO FUNCIONA SI LOS ENLACES ESTÁN EN ORDEN ( nodo_origen)!!!
			k=enlaces[i].nodo_origen;
			if(j>aux2){
				aux2=j;
			}
			j=1;
		}
		else{
			j++;
		}
		(*numero_enlaces)=i;
	}
	for(i=0;i<45;i++){				//Aprovecho para incializar el vector de colores
		colores[i]=i;
	}

	*numero_nodos = aux1;
	*grado = aux2;
}
																									//del que estoy usando no haya problemas
void pintar_enlaces(ficha_enlace_t enlaces[],int numero_enlaces){
	int i;

	for(i = 1 ; i <= numero_enlaces;i++){
		printf("\n\nEl enlace  [ %i ]-------[ %i ]  es de color: {%i} ",enlaces[i].nodo_origen,enlaces[i].nodo_destino,enlaces[i].color);
	}
}

void inicializa(ficha_enlace_t enlaces[]){
	int i;
	for(i=0;i<100;i++){
		enlaces[i].color=0;
		enlaces[i].estado=0;
		enlaces[i].nodo_destino=0;
		enlaces[i].nodo_origen=0;
	}
}

void cortafuegos_1 (ficha_enlace_t enlaces[],int grado,int i,int numero_enlaces){

	int j=1;

	printf("\nPrimer cortafuegos");
	printf("\nVamos a analizar el enlace: [%i]--[%i] --> {%i}",enlaces[i].nodo_origen,enlaces[i].nodo_destino,enlaces[i].color);
	if(enlaces[i].estado == 1){
		printf("\nEnlace cerrado, no debemos operar con el");
	}
	else{
		printf("\nEnlace no cerrado");
		for(j=1;j<numero_enlaces;j++){
			if(enlaces[j].nodo_origen == enlaces[i].nodo_origen){
				printf("\nEnfrentando [%i]--[%i]  VS  [%i]--[%i]",enlaces[i].nodo_origen,enlaces[i].nodo_destino,enlaces[j].nodo_origen,enlaces[j].nodo_destino);
				if(enlaces[j].color == enlaces[i].color && enlaces[j].estado == 1){
					printf("\nDetecto coincidencia de color con el enlace: [%i]--[%i]--{%i}",enlaces[j].nodo_origen,enlaces[j].nodo_destino,enlaces[j].color);
					printf("\nVuelvo al origen para probar con otro color");
					if(enlaces[i].color==grado){
						enlaces[i].color = 0;
					}
					else{
						enlaces[i].color++;
					}
					cortafuegos_1(enlaces,grado,i,numero_enlaces);
				}
			}
		}
	}
	printf("\nCortafuegos 1 SUPERADO\n");
	//system("PAUSE");
}

void cortafuegos_2 (ficha_enlace_t enlaces[],int grado,int i,int numero_enlaces,int *fin){

	int j;

	printf("\nSegundo Cortafuegos");
	if(enlaces[i].estado==1){
		printf("\nEnlace cerrado no debemos operar con el");
	}
	else{
		for(j=1;j<=numero_enlaces;j++){
			if(enlaces[j].nodo_origen == enlaces[i].nodo_destino && enlaces[j].estado == 1){
				if(enlaces[j].color == enlaces[i].color){
					if(enlaces[i].color==grado){
						enlaces[i].color = 0;
					}
					else{
						enlaces[i].color++;
					}
					cortafuegos_1(enlaces,grado,i,numero_enlaces);
				}
			}
		}
	}

	printf("\nSegundo cortafuegos SUEPRADO\n");

	//system("PAUSE");
}

void cerrar_enlace(ficha_enlace_t enlaces[],int i,int numero_enlaces,int *fin){
	int x;
	if(enlaces[i].estado != 1){
		printf("\nProcedemos a cerrar los enlaces");

		enlaces[i].estado = 1;

		printf("\nCerramos enlace: [%i]--[%i]----{%i}",enlaces[i].nodo_origen,enlaces[i].nodo_destino,enlaces[i].color);

		for( x = 1 ; x <= numero_enlaces ; x++){
			if(enlaces[x].nodo_origen == enlaces[i].nodo_destino && enlaces[x].nodo_destino == enlaces[i].nodo_origen){
				enlaces[x].color = enlaces[i].color;
				enlaces[x].estado = 1;
				printf("\nCerramos enlace: [%i]--[%i]----{%i}",enlaces[x].nodo_origen,enlaces[x].nodo_destino,enlaces[x].color);
			}
		}

		(*fin)=(*fin)+2;
		//system("PAUSE");
	}
	else{
		printf("\nEnlace ya cerrado , no debemos operar con el");
	}


}

void asigna_color(ficha_enlace_t enlaces[],int grado,int numero_enlaces){
	int i;
	int anterior=1,color=0;
	for(i=1;i<=numero_enlaces;i++){
		if(enlaces[i].nodo_origen == anterior){
			enlaces[i].color = color;
			color++;
		}
		else{
			anterior=enlaces[i].nodo_origen;
			enlaces[i].color = 0;
			color = 1;
		}
	}
}

int main(){
	system("COLOR F3");																//Cambio el color porque me hadce daño verlo así


	int numero_nodos,grado,fin=0,primer_criterio,segundo_criterio,tercer_criterio,numero_enlaces;															//Variables importantes [NO TOCAR]

	int i=1;

	int colores[45];																//Vector de colores (Le doy un número al hacer porque no se usar todavía el MALOC

	FILE *fichero= fopen("grafo2.txt","r");											//fichero de entrada = grafo.txt para ejemplo de clase

	if(fichero==NULL){
		printf("No se ha podido abrir correctamente el fichero\n");					//Fichero no encontrado
	}
	else{
		inicializa (enlaces);

		leer_fichero( fichero,enlaces,&numero_nodos,&grado,colores,&numero_enlaces);							//Los enlaces estan numerado d forma natural ( empezando [1] )

		printf("\nNumero de nodos: %i\nGrado: %i \nNumero_enlaces %i",numero_nodos,grado,numero_enlaces);

		asigna_color(enlaces,grado,numero_enlaces);

		while(fin < numero_enlaces){


			cortafuegos_1(enlaces,grado,i,numero_enlaces);

			cortafuegos_2(enlaces,grado,i,numero_enlaces,&fin);

			cerrar_enlace(enlaces,i,numero_enlaces,&fin);

			i++;
		}

		pintar_enlaces (enlaces,numero_enlaces);

	}
}
