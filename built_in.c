#include "shell.h"


/**
 * _myexit - That Exit From Shell.
 * @info: The struct That used FOR Manage
 *	Steady Function Prototype.
 * Return: That will Exit When
 *	(0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exch;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exch = _erratoi(info->argv[1]);
		if (exch == -1)
		{
			info->status = 2;
			print_error(info, "Illegal Num: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - That Will Replace A Current Directory To A process.
 * @info: The struct That used FOR Manage
 *	Steady Function Prototype.
 * Return: This Will Return always 0 .
 */
int _mycd(info_t *info)
{
	char *m, *ddt, buf[1024];
	int chdir_mma;

	m = getcwd(buf, 1024);
	if (!m)
		_puts("TODO: >>getcwd Error: Unable to complete operation<<\n");
	if (!info->argv[1])
	{
		ddt = _getenv(info, "HOME=");
		if (!ddt)
			chdir_mma = /* TODO: Oh What Should This Be? */
				chdir((ddt = _getenv(info, "PWD=")) ? ddt : "/");
		else
			chdir_mma = chdir(ddt);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(m);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_mma = /* TODO: Oh What Should This Be? */
			chdir((ddt = _getenv(info, "OLDPWD=")) ? ddt : "/");
	}
	else
		chdir_mma = chdir(info->argv[1]);
	if (chdir_mma == -1)
	{
		print_error(info, "Can Not Get In to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buf, 1024));
	}
	return (0);
}

/**
 * _myhelp - That Will Replace A Current Directory To A process.
 * @info: The struct That used FOR Manage
 *	Steady Function Prototype.
 * Return: This Will Return always 0 .
 */
int _myhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("Help function is active, requested operation not supported \n");
	if (0)
		_puts(*arg_arr);

	return (0);
}
