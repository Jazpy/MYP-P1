ACLOCAL_AMFLAGS = -I m4
AUTOMAKE_OPTIONS = subdir-objects

AM_CFLAGS = -std=c99 -D_GNU_SOURCE -Wall $(CFLAGS) -I$(top_srcdir)/lib
AM_CPPFLAGS = ${GTK_CFLAGS}
AM_LDFLAGS = -lrt -lm $(LDFLAGS)

noinst_LTLIBRARIES = lib/libedd.la

END_LIST =

lib_libedd_la_SOURCES =		\
	src/tokenizer.c		\
	src/tokenizer.h		\
	src/binary_tree.c	\
	src/binary_tree.h	\
	src/shunting_yard.h	\
	src/shunting_yard.c	\
	src/linked_list.h	\
	src/linked_list.c	\
	src/grammar_checker.h	\
	src/grammar_checker.c	\
	src/view.h		\
	src/view.c		
	$(END_LIST)

bin_PROGRAMS = src/main

src_main_LDADD = ${GTK_LIBS} $(top_builddir)/lib/libedd.la $(AM_LDFLAGS)
src_main_CFLAGS = $(AM_CFLAGS)
src_main_SOURCES = src/main.c

TESTS = 				\
	tests/test-main			\
	$(END_LIST)

check_PROGRAMS = $(TESTS)

TEST_CFLAGS = $(AM_CFLAGS) @CHECK_CFLAGS@
TEST_LDADD = $(top_builddir)/lib/libedd.la @CHECK_LIBS@ $(AM_LDFLAGS)

tests_test_main_SOURCES = tests/test-main.c
tests_test_main_CFLAGS = $(TEST_CFLAGS)
tests_test_main_LDADD = $(TEST_LDADD)

EXTRA_DIST = doc/edd.dox doc/logo-cc.png

if HAVE_DOXYGEN
docs:
	cd $(top_srcdir)/doc && doxygen

docs-pdf: docs
	cd $(top_srcdir)/doc/latex && make
else
docs:
	echo "No se encontró doxygen: la documentación no puede generarse.";

docs-pdf: docs
endif

clean-local: clean-docs

clean-docs:
	rm -rf $(top_srcdir)/doc/html $(top_srcdir)/doc/latex

dist-hook:
	cd $(top_srcdir) && git log --no-color --stat --name-only --date=short --abbrev-commit > ${srcdir}/ChangeLog
