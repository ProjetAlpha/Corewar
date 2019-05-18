/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 18:30:52 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:31:52 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H

#define ASM_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "printf.h"
#include "op.h"


enum s_type
{
    DIRECT = 1,
    INDIRECT = 2,
    REGISTER = 3,
    LABEL_REF = 4
};

enum s_label_type
{
    IS_NAME = 1,
    IS_COMMENT = 2,
    IS_STR_NAME = 3,
    IS_STR_COMMENT = 4,
    IS_END_NAME = 5,
    IS_END_COMMENT = 6,
    IS_BASIC_LABEL = 7,
    IS_LABEL = 8,
    IS_INSTRUCTION = 9
};

typedef enum e_opcode
{
    LIVE_CODE = 0x01,
    LD_CODE = 0x02,
    ST_CODE = 0x03,
    ADD_CODE = 0x04,
    SUB_CODE = 0x05,
    AND_CODE = 0x06,
    OR_CODE = 0x07,
    XOR_CODE = 0x08,
    ZJMP_CODE = 0x09,
    LDI_CODE = 0x0a,
    STI_CODE = 0x0b,
    FORK_CODE = 0x0c,
    LLD_CODE = 0x0d,
    LLDI_CODE = 0x0e,
    LFORK_CODE = 0x0f,
    AFF_CODE = 0x10
}           t_OpEnum;

static const t_OpEnum Op_Code[] = {
    LIVE_CODE, LD_CODE, ST_CODE, ADD_CODE, SUB_CODE,
    AND_CODE, OR_CODE, XOR_CODE, ZJMP_CODE, LDI_CODE,
    STI_CODE, FORK_CODE, LLD_CODE, LLDI_CODE, LFORK_CODE, AFF_CODE
};


// les infos jusqu'au premier label = putcharfd:

// 1er corewar_magic.
// 2eme progname.
// 3eme progsize.
// 4eme comments.

// direct = 2 octets | indirecte = 4 octets.
// si octet de codage

typedef struct  s_header
{
    long corewar_magic;
    char *name;
    int dMaxProgName;
    long progsize; // nombre total d'octets.
    char *comment;
    int dMaxComments;
    int have_name;
    int have_comment;
    // corewar_magic = 4 octets = 00 ea 83 f3
    // progname = 1 char = 1 octet -- max = 128 char.
    // progsize = code sur 8 octets = nOctets.
    // comments = 2048 max
}               t_header;

typedef struct s_param
{
    // 2 octets ou 4 octets
    int n_octets;
    int type; // direct, indirecte, register, LABEL_REF(conv en char *, sinon en int).
    void *value; // str || int
}              t_param;

// label[i]->instructions[i]->param[i]...

typedef struct s_instruction
{
    int n_octets; // opcode + 1 (si octet de codage) + total params --> nOctets
    int type;
    int have_index;
    int param_count;
    unsigned char params_octet;
    unsigned char value;
    t_param **param;
}              t_instruction;

typedef struct  s_label
{
    int n_octets; // ==> total des nOctets instructions.
    int label_count;
    int instruction_count;
    char *name;
    t_instruction **instruction;
}               t_label;

typedef struct  s_lexer
{
    t_header *header;
    int label_count;
    t_label  **label;
}               t_lexer;

void put_error(char *str);
void put_parsing_error(char *str, int n_line, int pos_line);
void check_file_extension(char *file);
t_header *init_header(void);
t_param *init_param(void);
t_instruction *init_instruction(void);
t_label *init_label(void);
t_lexer *init_lexer(void);
void parse_file(char *file);

#endif
