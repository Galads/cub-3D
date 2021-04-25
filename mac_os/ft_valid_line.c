
int ft_valid_line(char **line)
{
	int i;

	i = 0;
	while ((*line)[i] == ' ')
		i++;
	return i;
}