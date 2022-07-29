#include "main.h"
#define delim " \t\r\n\a"

char *read_line(void) // Récupère les entrées
{
	char *line = NULL;
	ssize_t buffsize = 0; // initialisation des variables de getline

	if (getline(&line, &buffsize, stdin) == -1)// on teste la valeur de retour de getline()
	{
		if (feof(stdin)) // feof fonction de ferror qui traite les EOF(int) sur un flux(stdin)
		{
			exit(EXIT_SUCCESS); // quand l'user renvoie un EOF
		}
		else // pour checker les erreurs
		{
			perror("Can't Read your entry");
			exit(EXIT_FAILURE);
		}
	}

	return (line); // il faudra le free à la fin
}

char **parse_line(char *line) // analyse des entrées
{
	int bufsize = 32, position = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token; // il va récuperer un par un successivement les tokens émises par strtok()

	if(!tokens)// test le malloc
	{
		fprintf(stderr, "Malloc error: can't allocate\n");
		exit(EXIT_FAILURE); 
	}

	token = strtok(line, delim);

	while(token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 32;
			tokens = realloc(tokens, sizeof(char *) * bufsize); // réalloue de la mémoire dynamiquement
			if (!tokens)
			{
				fprintf(stderr, "Realloc error: can't allocate again");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, delim); // on remet la valeur à analyser à NULL pour ne pas perdre nos tokens
	}
	tokens[position] = NULL; // on rajoute NULL à notre liste de tokens

	return (tokens); // on oubliera pas de libérer la mémoire éventuelle alloué
}

int shell_launch(char **tokens) // lance un process 
{
	pid_t child_pid, wpid;
	int status;

	child_pid = fork(); // création du process

	if (child_pid == 0) // ce qui se passe dans le process enfant crée
	{
		if (execve(tokens[0], tokens, NULL) == -1) // le execvp permet de rechercher de lui même le pathname interpret
		{
			perror("Exec error: can't execute your command");
		}
		exit(EXIT_FAILURE);
	}
	else if (child_pid < 0)
		perror("Fork error: can't create the child process");
	else // Parent process
	{
		do {
			wpid = waitpid(child_pid, &status, WUNTRACED); 
			/* waitpid attend le process enfant child_pid et return ssi aucun fils n'est achevé ou si un fils 
			 * est bloqué
			 */
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		/* tant que WIFEXITED() ne se termine pas anormalement à cause d'un signal (WIFSIGNALED) on refait
		 * la boucle */
	}

	return (1);
}
