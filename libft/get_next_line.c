/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgoedkoo <mgoedkoo@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 17:28:13 by mgoedkoo      #+#    #+#                 */
/*   Updated: 2023/04/06 16:12:20 by mgoedkoo      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*memfree(char *mem1, char *mem2)
{
	if (mem1)
	{
		free(mem1);
		mem1 = NULL;
	}
	if (mem2)
	{
		free(mem2);
		mem2 = NULL;
	}
	return (NULL);
}

static char	*textmaker(int fd, char *text, char *temp)
{
	char	*buff;
	int		r;

	r = 1;
	while (!ft_strchr(text, '\n') && r != 0)
	{
		temp = text;
		buff = malloc(sizeof(char) * 11);
		if (!buff)
			return (memfree(text, NULL));
		r = read(fd, buff, 10);
		if (r == -1)
			return (memfree(buff, text));
		((char *) buff)[r] = '\0';
		text = ft_strjoin(temp, buff);
		if (!text)
			return (memfree(buff, temp));
		memfree(buff, temp);
	}
	return (text);
}

static char	*linemaker(int fd, char *nextline)
{
	static char	*text[OPEN_MAX];
	char		*temp;

	temp = NULL;
	if (!ft_strchr(text[fd], '\n'))
		text[fd] = textmaker(fd, text[fd], temp);
	if (!text[fd])
		return (NULL);
	if (!ft_strchr(text[fd], '\n'))
	{
		nextline = text[fd];
		text[fd] = NULL;
		return (nextline);
	}
	nextline = ft_substr(text[fd], 0, ft_strlen(text[fd])
			- ft_strlen(ft_strchr(text[fd], '\n')) + 1);
	if (!nextline)
		return (text[fd] = memfree(text[fd], NULL));
	temp = ft_substr(text[fd], ft_strlen(nextline), ft_strlen(text[fd])
			- ft_strlen(nextline));
	if (!temp)
		return (text[fd] = memfree(text[fd], nextline));
	text[fd] = memfree(text[fd], NULL);
	text[fd] = temp;
	return (nextline);
}

char	*get_next_line(int fd)
{
	char	*nextline;

	nextline = NULL;
	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	nextline = linemaker(fd, nextline);
	return (nextline);
}
