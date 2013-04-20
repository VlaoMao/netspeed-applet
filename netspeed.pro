TEMPLATE = subdirs
SUBDIRS = \
	  src \
	  translations

QMAKE_CLEAN += \
	      build-stamp \
	      configure-stamp \
	      timed.log
