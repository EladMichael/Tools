#ifndef __KMEAN_H_INCLUDED__   // if k-mean.h hasn't been included yet...
#define __KMEAN_H_INCLUDED__ 	 //   #define this so the compiler knows it has been included


#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

void Update_responsibilities(vector<k_mean>,vector< vector<double> >);
double Vector_Gaussian(vector<double>,vector<double>,vector<double>, double);


class k_mean
{
	double pi;
	vector<double> pos,r,sig;
public:
	k_mean(vector<double> initial, int points, int k_num);
	k_mean();
	void randomize(int dim, int low, int high);
	double R();
	double r_factor(vector<double> data){return Vector_Gaussian(data,pos,sig,pi);}
	void update_pos(vector< vector<double> > data);
	void update_sig(vector< vector<double> > data);
	void update_pi(double R_all);
	void set_r(vector<double> r_new){r=r_new;}
};


#endif