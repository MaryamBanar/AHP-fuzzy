#include<iostream>
#include<conio.h>

using namespace std;

    // Implements the fuzzy-AHP algorithm and AFM to analyze for fire detection
    
    //Returns approximate value of e^x
    float exponential (int n,float x)
    {
    	float sum=1.0f;   //initilize sum of series
    	for(int i=n-1;i>0;--i)
    	sum=1+x*sum/i;
    	return sum;
	}
	
  main(){
  	
  	//The threshold for judging sensor data is h.
  	//......................................................
  	//H==0 : Signal is absent.
  	//H==1 : Signal is present.  
    //.....................................................
    
    
    int i=1,j=1,temp=0,
	H,U[i],Ustar,
	n=10,
    S[i][j],
	C[i],e[i],E[i],
	m=0,m0=0,m1=0;
	
	float V[i][j],W0=1,DW[i],x=1.0f,h[i];
	
    
    for(;j<=2;j++)
	for(;i<=3;i++)
	{
		cin>>H>>V[i][j];
		
		//cal Ui
		if(H==0) U[i]=-1; 
		if(H==1) { U[i]=1; m++;}
		
		// cal weight0 --->W0      W0=log(PD/PF)
		if(H==1) W0=1/m; 
		if(H==0) W0=((-1/m)*(exponential(n,W0)));
		
		//cal 	Ustar
		Ustar+=U[i]*W0;
		
		//cal m1,m0
		if(U[i]==1&&Ustar==1) m1++; 
		if(U[i]==-1 && Ustar==-1) m0++;
		
	
		
		//cal delta weight ----> DW
		if(U[i]==1 && H==1) DW[i]=1/m1;
	    if(U[i]==-1 && H==0) DW[i]=1/m0;
	    if(U[i]==1 && H==0) DW[i]=((-1/m1)*(exponential(n,(DW[i]+W0))));
	   	if(U[i]==-1 && H==1) DW[i]=((-1/m0)*(exponential(n,(DW[i]-W0))));
	   
	   	//cal Ustar
	   	Ustar+=U[i]*DW[i];
	   
	   //cal S(i)
	   if(V[i][j]>(h[i]*DW[i])) S[i][j]=1;
	   if(V[i][j]<=(h[i]*DW[i])) S[i][j]=0;
	   
	   
	   }
	   temp=j;
	   
	   
	    for(i=1;i<=3;i++){
	    for(j=1;j<=temp;j++)
		{	
	    	 //cal C
	    	C[i]+=S[i][j];
	    }
	    	//cal e
			e[i]=(C[i]/temp)*100;
	    	
	    	//cal E
	    	if(e[i]>=90) E[i]=5;
	    	else if(e[i]>=70) E[i]=4;
	    	else if(e[i]>=50) E[i]=3;
	    	else if(e[i]>=30) E[i]=2;
	    	else if(e[i]<30) E[i]=1;
	    }
	    
	getch();
}
