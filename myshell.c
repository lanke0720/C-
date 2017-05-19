#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<sys/wait.h>

int main()
{
    while (1)
    {
        printf("[test@192.168.110.142 test]$ ");
        fflush(stdout);

        char buf[1024];
        ssize_t s = read(0, buf, sizeof(buf)-1);
        if (s > 0)
        {
            buf[s-1]= 0;
        }
        char *_myshell[32];
        _myshell[0] = buf;
        char* start = buf;
        int i = 1;
        while (*start)
        {
            if (*start == ' ')
            {
                *start = 0;
                start++;
                _myshell[i++] = start;
            }
            start++;
        }
    
        _myshell[i] = NULL;

        if (strcmp(_myshell[0], "exit") == 0)
        {
            break;
        }

        if (strcmp(_myshell[i-2], ">") == 0)
        {
            _myshell[i - 2] = NULL;
            pid_t id = fork();
            if (id < 0)
            {
                perror("fork error!");
            }
            else if (id == 0)//child
            {
                close(1);
                open(_myshell[i-1], O_WRONLY|O_CREAT, 0666);
                execvp(_myshell[0], _myshell);
            }
            else
            {
                wait(0);
            }
        }
        else
        {
            pid_t id = vfork();
            if (id < 0)
            {
                perror("vfork");
            }
            else if (0 == id)
            {
                execvp(_myshell[0], _myshell);
            }
            else
            {
                wait(0);
            }
        }
    }
    return 0;
}
