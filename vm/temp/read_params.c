#include "functions.h"

int     read_reg(int fd)
{
    uint8_t			buf[2];

    if ((read(fd, buf, 2)) < 0){
       return (-1);//exit_perror("?", 4);
    }
    return (hex_to_dec((char*)buf));
}

int     read_dir(int fd, int dir_number)
{ 
    uint8_t			buf[dir_number * 2];

    if ((read(fd, buf, dir_number * 2)) < 0){
         return (-1);//exit_perror("?", 4);
    }
    return (hex_to_dec((char*)buf));
}

int     read_ind(int fd)
{
    uint8_t			buf[4];

    if ((read(fd, buf, 2)) < 0){
        return (-1);//exit_perror("?", 4);
    }
    return (hex_to_dec((char*)buf));
}

int        read_params(t_vm_proc *pr, int fd)
{
    int temp;
    int dn;

    if ((pr)->param_type_1 == 'r'){
        temp = read_reg(fd);
        (pr)->param_value1 = temp;
    } else if ((pr)->param_type_1 == 'd'){
        if (((pr)->next_operation_code > 8 && (pr)->next_operation_code < 13) ||
        ((pr)->next_operation_code > 13 && (pr)->next_operation_code < 16)){
            dn = 2;
        } else {
            dn = 4;
        }
        temp = read_dir(fd, dn);
        (pr)->param_value1 = temp;
    } else if ((pr)->param_type_1 == 'i'){
        temp = read_ind(fd);
        (pr)->param_value1 = temp;
    }
    return (temp);
}
