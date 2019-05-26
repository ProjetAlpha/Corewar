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

// codage different idx ? ...
// indirecte --> val ou :val => 2 octets.
// directe ---> %val(4 octets, depend...) ou %:val(2 octets).
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

int check_next_param_char(char c, int is_last_param)
{
     if (is_last_param)
         return ((c >= 9 && c <= 13) || c == 32 || c == COMMENT_CHAR);
     return ((c >= 9 && c <= 13) || c == 32 || c == SEPARATOR_CHAR || c == COMMENT_CHAR);
}

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

// dir 4 = live, ld, and, or, xor, lld, aff;
// dir 2 = zjmp, ldi, sti, fork, lldi, lfork;

void get_direct_param(char *line, int *i, t_lexer *lexer, int curr_instruction)
{
    int index;
    int instru_type;
    int current_type;
    int param_count;

    index = 0;
    instru_type = (curr_instruction != 0) ?
    lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->value :
    lexer->label[lexer->label_count - 1]->instruction[curr_instruction]->value;
    if (instru_type == LIVE_CODE || instru_type == LD_CODE || instru_type == AND_CODE
        || instru_type == OR_CODE || instru_type == XOR_CODE || instru_type == LLD_CODE || instru_type == AFF_CODE)
        current_type = DIR4;
    else
        current_type = DIR2;
    param_count = (curr_instruction != 0) ? lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->param_count : 0;
    if ((line[*i] == '%' && ft_isdigit(line[*i + 1])) || (line[*i] == '%' && line[*i + 1] == '-' && ft_isdigit(line[*i + 2])))
    {
        (*i)+= (line[*i + 1] == '-') ? 2 : 1;
        while (ft_isdigit(line[*i + index]) && line[*i + index])
            index++;
        if (line[*i + index])
        {
            if (!check_next_param_char(line[*i + index], (lexer->param_count == (param_count + 1)) ? 1 : 0))
                put_parsing_error("Syntax error (invalid parameter format)", lexer->current_line, *i + index, lexer);
        }
        if (curr_instruction != 0)
            push_param(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1], NULL,
                ft_strsub(line, *i, index), current_type);
    }
    else
    {
        (*i)+=2;
        while (ft_isalnum(line[*i + index], 'l') || line[*i + index] == '_')
            index++;
        if (line[*i + index])
        {
            if (!check_next_param_char(line[*i + index], (lexer->param_count == (param_count + 1)) ? 1 : 0))
                put_parsing_error("Syntax error (invalid parameter format)", lexer->current_line, *i + index, lexer);
        }
        if (curr_instruction != 0)
            push_param(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1], NULL,
                ft_strsub(line, *i, index), current_type);
    }
    (*i)+=index;
}

void get_indirect_param(char *line, int *i, t_lexer *lexer, int curr_instruction)
{
    int index;
    int param_count;

    index = 0;
    param_count = (curr_instruction != 0) ? lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->param_count : 0;
    if (ft_isdigit(line[*i]) || (line[*i] == '-' && ft_isdigit(line[*i + 1])))
    {
        (*i)+= (line[*i] == '-') ? 1 : 0;
        while (ft_isdigit(line[*i + index]) && line[*i + index])
            index++;
        if (line[*i + index])
        {
            if (!check_next_param_char(line[*i + index], (lexer->param_count == (param_count + 1)) ? 1 : 0))
                put_parsing_error("Syntax error (invalid parameter format)", lexer->current_line, *i + index, lexer);
        }
        if (curr_instruction != 0)
            push_param(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1], NULL,
                ft_strsub(line, *i, index), T_IND);
    }else
    {
        (*i)++;
        while (ft_isalnum(line[*i + index], 'l') || line[*i + index] == '_')
            index++;
        if (line[*i + index])
        {
            if (!check_next_param_char(line[*i + index], (lexer->param_count == (param_count + 1)) ? 1 : 0))
                put_parsing_error("Syntax error (invalid parameter format)", lexer->current_line, *i + index, lexer);
        }
        if (curr_instruction != 0)
            push_param(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1], NULL,
                ft_strsub(line, *i, index), T_IND);
    }
    (*i)+=index;
}

void get_register_param(char *line, int *i, t_lexer *lexer, int curr_instruction)
{
    int index;
    int param_count;
    char *value;

    param_count = (curr_instruction != 0) ? lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->param_count : 0;
    (*i)++;
    index = 0;
    while (ft_isdigit(line[*i + index]) && line[*i + index])
        index++;
    if (line[*i + index])
    {
        if (!check_next_param_char(line[*i + index], (lexer->param_count == (param_count + 1)) ? 1 : 0))
            put_parsing_error("Syntax error (invalid parameter format)", lexer->current_line, *i + index, lexer);
    }
    value = ft_strsub(line, *i, index);
    if (ft_atoi(value) < 0 || ft_atoi(value) > 99)
        put_parsing_error("Syntax error (invalid register format)", lexer->current_line, *i + index, lexer);
    if (curr_instruction != 0 && ft_atoi(value) <= 99)
        push_param(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1], NULL,
            value, T_REG);
    (*i)+=index;
}

