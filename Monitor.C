#include <iostream>
#include <stdio.h>
#include <string>
#include <TCanvas.h>
#include <unistd.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <fstream>


using namespace std;

void Latchup(int);

void Monitor()
{
    TCanvas * c1 = new TCanvas("c1","Mongoose",1000,0,800,600);
    c1->Divide(2,2);
    c1->cd(1)->SetPad(.005, .255, .405, .995);
    c1->cd(2)->SetPad(.405, .255, .995, .995);
    c1->cd(3)->SetPad(.005, .005,.105, .1);
    c1->cd(4)->SetPad(.405, .005, .995, .255);
    TLatex * count = new TLatex();
    TLatex * time = new TLatex();
    char timestr[50];
    char countstr[50];
    char name[50];
    int now,then;
    FILE* in;
    int latchs,files;
    while(true)
    {
        now=0;
        latchs=0;
        then=60;
        in=popen("echo -en \r; ls | wc -l","r");
        c1->cd(2)->Clear();
        fgets(countstr,5,in);
        files=atoi(countstr);
        while(now<then)
        {
            sprintf(timestr,"#scale[6]{%d}",(then-now));
            time = new TLatex(.5,.05,timestr);
            c1->cd(4)->Clear();
            time->Draw();
            in=popen("echo -en \r; ls | wc -l","r");
            fgets(countstr,5,in);
            if(atoi(countstr)!=files)
            {
                latchs++;
                files=atoi(countstr);
                c1->cd(2)->Clear();
                Latchup(latchs,&name[0]);
                c1->cd(2)->Update();
                c1->cd(2)->SaveAs(name);
            }
            sprintf(countstr,"#scale[12]{%i}",latchs);
            count = new TLatex(.3,.45,countstr);
            c1->cd(1)->Clear();
            count->Draw();
            c1->Modified();
            c1->cd(1)->Update();
            c1->cd(4)->Update();
            c1->cd(2)->Update();
            now++;
            usleep(1000000); 
        }
    }
    pclose(in);
}


void Latchup(int latchs,char & buffer)
{
    string line;
    int n=0;
    vector<int> Time,Core,IO,ANG;
    sprintf(buffer,"latchup-%i.dat",latchs);
    ifstream myfile(buffer);
    if(!myfile.good()){cout<<endl<<"File could not be loaded.";}
    else
    {
        double T,dT,LDO,I_core,I_io,I_ang;
        while(n<342)
        {
            n=n+1;
            if(n<=4){getline(myfile,line);}
            if(n>4)
            {
                myfile>>T>>dT>>LDO>>I_core>>I_io>>I_ang;
                Time.push_back(dT);
                Core.push_back(I_core);
                IO.push_back(I_io);
                ANG.push_back(I_ang);
            }
        }
        TGraph * volt = new TGraph(n-4,&Time[0],&Core[0]);
        volt->SetLineColor(kBlue);
        volt->SetLineWidth(3);
        TGraph * curr = new TGraph(n-4,&Time[0],&ANG[0]);
        curr->SetLineColor(kCyan);
        curr->SetLineWidth(3);
        TMultiGraph * all= new TMultiGraph();
        all->Add(volt,"l");
        all->Add(curr,"l");
        all->SetTitle(buffer);
        all->Draw("A");
        myfile.close();
    }
        double slope[3]={0};
    bool Lathched=false;
    double temp;
    for (int i = 0; i < Time.size()-1; ++i)
    {
        temp=(Ang[i+1]-Ang[i])/(Time[i+1]-Time[i]);
        slope[0]+=temp;
        if(temp>slope[1]){slope[1]=temp;}
        if(temp<slope[2]){slope[2]=temp;}
    }
    slope[0]=slope[0]/(Time.size()-1);
    cout.flush();
    cout<<"Average slope was "<<slope[0]<<" Max was "<<slope[1]<<" min was "<<slope[2]<<endl;
    cin.get();
    cin.get();
}