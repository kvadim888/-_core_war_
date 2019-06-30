#include "functions.h"

int        write_to_map(t_core *core, int n, int s, int d){
    unsigned char	buf[CHAMP_MAX_SIZE+ 1];

    int i;
    t_vm_proc proc;
     printf("s: %i\n", s);
    proc.carry = s - 1;
    proc.next = NULL;
    proc.cycle_exec = 0;
    proc.cycles_for_operation = 0;
    core->chmps[n].processes = &proc;
    ft_bzero(buf, CHAMP_MAX_SIZE + 2);
    i = -1;
    printf("ch read name: %s\n", core->chmps[n].name);
    if (read(core->chmps[n].fd, buf, CHAMP_MAX_SIZE) < 0)
		return 0;
    while (buf[++i]){
        core->map[i + s] = buf[i];
        s++;
    }
unsigned char	buf2[1];
buf2[0] = core->map[0];
       printf("ch read 1111 %i\n", hex_to_dec(buf2, 1));
    while (s++ < d){
        core->map[i] = 0;
    }
     return (1);
}

int		create_map(t_core *core)
{
    int d;
    int i;
    int k;

    d = 0;
    i = -1;
    while (++i < core->ch_number) {
        if (!write_to_map(core, i, d, d + MEM_SIZE / core->ch_number))
            return (0);
        d += MEM_SIZE / core->ch_number;
    }
    printf("Map : %s\n", core->map);
    unsigned char	buf[2 + 1];
    buf[0] = core->map[0];
    buf[1] = core->map[1];
    buf[2] = '\0';
    printf("test to dec : %i\n",  hex_to_dec(buf, 2));
    return (1);
}