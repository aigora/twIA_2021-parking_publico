#include<stdio.h>
#include<windows.h>
#include<stdlib.h>//Biblioteca para asignación dinámica de memoria
#include<conio.h>//Biblioteca para el temporizador

void Estado1(int*,int*,int*);
void semaforo(void);
void semaforo2(void);
void salida(void);
void espera(void);
void espera2(void);

int main()
{
	int pulsadorvia = 0, * ppulsadorvia,pulsadorparking=0, * ppulsadorparking, dim = 1, contador = 0,salidacoche=0, * psalida;
	//Con asignacion dinamica de memoria reservo 4 bytes de memoria (equivalente del int)
	ppulsadorvia = (int*)malloc(dim * sizeof(int));
	ppulsadorparking = (int*)malloc(dim * sizeof(int));
	psalida= (int*)malloc(dim * sizeof(int));
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
		Estado1(ppulsadorvia,ppulsadorparking,psalida);
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
					espera2(); //Llamada a las funciones espera y semaforo
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
					espera(); //Llamada a las funciones espera y semaforo
					semaforo();
					contador++;
				}
				if (*ppulsadorparking != 0 && *ppulsadorvia == 0)
				{
					espera();
					salida();
					espera2(); //Llamada a las funciones espera y semaforo
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
	} while(*ppulsadorvia != 0 ||*ppulsadorparking!=0 || *psalida!=0);
	printf("\n\nSe han pulsado un total de %d veces los pulsadores de los semaforos", contador);

	free(ppulsadorvia);
	free(ppulsadorparking);
	free(psalida);//Libero el espacio reservado
	getchar();
	printf("\n\n");
	system("pause");
}
void Estado1(int* x,int* y,int* z)
{
	int pulsavia,pulsaparking,salida;
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
		else if(color == 1)
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