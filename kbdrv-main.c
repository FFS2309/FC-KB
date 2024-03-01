#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include "./keyboard_mapping.h"

#include <wiringx.h>

bool state[sizeof(columns)/sizeof(int)][sizeof(rows)/sizeof(int)];
#define BUF_LEN 512
int main() {
	
	if(wiringXSetup("duo", NULL) == -1){
		wiringXGC();
		return 1;
	}

	for(int i = 0; i < sizeof(columns)/sizeof(int); i++){
		if(wiringXValidGPIO(columns[i]) != 0){
			printf("Invalid GPIO %d\n", columns[i]);
			return 2;
		}
		pinMode(columns[i], PINMODE_OUTPUT);
		digitalWrite(columns[i], HIGH);
	}
	for(int i = 0; i < sizeof(rows)/sizeof(int); i++){
		if(wiringXValidGPIO(rows[i]) != 0){
			printf("Invalid GPIO %d\n", rows[i]);
			return 2;
		}
		pinMode(rows[i], PINMODE_INPUT);
	}
	if(wiringXValidGPIO(num_lock) != 0){
		printf("Invalid GPIO %d\n", num_lock);
		return 2;
	}
	pinMode(num_lock, PINMODE_OUTPUT);
	
	printf("Ready to start doing keyboard things :)\n");


	const char *filename = "/dev/hidg0";
	int fd = 0;
	fd_set rfds;
	char buf[BUF_LEN];
	int retval, cmd_len;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 200;

	if((fd = open(filename, O_RDWR, 0666)) == -1) {
		perror(filename);
		return 3;
	}

	while(true){
		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);
		
		tv.tv_sec = 0;
		tv.tv_usec = 200;
		retval = select(fd + 1, &rfds, NULL, NULL, &tv);
		if (retval == -1 && errno == EINTR)
			  continue;
		if (retval < 0) {
			  perror("select()");
			  return 4;
		}

		if(FD_ISSET(fd, &rfds)) {
			cmd_len = read(fd, buf, BUF_LEN - 1);
			for(int i = 0; i < cmd_len; i++){
				//CONTROL LEDS
				digitalWrite(num_lock, (buf[i] % 2 == 1 ? HIGH : LOW));
			}
		}

		char report[82];
		memset(&report, 0x0, 82);
		int curKey = 0;
		for(int c = 0; c < sizeof(columns)/sizeof(int); c++){
			digitalWrite(columns[c], LOW);
			for(int r = 0; r < sizeof(rows)/sizeof(int); r++){
				char curState = state[c][r];
				state[c][r] = (digitalRead(rows[r]) == LOW);
				if((state[c][r] == true || curState == true)){
					char bind[sizeof(mapping[c][r])/sizeof(char)];
					strcpy(bind, mapping[c][r]);
					char *binding = strtok(bind, " ");
					for(; binding != NULL; binding = strtok(NULL, " ")){
						for(int i = 0; kmod[i].opt != NULL; i++){
							if (strcmp(binding, kmod[i].opt) == 0) {
								report[0] = report[0] | kmod[i].val;
								break;
							}
						}
						for(int i = 0; kval[i].opt != NULL; i++){
							if(strcmp(binding, kval[i].opt) == 0 && curKey < 80) {
								report[2 + curKey++] = kval[i].val;
								break;
							}
						}
					}
				}
				//if(state[c][r] != curState) printf("statechange to %s column %d, row %d\n", (state[c][r] ? "HIGH" : "LOW"), c, r);
			}
			digitalWrite(columns[c], HIGH);
		}
		write(fd, report, 82);//Send Report over USB
		usleep(700);
	}

	close(fd);
	return 0;
}
