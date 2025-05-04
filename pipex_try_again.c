#include "pipex.h"


int main(int argc, char **argv, char **envp)
{
    size_t i;
    int infile;
    int outfile;

	if (argc < 5)
        ft_error("get the input formatting right stupid");
    if ((ft_strncmp(argv[2], "here_doc", 8)) == 0)
    {
        if (argc < 6)
            ft_error("you need >= 6 args to use here_doc");
        i = 3;
        if ((outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1)
            ft_error("open failed");
        here_doc(argv[2], envp);
    }
    else
    {
        i = 2
        if((infile = open(argv[1], O_RDONLY)) == -1)
            ft_erorr("open failed");
        if ((outfile = open(argv[argc - 2], O_RDONLY | O_CREAT | O_TRUNC, 0777)) == -1)
            ft_error("open failed");
        if ((dup2(infile, STDIN_FILENO)) == -1)
            ft_erorr("dup2 error")
    }
    while(i < argc - 2)
    {
        ft_child_process(argv[i], envp);    
        i++;
    }
    dup2(outfile, STDOUT_FILENO);
    ft_execute(argv[argc -2], envp);
    ft_error("failed to execute argument") // this is optional
}

void ft_here_doc(char *delim, char **envp)
{
	char *line;

    line = gnl_hack(int fd);
    // these are commands ?


}

int gnl_hack(int fd)
{
    // can read all at once - >> gross
    // this will read line by line from STDIN_FILENO (== 0)

}

void ft_child(char *cmd, char **envp)
{
    int pip[2];
    int pip;

    if((pipe(pip)) == -1)
        ft_error("pipe() creation error");
    if((pip = fork()) == -1)
        ft_error("fork() error");
    if (pip == 0)
    {
        close(fd[0]);
        dup2(pip[1], STDOUT_FILENO);
        ft_execute(cmd, envp);
    }    
    else
    {
        close(fd[1]);
        dup2(pip[0], STDIN_FILENO);
        wait(NULL);
    }
}

int ft_excute(char *cmd, char ** envp)
{
    char *path;
    char **args;

    path = ft_path(envp, cmd);
    if((args = ft_split(cmd, ' ')) == NULL)
        ft_error("error in splittng");
    execve(path, args, envp);
    ft_error("execve failed to execute");
}

char *ft_path(char **envp, char cmd)
{
    char **paths;
    char *path;
    size_t i;

    i = 0;
    paths = ft_get_paths(char **envp);
    while(paths[i] != NULL)
    {
        if((path = ft_join((const)paths[i], (const)cmd)) == NULL)
            ft_error("ft_join() failed");
        if ((access(path)) == /*accesible*/)
            break;
        free(path);
        i++;
    }
    return (path)
    // test each path for access.
}

char **ft_get_paths(char **envp)
{
    char **paths;
    size_t i; 

    i = 0;
    while(envp[i] != NULL)
    {
        if((ft_strncmp(envp[i], "PATH=", 5) == 0)
            break ;
        i++;
    }
    if (envp[i] == NULL)
        ft_error("no PATH variable in the envp passed ...");
    if((paths = ft_split(envp[i], ':')) == NULL)
        ft_error("error splitting");
    return (paths);
}




// ft_get_path ---> and all the derivatives of that.
///////////////////////// UTILS.C ///////////////////////
void ft_error(char *errmsg)
{
    perror(errmsg);
    exit(EXIT_FAILURE);
}

char *ft_join(const char *s1, const char *s2)
{

}