#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>//Biblioteca para asignación dinámica de memoria
#include<conio.h>//Biblioteca para el temporizador
#include<malloc.h>
#define TAM 5
#define DIM 5

struct coche
{
	char letra_matricula[4];
	int num_matricula;

};


//Funciones de los semaforos
void Estado1(int*, int*, int*);
void semaforo(void);
void semaforo2(void);
void salida(void);
void espera(void);
void espera2(void);

//Funciones del guiado
void situacion(int*);
void direccion(int*);
void lleno(int*, int*);

//Funciones aparcamiento
void parking_aid(int, int*, int*, int*, int*, char*);
void estado_plaza(int*, int*);


//Funciones gestion del parking
void meter_matricula(FILE* fp, char dia_actual[], struct coche* cars);
float seleccionarprecio(char dia_actual[], struct coche* cars);
int preciobase(char dia_actual[]);



int main()
{
	int funcionalidad, opcion;

	do
	{
		printf("\n\nBienvenido a nuestro programa\nQue funcionaldad de nuestro parking desea ver\n");
		printf("1-Gestion del parking\n2-Guiado de usuarios\n3-Aparcamiento\n4-Semaforos\n");
		scanf_s("%d", &funcionalidad);

		switch (funcionalidad)
		{
		case 1:
		{
			struct coche* cars;
			FILE* fp = 0;
			int* p, correcto, intento, i, j = 0, flag = 0, opc, gente = 0, n, numeros;
			char pass[10], dia_actual[30];
			const char contra[] = "A";
			float precio_total = 0;
			//contraseña para inicializar el parking
			{
				intento = 1;
				correcto = 0;
				printf("Hola Bernardo, buenos dias.\nIntroduce la password de operario(tiene tres intentos)\n");
				gets_s(pass);
				if (strcmp(pass, contra) == 0) correcto = 1;
				while ((correcto == 0) && (intento < 3))
				{
					intento++;
					printf("Contrasena incorrecta. %i intento: \n", intento);
					gets_s(pass);
					if (strcmp(pass, contra) == 0) correcto = 1;
				}
				if (correcto == 0)
				{
					printf("Has fallado los tres intentos, llamame al telefono 666 666 666\n\n");
				}
				else
				{
					printf("Clave generada correctamente!\n\n ");

					printf("Introduzca el numero de coches que podrian pasar al parking hoy\n");
					scanf_s("%d", &n);
					cars = (coche*)malloc(sizeof(coche) * n);

					printf("Hola, bienvenidos al parking, introduzca el dia de hoy(diasemana-dia-mes-año)\nACLARACION: en diasemana poner:\nlunes->1\nmartes->2\nmiercoles->3\njueves->\nviernes->5\nsabado->6\ndomingo->7\n");
					getchar();
					gets_s(dia_actual);

					//empieza la jornada laboral, el parking tiene 500 plazas. Serán guardadas las matriculas en un fichero. Esto es un parking moderno, y cada coche, según su año de matriculación(que obtendremos con las matriculas)
					//y el numero de horas que esté en el parking, tendra un precio u otro.

					//tendremos que elegir, metemos coche o sacamos coche
					do {
						printf("Ha llegado un coche, o se va un coche?\n1)HA LLEGADO\n2)SE VA\n3)SALIR(solo operarios)\n");
						scanf_s("%d", &opc);
						switch (opc)
						{
						case 1: //ha llegado->guardar matricula en un fichero
						{
							if (gente <= DIM)  //si queda espacio en el parking, meteremos un coche
							{
								printf("Hola, cliente. Introduzca su matricula NNNN LLL (donde las N son numeros y las L letras(mayusculas))\n");
								do
								{
									getchar();
									printf("Primero los numeros\nIMPORTANTE: 4 CIFRAS\n");
									scanf_s("%d", &cars->num_matricula);

								} while (cars->num_matricula < 999 || cars->num_matricula>10000); //para que el numero sea de cuatro cifras

								getchar();
								printf("\nAhora las letras\nIMPORTANTE: 3 CIFRAS\n");
								gets_s(cars->letra_matricula);
								meter_matricula(fp, dia_actual, cars);   //ahora que tenemos la matricula, la guardaremos en nuestro fichero de antes
								gente++;  //indica que se ha metido una persona
							}
							else   //si no queda espacio en el parking, diremos al cliente que esta lleno
							{
								printf("EL PARKING ESTA LLENO");
							}
							break;
						}
						case 2: //se va-> tiene que pagar
						{

							precio_total = seleccionarprecio(dia_actual, cars);
							printf("\nPRECIO A PAGAR:%f\n", precio_total);
							gente--;  //indica que se ha ido una persona
							break;
						}
						case 3:
							printf("Adios Bernardo! Tenga un buen dia\n");
							break;
						}


					} while (opc != 3);
				}
			}

			break;
		}

		case 2:  //Funcionalidad que muestra el guiado de los usuarios hasta la plaza disponible mas cercana
		{
			int* psensor, cocheentrada = 0, cierre = 0, completo = 0, * pcompleto, cochesalida = 0, plazasalida;
			psensor = (int*)malloc(TAM * sizeof(int));
			if (psensor == NULL)
			{
				printf("No hay memoria suficiente\n\n");
			}
			else
			{
				printf("Memoria asignada correctamente\n\n");
			}
			pcompleto = &completo;
			situacion(psensor);
			lleno(psensor, pcompleto);
			if (*pcompleto == 0)
			{
				do
				{
					printf("\n%cHa salido algun coche%c\n1-Si\n0-No\n", 168, 63);
					scanf_s("%d", &cochesalida);
					if (cochesalida == 1)
					{
						printf("%cEn que plaza estaba%c\n", 168, 63);
						scanf_s("%d", &plazasalida);
						*(psensor + (plazasalida - 1)) = 0;
					}
					printf("\n%cHay coche a la entrada%c\n1-Si\n0-No\n", 168, 63);
					scanf_s("%d", &cocheentrada);
					lleno(psensor, pcompleto);
					if (*pcompleto == 0)
					{
						if (cocheentrada == 1)
						{
							direccion(psensor);
						}
					}
					else
					{
						printf("\nLo sentimos nuestro parking esta comleto\n");
					}
					printf("\n%cEs la hora del cierre del parking%c:", 168, 63);
					scanf_s("%d", &cierre);
					printf("\n\n");
				} while (cierre != 1 && *pcompleto != 1);
			}
			else
			{
				printf("El parking esta completo\n");
			}
			break;
		}

		case 3:
		{
			char buzz = 'A';//la primera nota que oiremos por el altavoz será un Do (#A)
			int distancia = 30;//a partir de esta distancia (cm) entramos en el rango de funcionamiento del sensor y se activa el sistema
			int ledblanco = 0, ledverde = 0, ledamarillo = 0, ledrojo = 0;
			int libre = 1;
			int ocupada = 0;
			while (distancia > 0)//simulamos con esto el coche aparcando y la lectura del sensor que cada vez será menor
			{
				parking_aid(distancia, &ledblanco, &ledverde, &ledamarillo, &ledrojo, &buzz);
				distancia--;
			}
			estado_plaza(&libre, &ocupada);
			break;
			//en el arduino, los leds no están fijos, si no que parpadean y en el último tramo siguen una secuencia. esto no se puede simular en visual.

		}

		case 4: //Funcionalidad que muestra el funcionamiento de ls semaforos tanto para el control de la via como para el accseo a la via pública desde el parking
		{
			int pulsadorvia = 0, * ppulsadorvia, pulsadorparking = 0, * ppulsadorparking, dim = 1, contador = 0, salidacoche = 0, * psalida;
			//Con asignacion dinamica de memoria reservo 4 bytes de memoria (equivalente del int)
			ppulsadorvia = (int*)malloc(dim * sizeof(int));
			ppulsadorparking = (int*)malloc(dim * sizeof(int));
			psalida = (int*)malloc(dim * sizeof(int));
			if (ppulsadorvia == NULL)
			{
				printf("No hay espacio");
				exit(1);
			}
			if (ppulsadorparking == NULL)
			{
				printf("No hay espacio");
				exit(1);
			}
			if (psalida == NULL)
			{
				printf("No hay espacio");
				exit(1);
			}

			ppulsadorvia = &pulsadorvia;
			ppulsadorparking = &pulsadorparking;
			psalida = &salidacoche;
			do
			{
				Estado1(ppulsadorvia, ppulsadorparking, psalida);
				if (*psalida == 0)
				{
					if (*ppulsadorvia != 0 || *ppulsadorparking != 0)
					{
						if (*ppulsadorvia != 0 && *ppulsadorparking == 0)
						{
							espera(); //Llamada a las funciones espera y semaforo
							semaforo();
							contador++;
						}
						if (*ppulsadorparking != 0 && *ppulsadorvia == 0)
						{
							espera2(); //Llamada a las funciones espera2 y semaforo2
							semaforo2();
							contador++;
						}
						if (*ppulsadorparking != 0 && *ppulsadorvia != 0)
						{
							espera();
							semaforo();
							espera2();
							semaforo2();
							contador = contador + 2;

						}
					}
				}
				if (*psalida != 0)
				{
					if (*ppulsadorparking != 0 || *ppulsadorvia != 0)
					{
						if (*ppulsadorvia != 0 && *ppulsadorparking == 0)
						{
							espera();
							salida();
							espera();
							semaforo();
							contador++;
						}
						if (*ppulsadorparking != 0 && *ppulsadorvia == 0)
						{
							espera();
							salida();
							espera2();
							semaforo2();
							contador++;
						}
						if (*ppulsadorparking != 0 && *ppulsadorvia != 0)
						{
							espera();
							salida();
							espera();
							semaforo();
							espera2();
							semaforo2();
							contador = contador + 2;
						}
					}
				}
			} while (*ppulsadorvia != 0 || *ppulsadorparking != 0 || *psalida != 0);
			printf("\n\nSe han pulsado un total de %d veces los pulsadores de los semaforos", contador);

			free(ppulsadorvia); //Libero el espacio reservado
			free(ppulsadorparking);
			free(psalida);
			getchar();
			break;

		}


		}

		printf("\n%cDesea volver a escoger una funcionalidad%c\n0-NO\n1-SI\n", 168, 63);
		scanf_s("%d", &opcion);
	} while (opcion != 0);

	printf("\n\n\n");
	system("PAUSE");
}

