/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:14:10 by maemaldo          #+#    #+#             */
/*   Updated: 2024/06/11 18:47:19 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*    ft_strtrimtoken
basiquement un melange de strdup et strtrim :
on parcoure str si on tombe sur un guillemet: une autre boucle check si il y a un espace si oui
alors tu copie normalement sinon tu copie sans les guillemets,
	tout ca en enlevant les espaces et
les guillemets au debut et a la fin de str
*/

char	*ft_strtrimtoken(const char *str)
{
	const char	*start = str;
	const char	*end = str + ft_strlen(str) - 1;
	int			enclosed_in_quotes;
	size_t		len;
	char		*result;
	char		*dest;

	if (!str)
		return (NULL);
	while (*str && *str == ' ')
		str++;
	while (end > start && *str == ' ')
		end--;
	enclosed_in_quotes = 0;
	if ((*start == '"' && *end == '"') || (*start == '\'' && *end == '\''))
	{
		enclosed_in_quotes = 1;
		start++;
		end--;
	}
	len = end - start + 1;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	dest = result;
	while (start <= end)
	{
		if (enclosed_in_quotes || *str != ' ')
			*dest++ = *start;
		start++;
	}
	*dest = '\0';
	return (result);
}

int	ft_clear(char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		tmp = str[i];
		str[i] = ft_strtrimtoken(str[i]);
		free(tmp);
		if (!str[i])
			return (ft_free_tab(str), -1);
		i++;
	}
	return (0);
}

static int	ft_countwords(const char *s, char c)
{
	int	i;
	int	nb;
	int	in_quote;

	nb = 0;
	i = 0;
	in_quote = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			in_quote = !in_quote;
		if (!in_quote && (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')))
			nb++;
		i++;
	}
	return (nb);
}

static int	ft_wordsize(const char *s, char c)
{
	int	i;

	i = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		if (s[i + 1] == '\0')
			return (1);
		i++;
		while (s[i] && (s[i] != '"' && s[i] != '\''))
			i++;
		return (i + 1);
	}
	while (s[i] && (s[i] != c && s[i] != '"' && s[i] != '\''))
		i++;
	return (i);
}

static char	**ft_malloc_tab(char const *s, char c)
{
	char	**tab;
	int		size;

	if (!s)
		return (NULL);
	size = ft_countwords(s, c) + 1;
	size = 10;
	tab = (char **)malloc(sizeof(char *) * size);
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_token(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	tab = ft_malloc_tab(s, c);
	if (!tab)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = (char *)malloc(sizeof(char) * (ft_wordsize(&s[i], c) + 1));
			if (!tab[j])
				return (ft_free_tab(tab), NULL);
			ft_strlcpy(tab[j], (char *)&s[i], ft_wordsize(&s[i], c) + 1);
			i = i + ft_wordsize(&s[i], c);
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	ft_clear(tab);
	return (tab);
}
