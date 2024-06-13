/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimtoken.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:03:25 by maemaldo          #+#    #+#             */
/*   Updated: 2024/06/12 18:18:46 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*			ft_strtrimtoken
basiquement un melange de strdup et strtrim :
on parcoure str si on tombe sur un guillemet:
une autre boucle check si il y a un espace si oui
alors tu copie normalement sinon tu copie sans les guillemets,
	tout ca en enlevant les espaces et
les guillemets au debut et a la fin de str
*/

void	ft_isinquotes(char **start, char **end, int *in_quote)
{
	*in_quote = 0;
	if ((**start == '"' && **end == '"') || (**start == '\'' && **end == '\''))
	{
		*in_quote = 1;
		(*start)++;
		(*end)--;
	}
}

char	*ft_strtrimtoken(char *str)
{
	char	*start;
	char	*end;
	int		enclosed_in_quotes;
	char	*result;
	char	*dest;

	start = str;
	end = str + ft_strlen(str) - 1;
	while (*str && *str == ' ')
		str++;
	while (end > start && *str == ' ')
		end--;
	ft_isinquotes(&start, &end, &enclosed_in_quotes);
	result = malloc(end - start + 1 + 1);
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

// char	*ft_strtrimquotes(char *str)
// {
// 	char	*start;
// 	char	*end;
// 	int		enclosed_in_quotes;
// 	char	*result;
// 	char	*dest;

// 	start = str;
// 	end = str + ft_strlen(str) - 1;
// 	while (*str && *str == ' ')
// 		str++;
// 	while (end > start && *end == ' ')
// 		end--;
// 	enclosed_in_quotes = 0;
// 	if ((*start == '"' && *end == '"') || (*start == '\'' && *end == '\''))
// 	{
// 		enclosed_in_quotes = 1;
// 		start++;
// 		end--;
// 	}
// 	result = malloc(end - start + 1 + 1);
// 	if (!result)
// 		return (NULL);
// 	dest = result;
// 	while (start <= end)
// 	{
// 		if (enclosed_in_quotes || *start != ' ')
// 			*dest++ = *start;
// 		start++;
// 	}
// 	*dest = '\0';
// 	return (result);
// }

// char	*ft_strtrimtoken(char *str)
// {
// 	char	*trimmed_str;
// 	char	*final_str;

// 	// Step 1: Trim the quotes and leading/trailing spaces
// 	trimmed_str = ft_strtrimquotes(str);
// 	if (!trimmed_str)
// 		return (NULL);

// 	// Step 2: Trim the remaining spaces using ft_strtrim
// 	final_str = ft_strtrim(trimmed_str, " ");
// 	free(trimmed_str);

// 	return (final_str);
// }
