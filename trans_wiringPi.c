
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int main()
{
FILE *fp;
fp= fopen ("logfile.txt","w+");
char inp[25];
printf("Enter a string:");
scanf("%s",inp); 
short i=0;
short length=strlen(inp);
//short length=5;
fprintf(fp,"%d ",length);
short j=0,k=0,l=0;
short ascii_out[length];
short bit_out[8*length];
short n_zero=0;
short freq=20000;
short repeat_n=(12/100)*freq;
short first_flag=0;

while(j<length){
	ascii_out[j] = (int) inp[j];
	fprintf(fp,"\n ascii %d bits ",ascii_out[j]);

	if(ascii_out[j]<2)
		n_zero=7;
	else if(ascii_out[j]<4)
		n_zero=6;
	else if(ascii_out[j]<8)
		n_zero=5;
	else if(ascii_out[j]<16)
		n_zero=4;
	else if(ascii_out[j]<32)
		n_zero=3;
	else if(ascii_out[j]<64)
		n_zero=2;
	else if(ascii_out[j]<128)
		n_zero=1;

	for(k=0;k<n_zero;k++){
		bit_out[8*j+i]=0;
		i++;
	}
	i=0;
	while(ascii_out[j]>0){
		bit_out[8*j+7-i]=ascii_out[j]%2;
		ascii_out[j]=ascii_out[j]/2;
		i++;
	}
	for(k=0;k<8;k++){
		fprintf(fp,"%d ",bit_out[8*j+k]);
	}
	i=0;
	j++;
}
fclose(fp);

if(wiringPiSetup() == -1)
	exit(1);
pinMode(7,OUTPUT);

while(1){
  j=0;
  //if(j%8==0 & first_flag==0){
 //	printf("\n Sending Character %c ...... ",inp[(j/8)]);
  //}
  	
		printf("\n Sending String : %s ",inp);
	
  while(j<8*length){
	if(bit_out[j]==1){
		digitalWrite(7,1);
	}else if(bit_out[j]==0){
		digitalWrite(7,0);
	}
	if(l>repeat_n){
    	 	j++;l=1;
	}
	l++;
  }
  first_flag=1;
}
return 0;
}
