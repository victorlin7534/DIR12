#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

int main(){
  DIR *directory;
  long size=0;
  directory = opendir("./");
  struct dirent *cur;
  struct stat *file;
  while(cur = readdir(directory)){
    printf("file: %s\n",cur->d_name);
    if(cur->d_type==DT_REG){
      stat(cur->d_name,file);
      size += file->st_size;
    }
  }
  printf("directory size: %ld",size);
  closedir(directory);
  return 0;
}
