#include <unistd.h>
int	main()
{
	char str[20];
	*str = '\0';
	while (read(0,str, 10))
	{
		write(1,(const void*)'\n',1);
		write(1,str,50);
		*str = '\0';
	}
	
}