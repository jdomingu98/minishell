
#include "minishell.h"

static void	update_working_dir(t_data *data, char *new_path)
{
	char	*current_pwd;
	char	*old_pwd;

	current_pwd = get_env_value(data, "PWD");
	add_env_var(data, "OLDPWD", current_pwd);
	free(current_pwd);
	if (new_path[0] == '\0')
	{
		old_pwd = get_env_value(data, "OLDPWD");
		add_env_var(data, "PWD", old_pwd);
		free(old_pwd);
	}
	else
		add_env_var(data, "PWD", new_path);
}

static int	exec_cd(char *aux_path, t_data *data)
{
	char	*new_path;
	int		code_number;

	code_number = 0;
	if (chdir(aux_path) == -1)
		code_number = 1;
	if (code_number == 0)
	{
		new_path = getcwd(NULL, 0);
		update_working_dir(data, new_path);
		free(new_path);
	}
	return (code_number);
}

int	cd_builtin(t_command *cmd, t_data *data)
{
	char	*aux_path;
	int		code_number;

	code_number = 1;
	if (cmd->ac == 1
		|| (ft_strncmp(cmd->args[1], "--", 3) == 0 && cmd->ac == 2))
	{
		aux_path = get_env_value(data, "HOME");
		code_number = exec_cd(aux_path, data);
		free(aux_path);
	}
	else if (cmd->ac == 2 && ft_strncmp(cmd->args[1], "..", 3) == 0)
		code_number = exec_cd(cmd->args[1], data);
	else if (cmd->ac == 2 && ft_strncmp(cmd->args[1], ".", 2) == 0)
	{
		aux_path = get_env_value(data, "PWD");
		code_number = add_env_var(data, "OLDPWD", aux_path);
		free(aux_path);
	}
	else if (cmd->ac >= 2)
		code_number = exec_cd(cmd->args[1], data);
	if (code_number == 1)
		return (print_error("cd", cmd->args[1], strerror(errno), 1));
	return (code_number);
}
