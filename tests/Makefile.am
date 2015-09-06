## Process this file with automake to produce Makefile.in

TESTS = check_tokenizer
check_PROGRAMS = check_tokenizer
check_tokenizer_SOURCES = check_tokenizer.c $(top_builddir)/src/tokenizer.h
check_tokenizer_CFLAGS = @CHECK_CFLAGS@
check_tokenizer_LDADD = $(top_builddir)/src/libtokenizer.la @CHECK_LIBS@