void Estado1(int* x, int* y, int* z)
{
	int pulsavia, pulsaparking, salida;
	printf("\nSemaforo Via\nVerde\n\nSemaforo Parking\nRojo\n\nSemaforo Peaton Parking\nRojo\n\nSemaforo Peaton Via\nRojo");
	printf("\n\n\nPulse peaton de via\n");
	scanf_s("%d", &pulsavia);
	printf("\n\n\nPulse peaton de parking\n");
	scanf_s("%d", &pulsaparking);
	printf("\n\n\nPrevista salida de un coche del parking\n");
	scanf_s("%d", &salida);
	*x = pulsavia;
	*y = pulsaparking;
	*z = salida;
	system("cls");  //comando para borrar lo impreso en pantalla anteriormente
}

void espera(void)
{
	int seg;
	for (seg = 5; seg >= 0; seg--)
	{
		printf("\t\nSemaforo Via\nAmbar %d\t\n\nSemaforo Parking\nRojo %d\t\n\nSemaforo Peaton Parking\nRojo %d\t\n\nSemaforo Peaton Via\n Rojo %d", seg, seg, seg, seg);
		Sleep(999);
		system("cls");
	}
}

void semaforo(void)
{
	int color = 2, seg;
	while (color != 0)
	{
		if (color == 2) {
			for (seg = 10; seg >= 0; seg--) {
				printf("\t\nSemaforo Via\nRojo %d\t\n\nSemaforo Parking\nVerde %d\t\n\nSemaforo Peaton Parking\nRojo %d\t\n\nSemaforo Peaton Via\nVerde %d", seg, seg, seg, seg);
				Sleep(999);  //999 milisegundos 
				system("cls");
			}
		}
		else if (color == 1)
		{
			for (seg = 5; seg >= 0; seg--) {
				printf("\t\nSemaforo Via\nAmbar intermitente %d\t\n\nSemaforo Parking\nAmbar %d\t\n\nSemaforo Peaton Parking\nRojo %d\t\n\nSemaforo Peaton Via\nVerde Intermitente %d", seg, seg, seg, seg);
				Sleep(999);
				system("cls");
			}
		}
		color--;
	}
}

