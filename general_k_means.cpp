#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "k-means.h"

using namespace std;

int main(int argc, char* argv[]) //inputs should be ./executable data_file_path num_means
{
	// Process input arguments, and open the data file.
	if(argc!=3){cout<<"Incorrect Number of Arguments! Provide path and number of means."<<endl;return -1;}
	int num_means;
	string path;
	stringstream convert;
	convert<<argv[1]<<' '<<argv[2];
	convert>>path>>num_means;
	fstream f(path,fstream::in);

	// Find the number of lines, and the dimension of the data. The data must 
	// be all of the same dimension!
	string line;
	int lines,dim;
	lines=dim=0;
	// Out loop is for looping through every line of the file, to find the number
	// of lines! The inner loops, that only runs the first time, find the dimension 
	// of the data from the first row of data. I assume here that the data is 
	// delimited by spaces, but by changing the character in the quotation marks of
	// getline(linestream,item,' '), the delimiting character can be changed.
	for (int i = 0; getline(f,line); ++i)
	{
		lines++;
		if(i==0)
		{
			stringstream linestream(line);
			string item;
			for (int j = 0; getline(linestream,item,' '); ++j)
			{
				dim++;
			}
		}
	}
	// vector to hold every data point, each of which is a vector of dim dimensions
	vector< vector<double> > data(lines);
	// reset data file flags, go back to beginning of file
	rewind(f);
	// Read the data file into the container made above
	for (int i = 0; i < lines; ++i)
	{
		getline(f,line);
		for (int j = 0; j < dim; ++j)
		{
			line>>a;
			data[i].push_back(a);
		}
	}
	cout<<"Data successfully loaded from: "<<name<endl;

	vector<k_mean> means(num_means);
	// initialize each k-mean's position randomly between the 
	// bounds provided. Initial sigma will be 1 in all dimensions
	// and the amplitude will be 1 as well. Responsibilities will 
	// be calculated from this randomized position, not assigned 
	// arbitrarily, to avoid errors.
	for (int i = 0; i < num_means; ++i)
	{
		means[i].randomize(dim,-30,30);
	}
	cout<<"K-means initialized randomly."<<endl;
	Update_responsibilities(means,data);
	

}
