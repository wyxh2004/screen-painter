C_SOURCE_FILES += $(wildcard ./src/*.c)
C_SOURCE_FILES += $(wildcard ./adaptor/sdl/*.c)

C_INCLUDES += ./src ./include ./adaptor/sdl

include ./cc-with-test.mk
