#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
  DIR *directory;
  long size=0;
  char *dir = "./";
  if(argc > 1)
    dir = argv[1];
  directory = opendir(dir);
  struct dirent *cur;
  struct stat file;
  while(cur = readdir(directory)){
    printf("%s ",cur->d_name);
    if(cur->d_type==DT_REG){
       stat(cur->d_name,&file);
       printf("file %ld\n",file.st_size);
       size += file.st_size;
    }
    else{
      printf("directory\n");
    }
  }
  printf("directory size: %ld\n",size);
  closedir(directory);
  return 0;
}
