	#include <stdio.h>

	main() /* Simula una clave de acceso */
	{
	   int usuario,clave=18276;
	   printf("Introduce tu clave: ");
	   scanf("%d",&usuario);
	   if(usuario==clave)
	      printf("Acceso permitido al grupo 6");
	   else
	      printf("Acceso denegado");
	}
