/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_params.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/20 16:27:52 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/20 16:27:56 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

// indirecte --> val ou :val
// directe ---> %val(4 octets) ou %:val(2 octets)
/*
    -- live = 1 argument : %val.
    -- ld = 2 arguments : [%val / indirecte], REGISTRE.
    -- st = 2 arguments : REGISTRE, [Registre / indirecte].
    -- add = 3 arguments : REGISTRE1, REGISTRE2, REGISTRE3
    -- sub = commme add.
    -- and = [%val / indirecte / registre], [%val / indirecte / registre], REGISTRE.
    -- or = comme and (3 args, ...)
    -- xor = comme and (3args, ...)
    -- zjmp = suivi de %:val
    -- ldi = [REGISTRE, indirecte, %:val], [indirecte, %:val], REGISTRE
    -- stdi = [REGISTRE], [REGISTRE, indirecte, %:val], [indirecte, %:val]
    -- fork = %:val
    -- lld = [indirecte, %val], [REGISTRE]
    -- lldi = [REGISTRE, indirecte, %:val], [indirecte, %:val]
    -- lfork = [%:val]
    -- aff = [REGISTRE]
 */
void get_direct_param(char *line, int *i, t_lexer *lexer, int curr_instruction)
{
    int index;
    int current_type;

    current_type = (line[*i] == '%') ? DIR4 : DIR2;
    if (line[*i] == '%')
    {
        (*i)++;
        index = *i;
        while (ft_isdigit(line[index]))
            index++;
        if (curr_instruction != 0)
            push_param(lexer->label[lexer->label_count]->instruction[curr_instruction], NULL,
                ft_strsub(line, *i, index - *i), current_type);
    }
    else
    {
        (*i)+=2;
        index = *i;
        while (line[index])
            index++;
        if (curr_instruction != 0)
            push_param(lexer->label[lexer->label_count]->instruction[curr_instruction], NULL,
                ft_strsub(line, *i, index - *i), current_type);
    }
    (*i)+=index;
}

void get_indirect_param(char *line, int *i, t_lexer *lexer, int curr_instruction)
{
    int index;
    int current_type;

    current_type = T_IND;
    if (ft_isdigit(line[*i]))
    {
        index = *i;
        while (ft_isdigit(line[index]))
            index++;
        if (curr_instruction != 0)
            push_param(lexer->label[lexer->label_count]->instruction[curr_instruction], NULL,
                ft_strsub(line, *i, index - *i), current_type);
        (*i)+=index;
    }else
    {
        (*i)++;
        index = *i;
        while (line[index])
            index++;
        if (curr_instruction != 0)
            push_param(lexer->label[lexer->label_count]->instruction[curr_instruction], NULL,
                ft_strsub(line, *i, index - *i), current_type);
    }
    (*i)+=index;
}

int get_type(char *line, int *i, t_lexer *lexer)
{
    int index;
    int curr_instruction;
    int error;

    // todo les registres..... (<= 99).
    curr_instruction = lexer->label_count != 0 ? lexer->label[lexer->label_count]->instruction_count : 0;
    if (line[*i] == '%' && ft_isdigit(line[*i + 1]) || (line[*i + 1] == ':' && line[*i] == '%' && is_label(line, i + 2)))
    {
        get_direct_param(line, i, lexer, curr_instruction);
        return (1);
    }
    if ((line[*i] == ':' && is_label(line, i + 1)) || ft_isdigit(line[*i]))
    {
        get_indirect_param(line, i, lexer, curr_instruction);
        return (1);
    }
    return (0);
}

int get_param_count(int type_index)
{
    int params[4];
    int i;

    i = 0;
    params = param_type[type_index];
    while (params[i] != 0)
        i++;
    return (i);
}

int is_valid_params(t_lexer *lexer, int type_index)
{
    int params[4];
    int count_param;
    int curr_instruction;

    i = 0;
    curr_instruction = lexer->label_count != 0 ? lexer->label[lexer->label_count]->instruction_count : 0;
    params = param_type[type_index];
    count_param = get_param_count(type_index);
    if (curr_instruction != 0)
    {
        if (lexer->label[lexer->label_count]->instruction[curr_instruction]->param_count != count_param)
            return (0);
        while (i < lexer->label[lexer->label_count]->instruction[curr_instruction]->param_count)
        {
            if (!(lexer->label[lexer->label_count]->instruction[curr_instruction]->type & params[i]))
                return (0);
            i++;
        }
    }
    return (1);
}

int get_params(char *line, int *i, t_lexer *lexer, int type_index)
{
    int params[4];
    int start_idx;
    int count_sep;
    //ld    p1  ,   p2  ,   p3
    start_idx = *i;
    params = param_type[type_index];
    while (((line[*i] >= 9 && line[*i] <= 13) || line[*i] == ' ') && line[*i])
        (*i)++;
    if (start_idx == *i)
        return (0);
    // nbre de virgule == (n_param - 1).
    count_sep = 0;
    while (line[*i])
    {
        if (count_sep > (get_param_count(type_index) - 1))
            return (0);
        while (((line[*i] >= 9 && line[*i] <= 13) || line[*i] == ' ') && line[*i])
            (*i)++;
        if (line[*i] == ',')
            count_sep++;
        if (!(get_type(line, i, lexer)))
            put_parsing_error("Syntax error (invalid instruction parameters)", 0, i, lexer);
        // !is_valid_char => nop.
        (*i)++;
    }
    if (!is_valid_params(lexer, type_index))
        put_parsing_error("Syntax error (invalid instruction parameters)", 0, i, lexer);
}
