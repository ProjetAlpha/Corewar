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

void debug_lexer(t_lexer *lexer)
{
    int i;
    int j;
    int k;

    ft_printf("\e[38;5;214m---\e[0m \e[38;5;85mheader\e[0m \e[38;5;214m---\e[0m \n");
    ft_printf("   \e[38;5;214m→ corewar magic :\e[0m %lX\n", lexer->header->corewar_magic);
    ft_printf("   \e[38;5;214m→ size :\e[0m %d\n", lexer->header->prog_size);
    ft_printf("   \e[38;5;214m→ name :\e[0m %s\n", lexer->header->name);
    ft_printf("   \e[38;5;214m→ comment :\e[0m %s\n", lexer->header->comment);

    i = -1;
    while (++i < lexer->label_count)
    {
        j = -1;
        if (ft_strcmp(lexer->label[i]->name, "no label") != 0)
            ft_printf("\e[38;5;214m----\e[0m \e[38;5;171mlabel\e[0m \e[38;5;214m---\e[0m \n%s\n", lexer->label[i]->name);
        while (++j < lexer->label[i]->instruction_count)
        {
            if (j == 0)
                ft_printf("\e[38;5;214m label addresse : %d\e[0m\n", lexer->label[i]->instruction[j]->addr_pos);
            (j == 0 ) ? ft_printf("   \e[38;5;214m---\e[0m \e[38;5;82minstructions\e[0m \e[38;5;214m---\e[0m \n          \e[38;5;214m→ opcode : \e[0m%d ",
            lexer->label[i]->instruction[j]->value)
            : ft_printf("          \e[38;5;214m→ opcode : \e[0m%d ", lexer->label[i]->instruction[j]->value);
            k = -1;
            while (++k < lexer->label[i]->instruction[j]->param_count)
            {
                (k == 0 ) ? ft_printf(" \e[38;5;214m→ params : \e[0m%s",
                (char*)lexer->label[i]->instruction[j]->param[k]->value) :
                ft_printf(", %s", (char*)lexer->label[i]->instruction[j]->param[k]->value);
                ft_printf("[type=%d|byte_pos=%d]", lexer->label[i]->instruction[j]->param[k]->type, lexer->label[i]->instruction[j]->param[k]->byte_pos);
            }
            ft_printf("\n             \e[38;5;214m→ total_byte : \e[0m%d ", lexer->label[i]->instruction[j]->total_byte);
            ft_printf("\n");
        }
    }
}

void compute_instru_bytes(t_instruction *instruction, t_instruction *prev_instruction, int pos)
{
    int i;

    i = 0;
    if (!instruction)
        return ;
    if (!(instruction->value == LIVE_CODE || instruction->value == FORK_CODE || instruction->value == ZJMP_CODE))
    {
        instruction->total_byte += (2 + (prev_instruction ? prev_instruction->total_byte : 0));
        instruction->addr_pos = (pos == 0) ? instruction->total_byte - 1 : 0;
    }
    else
    {
        instruction->total_byte += (1 + (prev_instruction ? prev_instruction->total_byte : 0));
        instruction->addr_pos = (pos == 0) ? instruction->total_byte : 0;
    }
    while (i < instruction->param_count)
    {
        if (instruction->param[i]->type == DIR2)
        {
            instruction->param[i]->byte_pos = instruction->total_byte + 1;
            instruction->total_byte += 2;
        }
        else if (instruction->param[i]->type == DIR4)
        {
            instruction->param[i]->byte_pos = instruction->total_byte + 1;
            instruction->total_byte += 4;
        }
        else if (instruction->param[i]->type == T_IND)
        {
            instruction->param[i]->byte_pos = instruction->total_byte + 1;
            instruction->total_byte += 2;
        }
        else if (instruction->param[i]->type == T_REG)
        {
            instruction->param[i]->byte_pos = instruction->total_byte + 1;
            instruction->total_byte += 1;
        }
        i++;
    }
}

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

int is_label(char *line, int i, int *cursor)
{
    int counter;

    counter = i;
    while (line[counter] && line[counter] != LABEL_CHAR)
    {
        if (!(ft_isalnum(line[counter], 'l') || line[counter] == '_'))
            return (0);
        counter++;
    }
    if (line[counter] != LABEL_CHAR)
        return (0);
    counter++;
    *cursor = counter - i;
    return (1);
}

void push_param(t_instruction *instruction, t_instruction *cpy_instru, char *value, int type)
{
    t_param **param;
    int i;

    i = 0;
    if (instruction->param_count == 0 && cpy_instru != NULL)
        return ;
    if (!(param = malloc(sizeof(t_param *) * (instruction->param_count + (value != NULL ? 1 : 0)))))
        put_error("malloc error\n");
    while (i < instruction->param_count)
    {
        param[i] = init_param();
        param[i]->value = ft_strdup(instruction->param[i]->value);
        param[i]->type = instruction->param[i]->type;
        param[i]->byte_pos = instruction->param[i]->byte_pos;
        i++;
    }
    if (value != NULL && type != 0)
    {
        param[i] = init_param();
        param[i]->value = ft_strdup(value);
        param[i]->type = type;
        (cpy_instru != NULL) ? cpy_instru->param_count++ : instruction->param_count++;
    }
    if (cpy_instru != NULL)
        cpy_instru->param = param;
    else
        instruction->param = param;
}

