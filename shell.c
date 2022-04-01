// Shell Creation Assignment CSC 280 - Preston Dickerson
// Import Statmets
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


// Main
int main(){
	while(1){
		char *token;
		char *token2;
		char cmd[64];
		char cmd2[64];

		for(int i = 0; i < 64; i++){
			cmd[i] = '\0';
			cmd2[i] = '\0';
		}


		printf("What should shell do?> ");
		fgets(cmd, 64, stdin);

		for(int i = 0; i < 64; i++){
			if(cmd[i] == '\n'){
				cmd[i] = '\0';
			}
		}

		strcpy(cmd2, cmd);

		// Parse Input
                int i = 0;
                int count = 0;
                
		// Get Count for Array
                token = strtok(cmd, " ");
                while(token != NULL){
                        count++;
                        token = strtok(NULL, " ");
                }


                // Create Array
                char *arr[count];
                token2 = strtok(cmd2, " ");

                // Fill array with null
                for(int z = 0; z < count; z++){
                        arr[z] = '\0';
                }


                // Fill array with value
                while(token2 != NULL){
                        arr[i++] = token2;
                        token2 = strtok(NULL, " ");
                }
		
		pid_t pi[10];
		if(strcmp(arr[0], "cd") == 0){
                        int chd = chdir(arr[1]);
			if(chd == -1){
				printf("Change Directory Failed\n");
			}
			else{
	    	        	printf("Directory changed: %s\n", arr[1]);
			}	
		}
		else if(strcmp(arr[0], "exit") == 0){
			printf("EXITING\n");
			return 0;
		}
		else{
			int fk = fork();

			if(fk < 0){
				printf("Failed at Fork! Exiting");
				exit(1);
			}

			else if(fk == 0){
				// Call Exec
				int exe = 0;
				if(count == 1){
					exe = execlp(arr[0], arr[0], (char *) NULL);
				}
				else if(count == 2){
                           	     if(strcmp(arr[0], "cd") == 0){
                                	        exe = 0;
                                     }
				     else{
						exe = execlp(arr[0], arr[0], arr[1], (char *) NULL);
				     }
				}
				else if(count == 3){
					exe = execlp(arr[0], arr[0], arr[1], arr[2], (char *) NULL);
				}
				else if(count == 4){
					exe = execlp(arr[0], arr[0], arr[1], arr[2], arr[3], (char *) NULL);
				}
				else if(count == 5){
					exe = execlp(arr[0], arr[0], arr[1], arr[2], arr[3], arr[4], (char *) NULL);
				}
				else if(count == 6){
					exe = execlp(arr[0], arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], (char *) NULL);
				}
				else if(count == 7){
					exe = execlp(arr[0], arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], (char *) NULL);
				}

				if(exe < 0){
					printf("Execlp Failed! Enter a valid command\n");
				}
				
			}
			else{
				int statval;
				pid_t pid;
			
				pid = wait(&statval);
				if (pid == -1) {
					printf("Wait Failed! Exiting\n");
					exit(1);
				}
			}
		}
	}

	return 0;
}
