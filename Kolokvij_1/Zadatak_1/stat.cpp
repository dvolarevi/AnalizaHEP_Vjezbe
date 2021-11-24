#include "stat.h"
#include <iostream>
#include <math.h>
#include <random>
#include <time.h>
#include <fstream>
using namespace std;
//#######################
//stat
//#######################
Statistics::Statistics(){
	cout << "Objekt je uspješno kreiran" << endl;
	};
//B)
double Statistics::NormalDistribution(int x, int y, double mi, double sigma){
	double P;
	double e;
	for(int x; x<y;x++){
		e=pow((x-mi),2)/(2*pow(sigma,2));
		e=exp(-e);
		P=sigma*sqrt(2*3.14);
		P=(1/P)*e;
		cout << "P:\t" << P << endl;
		}
	};
double Statistics::NormalDistribution(int x, double mi, double sigma){
	double P;
	double e;
	e=pow((x-mi),2)/(2*pow(sigma,2));
	e=exp(-e);
	P=sigma*sqrt(2*3.14);
	P=(1/P)*e;
	cout << "P:\t" << P << endl;
	};
double Statistics::NormalDistribution(double mi, double sigma){
	cout << "Raspon x in <0,10>" << endl;
	double P;
	double e;
	for(int x; x<11;x++){
		e=pow((x-mi),2)/(2*pow(sigma,2));
		e=exp(-e);
		P=sigma*sqrt(2*3.14);
		P=(1/P)*e;
		cout << "P:\t" << P << endl;
		}
	};
//A)
double Statistics::CalculatePi(){
	cout << "Default # events = 5000. " << endl;
	int interval, i;
	interval=5000;
    	double rand_x, rand_y, origin_dist, pi;
    	int circle_points = 0, square_points = 0;
  
	    srand(time(NULL));
	  
	    for (i = 0; i < (interval * interval); i++) {
	  
		rand_x = double(rand() % (interval + 1)) / interval;
		rand_y = double(rand() % (interval + 1)) / interval;
	  
		origin_dist = rand_x * rand_x + rand_y * rand_y;
	  
		if (origin_dist <= 1)
		    circle_points++;
	  
		square_points++;
	  
		pi = double(4 * circle_points) / square_points;
	  
	    }
	  
	    cout << "\nFinal Estimation of Pi = " << pi;
	};

double Statistics::CalculatePi(int broj_dog){
	int interval, i;
	interval=broj_dog;
    	double rand_x, rand_y, origin_dist, pi;
    	int circle_points = 0, square_points = 0;
  
	    srand(time(NULL));
	  
	    for (i = 0; i < (interval * interval); i++) {
	  
		rand_x = double(rand() % (interval + 1)) / interval;
		rand_y = double(rand() % (interval + 1)) / interval;
	  
		origin_dist = rand_x * rand_x + rand_y * rand_y;
	  
		if (origin_dist <= 1)
		    circle_points++;
	  
		square_points++;
	  
		pi = double(4 * circle_points) / square_points;
	  
	    }
	  
	    cout << "\nFinal Estimation of Pi = " << pi;
	};

double Statistics::CalculatePiVol(int broj_dog){
	int interval, i;
	interval=broj_dog;
    	double rand_x, rand_y, rand_z, origin_dist, pi;
    	int circle_points = 0, square_points = 0;
  
	    srand(time(NULL));
	  
	    for (i = 0; i < (interval * interval * interval); i++) {
	  
		rand_x = double(rand() % (interval + 1)) / interval;
		rand_y = double(rand() % (interval + 1)) / interval;
		rand_z = double(rand() % (interval + 1)) / interval;
	  
		origin_dist = rand_x * rand_x + rand_y * rand_y + rand_z * rand_z  ;
	  
		if (origin_dist <= 1)
		    circle_points++;
	  
		square_points++;
		pi = double(6 * circle_points) / square_points;
	  
	    }
	  
	    cout << "\nFinal Estimation of Pi_Volume = " << pi << "\n"<< endl;
	};









