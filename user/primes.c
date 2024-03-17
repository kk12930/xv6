#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RE 0
#define WR 1

int first_date(int p[2],int *date)
{
    if(read(p[RE],date,sizeof(int)))
    {
        return 1;
    }else {
        return 0;
    }
}

void transmit_date(int lite_pipe[2],int p[2],int first_date)
{
    int date;
    while(read(lite_pipe[RE],&date,sizeof(int)))
    {
        if(date % first_date != 0)
        {
            write(p[WR],&date,sizeof(int));
        }
    }
}
void primes(int lite_pipe[2])
{
    close(lite_pipe[WR]);
    int date;
    int *p1= &date;
    if(!first_date(lite_pipe,p1))
    {
        exit(0);
    }
    printf("prime %d\n",date);
    int p[2];
    pipe(p);
    transmit_date(lite_pipe,p,date);
    int pid = fork();
    if(pid == 0 )
    {
        primes(p);
    }else if (pid > 0)
    {
        close(lite_pipe[RE]);
        close(p[RE]);
        close(p[WR]);
        wait(0);
        exit(0);
    }
}

int main(int argc,char* argv[])
{
    if(argc != 1)
    {
        fprintf(2,"error: primers\n");
        exit(1);
    }
    int p_f_c[2];
    pipe(p_f_c);
    for(int i=2 ;i<=35;i++)
    {
        write(p_f_c[WR],&i,sizeof(int));
    }
    int pid = fork();
    if(pid == 0)
    {
        primes(p_f_c);
    }else if (pid > 0 )
    {
        close(p_f_c[WR]);
        close(p_f_c[RE]);
        wait(0);
        exit(0);
    } else {
        fprintf(2,"error : primes\n");
    }
    exit(0);

}

