libgetopt_portable
==================

This is a portable library, providing a function called "getopt_portable()"
which aims to provide functionality similar to an usual simple getopt
implementation.

Goals
-----
Simple and portable implementation of POSIX getopt. May be included in projects which
are supposed to work in non-POSIX environments, too.

POSIX specification of getopt():
https://pubs.opengroup.org/onlinepubs/9699919799/functions/getopt.html
POSIX Utility Syntax Guidelines:
https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap12.html#tag_12_02

Project Status
--------------
This software is under development, a work-in-progress. It is not yet stable
or suitable for general use.

Notes
-----
To prevent conflicts in naming, the function is called "getopt_portable" and
the variables "optarg", "opterr", "optind" and "optopt" are called "opt_arg",
"opt_err", "opt_ind" and "opt_opt".
