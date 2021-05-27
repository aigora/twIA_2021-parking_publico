#include<stdio.h>
#include<windows.h>
#include<malloc.h>
#define TAM 5

void situacion(int*);
void direccion(int*);
void lleno(int*,int*);

int main()
{
	int *psensor,cocheentrada=0,cierre=0,completo=0,*pcompleto,cochesalida=0,plazasalida;
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
	lleno(psensor,pcompleto);
	if (*pcompleto == 0)
	{
		do
		{
			printf("\n%cHa salido algun coche%c\n1-Si\n0-No\n",168,63);
			scanf_s("%d", &cochesalida);
			if (cochesalida == 1)
			{
				printf("%cEn que plaza estaba%c\n",168,63);
				scanf_s("%d",&plazasalida);
				*(psensor + (plazasalida - 1)) = 0;
			}
			printf("\n%cHay coche a la entrada%c\n1-Si\n0-No\n",168,63);
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
}

void situacion(int* psensor)
{
	int i;
	printf("\nIntroduzca el estado de cada sensor situado en cada plaza\n");
	for (i = 0; i < TAM; i++)
	{
		printf("Plaza %d:",i+1);
		scanf_s("%d", psensor+i);
		printf("\n");
	}
}
void direccion(int* psensor)
{
	int i=0,flag=0;

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
	int i=0,flag=0;
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
	} while (flag != 1 && i<TAM);
}