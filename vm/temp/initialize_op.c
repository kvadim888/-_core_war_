#include "functions.h"

void		init_live(t_core *core)
{
    (*core).oper[0].label = "live"; 
    (*core).oper[0].function = &live;
    (*core).oper[0].cycle_value = 10;
    (*core).oper[0].dir_number = 4;
    (*core).oper[0].check = NULL;

}

void		init_ld(t_core *core)
{
    (*core).oper[1].label = "ld"; 
    (*core).oper[1].function = &ld;
    (*core).oper[1].cycle_value = 5;
    (*core).oper[1].dir_number = 4;
    (*core).oper[1].check = &c_di_r;
}

void		init_st(t_core *core)
{
    (*core).oper[2].label = "st"; 
    (*core).oper[2].function = &st;
    (*core).oper[2].cycle_value = 5;
    (*core).oper[2].dir_number = 4;
    (*core).oper[2].check = &c_r_ri;
}

void		init_add(t_core *core)
{
    (*core).oper[3].label = "add"; 
    //(*core).oper[3].function = &st;
    (*core).oper[3].cycle_value = 5;
    (*core).oper[3].dir_number = 4;
    (*core).oper[3].check = &c_r_ri;
}

void		init_sub(t_core *core)
{
    (*core).oper[4].label = "sub"; 
   // (*core).oper[4].function = &st;
    (*core).oper[4].cycle_value = 5;
    (*core).oper[4].dir_number = 4;
    (*core).oper[4].check = &c_r_ri;
}
