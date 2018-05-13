#include <iostream>
#include <cmath>
#include <list>
#include <fstream>
#include <vector>
#include "gnuplot_i.hpp"


using namespace std;

int stopien;
double *wsp;
double start, stop;
double dokladnosc=0.1;
double (*funk)(double);

double wezel(int k, int n){
		return cos((2*k-1)/(2.0*n)*M_PI);
}
double wartosc(double x, int n){
		return cos(n*acos((x)));
}
double wzor(int j, int N){
		double sum = 0;
		for(int i=1; i<=N; i++)
				sum+=(funk(wezel(i,N))*cos(M_PI*j*(i-0.5)/N));

		sum*= (2.0/N);
		return sum;
}
double approx(double x, int N)
{
		double result = 0;
		for(int i = 0;i<=N-1;i++){
				result+= (wzor(i,N)*wartosc(x,i));
		}
		result -= (0.5*wzor(0,N));
		return result;
}
double sinus(double x){
	return sin(x*9);
}

double odw(double x)
{
	x =  fabs(x);
	return sin(9*x);
}
double bezw(double x)
{
	return fabs(x);
}
double horner(double x)
{
	double wynik = wsp[0];
	for(int i=1;i<=stopien;i++)
		wynik = wynik*x + wsp[i];
	
	return wynik;
}


void wybierzFunk(){
		cout << "Wybierz funkcje: \n1. f(x) = sinus(x+3)\n2. złożenie funkcji 1. i 4. f(x) = sinus(|x|+3) \n3. Wielomian \n4. f(x) = |x| \n ";
		int wybor;

		cin >> wybor;

		switch(wybor){
		case 1:
				funk=sinus;
				break;
		case 2:
				funk=odw;
				break;
		case 3:
			cout<<"Podaj stopien wielomianu: ";
			cin>>stopien;
			wsp = new double [stopien+1];
			for(int i=0;i<=stopien;i++)
			{
				cout<<"Podaj wspolczynnik stojacy przy potedze "<<stopien-i<<": ";
				cin>>wsp[i];
			}

				funk=horner;
				break;
		case 4:
				funk=bezw;
				break;
		default:
				cout << "Złą wartość \n";
		}
}

int main()
{
			wybierzFunk();
			start = -1;
			stop = 1;
			Gnuplot funkcja;
			Gnuplot main_plot;

			main_plot.set_title( "Wykres" );
			main_plot.set_xlabel( "X" );
			main_plot.set_ylabel( "Y" );


			main_plot.set_grid();
			main_plot.set_xrange( start , stop ) ;
			main_plot.set_yrange(-2,2);
			main_plot.set_style( "lines" );
			int precyzja = 1000 ;
			double skok = (stop-start)/precyzja;
			vector<double> x;
			vector<double> y;
			vector<double> y_approx2;
			vector<double> y_approx4;
			vector<double> y_approx5;
			vector<double> y_approx7;
			vector<double> y_approx10;
			for(double d=start; d<=stop;d+=skok){
				x.push_back(d);
				y.push_back(funk(d));
				y_approx2.push_back(approx(d,2));
				y_approx4.push_back(approx(d,4));
				y_approx5.push_back(approx(d,5));
				y_approx7.push_back(approx(d,7));
				y_approx10.push_back(approx(d,10));
			}
			funkcja.plot_xy( x, y, "Wykres funkcji." );
			getchar();
			main_plot.plot_xy( x, y, "Wykres funkcji." );

			main_plot.plot_xy( x, y_approx2, "2 wezly" );
			main_plot.plot_xy( x, y_approx4, "4 wezly" );
			main_plot.plot_xy( x, y_approx5, "5 wezlow" );
			main_plot.plot_xy( x, y_approx7, "7 wezlow" );
			main_plot.plot_xy( x, y_approx10, "10 wezlow" );

			getchar();
			getchar();
			return 0;
			}

