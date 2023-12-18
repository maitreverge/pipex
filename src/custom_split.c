/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:15:06 by flverge           #+#    #+#             */
/*   Updated: 2023/12/18 14:27:54 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*pipex_ft_strncpy(char *dest, char const *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static void	pipex_sub_check(char const *s, char c, size_t *i, size_t *start)
{
	while (s[*i] == c)
		(*i)++;
	if (s[*i] != c && s[*i])
	{
		*start = *i;
		while (s[*i] != c && s[*i])
			(*i)++;
	}
}

static void	pipex_allocation(char **buffer, char const *s, char c, size_t len_s)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	if (!s)
		return ;
	while (s[i])
	{
		pipex_sub_check(s, c, &i, &start);
		if (j < len_s)
		{
			// One spot more for /
			buffer[j] = ft_calloc(sizeof(char), (i - start + 2));
			if (!buffer[j])
				return ;
			pipex_ft_strncpy(buffer[j], &s[start], i - start);
			ft_strlcat(buffer[j], "/", ft_strlen(buffer[j]) + 2);
			j++;
		}
		while (s[i] == c && s[i])
			i++;
	}
}
/*
Flow d'allocation :
! Etape 1 : La chaine se met a etre parcourue
! Etape 2 : subcheck est appellee, qui next les char c consecutifs
( de la meme facon que ft_countwords le fait)
*/

/*
! Etape 3 : l'index J est l'index des blocs de memoire qui consistuent
le coeur de fonctionnement de ft_split. C'est grace a ce dernier que
l'on va pouvoir se "deplacer" dans le char **buffer original
! Etape 4 : Le buffer[j] actuel est calloc
*/
/*
! Etape 5 : le buffer[j] est ensuite rempli avec la
bonne taille de start et de i
! Etape 6 : la chaine s principale est continuellement parcourue
tant que des char c consecutifs sont present apres un mot
(pareil que ft_countwords
*/

static size_t	ft_pipex_countwords(char const *str, char c)
{
	size_t	result;
	int		i;

	result = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i])
		{
			result++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (result);
}
/*
ft_countwords a pour but de compter le bon nombre de mots
! La fonction parcours la chaine et fait ceci :
1.1 : Continue a la parcourir tant que des char c consecutifs sont presents
ce qui ne compte pas pour des mots
1.2 : Si un caractere rencontre est different de char c, ceci indique 
un mot supplementaire, donc result++
1.3 : la chaine continue ensuite d'etre parcourue tant que la chaine
existe ET que les char presents sont differents

Ceci permet d'eviter les faux positifs de mots avec des char c
consecutifs en debut ET et fin de chaine
*/

char	**ft_pipex_split(char const *s, char c)
{
	char	**buffer;
	size_t	len_s;

	len_s = ft_pipex_countwords(s, c);
	buffer = (char **)ft_calloc(sizeof(char *), (len_s + 1));
	if (!buffer)
		return (NULL);
	pipex_allocation(buffer, s, c, len_s);
	return (buffer);
}
/*
Flow de split
! Etape 1 : calculer le bon nombre de mots avec ft_countwords
! Etape 2 : Allocation sur un char** du bon nombre de "blocs"
+ un bloc pour y stocker la valeur NULL
! Etape 3 : fonction allocation joue le role de split, voir au dessus
*/
