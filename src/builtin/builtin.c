#include "../../include/builtin.h"

int run_builtin(char **argv, t_bash *bash)
{
    if (ft_strcmp(argv[0], "echo") == 0)
        return (ft_echo(argv));
    else if (ft_strcmp(argv[0], "cd") == 0)
        return (ft_cd(argv, bash));
    else if (ft_strcmp(argv[0], "pwd") == 0)
        return (ft_pwd());
    else if (ft_strcmp(argv[0], "export") == 0)
        return (ft_export(argv, bash));
    else if (ft_strcmp(argv[0], "unset") == 0)
        return (ft_unset(argv, bash));
    else if (ft_strcmp(argv[0], "env") == 0)
        return (ft_env(bash));
    else if (ft_strcmp(argv[0], "exit") == 0)
        return (ft_exit(argv, bash));
    return (1);
}

int	is_builtin(const char *cmd)
{
    if (!cmd)
        return (0);
    return (!ft_strcmp(cmd, "cd")
        || !ft_strcmp(cmd, "echo")
        || !ft_strcmp(cmd, "pwd")
        || !ft_strcmp(cmd, "export")
        || !ft_strcmp(cmd, "unset")
        || !ft_strcmp(cmd, "env")
        || !ft_strcmp(cmd, "exit"));
}