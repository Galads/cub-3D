
int ft_valid_line(char **line)
{
	int i;

	i = 0;
	while ((*line)[i] == ' ')
		(*line)[i++];
	return i;
}