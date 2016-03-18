
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int main()
{
FILE *fp;
fp= fopen ("logfile.txt","w+");
//char inp[]="a";
int freq_hz;
char inp[25];
char frequency[25];
printf("Enter frequency:");
scanf("%s",frequency);
freq_hz=atoi(frequency);
//printf("Chosen Frequency is: %i \n",freq_hz);
printf("Enter a string:");
scanf("%s",inp);
printf("Transmitting... ");
short i=0;
short length=strlen(inp);
//short length=5;
fprintf(fp,"%d ",length);
short j=0,k=0,l=0;
short ascii_out[length];
short bit_out[8*length];
short n_zero=0;
int repeat_n=(1000000/freq_hz)*(100/5.6);

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
  while(j<8*length){
	if(bit_out[j]==1){
		digitalWrite(7,1);
	}else if(bit_out[j]==0){
		digitalWrite(7,0);
	}
	if(l>repeat_n){
    	 	j++;l=0;
	}
	l++;
  }
}
return 0;
}
