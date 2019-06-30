#include "functions.h"



//main__________________________________________________________________________
int     main(int ac, char**av)
{   
    t_core core; 
    //core  = (t_core)ft_memalloc(sizeof(t_core));

    read_params(ac, av, &core);
    printf("-------------------------------------\n");
    create_map(&core);
    printf("-------------------------------------\n");
    cycle(&core);

    return (0);
}