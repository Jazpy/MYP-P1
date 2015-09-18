## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libmain_check.la
libmain_check_la_SOURCES = tokenizer.c tokenizer.h grammar_checker.c grammar_checker.h shunting_yard.c shunting_yard.h binary_tree.c binary_tree.h linked_list.c linked_list.h view.c view.h

bin_PROGRAMS = main
main_SOURCES = main.c
AM_CPPFLAGS = ${GTK_CFLAGS}
main_LDADD = ${GTK_LIBS} libmain_check.la
