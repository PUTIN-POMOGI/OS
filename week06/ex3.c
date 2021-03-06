#include <stdio.h>
#include <stdlib.h>

int at[10];
int bt[10];
int done[10];
int ct[10];
int tat[10];
int wt[10];
int queue[11];
int inQueue=0;
float averageTAT=0;
float averageWT=0;

void swap(int id1,int id2){
int t=at[id1];
at[id1]=at[id2];
at[id2]=t;
t=bt[id1];
bt[id1]=bt[id2];
bt[id2]=t;
}

void swapId(int id1,int id2){
int t=queue[id1];
queue[id1]=queue[id2];
queue[id2]=t;
}

void sort(int n){
for (int i=0;i<n;i++){
	for (int j=0;j<n-i-1;j++){
		if (at[j]>at[j+1]){
			swap(j,j+1);
		}
	}
}
}

void shrink(){
for (int i=0;i<inQueue;i++){
	queue[i]=queue[i+1];
}
queue[inQueue]=-1;
}

void printArray(int n){
printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
for (int i=0;i<n;i++){
	printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i,at[i],bt[i],ct[i],tat[i],wt[i]);
}
printf("\nAverage Turnaraound Time = %f\nAverage WT = %f\n",averageTAT,averageWT);
}

void solve(int n){
int time=0;
for (int i=0;i<n;i++){
	done[i]=0;
}
int started=-1;
int currentAt=0;
queue[0]=-1;
while(1){
	time++;
	if(inQueue>0){
		done[queue[0]]++;
		if(done[queue[0]]==bt[queue[0]]){
			ct[queue[0]]=time;
			tat[queue[0]]=ct[queue[0]]-at[queue[0]];
			averageTAT+=tat[queue[0]];
			wt[queue[0]]=tat[queue[0]]-bt[queue[0]];
			averageWT+=wt[queue[0]];
			shrink();
			inQueue--;
		} else {
			queue[inQueue]=queue[0];
			shrink();
		}
	}
	while(time>=at[currentAt]){
		if (currentAt==n){break;}
		queue[inQueue]=currentAt;
		inQueue++; currentAt++;
	}
	if ((currentAt==n)&&(inQueue==0)){break;}
}
averageTAT=averageTAT/n;
averageWT=averageWT/n;
}

int main(){
int i=0;
FILE *fp= fopen("input.csv","r");
while (fscanf(fp,"%d,%d",&at[i],&bt[i])==2){
	i++;
}
sort(i);
solve(i);
printArray(i);
fclose(fp);
}
