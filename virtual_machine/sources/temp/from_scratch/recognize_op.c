#include "functions.h"

int			read_op_code(t_champion ch, t_core *core, int p)
{
	unsigned char			buf[2];
    t_vm_proc       *pr;
    int             code;

	ft_bzero(buf, 2);
 //	if ((read(ch->fd, buf, 1)) < 0)
//		return -1;    
    printf("p = %i\n", p);
    buf[0] = core->map[p];
	code = hex_to_dec(buf, 1);
    printf("buf = %s\n", buf);
    printf("code = %i\n", code);
   /* ft_putstr("\n");
    ft_putstr(buf);
    ft_putstr("read_op_code\n");
    ft_putnbr(code);
    ft_putstr("\n");
    if (code > -1 && code < 17)
    {
        pr = (t_vm_proc*)ft_memalloc(sizeof(t_vm_proc));
        pr->next_operation_code = code;
        if (code != 1 && code != 9 && code != 12 & code != 15){
            if ((read(ch->fd, buf, 2)) < 0)
		        return -2;
            if (check_codage(pr, *core, (char*)buf) != 1){
                return -2;// exit_perror("invalid codage", 4);
            }
            read_params(pr, ch->fd);
        } else {
            return 0;
        }
    }*/
    return (1);
}
