#include "vm.h"

t_list		*carriage_filter(t_list *lst)
{
    t_list		head;
    t_list		*prev;
    t_carriage	*carriage;

    head.next = lst;
    prev = &head;
    while (lst)
    {
        carriage = lst->content;
        if (carriage->live <= 0)
        {
            prev->next = lst->next;
            ft_lstdelone(&lst, ft_lstrm);
            lst = prev->next;
        }
        else
        {
            prev = lst;
            lst = lst->next;
        }
    }
    return (head.next);
}

t_champion	*game_loop()
{
    while (g_game.carriages && ft_lstlen(g_game.carriages))
    {
        g_game.cycle_counter++;
        g_game.check_counter++;
        ft_lstiter(g_game.carriages, exec_function);
        if (g_game.check_counter >= g_game.check_period)
        {
            g_game.check_counter = 0;
            g_game.check_amount++;
            g_game.carriages = carriage_filter(g_game.carriages);
            if (g_game.check_amount == MAX_CHECKS ||
                g_game.live_counter >= NBR_LIVE)
                g_game.check_period -= (g_game.check_period > 0)
                                        ? CYCLE_DELTA : 0;
        }
        if (g_game.dump_counter >= g_game.dump_period)
        {
            log_field(32); //todo log_mode
            exit(0);
        }
        if (g_game.show_counter >= g_game.show_period)
            log_field(32); //todo log_mode
    }
    return (g_game.survivor);
}

void	field_init()
{
    int			len;
    t_list		*tmp;
    t_champion	*champ;
    t_carriage	carriage;

    ft_bzero(g_game.field, MEM_SIZE);
    len = ft_lstlen(g_game.players);
    carriage = (t_carriage){.carry = 0, .live = 0, .rest = 0};
    ft_bzero(&carriage.operation, sizeof(t_operation));
    tmp = g_game.players;
    while (tmp)
    {
        champ = tmp->content;
        carriage.id = champ->number;
        carriage.reg[0] = -champ->number;
        carriage.pos = (carriage.id - 1) * (MEM_SIZE / len);
        ft_memcpy(g_game.field + carriage.pos,
                  champ->code, champ->header->prog_size);
        ft_lstadd(&g_game.carriages, ft_lstnew(&carriage, sizeof(t_carriage)));
        tmp = tmp->next;
    }
}
