//Zadanie 1        Wroc³aw, 14 wrzesien 2015r.*************/
//Przedmiot ODPP                                         /
//Monika Stec                                          /
/******************Wczytywanie z pliku**************/


#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int MAX(int liczba_maszyn,int liczba_zadan,int P[][30], int C[][30]){
	int Cmax2=0;
		//czesc glowna
	for (int k=1; k<=liczba_maszyn; k++)
	{
		for(int i=1;i<=liczba_zadan;i++)
		{
			C[i][k]=max(C[i][k-i],C[i-1][k])+P[i-1][k-1];

			if(C[i][k]>Cmax2){

				Cmax2=C[i][k];
			}
		}
	}

	return Cmax2;

}

int main(){
	
/*******************Deklaracja**************************************************/
	int liczba_zadan, liczba_maszyn;
	int Cmax[100000]; // funkcja celu
	int P[110][30];
	int C[110][30];
	//int PI[110];
	int tablica[110][30];
	int n,lb,tmp, tmp1;
	double Temp, lambda;
	double szansa, kontrszansa;
	int Cmax2,minimum;

/****************Odczyt z pliku*************************************/
	ifstream plik("NEH7.DAT",ios::in);
	plik >> liczba_zadan; // Wczytanie wartosci oznaczajacej ilosc zadan 
	plik >> liczba_maszyn;

	//lb=liczba_zadan*(liczba_zadan-1)/2;
	//iteracja
	lb = 100000;
	Temp = 1000;
	lambda = 0.99999;
	//wczytanie danych

	for(int a=0; a<liczba_zadan;a++)
	{
	for(int b=0; b<liczba_maszyn; b++) // Wczytanie danych z pliku do tablic
		{
        plik>>P[a][b];
		C[0][b]=0;
		tablica[a][b]=P[a][b];
		}
	
	}
	// poczatkowe minimum, poprawiane rekurencyjnie
	minimum=MAX(liczba_maszyn,liczba_zadan,P,C);
	Cmax[0]=minimum;
	for(int j=1;j<lb+1;j++)
	{		
			tmp=rand() % (liczba_zadan-1);
			tmp1=rand() % (liczba_zadan-1);
			
			for(int b=0; b<liczba_maszyn; b++) // Wczytanie danych z pliku do tablic
			{
				tablica[tmp1][b]=P[tmp][b];
				tablica[tmp][b]=P[tmp1][b];
			}
		// Wyliczanie Cmax odbywa sie po kazdej zmianie w tablicy 
	Cmax[j]=MAX(liczba_maszyn,liczba_zadan,tablica,C);
		// Sprawdzenie nowego Cmaxa
	if(minimum>=Cmax[j]) 
	{
		minimum=Cmax[j];
		printf("minimum %d",minimum);


	}
	if (Cmax[j] - Cmax[j-1] >0) // Jeœli Cmax wiêksze o 1 to te¿ zostaje nowym Cmax
	{
			szansa = exp(-(Cmax[j] - Cmax[j-1]) / Temp); // Liczymy prawdopodobieñstwo zaakceptowania zmiany
			kontrszansa = rand()%101; // Losujemy liczbê
			kontrszansa = kontrszansa / 100; // Sprowadzamy do przedzia³u (0,1)
			if (szansa < kontrszansa) // Jeœli trafiliœmy to mamy nowy Cmax
			{

				for(int b=0; b<liczba_maszyn; b++) // Wczytanie danych z pliku do tablic
				{
					tablica[tmp1][b]=P[tmp][b];
					tablica[tmp][b]=P[tmp1][b];
				}		
			}
		}

		Temp = lambda*Temp; 
	// Zmniejszamy Temp
	}





	/*********************************************************************/
	/*************ZAPIS DO PLIKU*****************************************/
	ofstream wynik("04_11_3.txt", ios::out);
	wynik<<"minimum"<<endl;
	for(int i=0;i<liczba_zadan;i++){
		for (int k=0; k<liczba_maszyn ;k++)
		wynik<<tablica[i][k]<<' ';
	wynik<<endl;
  
	}

	/*for(int i=0;i<liczba_maszyn;i++){
		for (int k=0; k<liczba_zadan ;k++)
		wynik<<C[k+1][i+1]<<' ';
	wynik<<endl;
  
	*/
	wynik<<minimum<<endl;
	//wynik<<n[i]<<endl;
	wynik.close();
	getchar();
	//system("pause");
	//return 0;
}


