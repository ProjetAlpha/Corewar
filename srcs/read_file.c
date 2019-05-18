/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_file.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/17 13:54:40 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 13:54:41 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int is_name(char *line, int i)
{
    int counter;

    counter = 0;
    while (line[i] == NAME_CMD_STRING[counter] && line[i] && ++counter)
        i++;
    if (counter == 5)
        return (IS_NAME);
    return (0);
}

int is_comment(char *line, int i)
{
    int counter;

    counter = 0;
    while (line[i] == COMMENT_CMD_STRING[counter] && line[i] && ++counter)
        i++;
    if (counter == 8)
        return (IS_COMMENT);
    return (0);
}

/*int n_octets; // opcode + 1 (si octet de codage) + total params --> nOctets
int type;
int have_index;
int instruction_count;
unsigned char params_octet;
unsigned char value;*/

// push param dans la current instruction.
void push_param(t_instruction *instruction, t_instruction *cpy_instru, char *value)
{
    t_param **param;
    int i;

    i = 0;
    if (instruction->param_count == 0)
        return ;
    if (!(param = malloc(sizeof(t_param *) * (instruction->param_count + (value != NULL ? 1 : 0)))))
        put_error("malloc error\n");
    while (i < instruction->param_count)
    {
        param[i] = init_param();
        param[i]->value = ft_strdup(instruction->param[i]->value);
        i++;
    }
    if (value != NULL)
    {
        param[i] = init_param();
        param[i]->value = ft_strdup(value);
        cpy_instru->param_count++;
    }
    cpy_instru->param = param;
}

// push intrusction dans le current label.
void push_instruction(t_label *curr_label, t_label *cpy_label, int value)
{
    int i;
    t_instruction **instruction;

    i = 0;
    if (curr_label->instruction_count == 0)
        return ;
    // instruction count dans label stp.
    if (!(instruction = malloc(sizeof(t_instruction *) * (curr_label->instruction_count + (value != 0 ? 1 : 0)))))
        put_error("malloc error\n");
    while (i < curr_label->instruction_count)
    {
        instruction[i] = init_instruction();
        instruction[i]->value = curr_label->instruction[i]->value;
        if (curr_label->instruction[i]->param_count != 0)
            push_param(curr_label->instruction[i], instruction[i], NULL);
        i++;
    }
    if (value != 0)
    {
        instruction[i] = init_instruction();
        instruction[i]->value = value;
        cpy_label->instruction_count++;
    }
    cpy_label->instruction = instruction;
}

void push_label(t_lexer *lexer, char *name)
{
    t_label **label;
    int i;

    i = 0;
    // qd on push un label, on copie juste les instructions + les params, pas de push.
    if (!(label = malloc(sizeof(t_label *) * (lexer->label_count + 1))))
        put_error("malloc error\n");
    ft_printf("name to push : %s\n", name);
    while (i < lexer->label_count)
    {
        label[i] = init_label();
        label[i]->name = ft_strdup(lexer->label[i]->name);
        if (lexer->label[i]->instruction_count != 0)
            push_instruction(lexer->label[i], label[i], 0);
        i++;
    }
    label[i] = init_label();
    label[i]->name = ft_strdup(name);
    lexer->label = label;
    lexer->label_count++;
}


int  get_label(char *line, int *i, t_lexer *lexer)
{
    int counter;

    counter = *i;
    while (line[counter])
    {
        if (ft_strchr(LABEL_CHARS, line[counter]) == NULL && line[counter] != LABEL_CHAR)
            return (0);
        counter++;
    }
    push_label(lexer, ft_strsub(line, *i, counter));
    (*i)+=counter;
    return (1);
}

/*
int get_params()
{
    en fonction du type de l'instruction (op_code),
    verifier le nbre de params + le bon type de params.
    is_direct, is_indirect, is_register, is_adress.


    // push les params dans la current instruction.
}
*/

int get_instruction(char *line, int line_index)
{
    int i;
    int j;
    int tmp;
    static const char *valid_instruction[] = {
        "live", "ld", "st", "add",
        "sub", "and", "or", "xor",
        "zjmp", "ldi", "sti", "fork",
        "lld", "lldi", "lfork", "aff"
    };

    i = 0;
    while (i < 16)
    {
        j = 0;
        tmp = line_index;
        while (valid_instruction[i][j] == line[tmp] && ++tmp)
            j++;
        if (valid_instruction[i][j] == '\0')
        {
            push_instruction(lexer->label[lexer->label_count - 1], );
            // push l'instruction dans le current label.
            return (Op_Code[i]);
        }
        i++;
    }
    return (0);
}

// ------------- tant que pas de nouveau label, stock dans celui la.
// -------------- [nom instruction valid] [n_param][params_format, params_format]
// %:[label existe?] ---
/*int is_label_char(char *line, int type)
{

}*/

int is_valid_char(char c)
{
    return (ft_isalnum(c) || c == COMMENT_CHAR
            || c == '_' || c == LABEL_CHAR
            || c == DIRECT_CHAR || c == SEPARATOR_CHAR
            || (c >= 9 && c <= 13) || c == 32);
}

