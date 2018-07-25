/*
Shell 6 -- Coding Assignment1
Gursharan Deol
Nikita Joshi
Instructor: Michael Burrell
*/
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>   
#include <string.h>  

int main(void) {
   char text[100];
   char tokens[10][100];   

while(1){
	size_t j = 0;
	fgets(text, sizeof text, stdin); 

	size_t i = 0;          
   	size_t token_index = 0; 
   	size_t token_start = 0; 

	while (text[i] != '\0') {
			if (isspace(text[i]))
			 {
			 strncpy(tokens[token_index], &text[token_start],
			    i - token_start);
			 tokens[token_index][i - token_start] = '\0';
			 token_index++;
			 token_start = i + 1;
		     }
		i++;
	}
	
	if((strcmp(text, "exit\n") == 0) || (strcmp(text, "EXIT\n") == 0))
	{
		break;
	}
	
	pid_t child_pid = fork();
	
	if((strcmp(tokens[0], "cd") == 0) || (strcmp(tokens[0], "CD") ==0))
	{
		chdir(tokens[1]);
	}
	
	if(child_pid !=0)
	{
		if((strcmp(tokens[token_index -1], "&") != 0))
		{ 
		waitpid(child_pid, NULL, 0);
		sleep(1);
		}
	}
	else
	{
		size_t num_tokens = token_index;
		char *token_ptrs[num_tokens + 1];
		for ( j = 0; j < num_tokens; j++)
		 {
			token_ptrs[j] = tokens[j];
		}
		token_ptrs[num_tokens] = NULL;   

		execvp(token_ptrs[0], token_ptrs);
		return 1;		
	}
}
   return 0;
}