TEST_LOG_DRIVER = env AM_TAP_AWK='$(AWK)' $(SHELL) \
                  $(top_srcdir)/build-aux/tap-driver.sh

AM_TESTS_ENVIRONMENT = CRITERION_OUTPUTS='tap:-'; \
                       export CRITERION_OUTPUTS; \
                       CRITERION_VERBOSITY_LEVEL=2; \
                       export CRITERION_VERBOSITY_LEVEL;

check_PROGRAMS = basic_tests

basic_tests_SOURCES = basic_tests.c
basic_tests_CFLAGS = $(CRITERION_CFLAGS)
basic_tests_LDADD = $(top_builddir)/src/libdstring.la
basic_tests_LDFLAGS = $(CRITERION_LIBS)

TESTS = basic_tests
