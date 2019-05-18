/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 18:22:56 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 18:24:30 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"
// 1er corewar_magic.
// 2eme progname.
// 3eme progsize.
// 4eme comments.

// suivi par des 00 00 --- wtf is this ?

// Instructions :
// [op_code] [description] [params]
// params :
// - r1 = 01, r6 = 06 ...
// - %[digit] = code sur 4 octets
// -

//arriere : ff e6

// :%label X : adresse du premier octet de label X (apres op code).
// ff e6 = -26.
// ff = 250 => -1
// e6 = 230.
// d0 = 208
// -26 = position du label. XcurrentPosition(n octet) - posXlabel jusque au premier octet (apres op code)
// ou XcurrentPosition + posXlabel.
// si le label est apres :
// - XcurrentPosition du premier octet de la current line + posX du 1er octet du label.
// si le label est avant :
// - XcurrentPosition(n octet) - posXlabel du premier octet.
// si le label est avant : currpos(n octet) - pos du premier octet du label X.
// si le label est apres : (currPos{n octets} + 2) + nb octets jusqu'au premier octet du label X.
// ( 17 - 2 ) = 15.
// pos 1 er octet = 17. 17 - 2 (1 octet op code + 1 octet op code).
// si avant la label : ( Xpos 1er octet label - Xpos 1er octet la ligne courante ) = res;
// si apres le label : ( Xpos 1er octet la ligne courante - Xpos 1er octet label) = res;

int main(int argc, char **av)
{
	if (argc != 2)
		put_error("Invalid numbers of arguments.");
	check_file_extension(av[1]);
	parse_file(av[1]);
}
