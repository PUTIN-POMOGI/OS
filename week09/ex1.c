#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct page{
int id;
uint16_t counter;
};
int hits=0,ask=0;
void printMainMemory(struct page* pages,int n){
	for (int i=0;i<n;i++){
		printf("i = %d id = %d %d\n",i,pages[i].id,(int)pages[i].counter);
	}
	printf("current page number ");
}

void shifting(struct page* pages,int n){
	for (int j=0;j<n;j++){
		pages[j].counter >>=1;
	}
}
void tryFind(struct page* pages,int n,int pageId){
	int i=0;
	while (i<n){
		if ((pages[i].id==-1)||(pages[i].id==pageId)){
			pages[i].id=pageId;
			shifting(pages,n);
			pages[i].counter |=1 << (16 - 1);
			hits++;
			return;
		}
	i++;
	}

	int replace=0;
	for (int j=1;j<n;j++){
		if ((int)pages[j].counter < (int)pages[j-1].counter){
			replace=j;
		}
	}
	shifting(pages,n);
	pages[replace].id=pageId;
	pages[replace].counter=0;
	pages[replace].counter |=1 << (16 - 1);
}

int main(){
	FILE *fin=fopen("input.txt","r");
	int n;
	struct page pages[1200];
	for (int i=0;i<1200;i++){
		pages[i].id=-1;
		pages[i].counter=0;
	}
	printf("Please enter required number of page frames\n");
	scanf("%d",&n);
	int pageId;
	while (fscanf(fin,"%d",&pageId)==1){
		tryFind(pages,n,pageId);
		printMainMemory(pages,n);
		printf("%d\n\n",pageId);
		ask++;
	}
	printf("%d %d\n",hits,ask);
	fclose(fin);
}