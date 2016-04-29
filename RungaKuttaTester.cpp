#include <iostream>
#include <cmath>
using namespace std;
void evaluate(double s[],double ds[]);
void assign(double s[]);
bool Periodicity(double s[],double s0[],double);
double fx(double,double);
int main ()
{
 double s[4],ds[4],s0[4],tmp[4],k1[4],k2[4],k3[4],k4[4];      //Current and Delta Property Arrays, as well as Initials
 double t=0,dt=1,years=1;
 int a=0,j=0;
 double margin;

 double prec=dt;
while(prec>=pow(10,-7))
{
 while(j==0)
 {
  assign(s);
  margin= .01;
  t=0;
  while(t<=years)
  {
    evaluate(s,ds);
    for(int i=0;i<4;i++){k1[i]=dt*ds[i];}
    for(int i=0;i<4;i++){tmp[i]=s[i]+0.5*k1[i];}
    evaluate(tmp,ds);
    for(int i=0;i<4;i++){k2[i]=dt*ds[i];}
    for(int i=0;i<4;i++){tmp[i]=s[i]+0.5*k2[i];}
    evaluate(tmp,ds);
    for(int i=0;i<4;i++){k3[i]=dt*ds[i];}
    for(int i=0;i<4;i++){tmp[i]=s[i]+k3[i];}
    evaluate(tmp,ds);
    for(int i=0;i<4;i++){k4[i]=dt*ds[i];}
    for(int i=0;i<4;i++){s[i]= s[i]+(k1[i]+2.0*k2[i]+2.0*k3[i]+k4[i])/6.0;}
    //for(int i=0;i<4;i++){cout<<k1[i]<<" "<<k2[i]<<" "<<k3[i]<<" "<<k4[i]<<endl;}
    if(Periodicity(s,s0,margin)&&a>20){a=0;break;} //end of orbit statement
    a++;
    t = t+dt;
  }
  if(a==0){cout<<"Got it! With a timestep of "<<dt<<" the orbit has a period of "<<t<<".";break;}
  else if((dt-prec)<pow(10,-7)){j=1;}
  else{dt=dt-prec;cout<<"Let's try... "<<dt<<endl;}
 }
if(a==0){break;}
prec=prec*.1;
j=0;
}
return dt;
}

void evaluate(double s[],double ds[])
{ 
  ds[0]=s[2];
  ds[1]=s[3];
  ds[2]=fx(s[0],s[1]);
  ds[3]=fx(s[1],s[0]);
}

double fx(double p, double q)
{
  const double grav=39.47, msun=1.0;
  return (-grav*msun*p)/pow(pow(p,2)+pow(q,2),1.5);
}

bool Periodicity(double s[],double s0[],double margin)
{
 if(
  s[0]>=(s0[0]-margin)&&
  s[0]<=(s0[0]+margin)&&
  s[1]>=(s0[1]-margin)&&
  s[1]<=(s0[1]+margin)&&
  s[2]>=(s0[2]-margin)&&
  s[2]<=(s0[2]+margin)&&
  s[3]>=(s0[3]-margin)&&
  s[3]<=(s0[3]+margin))
  {return true;}
 else{return false;}
}
void assign(double s[])
{
  s[0]=1;       //Initial X position
  s[1]=0;       //Initial Y position
  s[2]=0;     //Initial X velocity
  s[3]=6.28;     //Initial Y velocity
}
