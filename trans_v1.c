#include <stdio.h>
#include <wiringPi.h>

int main(void)

{
printf("Raspberry PI blink");
if(wiringPiSetup () == -1 )
	return -1;
pinMode(7,OUTPUT); //pin17

while(1){
digitalWrite(7,1);
digitalWrite(7,0);
}
return 0;
}
