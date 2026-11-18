# PSL1GHT build template. Requires a configured PS3DEV + PSL1GHT toolchain.
include $(PSL1GHT)/ppu_rules

TARGET       := EBOOT
TITLE        := Horizon PS3 Test Client
CONTENT_ID   := UP0001-HORIZONPS300_00-0000000000000000

SOURCES      := source/main.c
INCDIR       :=
LIBS         := -ltiny3d -lfreetype -lfont -lio -lsysutil

# ppu_rules supplies the ELF/SELF rules. Packaging support depends on the
# installed PSL1GHT distribution; run `make pkg` if that target is provided.
