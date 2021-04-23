//
// Created by Belwas Rice on 4/23/21.
//

char *ft_valid_line(char **line)
{
	int i;

	i = 0;
	while ((*line)[i] == ' ')
		(*line)[i++];
	return (line)[i];
}