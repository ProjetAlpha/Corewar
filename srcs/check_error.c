/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/17 13:36:22 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 13:36:24 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include "asm.h"

void put_error(char *str)
{
    ft_printf("%s\n", str);
    exit(0);
}

void put_parsing_error(char *str, int n_line, int pos_line, t_lexer *lexer)
{
    ft_printf("%s at [%d, %d]\n", str, n_line, pos_line);
    free_all(lexer);
    exit(0);
}

void check_file_extension(char *file)
{
    int len;

    len = ft_strlen(file);
    if (file[len - 1] != 's' || file[len - 2] != '.')
        put_error("Wrong file extension.");
}
