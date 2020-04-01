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

int getopt_portable(int argc, char * const argv[], const char *optstring);
extern char *opt_arg;
extern int opt_err;
extern int opt_ind;
extern int opt_opt;

