#include "parser.h"

int	ft_check_valid_files(char *argv, char *str)
{
	char	*line;

	if (!ft_strncmp(argv, "--save", ft_strlen("--save")))
		line = str;
	else
		line = ft_strrchr(argv, *str);
	if (!line)
		return (0);
	if (!ft_strncmp(line, str, ft_strlen(str)))
		return (1);
	return (0);
}
