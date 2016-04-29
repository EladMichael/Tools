#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;

k_mean::k_mean(vector<double> initial, int points, int k_num)
{
	pos=initial;
	vector<double> responsibilities;
	for (int i = 0; i < points; ++i)
	{
		responsibilities.push_back(0);
	}
	r=responsibilities;
	sig = 1;
	pi = 1/k_num;
}

k_mean::randomize(int dim, int low, int high)
{
	vector<double> pos_r;
	double temp;
	vector<double> sig_r(dim,1);
	double pi_r=1;
	for (int j = 0; j < dim; ++j)
	{
		temp = rand()%((high-low)*100);
		pos_r.push_back(temp/100+low);
	}
	pos=pos_r;
	sig=sig_r;
	pi=pi_r;
}

k_mean::R()
{
	double sum = 0;
	for (int i = 0; i < r.size(); ++i)
	{
		sum+=r[i];
	}
	return sum;
}

k_mean::update_pos(vector< vector<double> > data)
{
	double temp=0;
	double resp = R();
	vector<double> new_pos;
	for (int f = 0; f < data[0].size(); ++f)
	{
		for (int n = 0; n < data.size(); ++n)
		{
			temp += r[n]*data[n][f];
		}
		new_pos.push_back(temp/resp);
		temp=0;
	}
	pos=new_pos;
}

k_mean::update_sig(vector< vector<double> > data)
{
	double temp=0;
	double resp = R();
	vector<double> new_sig;
	for (int i = 0; i < r.size(); ++i)
	{
		for (int n = 0; n < data.size(); ++n)
		{
			temp += r[n]*pow(data[n][i]-pos[i],2);
		}
		new_sig.push_back(sqrt(temp/resp));
		temp=0;
	}
	sig = new_sig;
}

k_mean::update_pi(double R_all)
{
	pi=R()/R_all;
}

double Vector_Gaussian(vector<double> data,vector<double> pos,vector<double> sig, double amp)
{
	double norm=1;
	double temp=0;
	for (int i = 0; i < sig.size(); ++i)
	{
		if(sig[i]==0){cout<<"Error: Axis "<<i<<" has zero variance! Cannot continue."<<endl; return -1;}
		norm=norm*sqrt(x*pi())*sig[i];
		temp+=-pow((pos[i]-data[i])/(sqrt(2)*sig[i]),2)
	}
	norm = 1/norm;
	return amp*norm*exp(temp);
}

void Update_responsibilities(vector<k_mean> means,vector< vector<double> > data)
{
	vector< vector<double> > factors(means.size());
	vector<double> denom(means.size())
	double temp=0;
	for (int i = 0; i < data.size(); ++i)
	{
		for(int j = 0; j < means.size() ; ++j)
		{
			factors[j].push_back(means[j].r_factor(data[i]));
			temp+=factors[j][i];		
		}
		denom.push_back(temp);
	}
	vector<double> temp_v;
	for (int j = 0; j < factors.size(); ++j)
	{
		for (int i = 0; i < data.size(); ++i)
		{
			temp_v.push_back(factors[j][i]/denom[i]);
		}
		means[j].set_r(temp_v);
		temp_v.clear();
	}
}