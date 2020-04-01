/*
 * libgetopt_portable - portable implementation of POSIX getopt
 * Copyright (C) 2019-2020 Robert Imschweiler
 * 
 * This file is part of libgetopt_portable.
 * 
 * libgetopt_portable is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * libgetopt_portable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with libgetopt_portable.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libgetopt_portable.h"


/* internal functions */
static void err(const char *format, ...);
static void err_no_arg(char *prog_name, int opt);
static void err_no_opt(char *prog_name, int opt);
static int  is_end_of_options(const char *str);
static int  is_opt(const char *str);

/* global variables */
static int old_optind = 1;
static int optstring_startet_with_colon = 0;

/* definition of extern variables */
char *opt_arg = NULL;
int opt_err = 1;
int opt_ind = 1;
int opt_opt = '?';


void
err(const char *format, ...)
{
	va_list args;

	if (!opt_err || optstring_startet_with_colon)
		return;

	if (format) {
		va_start(args, format);
		vfprintf(stderr, format, args);
		fputc('\n', stderr);
		va_end(args);
	}
}

void
err_no_arg(char *prog_name, int opt)
{
	err("%s: option requires an argument -- '%c'", prog_name, opt);
}

void
err_no_opt(char *prog_name, int opt)
{
	err("%s: invalid option -- '%c'", prog_name, opt);
}

int
is_end_of_options(const char *str)
{
	return !strcmp(str, "--");
}

int
is_opt(const char *str)
{
	return (strlen(str) > 1 && *str == '-' && *++str != '-');
}

static int
parse(int argc, char * const argv[], const char *optstring)
{
	static char *next = NULL;
	char opt, *tmp;

	if (!argv[opt_ind]) {
		return -1;
	} else if (is_end_of_options(argv[opt_ind])) {
		opt_ind++;
		return -1;
	} else if (!is_opt(argv[opt_ind])) {
		return -1;
	}

	/* remember to skip leading dash */
	if (!next || opt_ind != old_optind)
		next = argv[opt_ind]+1;

	opt = *next;
	next = *(next+1) ? next+1 : NULL;

	tmp = strchr(optstring, opt);
	if (!tmp) {
		opt_opt = opt;
		err_no_opt(argv[0], opt);
		return '?';
	}

	if (*(tmp+1) != ':') {
		/* do not increment opt_ind if there are grouped options */
		if (!next)
			opt_ind++;
		return opt;
	}
	opt_ind++;

	if (next) {
		opt_arg = next;
		next = NULL;
	} else if (++opt_ind <= argc) {
		opt_arg = argv[opt_ind-1];
	} else {
		opt_opt = opt;
		err_no_arg(argv[0], opt);
		return optstring_startet_with_colon ? ':' : '?';
	}

	return opt;
}

int
getopt_portable(int argc, char * const argv[], const char *optstring)
{
	char opt;

	if (!opt_ind || opt_ind >= argc || (opt_err != 0 && opt_err != 1))
		return -1;

	/* reset */
	opt_arg = NULL;
	opt_opt = '?';
	
	if (*optstring == ':') {
		optstring_startet_with_colon = 1;
		optstring++;
	}

	opt = parse(argc, argv, optstring);

	old_optind = opt_ind;

	return opt;
}

