#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([dstring], [0.1.0], [contact.melephas@gmail.com])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/dstring.c])
AC_CONFIG_HEADERS([include/config.h])

AM_INIT_AUTOMAKE([foreign dist-xz no-dist-gzip -Wall])
LT_PREREQ([2.4.6])
AM_PROG_AR
LT_INIT

# Checks for programs.
AC_PROG_AWK
AC_PROG_MAKE_SET
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([CRITERION], [criterion], [], [
    AC_MSG_ERROR([unable to find Criterion])
])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h string.h errno.h stdio.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT64_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strerror calloc free memcpy exit])

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_FILES([Makefile src/Makefile include/Makefile tests/Makefile])

AC_REQUIRE_AUX_FILE([tap-driver.sh])
AC_OUTPUT
