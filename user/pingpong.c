#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RE 0
#define WR 1

int main(int argc,char * argv[])
{
    if (argc != 1)
    {
        fprintf(2,"error: pingpong\n");
        exit(1);
    }
    int p_f_z[2];
    int p_z_f[2];
    char buf[1];
    buf[0]='z';
    pipe(p_f_z);
    pipe(p_z_f);
    int pid = fork();
    if(pid == 0 )
    {
        close(p_f_z[WR]);
        close(p_z_f[RE]);
        if(read(p_f_z[RE],buf,sizeof(buf)))
        {
            printf("%d: received ping\n",getpid());
            write(p_z_f[WR],buf,sizeof(buf));
            close(p_f_z[RE]);
            close(p_z_f[WR]);
            exit(0);
        }
    } else if (pid > 0)
    {
        close(p_f_z[RE]);
        close(p_z_f[WR]);
        if(write(p_f_z[WR],buf,sizeof(buf)))
        {
            wait(0);
            if(read(p_z_f[RE],buf,sizeof(buf)))
            {
                printf("%d: received pong\n",getpid());
            }
            close(p_f_z[WR]);
            close(p_z_f[RE]);
            exit(0);
        }
    }else {
        fprintf(2,"error : pingpong\n");
        exit(1);
    }
    exit(0);
}

