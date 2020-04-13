//Name: Unixls.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

struct passwd *pd;
struct dirent *dp;
char * actualpath(char * arg, char * path){
	pd = getpwuid(getuid());


	if(strcmp(arg, "~")){
		strcpy(path, pd->pw_dir);
		strcat(path,"/");
		strcat(path, dp->d_name);
	}
	if(strcmp(arg, "..")== 0){
		realpath("../", path);
		strcat(path,"/");
		strcat(path, dp->d_name);
	}
	if(strcmp(arg, ".")== 0){
		realpath("./", path);
		strcat(path,"/");
		strcat(path, dp->d_name);		
	}else{
		strcpy(path, arg);
	}
	return path;
}

int main(int argc,char **argv) { 

	DIR *dir;

	char path[256] = "\n";
	char *time = NULL;
	char link_name[256] = "\n";
	//char * filen_name;

	if(argc == 1) dir = opendir(".");
	else dir = opendir(argv[1]);
 
 	struct group *grp;
	
	struct stat filestat;

/*	while((dp = readdir(dir)) != NULL){
		if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;
		printf("%15s", dp->d_name);
	}*/

/*	while((dp = readdir(dir)) != NULL){
		if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;
		printf("%li\t%s\n", dp->d_ino, dp->d_name);
	}*/

	while((dp = readdir(dir)) != NULL){
	
		if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;

		path = actualpath(argv[1], path);

		lstat(path, &filestat);

		printf("%li ", dp->d_ino);


		if(filestat.st_mode & S_ISDIR(filestat.st_mode)) printf("d");

		else if(filestat.st_mode & S_ISCHR(filestat.st_mode)) printf("c");
		else if(filestat.st_mode & S_ISBLK(filestat.st_mode)) printf("b");
		else if(filestat.st_mode & S_ISFIFO(filestat.st_mode)) printf("p");
		else if(filestat.st_mode & S_ISSOCK(filestat.st_mode)) printf("s");
		else if(filestat.st_mode & S_ISLNK(filestat.st_mode)) printf("l");
		else printf("-");


		printf( (filestat.st_mode & S_IRUSR) ? "r" : "-");	//http://codewiki.wikidot.com/c:system-calls:stat
	    printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");
	    printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");
	    printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
	    printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
	    printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
	    printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
	    printf( (filestat.st_mode & S_IXOTH) ? "x" : "-");

	    printf(" %ld ",filestat.st_nlink);

		pd = getpwuid(filestat.st_uid);
		printf("%s ", pd->pw_name);

		grp = getgrgid(filestat.st_gid);
		printf("%s ", grp->gr_name);

		printf("%6li ", filestat.st_size);

		time = ctime(&filestat.st_atime);
		for(int i = 4; i < 20; i ++){
			printf("%c", time[i]);
		}

		printf("%s ", dp->d_name);

		readlink(path, link_name, 256);

		if (filestat.st_mode & S_ISLNK(filestat.st_mode)) printf(" -> %s ", link_name);
		printf("\n");
	}
}