int is_valid_format(char *line, int *i, t_lexer *lexer, int *currentType)
{
    int j;
    int start_idx;
    int tmp;

    start_idx = *i;
    tmp = 0;
    // plusieurs ligne de coms ou name.
    if (*currentType == IS_STR_NAME || *currentType == IS_STR_COMMENT)
    {
        while (line[*i] != '"' && line[*i])
            (*i)++;
        // free header => fonction qui free et retourne 0.
        if ((*currentType == IS_STR_NAME && *i + ft_strlen(lexer->header->name) >= PROG_NAME_LENGTH)
        || (*currentType == IS_STR_COMMENT && *i + ft_strlen(lexer->header->comment) >= COMMENT_LENGTH))
        {
                ft_printf("outch la taille\n");
                return (0);
        }
        if (*currentType == IS_STR_NAME)
        {
            *currentType = (line[*i] == '"') ? IS_END_NAME : IS_STR_NAME;
            line[*i] == '"' ? (*i)++ : 0;
            lexer->header->name = ft_strjoin(lexer->header->name, ft_strsub(line, start_idx, *i));
            ft_printf("name : |%s|\n", lexer->header->name);
        }
        if (*currentType == IS_STR_COMMENT)
        {
            *currentType = (line[*i] == '"') ? IS_END_COMMENT : IS_STR_COMMENT;
            line[*i] == '"' ? (*i)++ : 0;
            lexer->header->comment = ft_strjoin(lexer->header->comment, ft_strsub(line, start_idx, *i));
            ft_printf("comment : |%s|\n", lexer->header->comment);
        }
        return (1);
    }
    if (line[*i] == '.')
    {
        if (is_name(line, *i) == IS_NAME)
            *currentType = IS_NAME;
        else if (is_comment(line, *i) == IS_COMMENT)
            *currentType = IS_COMMENT;
        else
            return (0);
    }
    if (*currentType == IS_NAME || *currentType == IS_COMMENT)
    {
        (*i) += (*currentType == IS_NAME) ? 5 : 8;
        while (((line[*i] >= 9 && line[*i] <= 13) || line[*i] == ' ') && line[*i])
            (*i)++;
        tmp = *i - start_idx;
        j = 0;
        if (line[*i] != '"')
            return (0);
        if (line[*i])
        {
            (*i)++;
            while (line[*i] != '"' && line[*i])
                (*i)++;
        }
        // free header => fonction qui free et retourne 0.
        if ((*currentType == IS_NAME && j >= PROG_NAME_LENGTH) || (*currentType == IS_COMMENT && j >= COMMENT_LENGTH))
            return (0);
        if (*currentType == IS_NAME)
        {
            lexer->header->have_name = 1;
            lexer->header->name = ft_strsub(line, start_idx + tmp, *i);
            *currentType = (line[*i] == '"') ? IS_END_NAME : IS_STR_NAME;
            (line[*i] == '"') ? (*i)++ : 0;
        }
        if (*currentType == IS_COMMENT)
        {
            lexer->header->have_comment = 1;
            lexer->header->comment = ft_strsub(line, start_idx + tmp, *i);
            *currentType = (line[*i] == '"') ? IS_END_COMMENT : IS_STR_COMMENT;
            (line[*i] == '"') ? (*i)++ : 0;
        }
    }
    return (1);
}

void handle_line(char *line, t_lexer *lexer, int n_line, int *currentType)
{
    int i;

    i = 0;
    // en fonction du current type, balance les fonctions adequates...
    while (line[i])
    {
        if (!(*currentType == IS_STR_NAME || *currentType == IS_STR_COMMENT))
        {
            while (((line[i] >= 9 && line[i] <= 13) || line[i] == ' ') && line[i])
                i++;
        }
        if (line[i] == COMMENT_CHAR)
            return ;
        if (lexer->header->have_name && *currentType == IS_END_NAME && line[i])
        {
            if (is_comment(line, i) != IS_COMMENT)
                put_parsing_error("Syntax error (header name)", n_line, i);
        }
        if (lexer->header->have_comment && *currentType == IS_END_COMMENT && line[i])
        {
            //if (!get_)
            // *currentType = 0;
            // si comment n'est pas suivi c'est pas suivi par une instruction ou label ==> NOP.
            //ft_printf("label match %d\n", get_label(line, i));
            if (!get_label(line, &i, lexer) && !get_instruction(line, i))
                put_parsing_error("Syntax error (invalid instruction or label)", n_line, i);
        }
        // plus explicite pour la taille stp + qd on a pas de pnt..+ qd on a deja un nom ou comment...
        if (!is_valid_format(line, &i, lexer, currentType))
            put_parsing_error("Syntax error (format)", n_line, i);
        if (line[i])
        {
            if (!is_valid_char(line[i]) && !(*currentType == IS_STR_NAME || *currentType == IS_STR_COMMENT))
                put_parsing_error("Syntax error (invalid char)", n_line, i);
        }
        line[i] ? i++ : 0;
    }
}

void parse_file(char *file)
{
    int fd;
    char *line;
    //char *tmp_line;
    int  c_line;
    t_lexer *lexer;
    int currentType;
    fd = open(file, O_RDONLY);

    lexer = init_lexer();
    c_line = 0;
    currentType = 0;
    // ------------ 1 nom et un comment.
    // ------------ rien d'autre que espace entre name et comment.
    // ------------- tant que pas de nouveau label, stock dans celui la.
    // -------------- [nom instruction valid] [n_param][params_format, params_format]
    // %:[label existe?] ---
    lexer->header->corewar_magic = COREWAR_EXEC_MAGIC;
    if (fd < 0)
        put_error("Error : cant open this file.");
    while (get_next_line(fd, &line))
    {
        c_line++;
        // handle_header()..
        // handle_label()...
        // handle_instruction()...
        // handle_params()...
        handle_line(line, lexer, c_line, &currentType);
        free(line);
    }
}
