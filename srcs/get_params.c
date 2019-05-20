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

 void get_param_val(int param[4], int type_index)
 {
     int i;

     i = 0;
     while (i < 4)
     {
         param[i] = param_type[type_index][i];
         i++;
     }
 }

void get_direct_param(char *line, int *i, t_lexer *lexer, int curr_instruction)
{
    int index;
    int current_type;

    index = 0;
    current_type = (line[*i] == '%') ? DIR4 : DIR2;
    if (line[*i] == '%')
    {
        (*i)++;
        index = 0;
        while (ft_isdigit(line[*i + index]) && line[*i + index])
            index++;
        ft_printf("curr instru : %d \n", curr_instruction);
        if (curr_instruction != 0)
        {
            push_param(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1], NULL,
                ft_strsub(line, *i, index), current_type);
            ft_printf("push dir\n");
        }
    }
    else
    {
        (*i)+=2;
        while (line[*i + index] != SEPARATOR_CHAR && line[*i + index] != COMMENT_CHAR && line[*i + index])
            index++;
        if (curr_instruction != 0)
            push_param(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1], NULL,
                ft_strsub(line, *i, index), current_type);
    }
    (*i)+=index;
    ft_printf("curr char val %c\n", line[*i]);
}

void get_indirect_param(char *line, int *i, t_lexer *lexer, int curr_instruction)
{
    int index;

    index = 0;
    if (ft_isdigit(line[*i]))
    {
        while (ft_isdigit(line[*i + index]) && line[*i + index])
            index++;
        if (curr_instruction != 0)
        {
            push_param(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1], NULL,
                ft_strsub(line, *i, index), T_IND);
            ft_printf("push indi \n");
        }
    }else
    {
        (*i)++;
        while (line[*i + index] != SEPARATOR_CHAR && line[*i + index] != COMMENT_CHAR && line[*i + index])
            index++;
        if (curr_instruction != 0)
        {
            push_param(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1], NULL,
                ft_strsub(line, *i, index), T_IND);
            ft_printf("push indi \n");
        }
    }
    (*i)+=index;
}

void get_register_param(char *line, int *i, t_lexer *lexer, int curr_instruction)
{
    int index;
    char *value;

    (*i)++;
    index = 0;
    while (ft_isdigit(line[*i + index]) && line[*i + index])
        index++;
    value = ft_strsub(line, *i, index);
    if (curr_instruction != 0 && ft_atoi(value) < 99)
        push_param(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1], NULL,
            value, T_REG);
    (*i)+=index;
}

int get_type(char *line, int *i, t_lexer *lexer)
{
    int curr_instruction;
    int param_count;


    curr_instruction = (lexer->label_count != 0) ? lexer->label[lexer->label_count - 1]->instruction_count : 0;
    param_count = (curr_instruction != 0) ?
    lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->param_count : 0;
    ft_printf("value %c\n", line[*i]);
    if ((line[*i] == '%' && ft_isdigit(line[(*i) + 1]))
    || (line[(*i) + 1] == ':' && line[*i] == '%'
    && is_label(line, (*i) + 2, 0)))
        get_direct_param(line, i, lexer, curr_instruction);
    else if ((line[*i] == ':' && is_label(line, (*i) + 1, 0)) || ft_isdigit(line[*i]))
        get_indirect_param(line, i, lexer, curr_instruction);
    else if (line[*i] == 'r' && ft_isdigit(line[(*i) + 1]))
        get_register_param(line, i, lexer, curr_instruction);
    if (curr_instruction != 0)
    {
        if (lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->param_count == param_count)
        {
            ft_printf("no params pushed to stack\n");
            return (0);
        }
    }
    return (1);
}

int get_param_count(int type_index)
{
    int params[4];
    int i;

    i = 0;
    get_param_val(params, type_index);
    //params = {param_type[type_index][0], param_type[type_index][1], param_type[type_index][2], param_type[type_index][3]};
    while (params[i] != 0)
        i++;
    return (i);
}

int is_valid_params(t_lexer *lexer, int type_index)
{
    int params[4];
    int i;
    int count_param;
    int curr_instruction;

    i = 0;
    curr_instruction = lexer->label_count != 0 ? lexer->label[lexer->label_count]->instruction_count : 0;
    get_param_val(params, type_index);
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

void get_params(char *line, int *i, t_lexer *lexer, int type_index)
{
    int params[4];
    int start_idx;
    int count_sep;
    //ld    p1  ,   p2  ,   p3
    start_idx = *i;
    get_param_val(params, type_index);
    while (((line[*i] >= 9 && line[*i] <= 13) || line[*i] == ' ') && line[*i])
        (*i)++;
    if (line[*i] == COMMENT_CHAR)
        return ;
    if (start_idx == *i)
        put_parsing_error("Syntax error (invalid instruction space with parameters)", lexer->current_line, *i, lexer);
    // nbre de virgule == (n_param - 1).
    count_sep = 0;
    while (line[*i])
    {
        ft_printf("char begin boucle : %c\n", line[*i]);
        while (((line[*i] >= 9 && line[*i] <= 13) || line[*i] == ' ' || line[*i] == ',') && line[*i])
        {
            if (line[*i] == ',')
                count_sep++;
            if (count_sep > (get_param_count(type_index) - 1))
                put_parsing_error("Syntax error (invalid instruction coma)", lexer->current_line, *i, lexer);
            (*i)++;
        }
        if (line[*i] == COMMENT_CHAR)
            break;
        ft_printf("char before tyep : %c\n", line[*i]);
        if (!(get_type(line, i, lexer)))
        {
            ft_printf("error with this char : |%c|\n", line[*i]);
            put_parsing_error("Syntax error (invalid instruction parameter's type)", lexer->current_line, *i, lexer);
        }
        if (line[*i] == COMMENT_CHAR)
            break;
        // !is_valid_char => nop.
        (*i)++;
    }
    if (!is_valid_params(lexer, type_index))
        put_parsing_error("Syntax error (invalid instruction parameter's format)", 0, *i, lexer);
}
