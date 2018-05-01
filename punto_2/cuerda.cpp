#include "iostream"
#include "fstream"
#include "math.h"
using namespace std;

int nx=101;
float L = 100.0;
float dx = L/float(nx-1);
float c = sqrt(40.0/10.0);
float dt = sqrt(0.5)*dx/c;
int nt = 566;
float Tf = 200.0;
float coef = 0.99;

float cuerda1[566][101];
float x[101];

ofstream datos_cuerda("datos_cuerda.txt");

void crear_cuerda()
{
	for (int i = 0; i < nx; ++i)
	{
		x[i] = float(i*dx);
		cuerda1[0][i] = 1.25*x[i]/L;

		if (x[i]>0.8*L)
		{
			cuerda1[0][i] = 5.0-5.0*x[i]/L;
		}
	}
}

void primer_paso()
{
	for (int i = 0; i < nx; ++i)
	{
		cuerda1[1][i] = cuerda1[0][i]*coef;
	}
}


void imprimir_datos(int k)
{// Imprime todo el dominio

	datos_cuerda << endl;
	for (int i = 0; i < nx; ++i)
	{
		datos_cuerda << cuerda1[k][i] << " ";
	}	
}

void mover_y_actualizar(int k)
{	
	float r = c*c*dt*dt/(dx*dx);
	//cout << r << endl;

	// Aplicar eq onda en nodos interiores
	for (int i = 0; i < nx; ++i)
	{
		if (i!=0 & i!=nx-1)
		{ // diferencias finitas 2d
			cuerda1[k+1][i] = 2.0*cuerda1[k][i] + r*(cuerda1[k][i-1]-2.0*cuerda1[k][i]+cuerda1[k][i+1]) - cuerda1[k-1][i];
		}else
		{
			cuerda1[k+1][i] = 0.0;
		}
		
	}

	// actualizar dominio
	for (int i = 0; i < nx; ++i)
	{
		cuerda1[k][i] = cuerda1[k][i];
	}

	// Imprimir
	imprimir_datos(k);

}



int main()
{

	crear_cuerda();
	primer_paso();

	for (int k = 1; k < nt; ++k)
	{
		mover_y_actualizar(k);
	}

	//imprimir_datos();
	return 0;
}