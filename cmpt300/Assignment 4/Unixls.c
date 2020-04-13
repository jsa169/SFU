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
#include <pwd.h>	//used to find path of '~'
#include <grp.h>	//used to prin file group
#include <time.h>	//used to print time


struct passwd *pd;	//pwd, used to find full path of "~"
struct dirent *dp;	//Infor about each file
struct stat filestat;	//Stats about each file

DIR *dir;	//Direcotry
struct group *grp;	//Group of file
int max_len;
int width;

//Find the full path of a given path, fro example, '~' will be translated to /Home/
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

//find the space a file's name takes, for example 'file' will return 4, since it takes 4 spaces
int get_filesize(char * name){

	struct stat statbuf;
    lstat(name, &statbuf);
    return statbuf.st_size;

}

//option -li or -l for Unixls
void ls_li(char *directory, int i){
	char path[256] = "\n";	//Actual full path buffer
	char *time = NULL;	//Last mod time buffer
	char link_name[256] = "\n";	//Linked file name fuffer
	max_len=0;
	width = 0;
	dir = opendir(directory);

    if(dir == NULL) {	//directory given does not exist or is not a directory

    	if(lstat(directory, &filestat) == -1){	//return if directory given is not a file
			printf("Unixls: cannot access '%s': No such file or directory\n", directory);
    		return;
    	}

    	if(!(filestat.st_mode & S_ISDIR(filestat.st_mode))){ //if giving directory is file
    		if(i) printf("%li ", filestat.st_ino);	//print inode

    		if(filestat.st_mode & S_ISDIR(filestat.st_mode)) printf("d");	//print file type
			else if(filestat.st_mode & S_ISCHR(filestat.st_mode)) printf("c");
			else if(filestat.st_mode & S_ISBLK(filestat.st_mode)) printf("b");
			else if(filestat.st_mode & S_ISFIFO(filestat.st_mode)) printf("p");
			else if(filestat.st_mode & S_ISSOCK(filestat.st_mode)) printf("s");
			else if(filestat.st_mode & S_ISLNK(filestat.st_mode)) printf("l");
			else printf("-");	

			printf( (filestat.st_mode & S_IRUSR) ? "r" : "-");	//print file permissions
		    printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");	//http://codewiki.wikidot.com/c:system-calls:stat
		    printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");
		    printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
		    printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
		    printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
		    printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
		    printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
		    printf( (filestat.st_mode & S_IXOTH) ? "x" : "-");

		    printf(" %ld ",filestat.st_nlink);	//print number of links

		 	pd = getpwuid(filestat.st_uid);	//print owner name
			printf("%s ", pd->pw_name);

			grp = getgrgid(filestat.st_gid);	//print group name
			printf("%s ", grp->gr_name);

			printf("%*li ",7, filestat.st_size);   //print file size

			time = ctime(&filestat.st_mtime);	//print last monify time
			for(int i = 4; i < 16; i ++){
				printf("%c", time[i]);
			}

			printf(" ");
   			int i;
    		for( i = strlen(directory) - 2;i >= 0; i--){
    			if (directory[i] == '/') break;
    		}
    		for(i = i + 1; i < strlen(directory); i++){	//print file name
    			printf("%c", directory[i]);
    		}

			readlink(directory, link_name, 256);

			if (filestat.st_mode & S_ISLNK(filestat.st_mode)) printf(" -> %s ", link_name);
			printf("\n");	//if islink -> print lined  file name

    		return;
    	}   	
    }

    while((dp = readdir(dir)) != NULL){ // Read file one by one inside directory
    	if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;
    	//Avoid hidden files
    	actualpath(directory, path);

		if (get_filesize(path) > max_len)	//find the largest file size
	        max_len = get_filesize(path); 
	}
	while (max_len != 0) {	//find the number of digits in the largest file size, this number will be the
        max_len /= 10;     //column width for file size
        ++width;
    }
	closedir(dir);

	
	dir = opendir(directory);

	while((dp = readdir(dir)) != NULL){ // Read files one by one inside directory again

		if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;

		actualpath(directory, path);
		lstat(path, &filestat);
		if(i) printf("%li ", dp->d_ino);


		if(filestat.st_mode & S_ISDIR(filestat.st_mode)) printf("d"); //if option i -> print inode number

		else if(filestat.st_mode & S_ISCHR(filestat.st_mode)) printf("c");	//print print file type
		else if(filestat.st_mode & S_ISBLK(filestat.st_mode)) printf("b");
		else if(filestat.st_mode & S_ISFIFO(filestat.st_mode)) printf("p");
		else if(filestat.st_mode & S_ISSOCK(filestat.st_mode)) printf("s");
		else if(filestat.st_mode & S_ISLNK(filestat.st_mode)) printf("l");
		else printf("-");


		printf( (filestat.st_mode & S_IRUSR) ? "r" : "-");	//print file permissions
	    printf( (filestat.st_mode & S_IWUSR) ? "w" : "-");	
	    printf( (filestat.st_mode & S_IXUSR) ? "x" : "-");//http://codewiki.wikidot.com/c:system-calls:stat
	    printf( (filestat.st_mode & S_IRGRP) ? "r" : "-");
	    printf( (filestat.st_mode & S_IWGRP) ? "w" : "-");
	    printf( (filestat.st_mode & S_IXGRP) ? "x" : "-");
	    printf( (filestat.st_mode & S_IROTH) ? "r" : "-");
	    printf( (filestat.st_mode & S_IWOTH) ? "w" : "-");
	    printf( (filestat.st_mode & S_IXOTH) ? "x" : "-");

	    printf(" %ld ",filestat.st_nlink);	//print number of links

		pd = getpwuid(filestat.st_uid);	//print print owner name
		printf("%s ", pd->pw_name);

		grp = getgrgid(filestat.st_gid);	//print group name
		printf("%s ", grp->gr_name);

		printf("%*li ",width, filestat.st_size);	//print file size

		time = ctime(&filestat.st_mtime);	//print last modification time
		for(int i = 4; i < 16; i ++){
			printf("%c", time[i]);
		}

		printf(" %s ", dp->d_name);	//print file name 

		readlink(path, link_name, 256);

		if (filestat.st_mode & S_ISLNK(filestat.st_mode)) printf(" -> %s ", link_name);
		printf("\n");	//if islink -> print file name of the linked file
	}
	closedir(dir);

}	

