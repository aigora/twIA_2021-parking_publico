#include<stdio.h>
#include<windows.h>
void parking_aid(int, int*, int*, int*, int*, char*);
void estado_plaza(int*,int*);
int main()
{
	char buzz='A';//la primera nota que oiremos por el altavoz será un Do (#A)
	int distancia=30;//a partir de esta distancia (cm) entramos en el rango de funcionamiento del sensor y se activa el sistema
	int ledblanco = 0, ledverde = 0, ledamarillo = 0, ledrojo = 0;
	int libre = 1;
	int ocupada = 0;
	while (distancia > 0)//simulamos con esto el coche aparcando y la lectura del sensor que cada vez será menor
	{
		parking_aid(distancia, &ledblanco, &ledverde, &ledamarillo, &ledrojo, &buzz);
		distancia--;
	}
	estado_plaza(&libre, &ocupada);
	//en el arduino, los leds no están fijos, si no que parpadean y en el último tramo siguen una secuencia. esto no se puede simular en visual.
}
void parking_aid(int distancia, int *ledblanco, int *ledverde, int *ledamarillo, int *ledrojo, char *buzz)
{
	if (distancia < 30 && distancia>=20)
	{
		*ledblanco = 1;
		*buzz = 'B';//ahora tenemos un re (#B)
		printf("%d %d %d %d %c\n", *ledblanco, *ledverde, *ledamarillo, *ledrojo, *buzz);
	}
	if (distancia < 20 && distancia >= 10)
	{
		*ledverde = 1;
		*buzz = 'C';//#C
		printf("%d %d %d %d %c\n", *ledblanco, *ledverde, *ledamarillo, *ledrojo, *buzz);
	}
	if (distancia < 10 && distancia >= 5)
	{
		*ledamarillo = 1;
		*buzz = 'D';//#D
		printf("%d %d %d %d %c\n", *ledblanco, *ledverde, *ledamarillo, *ledrojo, *buzz);
	}
	if (distancia < 5 && distancia>0)//no hace falta >=0 porque ya eliminamos esa posibilidad con el while
	{
		*ledrojo = 1;
		*buzz = 'E';//#E
		printf("%d %d %d %d %c\n", *ledblanco, *ledverde, *ledamarillo, *ledrojo, *buzz);
	}
	return;
}
void estado_plaza(int *libre, int *ocupada)
{
	int aux = 0;
	aux = *libre;
	*libre = *ocupada;
	*ocupada = aux;
	if (*libre == 0)
	{
		printf("la plaza esta ocupada\n");
	}
	return;
}