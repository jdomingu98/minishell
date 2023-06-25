
#include "minishell.h"

/* update_pwds:
 * Change old pwd and new pwd with the one at the parameter 
 * if the "new" parameter is null, then swap oldpwd and pwd
 */
static void	update_pwds(t_shell_data *data, char *new)
{
	char	*pwd;
	char	*oldpwd;

	pwd = get_env_value(data, "PWD");
	set_env_var(data, "OLDPWD", pwd);
	free(pwd);
	if (new[0] == '\0')
	{
		oldpwd = get_env_value(data, "OLDPWD");
		set_env_var(data, "PWD", oldpwd);
		free(oldpwd);
	}
	else
		set_env_var(data, "PWD", new);
}

/* exec_cd:
* Executes the builtin cd command by changing the working directory.
* Returns 0 on success, 1 on failure.
*/

static int	exec_cd(char *pathaux, t_shell_data *data)
{
	char	*new_path;
	int		result;

	result = 0;
	if (chdir(pathaux) == -1)
		result = 1;
	if (result == 0)
	{
		new_path = getcwd(NULL, 0);
		update_pwds(data, new_path);
		free(new_path);
	}
	return (result);
}

/* built_in_cd:
* checks the folder movement you want to do
* if possible returns 0 and executes it,
* in case of error returns 1.
*/

int	built_in_cd(t_command *command, t_shell_data *data)
{
	char	*path_aux;
	int		result;

	result = 1;
	if (command->argc == 1
		|| (ft_strncmp(command->argv[1], "--", 3) == 0 && command->argc == 2))
	{
		path_aux = get_env_value(data, "HOME");
		result = exec_cd(path_aux, data);
		free(path_aux);
	}
	else if (command->argc == 2 && ft_strncmp(command->argv[1], "..", 3) == 0)
		result = exec_cd(command->argv[1], data);
	else if (command->argc == 2 && ft_strncmp(command->argv[1], ".", 2) == 0)
	{
		path_aux = get_env_value(data, "PWD");
		result = set_env_var(data, "OLDPWD", path_aux);
		free(path_aux);
	}
	else if (command->argc >= 2)
		result = exec_cd(command->argv[1], data);
	if (result == 1)
		return (print_error("cd", command->argv[1], strerror(errno), 1));
	return (result);
}