// -------- TODO --------
// to do : comment char peut etre ; ou # ... mdr...lol.
// on peut flip le comment et le name.
// taille du com. + name.
// label:[nospace]instruction...
// y a pas d'espace .. neg_indirect_error.s
// sq_at_header.s

int get_type(char *line, int *i, t_lexer *lexer)
{
    int curr_instruction;
    int param_count;

    curr_instruction = (lexer->label_count != 0) ? lexer->label[lexer->label_count - 1]->instruction_count : 0;
    param_count = (curr_instruction != 0) ?
    lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->param_count : 0;
    //ft_printf("curr char |%c|\n", line[*i]);
    if ((line[*i] == '%' && (ft_isdigit(line[*i + 1]) || (line[*i + 1] == '-' && ft_isdigit(line[*i + 2]))))
    || (line[*i] == '%' && line[*i + 1] == ':'
    && (ft_isalnum(line[*i + 2], 'l') || line[*i + 2] == '_')))
    {
        get_direct_param(line, i, lexer, curr_instruction);
    }
    else if ((line[*i] == ':' && (ft_isalnum(line[*i + 1], 'l') || line[*i + 1] == '_')) || (ft_isdigit(line[*i]) || (line[*i] == '-' && ft_isdigit(line[*i + 1]))))
        get_indirect_param(line, i, lexer, curr_instruction);
    else if (line[*i] == 'r' && ft_isdigit(line[*i + 1]) && line[*i + 1] >= '0')
        get_register_param(line, i, lexer, curr_instruction);
    if (curr_instruction != 0)
    {
        if (lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->param_count == param_count)
            return (0);
    }
    return (1);
}

int get_param_count(int type_index)
{
    int params[4];
    int i;

    i = 0;
    get_param_val(params, type_index);
    while (params[i] != 0)
        i++;
    return (i);
}

// pas suivi d'un octet de codage : fork, zjmp, live.
// live : suivi 4 octets = numero du joueur.

// 1er octet apres op_code instruction.

// instruction->total_byte = curr_param_total_pos + prev_instru_total_byte + (1 ou 2 si byte codage);
// instruction->byte_addr_pos = instruction->total_byte - 2;

// instruction : total des octets de param + 1 (=octet instru) + 1 (si octet de codage = pas fork, zjmp, live).
// params : DIR2 = 2 | DIR 4 = 4 | IND = 2.

//

int is_valid_params(t_lexer *lexer, int type_index, int *curr_idx)
{
    int params[4];
    int i;
    int count_param;
    int curr_instruction;

    i = 0;
    curr_instruction = lexer->label_count != 0 ? lexer->label[lexer->label_count - 1]->instruction_count : 0;
    get_param_val(params, type_index);
    count_param = get_param_count(type_index);
    if (curr_instruction != 0)
    {
        if (lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->param_count != count_param)
            put_parsing_error("Syntax error (invalid parameter's count)", lexer->current_line, *curr_idx, lexer);
        while (i < lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->param_count)
        {
            if (!(lexer->label[lexer->label_count - 1]->instruction[curr_instruction - 1]->param[i]->type & params[i]))
                put_parsing_error("Syntax error (invalid parameter's format)", lexer->current_line, *curr_idx, lexer);
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
    int param_count;

    start_idx = *i;
    get_param_val(params, type_index);
    while (((line[*i] >= 9 && line[*i] <= 13) || line[*i] == ' ') && line[*i])
        (*i)++;
    if (line[*i] == COMMENT_CHAR)
        return ;
    if (start_idx == *i)
        put_parsing_error("Syntax error (no space after instruction)", lexer->current_line, *i, lexer);
    param_count = get_param_count(type_index);
    lexer->param_count = param_count;
    count_sep = 0;
    while (line[*i])
    {
        while (((line[*i] >= 9 && line[*i] <= 13) || line[*i] == ' ' || line[*i] == ',') && line[*i])
        {
            if (line[*i] == ',')
                count_sep++;
            if (count_sep > (param_count - 1))
                put_parsing_error("Syntax error (invalid instruction coma)", lexer->current_line, *i, lexer);
            (*i)++;
        }
        if (line[*i] == COMMENT_CHAR || line[*i] == '\0')
            break;
        if (!(get_type(line, i, lexer)))
            put_parsing_error("Syntax error (invalid instruction parameter's type)", lexer->current_line, *i, lexer);
        if (line[*i] == COMMENT_CHAR)
            break;
        if (line[*i] == ',')
            count_sep++;
        // !is_valid_char => nop.
        line[*i] ? (*i)++ : 0;
    }
    if (count_sep > (param_count - 1))
        put_parsing_error("Syntax error (invalid params coma)", lexer->current_line, *i, lexer);
    if (!is_valid_params(lexer, type_index, i))
        put_parsing_error("Syntax error (invalid instruction parameter's format)", lexer->current_line, *i, lexer);
}
