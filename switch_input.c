#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#define BUTTON 0 // 17
#define BUTTON2 2 // 27

pid_t id = 0;

void* play_C() {
	system("mpg321 sound/Piano_C4_30.mp3");
	id = pthread_self();
}

void* play_D() {
	system("mpg321 sound/Piano_C4_30.mp3");
}
	
int main(void)
{
	pthread_t t1, t2;
	int flag = -1;

    if(wiringPiSetup()==-1)
	   return -1;
	pinMode(BUTTON,INPUT);
		while(1)
	{
		if (digitalRead(BUTTON) != HIGH && digitalRead(BUTTON2) != HIGH && flag == -1) {
			printf("Button not pressed\n");	
		}

		else {
			if(digitalRead(BUTTON) == HIGH) {
				printf("Button C pressed\n");
				if(flag == -1) {
					flag = pthread_create(&t1, NULL, play_C, NULL);
				}
			} else {
				if(flag == 0) {
					kill(id, 0);
					flag = -1;
				}
			}

			if(digitalRead(BUTTON2) == HIGH) {
				printf("Button D pressed\n");
				pthread_create(&t1, NULL, play_D, NULL);
			}
		}
		
		sleep(0.08);
	}
	return 0;
}
