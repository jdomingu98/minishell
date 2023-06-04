#include "minishell.h"

/*static int	init_data(t_data *data, char **env)
{

}*/

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	
	(void) envp;
	(void) argv;
	g_last_status_code = 0;
	if (argc != 1 /*|| !init_data(&data, envp)*/)
		exit(EXIT_FAILURE);
	data.input = NULL;
	while (1)
	{
		set_interactive_signals();
		data.input = readline("MinishellAnyPercent >");
		//set_noninteractive_signals();
		/*if (parse_input(&data))
			g_last_status_code = 0;
		else
			g_last_status_code = 1;*/
		usleep(5000);
		g_last_status_code = 1;
		free(data.input); //cambiar
		data.input = NULL;
	}
	exit(g_last_status_code);
	return (0);
}