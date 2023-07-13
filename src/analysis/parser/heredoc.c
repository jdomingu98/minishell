#include "minishell.h"

static void	read_heredoc(int fd, char *token_value, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline(" >> ");
		if (!line)
			break ;
		expand_variables(&line, data, true);
		if (ft_strncmp(line, token_value, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

t_error	create_heredoc(t_list *cmd_list, char *token_value, t_data *data)
{
	t_command		*cmd;
	static size_t	hdoc_number = 0;
	char			*fname;
	char			*tmp;

	cmd = (t_command *) ft_lstlast(cmd_list)->content;
	tmp = ft_itoa(hdoc_number++);
	if (!tmp)
		return (MALLOC);
	fname = ft_strjoin("/tmp/.minishell_heredoc_", tmp);
	free(tmp);
	if (!fname)
		return (MALLOC);
	read_heredoc(open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0666),
		token_value, data);
	cmd->in_fileno = open(fname, O_RDONLY, 0666);
	free(fname);
	return (NO_ERROR);
}