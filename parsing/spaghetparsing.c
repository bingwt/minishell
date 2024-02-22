#include <stdio.h>

// change all static size to ft_calloc and remove
// arg_count as we can iterate through with while (arr[i])
// as long as we remember to set NULL after final arg

char	**input_parser(char *input)
{
	char	space_split[100][50]; // res after parsing quotes/space, up to 10 cmds of 50 char len
	int		squote = 0;
	int		dquote = 0; // flags to check when quotes are open/closed
	int		i = 0; // go through space_split char by char
	int		j = 0; // fill up res with non special arg chars
	int		arg_index = 0; // for filling up res
	int		arg_size[10]; // number of char in each arg
	int		arg_count = 0; // number of cmds in space_split
	char	c;

	// current implementation does not account for awk
	// and for unclosed quotes
	while (input[i])
	{
		c = input[i];
		if (c == '\'')
			squote = !squote;
		else if (c == '\"')
			dquote = !dquote;
		else if (c == ' ')
		{
			if (!squote && !dquote && j > 0) // if no quotes, delim by space
			{
				space_split[arg_index][j] = '\0';
				arg_size[arg_index] = j;
				arg_index++;
				j = 0;
			}
			else if (j)
				space_split[arg_index][j++] = c; // there are quotes, copy the space
		}
		else
			space_split[arg_index][j++] = c;
		i++;
	if (j > 0)
	{
		space_split[arg_index][j] = '\0';
		arg_size[arg_index] = j;
		arg_count = arg_index + 1;
	}

	//to this point, space_split should be split by spaces without repeats
	//unless spaces occur between quotes where they will be preserved
	int p = 0;
	while (p < arg_count)
	{
		printf("%d: %s\n", p, space_split[p]);
		p++;
	}
/*
	char	pipe_split[100][100];
	arg_index = 0;
	i = 0;
	// if there is any syntax error for | none of the cmds will run,
	// whole line will be void whether | is at beginning or if consecutive |
	if (!ft_strcmp(space_split[0], "|"))
	{
		while (arg_index < arg_count)
		{
			// if consecutive pipe, error whole line
			if (!ft_strcmp(space_split[arg_index], "|")
				&& !ft_strcmp(space_split[arg_index - 1], "|"))
			{
				pipe_split = NULL;
				break ;
			}
			// ft_calloc everything and strjoin_free
			if (ft_strcmp(space_split[arg_index], "|"))
				pipe_split[i] = ft_strjoin(pipe_split[i], space_split[arg_index]);
			else
				i++;
			arg_index++;
		}
	}
	else
		pipe_split = NULL;
	*/
}
