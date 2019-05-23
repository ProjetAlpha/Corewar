/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_struct.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/17 13:58:20 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 13:58:22 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include "asm.h"

t_header *init_header(void)
{
    t_header *header;

    if (!(header = malloc(sizeof(t_header))))
        put_error("malloc error");
    header->corewar_magic = COREWAR_EXEC_MAGIC;
    header->name = NULL;
    header->have_name = 0;
    header->have_comment = 0;
    header->dMaxProgName = 0;
    header->progsize = 0;
    header->comment = NULL;
    header->dMaxComments = 0;
    return (header);
}

t_param *init_param(void)
{
    t_param *param;

    if (!(param = malloc(sizeof(t_param))))
        put_error("malloc error");
    param->n_octets = 0;
    param->type = 0;
    param->value = NULL;
    return (param);
}

t_instruction *init_instruction(void)
{
    t_instruction *instruction;

    if (!(instruction = malloc(sizeof(t_instruction))))
        put_error("malloc error");
    instruction->n_octets = 0;
    instruction->type = 0;
    instruction->have_index = 0;
    instruction->params_octet = 0;
    instruction->param_count = 0;
    instruction->value = 0;
    instruction->param = NULL;
    return (instruction);
}

t_label *init_label(void)
{
    t_label *label;

    if (!(label = malloc(sizeof(t_label))))
        put_error("malloc error");
    label->n_octets = 0;
    label->instruction_count = 0;
    label->name = NULL;
    label->instruction = NULL;
    return (label);
}

t_lexer *init_lexer(void)
{
    t_lexer *lexer;

    if (!(lexer = malloc(sizeof(t_lexer))))
        put_error("malloc error");
    lexer->header = init_header();
    lexer->label_count = 0;
    lexer->current_line = 0;
    lexer->param_count = 0;
    lexer->label = NULL;
    return (lexer);
}