void espera2(void)
{
	int seg;
	for (seg = 5; seg >= 0; seg--)
	{
		printf("\t\nSemaforo Via\nVerde %d\t\n\nSemaforo Parking\nRojo %d\t\n\nSemaforo Peaton Parking\nRojo %d\t\n\nSemaforo Peaton Via\n Rojo %d", seg, seg, seg, seg);
		Sleep(999);
		system("cls");
	}
}

void semaforo2(void)
{
	int color = 2, seg;
	while (color != 0)
	{
		if (color == 2) {
			for (seg = 10; seg >= 0; seg--) {
				printf("\t\nSemaforo Via\nVerde %d\t\n\nSemaforo Parking\nRojo %d\t\n\nSemaforo Peaton Parking\nVerde %d\t\n\nSemaforo Peaton Via\nRojo %d", seg, seg, seg, seg);
				Sleep(999);  //999 milisegundos 
				system("cls");
			}
		}
		else if (color == 1)
		{
			for (seg = 5; seg >= 0; seg--) {
				printf("\t\nSemaforo Via\nVerde %d\t\n\nSemaforo Parking\nAmbar intermitente %d\t\n\nSemaforo Peaton Parking\nVerde intermitente %d\t\n\nSemaforo Peaton Via\nRojo %d", seg, seg, seg, seg);
				Sleep(999);
				system("cls");
			}
		}
		color--;
	}

}

