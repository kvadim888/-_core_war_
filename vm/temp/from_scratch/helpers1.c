#include "functions.h"


char      *remove_spaces(char *s, int len){
    char *ns;
    int sp;
    int i;

    i = -1;
    sp = 0;
    ns = (char*)ft_memalloc(sizeof(char) * len + 1);
    ns = ft_memalloc(sizeof(char) * ft_strlen(s));
    while (s[++i])
    {
        if (s[i] == ' ')
        {
            sp++;
        }
        ns[i] = s[i + sp];
    }
    return ns;  
}


char    **get_quads(){
    char **quads;

    quads = (char **)ft_memalloc(sizeof(char*) * 16);
    quads[0] = "0000\0";
	quads[1] = "0001\0";
	quads[2] = "0010\0";
	quads[3] = "0011\0";
	quads[4] = "0100\0";
	quads[5] = "0101\0";
	quads[6] = "0110\0";
	quads[7] = "0111\0";
	quads[8] = "1000\0";
	quads[9] = "1001\0";
	quads[10] = "1010\0";
	quads[11] = "1011\0";
	quads[12] = "1100\0";
	quads[13] = "1101\0";
	quads[14] = "1110\0";
	quads[15] = "1111\0";
	return (quads);
}


char    *hex_to_bin(unsigned char c)
{
    char    **quads;

    quads = get_quads();
  if (c >= '0' && c <= '9') {
  	return quads[(int)c - (int)'0'];
  }
  if (c >= 'A' && c <= 'F') {
  	return quads[10 + (int)c - (int)'A'];
  }
  if (c >= 'a' && c <= 'f') {
  	return quads[10 + (int)c - (int)'a'];
  }
  return NULL;
}


int				hex_to_dec(unsigned char *buf, int i)
{
	int res;

	res = 0;
	if (!i)
		return (0);
    if (i == 4)
	{
		res += buf[0] * 16777216;
		res += buf[1] * 65536;
		res += buf[2] * 256;
		res += buf[3];
	} else 
    {
	    if (i == 2)
	    {
		    res += buf[0] * 256;
		    res += buf[1];
        } else 
           res += buf[0];
		res = (short)res;
	}
	return (res);
}


