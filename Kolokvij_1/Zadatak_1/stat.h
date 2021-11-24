#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

class Statistics{
	public:
		Statistics();
		double CalculatePi();
		double CalculatePiVol(int broj_dog);
		double CalculatePi(int broj_dog);
		double NormalDistribution(double mi, double sigma);
		double NormalDistribution(int x, double mi, double sigma);
		double NormalDistribution(int x, int y, double mi, double sigma);
};

