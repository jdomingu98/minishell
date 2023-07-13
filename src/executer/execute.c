
#include"minishell.h"

static char	*validate_entry(char *cmd, char **path)
{
	char	*cmd_and_path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (path[i])
	{
		cmd_and_path = ft_strjoin(path[i], cmd);
		if (!cmd_and_path)
			return (0);
		if (access(cmd_and_path, X_OK) == 0)
			return (cmd_and_path);
		free(cmd_and_path);
		i++;
	}
	return (0);
}

static int	executer_aux(t_command *in_str, t__data *data)
{
	char	**path;
	char	*cmd_and_path;

	path = get_path(data->env);
	if (!path)
		return (1);
	cmd_and_path = validate_entry(in_str->args[0], path);
	free_path(path);
	if (cmd_and_path != 0)
	{
		execve(cmd_and_path, in_str->args, data->env);
		return (errno);
	}
	return (127);
}

static int	execute_common(t_command *in_str, t_data *data)
{
	int		code_number;

	code_number = 0;
	g_sig.pid = fork();
	if (g_sig.pid < 0)
		return (g_sig.pid);
	if (g_sig.pid == 0)
	{
		code_number = executer_aux(in_str, data);
		exit(code_number);
	}
	waitpid(g_sig.pid, &code_number, 0);
	code_number = decode_exit_code(code_number);
	if (code_number == 127)
		print_error(in_str->args[0], 0, "command not found", code_number);
	return (code_number);
}

int	execute(t_list *in_str, t_data *data)
{
	int			status;
	t_command	*cmd;

	cmd = (t_command *) in_str->content;
	if (!cmd->args || !cmd->args[0])
		return (0);
	if (cmd->in_fileno > 0)
		dup2(cmd->in_fileno, STDIN_FILENO);
	if (cmd->out_fileno > 0)
		dup2(cmd->out_fileno, STDOUT_FILENO);
	close_pipes(data, in_str);
	if (is_builtin(cmd->args[0]))
		status = execute_builtins(cmd, data);
	else
		status = execute_common(cmd, data);
	if (cmd->out_fileno > 0)
		close(cmd->out_fileno);
	if (in_str->next)
		close(((t_command *)in_str->next->content)->in_fileno);
	if (cmd->in_fileno > 0)
		dup2(data->dup_stdin, STDIN_FILENO);
	if (cmd->out_fileno > 0)
		dup2(data->dup_stdout, STDOUT_FILENO);
	return (status);
}

int	execute_pipex(t_data *data)
{
	int		status;
	int		ultimate_status;
	int		ultimate_pid;
	t_list	*cmds;

	cmds = data->command_list;
	while (cmds)
	{
		ultimate_pid = fork();
		if (ultimate_pid < 0)
			return (ultimate_pid);
		if (ultimate_pid == 0)
			exit(execute(cmds, data));
		cmds = cmds->next;
	}
	close_pipes(data, 0);
	cmds = data->commands;
	while (cmds)
	{
		if (ultimate_pid == waitpid(-1, &status, 0))
			ultimate_status = decode_exit_code(status);
		cmds = cmds->next;
	}
	return (ultimate_status);
}
