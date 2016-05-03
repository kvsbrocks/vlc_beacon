#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int iscii(char c);

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
short bit_out[5*length];
short n_zero=0;
int repeat_n=(1000000/freq_hz)*(500/25);
//fprintf(fp,"%d ",repeat_n);
//int repeat_n=freq_hz;
while(j<length){
	ascii_out[j] = iscii(inp[j]);
	fprintf(fp,"\n ascii %d bits ",ascii_out[j]);

	if(ascii_out[j]<2)
		n_zero=4;
	else if(ascii_out[j]<4)
		n_zero=3;
	else if(ascii_out[j]<8)
		n_zero=2;
	else if(ascii_out[j]<16)
		n_zero=1;

	for(k=0;k<n_zero;k++){
		bit_out[5*j+i]=0;
		i++;
	}
	i=0;
	while(ascii_out[j]>0){
		bit_out[5*j+4-i]=ascii_out[j]%2;
		ascii_out[j]=ascii_out[j]/2;
		i++;
	}
	//for(k=0;k<5;k++){
	//	fprintf(fp,"%d ",bit_out[5*j+k]);
	//}
	i=0;
	j++;
}
for(k=0;k<5*length;k++){
 fprintf(fp,"%d ",bit_out[k]);
}
fclose(fp);

if(wiringPiSetup() == -1)
	exit(1);
pinMode(7,OUTPUT);

while(1){
  j=0;l=0;
  while(j<10){
     if(j%2==0){
	digitalWrite(7,0);
     }else{
	digitalWrite(7,1);
     }
     if(l>repeat_n){
	j++;l=0;
     }
    l++;
  }
  j=0;l=0;
  while(j<5*length){
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


int iscii(char c)
{
 switch(c){
	case '.':return 1;break;
	case 'a':return 2;break;
	case 'b':return 3;break;
	case 'c':return 4;break;
	case 'd':return 5;break;
	case 'e':return 6;break;
	case 'f':return 7;break;
	case 'g':return 8;break;
	case 'h':return 9;break;
	case 'i':return 5;break;
	case 'j':return 21;break;
	case 'k':return 12;break;
	case 'l':return 11;break;
	case 'm':return 14;break;
	case 'v':return 15;break;
	case 'o':return 16;break;
	case 'p':return 17;break;
	case 'q':return 18;break;
	case 'r':return 19;break;
	case 's':return 20;break;
	case 't':return 21;break;
	case 'u':return 22;break;
	case 'v':return 23;break;
	case 'w':return 24;break;
	//case 'x':return 25;break;
	case 'y':return 26;break;
	case 'z':return 27;break;
	case 'n':return 28;break;
	case 'o':return 29;break;
	case 'x':return 30;break;
	case 'x':return 31;break;
	//case 'z':return 32;break;
  }
}
