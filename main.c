#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
	int READ = 0, WRITE = 1;
	int p_to_c[2], c_to_p[2];
	pipe(p_to_c);
	pipe(c_to_p);
	int f = fork();
	
	if (f) {
		close(c_to_p[WRITE]);
		close(p_to_c[READ]);
		int send = 21;
		
		printf("P: Sending %d to child\n", send);
		write(p_to_c[WRITE], &send, sizeof(int));
		
		int status, get;
		wait(&status);
		
		read(c_to_p[READ], &get, sizeof(get));
		printf("P: Received %d from child\n", get);
		
		close(c_to_p[READ]);
		close(p_to_c[WRITE]);
	}
	
	else {
		close(c_to_p[READ]);
		close(p_to_c[WRITE]);
		int get;
		
		read(p_to_c[READ], &get, sizeof(int));
		printf("C: Received %d from parent\n", get);
		int send = get % 10;
		printf("C: Modding by 10 and sending %d to parent\n", send);
		write(c_to_p[WRITE], &send, sizeof(send));
		
		close(c_to_p[WRITE]);
		close(p_to_c[READ]);
	}
	
	return 0;
}
