#
# Component Makefile
#

COMPONENT_ADD_INCLUDEDIRS := .
COMPONENT_ADD_INCLUDEDIRS += ../freertos/include/freertos/

COMPONENT_SRCDIRS := src wolfcrypt/src

CFLAGS += -DWOLFSSL_USER_SETTINGS

COMPONENT_OBJEXCLUDE := wolfcrypt/src/aes_asm.o
COMPONENT_OBJEXCLUDE += wolfcrypt/src/evp.o
COMPONENT_OBJEXCLUDE += wolfcrypt/src/misc.o
COMPONENT_OBJEXCLUDE += src/bio.o
