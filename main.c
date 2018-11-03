#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

void psp(int sp){
	for(;sp>=0;sp--)
		printf("  ");
}

double la(DIR *directory,double size,int sp){
	struct dirent *cur;
	struct stat file;
	char *check = "..HEAD";
	while(cur = readdir(directory)){
  		if(cur->d_type==DT_DIR){
	      psp(sp);printf("directory: %s\n",cur->d_name);
	      if(strstr(check,cur->d_name)==NULL)
	      	size += la(opendir(cur->d_name),0,sp+1);
	    }
	    else{
	       stat(cur->d_name,&file);
	       psp(sp); printf("file: %s %.3lf KB\n",cur->d_name,file.st_size/1000.0);
	       size += file.st_size;
	    }
  	}
  	printf("directory size: %.3lf KB\n",size/1000.0);
  	return size;
}
/*
int main(int argc, char *argv[]){
	char *dir = argv[1];
	while(!opendir(dir)){
		printf("%s\n",strerror(errno));
	  	printf("Please enter a path: ");
	  	scanf("%s\n",dir);
	}

	DIR *directory = opendir(dir);
	la(directory,0,0);
	closedir(directory);

	return 0;
}
*/
int main(int argc, char *argv[]){
	DIR *directory;
	long size=0;
	char *dir = malloc(20);
	if(argc > 1){
		dir = argv[1];
	}
	else{
		printf("Enter directory:\n");
		fgets(dir,20,stdin);
		dir[strlen(dir)-1]=0;
		printf("\n");
	}
	struct dirent *cur;
	struct stat file;
	directory = opendir(dir);
	printf("Directories:\n");
	while(cur = readdir(directory)){
		if(cur->d_type==DT_DIR){
			printf("%s\n ",cur->d_name);
			stat(cur->d_name,&file);
			size += file.st_size;
		}
	}
	printf("\nRegular files:\n\n");
	directory = opendir(dir);
	while(cur = readdir(directory)){
		if(cur->d_type==DT_REG){
			printf("%s ",cur->d_name);
			stat(cur->d_name,&file);
			if (file.st_size>1000){
				printf("file: %s %.3lf KB\n",cur->d_name,file.st_size/1000.0);
			}
			else{
				printf("file: %s %ld B\n",cur->d_name,file.st_size);
			}
			size += file.st_size;
		}
	}
	printf("\nTotal directory size: %.3lf KB\n",size/1000.0);
	closedir(directory);
	return 0;
}
