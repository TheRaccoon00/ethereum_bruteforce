#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <errno.h>

int checkHash(char* hash, char** wordlist, int nb_words);
void removeHashFromList(int index, int* nb_targets, char** targets);
char** loadFile(char* filename, int* nb_lines);

int main(int argc, char** argv){
	if (argc < 3){
		errno = EINVAL;
		perror("At least one argument is missing. Usage: ./crack [TARGET].txt [WORDLIST].txt");
		exit(EXIT_FAILURE);
	}

	int i = 0, index;
	int nb_lines_target = 0, nb_lines_wordlist = 0;

	char* targets_filename = calloc(strlen(argv[1]),sizeof(char));
	char* wordlist_filename = calloc(strlen(argv[2])+9,sizeof(char));
	char* end_of_filename = "_address.txt";

	strcpy(targets_filename,argv[1]);

	for(i = 0; i < (strlen(argv[2]) - 4); i++){
		wordlist_filename[i] = argv[2][i];
	}
	strncat(wordlist_filename,end_of_filename,strlen(end_of_filename));

	char** target_array = loadFile(targets_filename,&nb_lines_target);
	char** wordlist_array = loadFile(wordlist_filename,&nb_lines_wordlist);

	if (target_array == NULL || wordlist_array == NULL){
		exit(EXIT_FAILURE);
	}

	for(i=0;i<nb_lines_target;i++){
		index = checkHash(target_array[i],wordlist_array,nb_lines_wordlist);
		if (index != -1){
			printf("%s,%d,%s\n",wordlist_filename,index+1,target_array[i]);
		}
	}
	exit(EXIT_SUCCESS);
}

int checkHash(char* hash, char** wordlist, int nb_words){
	int i = 0;
	for(i = 0; i < nb_words; i++){
		if (strncmp(hash,wordlist[i],strlen(hash)) == 0)
			return i;
	}
	return -1;
}

char** loadFile(char* filename, int* nb_lines){
	FILE* file = NULL;
	char** buffer;
	int i = 0;
	file = fopen(filename, "r");

	if (file == NULL){
		printf("File is missing: %s\n",filename);
		perror("File not found");
		return NULL;
	}

	while (EOF != (fscanf(file, "%*[^\n]"), fscanf(file,"%*c")))
		*nb_lines = *nb_lines+1;

	// Back to the top of the file
	rewind(file);

	// Initialize buffer
	buffer = (char**)calloc(*nb_lines,sizeof(char*));
	for(i=0;i<*nb_lines;i++){
		buffer[i] = calloc(64,sizeof(char));
		fgets(buffer[i],64,file);
		buffer[i][strlen(buffer[i]) - 1] = '\0';
	}

	// Close file
	fclose(file);
	return buffer;
}
