#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int atoi_(char * argv)
{
    int n=0;
    while(*argv != '\n' && (int)*argv >='0' && (int)*argv <= '9')
    {
        n=(int)*argv-'0'+n*10;
        argv++;
    }
    return n;
}

int main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(2,"usage:sleep pid ...\n");
        exit(1);

    }else {
        int n=atoi_(argv[1]);
        sleep(n);
        exit(0);
    }
    exit(0);
}
