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
	int extchk;

	if (info->argv[1])
	{

		extchk = _erratoi(info->argv[1]);
		if (extchk == -1)
		{
			info->status = 2;
			print_error(info, "An Illegal num: ");
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
	char *c, *dr, buf[1024];
	int cdi_rt;

	c = getcwd(buf, 1024);
	if (!c)
		_puts("TODO: >>Getcwd Failure Emsg Here<<\n");
	if (!info->argv[1])
	{
		dr = _getenv(info, "HOME=");
		if (!dr)
			cdi_rt = /* TODO: What Should That Be? */
				chdir((dr = _getenv(info, "PWD=")) ? dr : "/");
		else
			cdi_rt = chdir(dr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		cdi_rt = /* TODO: What Should That Be? */
			chdir((dr = _getenv(info, "OLDPWD=")) ? dr : "/");
	}
	else
		cdi_rt = chdir(info->argv[1]);
	if (cdi_rt == -1)
	{
		print_error(info, "Can Not Cd To ");
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
	char **rg_arr;

	rg_arr = info->argv;
	_puts("The Help Call Works. A Function Not Implemented Yet\n");

	if (0)
		_puts(*rg_arr);

	return (0);
}