//ls without any options
void ls(char *directory, int wid){	

	max_len=0;

    dir = opendir(directory);

    if(dir == NULL) {	//directory given does not exist or is not a directory

    	if(lstat(directory, &filestat) == -1){ //directory does not exit & is not a file
			printf("\nUnixls: cannot access '%s': No such file or directory\n", directory);
    		return;
    	}

    	if(!(filestat.st_mode & S_ISDIR(filestat.st_mode))){ 	//directory given is a file
    		int i;
    		for( i = strlen(directory) - 2;i >= 0; i--){
    			if (directory[i] == '/') break;
    		}
    		for(i = i + 1; i < strlen(directory); i++){ //print the file name only, omit the path
    			printf("%c", directory[i]);
    		}
    		printf("\t");
    		return;
    	}
	
    }

    while((dp = readdir(dir)) != NULL){ //Read every file in side the directory to find the max width a file name can take
    	if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;	//Omit all hidden files
		if (strlen(dp->d_name) > max_len)
	        max_len = strlen(dp->d_name);
	}

	closedir(dir);

	int wid_remain = wid;

	dir = opendir(directory);
	while((dp = readdir(dir)) != NULL){	//Read every file in side the directory again and print their name.

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

//ls with option -i
void ls_i(char *directory, int wid){
	max_len = 0;
    
    dir = opendir(directory);

    if(dir == NULL) {	//directory given does not exist or is not a directory

    	if(lstat(directory, &filestat) == -1){ //directory does not exit & is not a file
			printf("\nUnixls: cannot access '%s': No such file or directory\n", directory);
    		return;
    	}

    	if(!(filestat.st_mode & S_ISDIR(filestat.st_mode))){	//directory given is a file
    		int i;
    		for( i = strlen(directory) - 2;i >= 0; i--){
    			if (directory[i] == '/') break;
    		}
    		printf("%ld ", filestat.st_ino);
    		for(i = i + 1; i < strlen(directory); i++){	//print inod number followed by file name
    			printf("%c", directory[i]);
    		}
    		printf("\t");
    		return;
    	}   	
    }


    while((dp = readdir(dir)) != NULL){	//Read every file in side the directory to find the max width a file name can take
    	if(!strcmp(dp->d_name, ".")||!strcmp(dp->d_name, "..")||dp->d_name[0] == '.') continue;
		if (strlen(dp->d_name) > max_len)
	        max_len = strlen(dp->d_name);
	}

	closedir(dir);

	int wid_remain = wid;

	dir = opendir(directory);
	while((dp = readdir(dir)) != NULL){//Read every file in side the directory again and print their inode & file name

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

//main function
int main(int argc,char **argv) {
	struct winsize w;	//Terminal windoe size
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	char cur[10];	//Current directory
	int i = 0;	//option -i, 1 or 0
	int l = 0;	//option -l, 1 or 0
	int havedir[99] = {0};	//List to keep track of which argument is a directory
	int noncurrentdir_count = 0;	//Total directory given by the arguments

	strcat(cur, ".");
	if(argc == 1){	//if not option and no path given, list the files in current directory
		ls(cur, w.ws_col);
		exit(1);
	}

	int count = 0;
	while(count < argc){	//Determin if option -i and -l, also record which argument is a directory using havedir[]
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
		if(argv[count][0] == '-'){
			continue;
		}
		havedir[count] = 1;
		noncurrentdir_count++;

	}


	if(noncurrentdir_count == 0){	//If there is not directory given, ls on current directory with -option

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


	for(int count = 1; count < argc; count++){	//If 1 or more directoy is given, ls on all with give option
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
}//end of Unixls.c