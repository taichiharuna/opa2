#include <stdio.h>
#include <stdlib.h>

#define N 32768
#define L 7

#define M 100

int main()
{
	FILE *fp;
	
	int i,m,t;
	int tmp1,tmp2;
	double dtmp1,dtmp2;
	
	double degav,ccav;
	double degavav[L],ccavav[L];
	
	double *degdist,*knn,*ck;
	double *degdistav,*knnav,*ckav;
	int *cnt;
	
	int tout[]={512,1024,2048,4096,8192,16384,32768,65536,131072};
	
	char filename[100];
	
	degdist=malloc(sizeof(double)*N);
	knn=malloc(sizeof(double)*N);
	ck=malloc(sizeof(double)*N);
	
	degdistav=malloc(sizeof(double)*N);
	knnav=malloc(sizeof(double)*N);
	ckav=malloc(sizeof(double)*N);
	cnt=malloc(sizeof(int)*N);
	
	for (t=0;t<L;t++){
		degavav[t]=0.0; ccavav[t]=0.0;
		for (i=0;i<tout[t];i++){
			degdistav[i]=0.0; knnav[i]=0.0; ckav[i]=0.0;
			cnt[i]=0.0;
		}
		
		for (m=0;m<M;m++){
			degav=0.0; ccav=0.0;
			for (i=0;i<tout[t];i++){
				degdist[i]=0.0; knn[i]=0.0; ck[i]=0.0;
			}
			
			sprintf(filename,"id-deg-knn-cc_t%d_trial%d.txt",tout[t],m);
			fp=fopen(filename,"r");
			for (i=0;i<tout[t];i++){
				fscanf(fp,"%d %d %lf %lf",&tmp1,&tmp2,&dtmp1,&dtmp2);
				
				degav+=tmp2;
				ccav+=dtmp2;
				
				degdist[tmp2]+=1.0;
				knn[tmp2]+=dtmp1;
				ck[tmp2]+=dtmp2;
			}
			fclose(fp);
			
			degav/=tout[t]; degavav[t]+=degav;
			ccav/=tout[t]; ccavav[t]+=ccav;
			
			for (i=0;i<tout[t];i++){
				if (degdist[i]>0.0){
					knn[i]/=degdist[i];
					ck[i]/=degdist[i];
					cnt[i]++;
				}
				degdist[i]/=tout[t]; degdistav[i]+=degdist[i];
				knnav[i]+=knn[i];
				ckav[i]+=ck[i];
			}
			/*
			sprintf(filename,"degdist-knn-ck_t%d_trial%d.txt",tout[t],m);
			fp=fopen(filename,"w");
			for (i=0;i<tout[t];i++){
				fprintf(fp,"%d %.15lf %.15lf %.15lf\n",i,degdist[i],knn[i],ck[i]);
			}
			fclose(fp);
			*/
		}
		degavav[t]/=M;
		ccavav[t]/=M;
		
		sprintf(filename,"degdist-knn-ck_t%d.txt",tout[t]);
		fp=fopen(filename,"w");
		for (i=0;i<tout[t];i++){
			degdistav[i]/=M;
			if (cnt[i]>0.0){ //if cnt[i]==0 we think that we have no samples for knn and ck
				knnav[i]/=cnt[i];
				ckav[i]/=cnt[i];
			}
			fprintf(fp,"%d %.15f %.15f %.15f %d\n",i,degdistav[i],knnav[i],ckav[i],cnt[i]);
		}
		fclose(fp);
	}
	
	fp=fopen("degav-ccav.txt","w");
	for (t=0;t<L;t++){
		fprintf(fp,"%d %.15f %.15f\n",tout[t],degavav[t],ccavav[t]);
	}
	fclose(fp);
	
	return 0;
}
