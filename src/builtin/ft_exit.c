
#include "../../include/builtin.h"

long long ft_atoll(const char *str)
{
    long long res;
    int sign;

    res = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if(*str == '-')
            sign = -1;
        str++;
    }
    while (ft_isdigit(*str))
    {
        if (res > (LLONG_MAX - (*str - '0')) / 10)
        {
            if (sign == 1)
                return (LLONG_MAX);
            return (LLONG_MIN);
        }
        res = res * 10 + *str - 48;
        str++;
    }
    return (res * sign);
}


int is_valid_num(char *str)
{
    int i;

    i = 0;
    if (!str || !*str)
        return (0);
    while (str[i] == ' ' || (str[i] >= 0 && str[i] <= 9))
        i++;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!ft_isdigit(str[i]))
        return (0);
    while (str[i])
    {
        if (ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}


int ft_exit(char **argv, t_bash *shell)
{
    long long exit_code;
    int arg_count;

    arg_count = 0;
    if (argv)
    {
        while(argv[arg_count])
            arg_count++;
    }
    printf("exit\n");
    if (arg_count == 0)
        exit(shell->last_exit_code);
    if (!is_valid_num(argv[1]))
    {
        ft_printf_fd(STDERR_FILENO, "minishell: exit: %s: numeric arguments required\n", argv[0]);
        exit(2);
    }
    if (arg_count > 1)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
        return (1);
    }
    exit_code = ft_atoll(argv[1]);
    exit((int)(exit_code % 256));
}


// dont forget to actualise exit_status in main loop