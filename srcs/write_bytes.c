/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   write_bytes.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/27 17:27:37 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/27 17:58:33 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

char  *create_path(char *file)
{
    char *path;
    int i;
    int len;

    i = -1;
    len = ft_strlen(file);
    path = ft_memalloc(ft_strlen(file) + 4);
    while (++i < len - 2)
        path[i] = file[i];
    path[i++] = '.';
    path[i++] = 'c';
    path[i++] = 'o';
    path[i++] = 'r';
    return (path);
}

t_label *find_label(t_lexer *lexer, void *value)
{
    int i;
    t_label *label;

    label = NULL;
    i = -1;
    while (++i < lexer->label_count)
    {
        if (!ft_strcmp((char*)(lexer->label[i]->name), (char*)value))
            label = lexer->label[i];
    }
    if (!label)
        put_error("label not found");
    if (!label->instruction_count)
        put_error("Not a valid label addresse");
    return (label);
}

void  check_labels_ref(t_lexer *lexer)
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
            k = -1;
            while (++k < lexer->label[i]->instruction[j]->param_count)
            {
                if (lexer->label[i]->instruction[j]->param[k]->type & IS_REF)
                    find_label(lexer, lexer->label[i]->instruction[j]->param[k]->value);
            }
        }
    }
}

void put_bytes(int fd, int value, int len)
{
    unsigned char o1;
    unsigned char o2;
    unsigned char o3;
    unsigned char o4;

    o1 = (value >> 24) & 0xff;
    o2 = (value >> 16) & 0xff;
    o3 = (value >> 8) & 0xff;
    o4 = value & 0xff;

    if (len == 1)
        ft_putchar_fd(o4, fd);
    if (len == 2)
    {
        ft_putchar_fd(o3, fd);
        ft_putchar_fd(o4, fd);
    }
    if (len == 4)
    {
        ft_putchar_fd(o1, fd);
        ft_putchar_fd(o2, fd);
        ft_putchar_fd(o3, fd);
        ft_putchar_fd(o4, fd);
    }
}

void put_header_bytes(int fd, t_header *header)
{
    int i;
    int len;

    i = -1;
    put_bytes(fd, header->corewar_magic, 4);
    len = ft_strlen(header->name);
    while (++i < len)
        ft_putchar_fd(header->name[i], fd);
    i = -1;
    len = PROG_NAME_LENGTH - len;
    while (++i < len)
        ft_putchar_fd('\0', fd);
    i = -1;
    while (++i < 8)
        ft_putchar_fd((unsigned char)((header->prog_size >> (56 - (8 * i))) & 0xff), fd);
    i = -1;
    len = ft_strlen(header->comment);
    while (++i < len)
        ft_putchar_fd(header->comment[i], fd);
    i = -1;
    len = (COMMENT_LENGTH - len) + 4;
    while (++i < len)
        ft_putchar_fd('\0', fd);
}

void put_param_bytes(int fd, t_param *param, t_lexer *lexer, int curr_addr)
{
    int label_pos;

    label_pos = 0;
    if ((param->type & DIR2) && !(param->type & IS_REF))
        put_bytes(fd, ft_atoi((char*)param->value), 2);
    if ((param->type & DIR4) && !(param->type & IS_REF))
        put_bytes(fd, ft_atoi((char*)param->value), 4);
    if ((param->type & T_IND) && !(param->type & IS_REF))
        put_bytes(fd, ft_atoi((char*)param->value), 2);
    if (param->type & T_REG)
        put_bytes(fd, ft_atoi((char*)param->value), 1);
    // si posX > label_posX => posX - label_posX --- else label_posX - posX.
    //
    if (param->type & IS_REF)
    {
        label_pos = find_label(lexer, (char*)param->value)->instruction[0]->addr_pos;
        if (param->type & DIR2)
            put_bytes(fd, label_pos - curr_addr, 2);
        if (param->type & DIR4)
            put_bytes(fd, label_pos - curr_addr, 4);
        if (param->type & T_IND)
            put_bytes(fd, label_pos - curr_addr, 2);
    }
}

// 01 = 1 = REG.
// 10 = 2 = DIR.
// 11 = 3 = IND
void put_opcode(int fd, t_param **param, int param_count)
{
    int i;
    unsigned char code;

    code = 0;
    i = -1;
    while (++i < param_count)
    {
        if (param[i]->type & DIR2 || param[i]->type & DIR4)
            code |= (2 << (3 - i) * 2);
        if (param[i]->type & T_IND)
            code |= (3 << (3 - i) * 2);
        if (param[i]->type & T_REG)
            code |= (1 << (3 - i) * 2);
    }
    ft_putchar_fd(code, fd);
}

void write_bytes(t_lexer *lexer, char *file)
{
    int i;
    int j;
    int k;
    int fd;
    char *path;

    check_labels_ref(lexer);
    path = create_path(file);
    fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd < 0)
        put_error(strerror(errno));
    put_header_bytes(fd, lexer->header);
    i = -1;
    while (++i < lexer->label_count)
    {
        j = -1;
        while (++j < lexer->label[i]->instruction_count)
        {
            put_bytes(fd, lexer->label[i]->instruction[j]->value, 1);
            k = -1;
            if (lexer->label[i]->instruction[j]->value != LIVE_CODE
                && lexer->label[i]->instruction[j]->value != ZJMP_CODE
                && lexer->label[i]->instruction[j]->value != AFF_CODE
                && lexer->label[i]->instruction[j]->value != FORK_CODE)
            put_opcode(fd, lexer->label[i]->instruction[j]->param, lexer->label[i]->instruction[j]->param_count);
            while (++k < lexer->label[i]->instruction[j]->param_count)
                put_param_bytes(fd, lexer->label[i]->instruction[j]->param[k], lexer, lexer->label[i]->instruction[j]->addr_pos);
        }
    }
    ft_printf("Writing output to %s\n", path);
}
