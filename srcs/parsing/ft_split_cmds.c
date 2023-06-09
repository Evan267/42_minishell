/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eberger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:52:59 by eberger           #+#    #+#             */
/*   Updated: 2023/06/09 10:22:26 by eberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **ft_realloc_split(char **cmds, size_t size) {
    char **new_cmds = malloc((size + 1) * sizeof(char *));
    if (new_cmds) {
        for (size_t i = 0; i < size; i++) {
            new_cmds[i] = cmds[i];
        }
        new_cmds[size] = NULL;
        free(cmds);
    }
    return new_cmds;
}

static int is_quote(char c) {
    return c == '"' || c == '\'';
}

char	**ft_split_cmds(char const *s, char c)
{
    if (s == NULL)
        return NULL;

    size_t capacity = 16;
    size_t size = 0;
    char **cmds = malloc(sizeof(char *) * capacity);
    if (cmds == NULL)
        return NULL;

    const char *start = s;
    int in_quotes = 0;
    char quote_char = '\0';

    while (*s) {
        if (is_quote(*s)) {
            if (!in_quotes) {
                in_quotes = 1;
                quote_char = *s;
            } else if (*s == quote_char) {
                in_quotes = 0;
                quote_char = '\0';
            }
        } else if (*s == c && !in_quotes) {
            size_t len = s - start;
            cmds[size] = malloc(len + 1);
            if (cmds[size] == NULL) {
                // Gestion d'erreur : libération de la mémoire allouée
                for (size_t i = 0; i < size; i++) {
                    free(cmds[i]);
                }
                free(cmds);
                return NULL;
            }
            memcpy(cmds[size], start, len);
            cmds[size][len] = '\0';
            size++;
            if (size >= capacity) {
                cmds = ft_realloc_split(cmds, capacity);
                if (!cmds) {
                    // Gestion d'erreur : libération de la mémoire allouée
                    for (size_t i = 0; i < size; i++) {
                        free(cmds[i]);
                    }
                    free(cmds);
                    return NULL;
                }
                capacity++;
            }
            start = s + 1;
        }
        s++;
    }

    // Ajouter la dernière commande après la dernière occurrence de '|'
    size_t len = s - start;
    cmds[size] = malloc(len + 1);
    if (cmds[size] == NULL) {
        // Gestion d'erreur : libération de la mémoire allouée
        for (size_t i = 0; i < size; i++) {
            free(cmds[i]);
        }
        free(cmds);
        return NULL;
    }
    memcpy(cmds[size], start, len);
    cmds[size][len] = '\0';
    size++;

    // Réallouer la mémoire pour la taille exacte
    char **result = ft_realloc_split(cmds, sizeof(char *) * (size + 1));
    if (result == NULL) {
        // Gestion d'erreur : libération de la mémoire allouée
        for (size_t i = 0; i < size; i++) {
            free(cmds[i]);
        }
        free(cmds);
        return NULL;
    }
    result[size] = NULL;

    return result;
}
