#include "iostream"
#include "fstream"
#include "math.h"
using namespace std;

int n=511;
int dominio[511][511];
float Voltaje1[511][511];
float Voltaje2[511][511];
float L = 5.0;
float h = 5.0/512.0;

void crear_dominio()
{
	// Llenar matriz de dominio
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			dominio[i][j] = 0; // inicializar todo en verdadero
		}
	}

	for (int i = 0; i < n; ++i)
	{
		dominio[i][0] = 2; // borde izq
		dominio[i][n-1] = 2; // borde derecho
		dominio[0][i] = 2; // borde sup
		dominio[n-1][0] = 2; // borde inf
	}

	float d = 1.0;
	float l = 2.0;

	int j0 = n*(1.0/2.0-l/(2*L));
	int Dj = n*(l/L);

	int i0 = n*(1.0/2.0-d/(2*L));
	int Di = n*(d/L);

	for (int j = j0; j < j0+Dj; ++j)
	{
		dominio[i0][j] = 1;
		dominio[i0+Di][j] = -1;
	}


	// Lenar matriz de voltaje
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if(dominio[i][j]==0 | dominio[i][j]==2)
			{ // los nodos centrales y los bordes tienen voltaje inicial 0
				Voltaje1[i][j] = 0.0;
			}else if (dominio[i][j]==1)
			{
				Voltaje1[i][j] = 50.0;
			}else if (dominio[i][j]==-1)
			{
				Voltaje1[i][j] = -50.0;
			}

			Voltaje2[i][j] = Voltaje1[i][j];
		}
	}

}

void relajar_gradientes_y_actualizar()
{	
	// Aplicar metodo de relajacion en nodos interiores unicamente
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if(dominio[i][j]==0)
			{ // Solo para nodos interiores
				Voltaje2[i][j] = Voltaje1[i][j+1] + Voltaje1[i][j-1] + Voltaje1[i+1][j] + Voltaje1[i-1][j];
				Voltaje2[i][j] = Voltaje2[i][j]/4.0;
			}
		}

	}

	// actualizar dominio
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			Voltaje1[i][j] = Voltaje2[i][j];
		}

	}

}

void imprimir_datos()
{

	float E[511][511][2];

	ofstream datos_placas("datos_placas.txt");
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			datos_placas << Voltaje1[i][j] << ",";

			if (dominio[i][j]!=2)
			{ //calcular campo electrico para nodos interiores
				E[i][j][0] = -( Voltaje2[i][j]-Voltaje2[i][j-1] )/h;
				E[i][j][1] = -( Voltaje2[i][j]-Voltaje2[i-1][j] )/h;
			}else
			{
				E[i][j][0] = 0.0;
				E[i][j][1] = 0.0;
			}	
		}
		datos_placas << endl;
	}

	// Imprimir campo electrico X
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			datos_placas << E[i][j][0] << ",";
		}
		datos_placas << endl;
	}

	// Imprimir campo electrico y
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			datos_placas << E[i][j][1] << ",";
		}
		datos_placas << endl;
	}

}

int main()
{

	crear_dominio();

	for (int k = 0; k < int(0.01*2*pow(n,2)); ++k)
	{
		relajar_gradientes_y_actualizar();
	}

	imprimir_datos();
	return 0;
}