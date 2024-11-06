# ----------------------------
# Makefile Options
# ----------------------------

NAME = TriSolve
ICON = Icon_1.png
DESCRIPTION = "This program helps you solve missing parts of a triangle,Made By Isaac Ruiz Kahle"
COMPRESSED = YES
COMPRESSED_MODE = zx0
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz



# ----------------------------

include $(shell cedev-config --makefile)

