//File: Unixls.c
//Name: Jichuan Shi
//
//Description: Simulates ls, with option -i and -l

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include <sys/ioctl.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


struct passwd *pd;
struct dirent *dp;
struct stat filestat;

DIR *dir;
struct group *grp;
int max_len;
int width;


void actualpath(char * arg, char * path){
	pd = getpwuid(getuid());

	if(strcmp(arg, "~") == 0 ||strcmp(arg, "~/")==0){
		strcpy(path, pd->pw_dir);
		strcat(path,"/");
		strcat(path, dp->d_name);
		return;
	}
	else if(strcmp(arg, "..")== 0 ||strcmp(arg, "..")==0){
		realpath("../", path);
		strcat(path,"/");
		strcat(path, dp->d_name);

	}
	else if(strcmp(arg, ".")== 0 ||strcmp(arg, ".")==0){
		realpath("./", path);
		strcat(path,"/");
		strcat(path, dp->d_name);
		
	}else{
		strcpy(path, arg);
		strcat(path,"/");
		strcat(path, dp->d_name);		
	}
}

int get_filesize(char * name){
	struct stat statbuf;

    lstat(name, &statbuf);

    return statbuf.st_size;
}

void ls_li(char *directory, int i){
	char path[256] = "\n";
	char *time = NULL;
	char link_name[256] = "\n";
	max_len=0;
	width = 0;
	dir = opendir(directory);

    if(dir == NULL) {

    	if(lstat(directory, &filestat) == -1){
			printf("Unixls: cannot access '%s': No such file or directory\n", directory);
    		return;
    	}

    	if(!(filestat.st_mode & S_ISDIR(filestat.st_mode))){
    		if(i) printf("%li ", filestat.st_ino);

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

			printf("%*li ",7, filestat.st_size);   

			time = ctime(&filestat.st_mtime);
			for(int i = 4; i < 16; i ++){
				printf("%c", time[i]);
			}

			printf(" ");
   			int i;
    		for( i = strlen(directory) - 2;i >= 0; i--){
    			if (directory[i] == '/') break;
    		}
    		for(i = i + 1; i < strlen(directory); i++){
    			printf("%c", directory[i]);
    		}

			readlink(directory, link_name, 256);

			if (filestat.st_mode & S_ISLNK(filestat.st_mode)) printf(" -> %s ", link_name);
			printf("\n");

    		return;
    	}   	
    }

    while((dp = readdir(dir)) != NULL){
    	if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;
    	actualpath(directory, path);
		if (get_filesize(path) > max_len)
	        max_len = get_filesize(path);
	}
	while (max_len != 0) {
        max_len /= 10;     // n = n/10
        ++width;
    }
	closedir(dir);

	
	dir = opendir(directory);

	while((dp = readdir(dir)) != NULL){

		if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;

		actualpath(directory, path);
		lstat(path, &filestat);
		if(i) printf("%li ", dp->d_ino);


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

		printf("%*li ",width, filestat.st_size);

		time = ctime(&filestat.st_mtime);
		for(int i = 4; i < 16; i ++){
			printf("%c", time[i]);
		}

		printf(" %s ", dp->d_name);

		readlink(path, link_name, 256);

		if (filestat.st_mode & S_ISLNK(filestat.st_mode)) printf(" -> %s ", link_name);
		printf("\n");
	}
	closedir(dir);

}	

void ls(char *directory, int wid){



	max_len=0;
	width = 0;

    dir = opendir(directory);

    if(dir == NULL) {

    	if(lstat(directory, &filestat) == -1){
			printf("Unixls: cannot access '%s': No such file or directory\n", directory);
    		return;
    	}

    	if(!(filestat.st_mode & S_ISDIR(filestat.st_mode))){
    		int i;
    		for( i = strlen(directory) - 2;i >= 0; i--){
    			if (directory[i] == '/') break;
    		}
    		for(i = i + 1; i < strlen(directory); i++){
    			printf("%c", directory[i]);
    		}
    		printf("\t");
    		return;
    	}
    	
    }

    while((dp = readdir(dir)) != NULL){
    	if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;
		if (strlen(dp->d_name) > max_len)
	        max_len = strlen(dp->d_name);
	}

	closedir(dir);

	int wid_remain = wid;

	dir = opendir(directory);
	while((dp = readdir(dir)) != NULL){

		if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;
		printf("%-*s", max_len+1,dp->d_name);
		wid_remain = wid_remain - max_len;
		if(wid_remain <= max_len) {
			printf("\n");
			wid_remain = wid;
		}

	}
	closedir(dir);
	printf("\n");
}

void ls_i(char *directory, int wid){
	max_len=0;
	width = 0;
    
    dir = opendir(directory);

    if(dir == NULL) {

    	if(lstat(directory, &filestat) == -1){
			printf("Unixls: cannot access '%s': No such file or directory\n", directory);
    		return;
    	}

    	if(!(filestat.st_mode & S_ISDIR(filestat.st_mode))){
    		int i;
    		for( i = strlen(directory) - 2;i >= 0; i--){
    			if (directory[i] == '/') break;
    		}
    		printf("%ld ", filestat.st_ino);
    		for(i = i + 1; i < strlen(directory); i++){
    			printf("%c", directory[i]);
    		}
    		printf("\t");
    		return;
    	}   	
    }


    while((dp = readdir(dir)) != NULL){
    	if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;
		if (strlen(dp->d_name) > max_len)
	        max_len = strlen(dp->d_name);
	}

	closedir(dir);

	int wid_remain = wid;

	dir = opendir(directory);
	while((dp = readdir(dir)) != NULL){

		if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;
		printf("%li %-*s", dp->d_ino, max_len+1,dp->d_name);
		wid_remain = wid_remain - max_len - 7;
		if(wid_remain <= max_len+7) {
			printf("\n");
			wid_remain = wid;
		}
	}
	closedir(dir);
	printf("\n");
}

int main(int argc,char **argv) {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	char cur[10];
	int i = 0;
	int l = 0;
	int havedir[10] = {0};
	int noncurrentdir_count = 0;

	strcat(cur, ".");
	if(argc == 1){
		ls(cur, w.ws_col);
		exit(1);
	}

	int count = 0;
	while(count < argc){
		count++;
		if (count >= argc) break; 
		if(strcmp(argv[count], "-i") == 0) {
			i = 1;
			continue;
		}
		if(strcmp(argv[count], "-l") == 0) {
			l = 1;
			continue;
		}
		if(strcmp(argv[count], "-il") == 0) {
			i = 1;
			l = 1;
			continue;			
		}
		if(strcmp(argv[count], "-li") == 0) {
			i = 1;
			l = 1;
			continue;
		}
		havedir[count] = 1;
		noncurrentdir_count++;

	}


	if(noncurrentdir_count == 0){

		if(l == 1){
			if(i == 1) ls_li(cur, 1);
			else ls_li(cur, 0);
		}else if (i == 1){
			ls_i(cur, w.ws_col);
		}else{
			ls(cur, w.ws_col);
		}
		exit(1);
	}


	for(int count = 1; count < argc; count++){
		if(havedir[count] == 1){
			if(noncurrentdir_count > 1){
				lstat(argv[count],&filestat);
				if(!(filestat.st_mode & S_ISDIR(filestat.st_mode)));
				else printf("\n%s:\n", argv[count]);
			}
			if(l == 1){
				if(i == 1) ls_li(argv[count], 1);
				else ls_li(argv[count], 0);
			}else {
				if (i == 1){
					ls_i(argv[count], w.ws_col);
				}else{
					ls(argv[count], w.ws_col);
				}
			}
		}
	}
	printf("\n");
}