void salida(void)
{
	int color = 2, seg;
	while (color != 0)
	{
		if (color == 2) {
			for (seg = 10; seg >= 0; seg--) {
				printf("\t\nSemaforo Via\nRojo %d\t\n\nSemaforo Parking\nVerde %d\t\n\nSemaforo Peaton Parking\nRojo %d\t\n\nSemaforo Peaton Via\nRojo %d", seg, seg, seg, seg);
				Sleep(999);  //999 milisegundos 
				system("cls");
			}
		}
		else if (color == 1)
		{
			for (seg = 5; seg >= 0; seg--) {
				printf("\t\nSemaforo Via\nAmbar intermitente %d\t\n\nSemaforo Parking\nAmbar %d\t\n\nSemaforo Peaton Parking\nRojo %d\t\n\nSemaforo Peaton Via\nRojo %d", seg, seg, seg, seg);
				Sleep(999);
				system("cls");
			}
		}
		color--;
	}
}

void situacion(int* psensor)
{
	int i;
	printf("\nIntroduzca el estado de cada sensor situado en cada plaza\n");
	for (i = 0; i < TAM; i++)
	{
		printf("Plaza %d:", i + 1);
		scanf_s("%d", psensor + i);
		printf("\n");
	}
}
void direccion(int* psensor)
{
	int i = 0, flag = 0;

	do
	{
		if (*(psensor + i) == 0)
		{
			printf("\nDirijase a la plaza numero %d\n", i + 1);
			*(psensor + i) = 1;
			flag = 1;
			i++;
		}
		i++;
	} while (flag != 1);
}
void lleno(int* psensor, int* pcompleto)
{
	int i = 0, flag = 0;
	do
	{
		if (*(psensor + i) == 1)
		{
			*pcompleto = 1;
			i++;
		}
		else if (*(psensor + i) == 0)
		{
			*pcompleto = 0;
			i++;
			flag = 1;
		}
	} while (flag != 1 && i < TAM);
}

void meter_matricula(FILE* fp, char dia_actual[], struct coche* cars)
{
	fopen_s(&fp, dia_actual, "at");
	if (fp == NULL)
	{
		printf("ERROR 02\n");
	}
	else
	{
		printf("SE HA ABIERTO CORRECTAMENTE\n");
		fprintf(fp, "%d %s\n", cars->num_matricula, cars->letra_matricula, 3);
	}
	fclose(fp);
}

float seleccionarprecio(char dia_actual[], struct coche* cars)  //falta determinar precios
{
	float horas = 0, precio = 0;
	int precio_bas = 0;
	printf("Esperemos que haya disfrutado la estancia, cuantas horas ha estado?\n");  //preguntamos las horas
	scanf_s("%d", &horas);
	//de lunes a jueves, el precio base sera: 3euros/h
	//viernes,sabados y domingos, el precio base sera: 5euros/h
	precio_bas = preciobase(dia_actual);
	printf("\nprecio base= %d, Ahora tocara añadirle el impuesto por antiguedad del coche\n", precio_bas);

	//ahora como el vehiculo sale, necesitamos otra vez el numero de matricula

	printf("\ndigame SOLO las letras de su matricula:\n");
	gets_s(cars->letra_matricula);
	getchar();
	printf("%c", cars->letra_matricula[0]);

	if (cars->letra_matricula[0] == 'A' || cars->letra_matricula[0] == 'B') //--> hasta 2002
	{
		precio = (float)precio_bas + (precio_bas * 0.5);  //50%
	}
	else if (cars->letra_matricula[0] == 'C' || cars->letra_matricula[0] == 'D')  //--> hasta 2006
	{
		precio = (float)precio_bas + (precio_bas * 0.4);  //40%
	}
	else if (cars->letra_matricula[0] == 'E' || cars->letra_matricula[0] == 'F' || cars->letra_matricula[0] == 'G') //--> hasta 2010
	{
		precio = (float)precio_bas + (precio_bas * 0.3);  //30%
	}
	else if (cars->letra_matricula[0] == 'H' || cars->letra_matricula[0] == 'I' || cars->letra_matricula[0] == 'J') //--> hasta 2017
	{
		precio = (float)precio_bas + (precio_bas * 0.2);  //20%
	}
	else if (cars->letra_matricula[0] == 'K' || cars->letra_matricula[0] == 'L') //--> hasta 2021
	{
		precio = (float)precio_bas;  //0%
	}
	return precio;
	printf("%f\n", precio);
}


int preciobase(char dia_actual[])
{
	int precio_base;

	if (dia_actual[0] >= 49 && dia_actual[0] <= 52)  //mirando en el codigo ascii, estos seran los numeros del 1 al 4
	{
		precio_base = 3;
	}

	else if (dia_actual[0] >= 53 && dia_actual[0] <= 56) //mirando en el codigo ascii, estos seran los numeros del 5 al 7
	{
		precio_base = 5;
	}
	return precio_base;
}

void parking_aid(int distancia, int* ledblanco, int* ledverde, int* ledamarillo, int* ledrojo, char* buzz)
{
	if (distancia < 30 && distancia >= 20)
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
void estado_plaza(int* libre, int* ocupada)
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