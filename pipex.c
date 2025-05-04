
#include "pipex.h"

// main.c
// -- check input
// -- check for here_doc (remember the outfile needs to be different)
// -- if not -- do regular file moving around
// -- while loop for child processes
// -- final output redirection to outfile

// child_process
// -- create pipe, fork
// -- chid of fork to call ft_execute
// -- parent to wait and dup2(fd[0], STDOUT_FILE)

// ft_excute
// int execve(char *path, char **args, char **env);
// -- find the path of the thing that you need to excute (use a ft_split function here)
// -- -- need to check acss of each of the paths
// -- pass it all to the execve function 

// main 
// here_doc
// get_next_line
// ft_child
// ft_execure

int main(int argc, char **argv, char **envp)
{
    size_t i;
    int infile;
    int outfile;

    if (argc < 5)
        ft_error("formatting: 'infile cmd1 cmd2 ... cmdx outfile'");
    if(ft_strncmp(argv[1], "here_doc", 8) == 0)
    {
        if (argc < 6)
            ft_error("you hella stupid boi");
        i = 3;
        if ((outfile = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0777)) == -1) // some thigns aren't right here wth infile vvs outfile graaaaaaaa
            ft_error("failed to open");
        ft_here_doc(argv[2], argc); // doesn't do the here file crap, just directly passes it to the intermediate executions? 
    }
    else
    {
        i = 2;
        if ((outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777)) == -1)
            ft_error("failed to open");
        if ((infile = open(argv[1], O_RDONLY)) == -1)
            ft_error("failed to open");
        dup2(infile, STDIN_FILENO);
    }
    while (i < argc - 2)
    {
        ft_child(argv[i], enpv)
        i++;
    }
    dup2(outfile, STDOUT_FILE);
    ft_excute(argv[argc - 2], envp);
    ft_error("bash function call didn't work :)"); // what do you want to return lol
}


void ft_here_doc(char *input_name, int argc)
{
    pid_t reader;
    int fd[2];
    char *line;

    if (pipe(fd) == -1)
        ft_error("error with pipe creation")
    if ((reader = fork()) == -1)
        ft_error("error with fork");
    if (reader == 0)
    {
        close(fd[0]);

    }
    else
    {

    }



}



int ft_child(char *cmd, char **envp)
{
    int pip[2];
    int pid;

    if((pipe(pip)) == -1)
        ft_error("error in pipe creation");
    if ((pid = fork()) == -1)
        ft_error("fork failed")
    if(pid == 0)
    {
        close(pip[0]);
        dup2(pip[1], STDOUT_FILENO);
        ft_execute(cmd, envp);
    }
    else
    {
        close(pip[1]);
        dup2(pip[0], STDIN_FILENO);
        wait(NULL); // IK he does waitpid, but I think he can just do wait. 
        return (0);
    }
}

void ft_execute(char *cmd, char **env)
{
    char *path; 
    char **cmds;

    // need to make sure to free the dynamic memory before you do the exec call.
    if((cmds = ft_split(cmd, ' ')) == NULL)
        ft_error("split failed :)");
    path = ft_path(cmd, env);
    execve(path, cmds, env);
    ft_error("execve failed"); 
    // don't need to think about STDIN_FILENO or STDOUT_FILENO --> they are done by parent function
}

char *ft_path(char *cmd, char **env)
{
    char **paths;
    char *path;
    char *args;
    size_t i;
    
    i = 0;
    paths = ft_get_paths(char * cmd, char **env);
    while(paths[i] != NULL)
    {
        // path = ft_join(paths[i], cmd)
        // if (test for acess)
        // -- path = 
        // -- break 
        free(path);
        i++;
    }
}


////////////////////////////// UTILS.C ///////////////////////////////////
void ft_error(char *errmsg)
{
    perror(errmsg);
    exit(EXIT_FAILURE);
}

// what did here_doc actually do ? 
void here_doc()
{


}



// make utils later
// void ft_error(char *errmsg)
// here_doc cmd