#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

const char * app; //wordcount or sort
const char * impl; //procs or threads
int num_maps; //number of maps
int num_reduces; //number of reduces
const char * infile; //name of input file
const char * outfile; //name of output file


int main(int argc, char ** argv){
    
    if(argc < 13){
        printf("Error: not enough arguments\n");
        exit(1);
    }
    app = argv[2];
    
    //basic error check
    if( (strcmp(app,"wordcount") != 0) && (strcmp(app,"sort") != 0) ){
        printf("Error: Invalid app name\n");
        exit(1);
    }
    impl = argv[4];

    //basic error check
    if( (strcmp(impl,"procs") != 0) && (strcmp(impl,"threads") != 0) ){
        printf("Error: Invalid argument\n");
        exit(1);
    }
    num_maps = atoi(argv[6]);
    num_reduces = atoi(argv[8]);
    infile = argv[10];
    outfile = argv[12];

    FILE *f = fopen(infile, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char * buffer = malloc(fsize+1); //error check
    fread(buffer,fsize,1,f); //error check
    fclose(f);

    buffer[fsize] = 0;


    printf("%s\n", buffer);

    return 0;
}
