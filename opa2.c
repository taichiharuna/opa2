#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>

#define N 131072 //the final number of nodes
#define I 2 // the initial number of nodes

#define MI 0 //the initial trial number
#define MF 1 //(the final trial number) - 1

#define RS 0 //seed of the random number generator

int main()
{
	FILE *fp;
	
	double delta=1.0;
	int tout[]={512,1024,2048,4096,8192,16384,32768,65536,131072};
	
	int i,j,k,l,m,t,tt;
	int tmp,flag;
	
	int **nb; //neighbors of each node
	
	int x; //new node
	int vdx; //virtual degree of the node x
	int *tmparr;
	
	int z;
	int nzsize;
	int *nz;
	
	int *deg; //degree of each node
	
	double degav; //average degree
	double *knn; //average degree of the nearest neighbors of each node
	double *cc; //local clustering coefficient of each node
	double ccav; //average local clustering coefficient
	
	char filename[100];
	
	const gsl_rng_type * TYPE;
	gsl_rng * ran;
	
	
	gsl_rng_env_setup();
	TYPE=gsl_rng_default;
	ran=gsl_rng_alloc(TYPE);
	gsl_rng_set(ran,RS);
	
	tmparr=malloc(sizeof(int)*N);
	nz=malloc(sizeof(int)*N);
	
	deg=malloc(sizeof(int)*N);
	knn=malloc(sizeof(double)*N);
	cc=malloc(sizeof(double)*N);
	
	nb=malloc(sizeof(int*)*N);
	for (i=0;i<N;i++){
		nb[i]=malloc(sizeof(int)*N);
	}
	
	for (m=MI;m<MF;m++){
		
		//generation of the initial network
		for (i=0;i<I;i++){
			deg[i]=0;
			for (j=0;j<I;j++){
				if (j!=i){
					nb[i][deg[i]]=j;
					deg[i]++;
				}
			}
		}
		
		tt=0;
		for (t=I;t<N;t++){
			//adding (t+1)-th node: copying degree step
			x=(int)(gsl_rng_uniform(ran)*t);
			vdx=1+(int)(gsl_rng_uniform(ran)*ceil(delta*deg[x]));
			deg[t]=0;
			
			//new OPA pre-adjunction rule
			j=0;
			for (i=0;i<t;i++){
				if (vdx<=ceil(delta*deg[i])){
					tmparr[j]=i;
					j++;
				}
			}
			z=tmparr[(int)(gsl_rng_uniform(ran)*j)];
			nzsize=deg[z]+1;
			for (i=0;i<nzsize-1;i++){
				nz[i]=nb[z][i];
			}
			nz[nzsize-1]=z;
			
			/*//OPA pre-adjunction rule
			nzsize=0;
			for (i=0;i<t;i++){
				if (vdx<=ceil(delta*deg[i])){
					nz[nzsize]=i;
					nzsize++;
				}
			}
			*/
			
			/*//OPA adjunction rule
			tmp=t;
			for (i=0;i<t;i++){
				if (vdx<=ceil(delta*deg[i]) && deg[i]<tmp)tmp=deg[i];
			}
			nzsize=0;
			for (i=0;i<t;i++){
				if (deg[i]==tmp){
					nz[nzsize]=i;
					nzsize++;
				}
			}
			*/
			
			//choosing the targets of the new node x
			if (vdx>=nzsize){
				for (i=0;i<nzsize;i++){
					nb[nz[i]][deg[nz[i]]]=t; deg[nz[i]]++;
					nb[t][deg[t]]=nz[i]; deg[t]++;
				}
			} else{
				for (j=0;j<vdx;j++){
					i=j+(int)(gsl_rng_uniform(ran)*(nzsize-j));
					
					nb[nz[i]][deg[nz[i]]]=t; deg[nz[i]]++;
					nb[t][deg[t]]=nz[i]; deg[t]++;
					
					tmp=nz[j];
					nz[j]=nz[i];
					nz[i]=tmp;
				}
			}
			
			//output
			if (t+1==tout[tt]){
				//degav
				degav=0.0;
				for (i=0;i<t+1;i++){
					degav+=deg[i];
				}
				degav/=(t+1);
				
				//knn
				for (i=0;i<t+1;i++){
					knn[i]=0.0;
					for (j=0;j<deg[i];j++){
						knn[i]+=deg[nb[i][j]];
					}
					if (deg[i]>0)knn[i]/=deg[i];
				}
				
				//cc
				ccav=0.0;
				for (i=0;i<t+1;i++){
					tmp=0;
					for (j=0;j<deg[i];j++){
						for (k=j+1;k<deg[i];k++){
							flag=0;
							for (l=0;l<deg[nb[i][j]];l++){
								if (nb[nb[i][j]][l]==nb[i][k]){
									flag=1;
									break;
								}
							}
							if (flag==1)tmp++;
						}
					}
					
					if (deg[i]>1)cc[i]=2.0*tmp/(deg[i]*(deg[i]-1));
					else cc[i]=0.0;
					
					ccav+=cc[i];
				}
				ccav/=(t+1);
				
				sprintf(filename,"id-deg-knn-cc_t%d_trial%d.txt",t+1,m);
				fp=fopen(filename,"w");
				for (i=0;i<t+1;i++){
					fprintf(fp,"%d %d %.15f %.15f\n",i,deg[i],knn[i],cc[i]);
				}
				fclose(fp);
				
				printf("m=%d t=%d degav=%f ccav=%f\n",m,t+1,degav,ccav);
				
				tt++;
			}//end of output
			
		}//end of t-loop
		
	}//end of m-loop
	
	free(tmparr);
	free(nz);
	free(deg);
	free(knn);
	free(cc);
	for (i=0;i<N;i++){
		free(nb[i]);
	}
	free(nb);
	
	return 0;
}
