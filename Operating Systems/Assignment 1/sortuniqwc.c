/*
	Peyton Somerville
	(worked alone)
*/

#include <stdio.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc,char*arv[]) {
		
	//create first pipe fd1
	int fd1[2];
	if (pipe(fd1) == -1) {
		fprintf(stderr, "Pipe failed\n");
		return 1;
	}

	// fork first child
	pid_t pid;
	pid = fork();	// create first child for sort
	if (pid < 0) {	
		// fork error
		fprintf(stderr, "Fork failed for first child\n");
		return 1;
	}
	if (pid == 0) { // first child process, run sort
		printf("The child process running sort is %d\n", getpid());
		// tie write end of pipe fd1 to standard output (file descriptor 1)
		dup2(fd1[WRITE_END], 1);
		// close read end of pipe fd1
		close(fd1[READ_END]);
		// start the sort command using execlp
		execlp("/usr/bin/sort", "sort", NULL);
		// should not get here
		printf("Should not be here after execlp to sort\n");
	}

	//create second pipe fd2
	int fd2[2];
	if (pipe(fd2) == -1) {
		fprintf(stderr, "Pipe failed\n");
		return 1;
	}

	// fork second 
	pid_t childpid;
	childpid = fork();	// create second child for uniq
	if (childpid < 0) {
		// fork error
		fprintf(stderr, "Fork failed for second child\n");
		return 1;
	}
	if (childpid == 0) { // second child process, run uniq
		printf("The child process running uniq is %d\n", getpid());
		// tie read end of fd1 to standard input (file descriptor 0)
		dup2(fd1[READ_END], 0);
		// tie write end of fd2 to standard output (file descriptor 1)
		dup2(fd2[WRITE_END], 1);
		// close write end of pipe fd1
		close(fd1[WRITE_END]);
		// close read end of pipe fd2
		close(fd2[READ_END]);
		// start the uniq command using execlp
		execlp("/usr/bin/uniq", "uniq", NULL);
		// should not get here
		printf("Should not be here after execlp to uniq\n");
	}

	// fork third child
	pid = fork();	// create third child for wc -l
	if (pid < 0) {
		// fork error
		fprintf(stderr, "Fork failed for third child\n");
		return 1;
	}
	if (pid == 0) { // third child process, run wc -l
		printf("The child process running wc -l is %d\n", getpid());
		// tie read end of fd2 to standard input (file descriptor 0)
		dup2(fd2[READ_END], 0);
		// close write end of pipe fd2
		close(fd2[WRITE_END]);
		// close read end of pipe fd1
		close(fd1[READ_END]);
		// close write end of pipe fd1
		close(fd1[WRITE_END]);
		// start the wc -l command using execlp
		execlp("/usr/bin/wc", "wc", "-l", NULL);
		// should not get here
		printf("Should not be here after execlp to wc -l\n");
	}

	// parent process code
	// close both ends of pipes fd1 and fd2
	close(fd1[READ_END]);
	close(fd1[WRITE_END]);
	close(fd2[READ_END]);
	close(fd2[WRITE_END]);
	// wait for third process to end.
	waitpid(pid, NULL, 0);
	printf("Last child has finished\n");

	return 0;
}