void push_instruction(t_label *curr_label, t_label *cpy_label, int value)
{
    int i;
    t_instruction **instruction;

    i = 0;
    if (curr_label->instruction_count == 0 && cpy_label != NULL)
        return ;
    if (!(instruction = malloc(sizeof(t_instruction *) * (curr_label->instruction_count + (value != 0 ? 1 : 0)))))
        put_error("malloc error\n");
    while (i < curr_label->instruction_count)
    {
        instruction[i] = init_instruction();
        instruction[i]->value = curr_label->instruction[i]->value;
        instruction[i]->param_count = curr_label->instruction[i]->param_count;
        instruction[i]->total_byte = curr_label->instruction[i]->total_byte;
        instruction[i]->addr_pos = curr_label->instruction[i]->addr_pos;
        if (curr_label->instruction[i]->param_count != 0)
            push_param(curr_label->instruction[i], instruction[i], NULL, 0);
        i++;
    }
    if (value != 0)
    {
        instruction[i] = init_instruction();
        instruction[i]->value = value;
        (cpy_label != NULL) ? cpy_label->instruction_count++ : curr_label->instruction_count++;
    }
    if (cpy_label != NULL)
        cpy_label->instruction = instruction;
    else
        curr_label->instruction = instruction;
}

void push_label(t_lexer *lexer, char *name)
{
    t_label **label;
    int i;

    i = 0;
    // qd on push un label, on copie juste les instructions + les params, pas de push.
    if (!(label = malloc(sizeof(t_label *) * (lexer->label_count + 1))))
        put_error("malloc error\n");
    while (i < lexer->label_count)
    {
        label[i] = init_label();
        label[i]->name = ft_strdup(lexer->label[i]->name);
        label[i]->instruction_count = lexer->label[i]->instruction_count;
        if (lexer->label[i]->instruction_count != 0)
            push_instruction(lexer->label[i], label[i], 0);
        i++;
    }
    label[i] = init_label();
    label[i]->name = ft_strdup(name);
    lexer->label = label;
    lexer->label_count++;
}


int  get_label(char *line, int *i, t_lexer *lexer, int *currentType)
{
    int counter;

    counter = 0;
    if (!is_label(line, *i, &counter))
        return (0);
    *currentType = IS_LABEL;
    if (line[*i])
        push_label(lexer, ft_strsub(line, *i, counter));
    (*i)+= counter;
    return (1);
}

// -- NOTE : int comment = 2 chars => comment = COMMENT_CHAR | COMMENT_CHAR_2 => c & COMMENT_CHAR, c & COMMENT_CHAR_2.

int is_instru_valid(char c)
{
    return ((c >= 9 && c <= 13) || c == COMMENT_CHAR || c == 32);
}

int get_instruction(char *line, int *line_index, t_lexer *lexer, int *currentType)
{
    int i;
    int j;
    t_label *curr_l;
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
        while (valid_instruction[i][j] == line[*line_index + j] && line[*line_index + j])
            j++;
        if (valid_instruction[i][j] == '\0' && is_instru_valid(line[*line_index + j]))
        {
            if (lexer->label_count == 0)
                push_label(lexer, "no label");
            curr_l = lexer->label[lexer->label_count > 0 ? lexer->label_count - 1 : lexer->label_count];
            push_instruction(lexer->label[lexer->label_count > 0 ?
                lexer->label_count - 1 : lexer->label_count], NULL, Op_Code[i]);
            (*line_index)+=j;
            get_params(line, line_index, lexer, i);
            if (*currentType == IS_LABEL && lexer->label_count > 1 && curr_l->instruction_count == 1)
                compute_instru_bytes(curr_l->instruction[curr_l->instruction_count - 1],
                lexer->label[lexer->label_count - 2]->instruction[lexer->label[lexer->label_count - 2]->instruction_count - 1],
                curr_l->instruction_count - 1);
            else if (curr_l->instruction_count > 1)
                compute_instru_bytes(curr_l->instruction[curr_l->instruction_count - 1],
                    curr_l->instruction[curr_l->instruction_count - 2], curr_l->instruction_count - 1);
            else if (lexer->label_count == 1 && curr_l->instruction_count == 1)
                compute_instru_bytes(curr_l->instruction[curr_l->instruction_count - 1], NULL, 0);
            *currentType = IS_INSTRUCTION;
            return (Op_Code[i]);
        }
        i++;
    }
    return (0);
}

