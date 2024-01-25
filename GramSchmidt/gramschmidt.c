#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define N 3
#define FOR_N(iter) for(int iter=0; iter<N; iter++)
void generavettore(double []);
void stampavec(double []);
void generamatrice(double [][N]);
void stampamatrice(double [][N]);
double norma(double []);
int main(int narg, char ** args){
	int fd_urandom=open("/dev/urandom",O_RDONLY);
	unsigned long seed;
	(fd_urandom!=-1)? read(fd_urandom,&seed,sizeof(long)) : (seed=time(NULL)) ;
	srand48(seed);
	double matrice[N][N]={0};
	generamatrice(matrice);
	stampamatrice(matrice);
}


void generavettore(double vec[]){
	FOR_N(i) vec[i]=2.*drand48()-1.;
}
void stampavec(double vec[]){
	printf("|");
	for(int i=0; i<N-1; i++) printf("%+.4lf ",vec[i]);
	printf("%+.4lf|\n",vec[N-1]);
}
double prodottoscalare(double v[], double w[]){
	double res=0.;
	FOR_N(i) res+=v[i]*w[i];
	return res;
}
double norma(double v[]){
	return sqrt(prodottoscalare(v,v));
}
void generamatrice(double mat[][N]){
	double prod,norm;
	FOR_N(i){ 
		generavettore(mat[i]);
		for(int j=0;j<i;j++){
			prod=prodottoscalare(mat[j],mat[i]);
			FOR_N(k) mat[i][k]-=prod*mat[j][k];
		}
		norm=norma(mat[i]);
		FOR_N(k) mat[i][k]/=norm;
	}
}


void stampamatrice(double mat[][N]){
	FOR_N(i) stampavec(mat[i]); 
}


