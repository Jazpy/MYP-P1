## Process this file with automake to produce Makefile.in

TESTS = check_main_check
check_PROGRAMS = check_main_check
check_main_check_SOURCES = check_main_check.c $(top_builddir)/src/tokenizer.h
check_main_check_CFLAGS = @CHECK_CFLAGS@
check_main_check_LDADD = $(top_builddir)/src/libmain_check.la @CHECK_LIBS@
