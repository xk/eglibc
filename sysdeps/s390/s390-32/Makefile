pic-ccflag = -fpic

ifeq ($(subdir),gmon)
sysdep_routines += s390-mcount
endif

ifeq ($(subdir),elf)
CFLAGS-rtld.c += -Wno-uninitialized -Wno-unused
CFLAGS-dl-load.c += -Wno-unused
CFLAGS-dl-reloc.c += -Wno-unused
endif

ifeq ($(subdir),csu)
ifeq (yes,$(build-shared))
# Compatibility
sysdep_routines += libgcc-compat
shared-only-routines += libgcc-compat
endif
endif
