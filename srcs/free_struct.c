/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_struct.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/20 14:03:12 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/20 14:03:22 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

static void free_components(t_lexer *lexer)
{
    int i;
    int j;
    int k;

    i = -1;
    while (++i < lexer->label_count)
    {
        j = -1;
        while (++j < lexer->label[i]->instruction_count)
        {
            free(lexer->label[i]->instruction[j]);
            k = -1;
            //while (++k < lexer->label[i]->instruction[i]->param_count)
                //free(lexer->label[i]->instruction[j]->param[k]);
            //if (lexer->label[i]->instruction[j]->param)
                //free(lexer->label[i]->instruction[j]->param);
        }
        free(lexer->label[i]->instruction);
        free(lexer->label[i]->name);
        free(lexer->label[i]);
        i++;
    }
    free(lexer->label);
}

void free_all(t_lexer *lexer)
{
    if (lexer && lexer->header)
    {
        if (lexer->header->name)
            free(lexer->header->name);
        if (lexer->header->comment)
            free(lexer->header->comment);
        free(lexer->header);
    }
    if (lexer)
    {
        free_components(lexer);
        free(lexer);
    }
}
