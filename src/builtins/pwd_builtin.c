
#include "minishell.h"

/* pwd_builtin:
*	Executes the builtin pwd command and displays the
*	current working directory path.
*	Returns 0 if successful, 1 if an error occured.
*/
/*int	pwd_builtin(t_data *data, char **args)
{
	//char	buf[PATH_MAX];
	char	*cwd;

	(void)args;
	(void) data;
	if (data->working_dir)
	{
		ft_putendl_fd(data->working_dir, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	errmsg_cmd("pwd", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}*/
 