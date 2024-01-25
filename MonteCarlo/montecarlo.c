#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

#define TRUE  1
#define FALSE 0
#define VERBOSE

#define Xmax 10
#define Nmin 1000
#define Nmax 1000000
#define M    100
#define dx   (((double)Xmax)/M)

#define TOprint 20
#define NargExp 3
double pdist(double, double);
double hitAndMiss(double);
int main(int narg, char * * argv){
	if (narg!=NargExp && narg!=1) {
		printf("Error inserted %i args, expected %i or 0!\n",narg-1,NargExp-1);
		return -1;
	}
	
	double lam;
	int    N;

	char zeroArgs=(narg==1)? TRUE : FALSE;
	if (!zeroArgs){
		lam=atof(argv[1]);
		N  =atoi(argv[2]);
	}

	if(zeroArgs){
		printf("Insert lambda value:\t");
		scanf("%lf",&lam);
	}
	while(lam<0.||lam>1.){

		printf("Error! lambda must be in [0,1]\t(inserted %lf)\n",lam);
		printf("Reinsert lambda value:\t");
		scanf("%lf",&lam);
	}
	if(zeroArgs){
		printf("Insert N value:\t");
		scanf("%i",&N);
	}
	if(N<Nmin||N>Nmax){
		printf("Error! N must be in [%i,%i]\t(inserted %i)\n",Nmin,Nmax,N);
		printf("Reinsert N value:\t");
		scanf("%i",&N);
	}

	int urandom_fd=open("/dev/urandom",O_RDONLY);
	unsigned long seed;
	(urandom_fd!=-1)? read(urandom_fd,&seed,sizeof(long)) : (seed=time(NULL));	
	srand48(seed);

	double x,P;
	int histo[M]={0};
	double histoNorm[M];
	for(int i=0; i<N; i++){
		x=hitAndMiss(lam);
		P=pdist(lam,x);
		#ifdef VERBOSE
			if(i<TOprint) printf("%.5lf %.5lf\n",x,P);
		#endif
		for(int j=0; j<M; j++){
			if(x>=j*dx && x<(j+1)*dx){
			       	histo[j]++;
				break;
			}	
		}
	}
	double frec;
	double meanX;
	FILE * fp=fopen("histoprob.dat","w");
	for(int i=0; i<M; i++){
		frec=((double)histo[i])/(N*dx);
		meanX=(i+0.5)*dx;
		fprintf(fp,"%lf %lf %lf\n",meanX,frec,pdist(lam,meanX));
	}
	fclose(fp);
	return 0;
}

double pdist(double l, double x){
	return x/(l*l)*exp(-x/l);
}
double hitAndMiss(double l){
	double x;
	double y;
	double Pmax=1./(l*M_E);
	do{
		y=Pmax*drand48();
		x=Xmax*drand48();
	}while(!(y<pdist(l,x)));
	return x;

}



