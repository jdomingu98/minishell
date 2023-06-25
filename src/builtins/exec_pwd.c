
#include "minishell.h"

/* pwd:
* Executes the builtin pwd command and displays the
* current working directory path.
* Returns 0 if successful, 1 if an error occured.
*/

int	exec_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if(!cwd)
		return(1);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (0);
}
