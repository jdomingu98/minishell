
#include "minishell.h"

int	pwd_builtin(void)
{
	char	*cwd;
	int		code_number;

	code_number = 0;
	cwd = getcwd(NULL, 0);
	if(!cwd)
	{
		code_number = 1;
		return(code_number);
	}
	ft_printf("%s\n", cwd);
	free(cwd);
	return (code_number);
}