int is_valid_char(char c)
{
    return (ft_isalnum(c, 'l') || c == COMMENT_CHAR
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
        if ((*currentType == IS_STR_NAME && (*i + ft_strlen(lexer->header->name) >= PROG_NAME_LENGTH))
        || (*currentType == IS_STR_COMMENT && (*i + ft_strlen(lexer->header->comment) >= COMMENT_LENGTH)))
                put_parsing_error("Syntax error (header name length > 128)", lexer->current_line, *i, lexer);
        if (*currentType == IS_STR_NAME)
        {
            *currentType = (line[*i] == '"') ? IS_END_NAME : IS_STR_NAME;
            lexer->header->name = ft_strjoin(lexer->header->name, ft_strsub(line, start_idx, *i - start_idx));
            line[*i] == '"' ? (*i)++ : 0;
        }
        if (*currentType == IS_STR_COMMENT)
        {
            *currentType = (line[*i] == '"') ? IS_END_COMMENT : IS_STR_COMMENT;
            lexer->header->comment = ft_strjoin(lexer->header->comment, ft_strsub(line, start_idx, *i - start_idx));
            line[*i] == '"' ? (*i)++ : 0;
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
        if ((*currentType == IS_NAME && (*i - (start_idx + tmp + 1)) >= PROG_NAME_LENGTH) || (*currentType == IS_COMMENT && (*i - (start_idx + tmp + 1)) >= COMMENT_LENGTH))
            put_parsing_error("Syntax error (header comment length > 2048)", lexer->current_line, *i, lexer);
        if (*currentType == IS_NAME)
        {
            lexer->header->have_name = 1;
            lexer->header->name = ft_strsub(line, (start_idx + tmp + 1), *i - (start_idx + tmp + 1));
            *currentType = (line[*i] == '"') ? IS_END_NAME : IS_STR_NAME;
            (line[*i] == '"') ? (*i)++ : 0;
        }
        if (*currentType == IS_COMMENT)
        {
            lexer->header->have_comment = 1;
            lexer->header->comment = ft_strsub(line, (start_idx + tmp + 1), *i - (start_idx + tmp + 1));
            *currentType = (line[*i] == '"') ? IS_END_COMMENT : IS_STR_COMMENT;
            (line[*i] == '"') ? (*i)++ : 0;
        }
    }
    return (1);
}

// 39 vs me = 52.

void handle_instruction(char *line, t_lexer *lexer, int n_line, int *currentType)
{
    int i;
    int error;

    i = 0;
    while (line[i])
    {
        error = 0;
        //ft_printf("before boucle other: |%c|\n", line[i]);
        while (((line[i] >= 9 && line[i] <= 13) || line[i] == ' ') && line[i])
            i++;
        if (line[i] == COMMENT_CHAR)
            return ;
        if (line[i])
        {
            //ft_printf("\nbefore label: %c\n", line[i]);
            if (!get_label(line, &i, lexer, currentType))
                error += 1;
            //ft_printf("after label: |%c|\n", line[i]);
            if (error == 1)
            {
                //ft_printf("before instru: %c\n", line[i]);
                if (!get_instruction(line, &i, lexer, currentType))
                        error += 1;
                //ft_printf("\nafter instru: |%c|\n", line[i]);
            }
            if (line[i] == COMMENT_CHAR)
                return ;
            if (error == 2)
                put_parsing_error("Syntax error (no instruction or label)", n_line, i, lexer);
        }
        //ft_printf("after other: |%c|\n", line[i]);
        if (line[i] != '\0')
        {
            if (!is_valid_char(line[i]))
                put_parsing_error("Syntax error (invalid char)", n_line, i, lexer);
        }
        line[i] ? i++ : 0;
    }
}


void handle_line(char *line, t_lexer *lexer, int n_line, int *currentType)
{
    int i;

    i = 0;

    if (lexer->header->have_name && lexer->header->have_comment &&
        (*currentType == IS_END_COMMENT
            || *currentType == IS_INSTRUCTION || *currentType == IS_LABEL))
    {
        handle_instruction(line, lexer, n_line, currentType);
        return ;
    }

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
                put_parsing_error("Syntax error (header name)", n_line, i, lexer);
        }
        // plus explicite pour la taille stp + qd on a pas de pnt..+ qd on a deja un nom ou comment...
        if (!is_valid_format(line, &i, lexer, currentType))
            put_parsing_error("Syntax error (format)", n_line, i, lexer);
        if (line[i] == COMMENT_CHAR)
                return ;
        if (line[i] != '\0')
        {
            if (!is_valid_char(line[i]) && !(*currentType == IS_STR_NAME || *currentType == IS_STR_COMMENT))
                put_parsing_error("Syntax error (invalid char)", n_line, i, lexer);
        }
        line[i] ? i++ : 0;
    }
}

void parse_file(char *file, int debug_mode)
{
    int fd;
    char *line;
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
        lexer->current_line = c_line;
        handle_line(line, lexer, c_line, &currentType);
        free(line);
    }
    if (lexer->header->name == NULL || lexer->header->comment == NULL)
        put_error("Format error (no header)");
    if (lexer->label_count == 0)
        put_error("Format error (no label)");
    lexer->header->prog_size = lexer->label[lexer->label_count - 1]->instruction[
    lexer->label[lexer->label_count - 1]->instruction_count - 1]->total_byte;
    // r100 = error.
    // asm -debug [file]
    // asm [file]
    if (debug_mode)
        debug_lexer(lexer);
}
