#include "iostream"
#include "fstream"
#include "math.h"
using namespace std;


int nt = int(500e3+1);
float dt=0.006;

float Q1[int(500e3+1)];
float Q2[int(500e3+1)];
float P1[int(500e3+1)];
float P2[int(500e3+1)];

float Q1k[4];
float Q2k[4];
float P1k[4];
float P2k[4];

void actualizar_rk4(int it)
{
	Q1[it+1] = Q1[it] + dt/6.0*( Q1k[0] + 2*Q1k[1] + 2*Q1k[2] +Q1k[3] );
	Q2[it+1] = Q2[it] + dt/6.0*( Q2k[0] + 2*Q2k[1] + 2*Q2k[2] +Q2k[3] );
	P1[it+1] = P1[it] + dt/6.0*( P1k[0] + 2*P1k[1] + 2*P1k[2] +P1k[3] );
	P2[it+1] = P2[it] + dt/6.0*( P2k[0] + 2*P2k[1] + 2*P2k[2] +P2k[3] );
}

float evaluar_derivada(int cual, float q1, float q2, float p1, float p2)
{
	float epsilon = 1.2;

	if (cual==0)
	{
		float dq1 = p1;
		return dq1;
	}else if (cual==1)
	{
		float dq2 = p2;
		return dq2;	
	}else if (cual==2)
	{
		float dp1=-2*q1/pow(pow(4.0*q1*q1+epsilon*epsilon,3),0.5);
		return dp1;
	}else if (cual==3)
	{
		float dp2;
		dp2 = (q1-q2)/pow(pow( (q1-q2)*(q1-q2)+epsilon*epsilon/4.0 ,3) ,0.5);
		dp2 = dp2 - (q1+q2)/pow(pow( (q1-q2)*(q1+q2)+epsilon*epsilon/4.0 ,3) ,0.5);
		return dp2;		
	}
}

void calcular_ks(int it)
{
	// k1
	Q1k[0] = evaluar_derivada(0, Q1[it], Q2[it], P1[it], P2[it]);
	Q2k[0] = evaluar_derivada(1, Q1[it], Q2[it], P1[it], P2[it]);
	P1k[0] = evaluar_derivada(2, Q1[it], Q2[it], P1[it], P2[it]);
	P2k[0] = evaluar_derivada(3, Q1[it], Q2[it], P1[it], P2[it]);

	//k2
	Q1k[1] = evaluar_derivada(0, Q1[it]+0.5*dt*Q1k[0], Q2[it]+0.5*dt*Q2k[0], P1[it]+0.5*dt*P1k[0], P2[it]+0.5*dt*P2k[0]);
	Q2k[1] = evaluar_derivada(1, Q1[it]+0.5*dt*Q1k[0], Q2[it]+0.5*dt*Q2k[0], P1[it]+0.5*dt*P1k[0], P2[it]+0.5*dt*P2k[0]);
	P1k[1] = evaluar_derivada(2, Q1[it]+0.5*dt*Q1k[0], Q2[it]+0.5*dt*Q2k[0], P1[it]+0.5*dt*P1k[0], P2[it]+0.5*dt*P2k[0]);
	P2k[1] = evaluar_derivada(3, Q1[it]+0.5*dt*Q1k[0], Q2[it]+0.5*dt*Q2k[0], P1[it]+0.5*dt*P1k[0], P2[it]+0.5*dt*P2k[0]);

	//k3
	Q1k[2] = evaluar_derivada(0, Q1[it]+0.5*dt*Q1k[1], Q2[it]+0.5*dt*Q2k[1], P1[it]+0.5*dt*P1k[1], P2[it]+0.5*dt*P2k[1]);
	Q2k[2] = evaluar_derivada(1, Q1[it]+0.5*dt*Q1k[1], Q2[it]+0.5*dt*Q2k[1], P1[it]+0.5*dt*P1k[1], P2[it]+0.5*dt*P2k[1]);
	P1k[2] = evaluar_derivada(2, Q1[it]+0.5*dt*Q1k[1], Q2[it]+0.5*dt*Q2k[1], P1[it]+0.5*dt*P1k[1], P2[it]+0.5*dt*P2k[1]);
	P2k[2] = evaluar_derivada(3, Q1[it]+0.5*dt*Q1k[1], Q2[it]+0.5*dt*Q2k[1], P1[it]+0.5*dt*P1k[1], P2[it]+0.5*dt*P2k[1]);

	//k4
	Q1k[3] = evaluar_derivada(0, Q1[it]+0.5*dt*Q1k[2], Q2[it]+0.5*dt*Q2k[2], P1[it]+0.5*dt*P1k[2], P2[it]+0.5*dt*P2k[2]);
	Q2k[3] = evaluar_derivada(1, Q1[it]+0.5*dt*Q1k[2], Q2[it]+0.5*dt*Q2k[2], P1[it]+0.5*dt*P1k[2], P2[it]+0.5*dt*P2k[2]);
	P1k[3] = evaluar_derivada(2, Q1[it]+0.5*dt*Q1k[2], Q2[it]+0.5*dt*Q2k[2], P1[it]+0.5*dt*P1k[2], P2[it]+0.5*dt*P2k[2]);
	P2k[3] = evaluar_derivada(3, Q1[it]+0.5*dt*Q1k[2], Q2[it]+0.5*dt*Q2k[2], P1[it]+0.5*dt*P1k[2], P2[it]+0.5*dt*P2k[2]);
}


int main()
{

	// valores inciales
	float a=0.353553390594;
	Q1[0] = a;
	Q2[0] = -a;
	P1[0] = 0.0;
	P2[0] = 0.0;

	cout << dt << endl;

	ofstream datos_caos("datos_caos.txt");

	for (int i3 = 0; i3 < nt-1; ++i3)
	//for (int i3 = 0; i3 < 20; ++i3)
	{
		calcular_ks(i3);
		actualizar_rk4(i3);

		if ( (Q1[i3] * Q1[i3+1]) < 0)
		{
			datos_caos << Q2[i3] << " " << P2[i3];
			datos_caos << endl;
		}
		
		//cout << Q1[i3] << "\t" << Q2[i3] << "\t" << P1[i3] << "\t" << P2[i3] << "\t";
//		for (int i = 0; i < 4; ++i)
//		{
//			cout << " " << P2k[i];
//		}
//		cout << endl;
	}

	
	

	//imprimir_datos();
	return 0;
}