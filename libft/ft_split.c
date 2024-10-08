/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgebetsb <bgebetsb@students.42vienna.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 15:47:00 by bgebetsb          #+#    #+#             */
/*   Updated: 2024/04/03 17:13:30 by bgebetsb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*get_next_word(char const *s, char c)
{
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	word = (char *)ft_calloc(++i, sizeof(char));
	if (word == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(word, s, i);
	return (word);
}

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			words++;
		}
		i++;
	}
	return (words);
}

void	free_stuff(char **splitted, size_t word_index)
{
	size_t	i;

	i = 0;
	while (i < word_index)
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	size_t	word_index;
	size_t	i;

	if (s == NULL)
		return (NULL);
	splitted = (char **)ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (splitted == NULL)
		return (NULL);
	word_index = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			splitted[word_index] = get_next_word(s + i, c);
			if (splitted[word_index] == NULL)
				return (free_stuff(splitted, word_index), NULL);
			word_index++;
		}
		i++;
	}
	return (splitted);
}
