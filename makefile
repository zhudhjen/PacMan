CC = wcc
# CFLAGS = -zq
LINKER = wlink
LFLAGS = option quiet

OBJS = ai.obj fool.obj testmain.obj

.c.obj : .autodepend
    $(CC) $<

test.exe : $(OBJS)
    $(LINKER) $(LFLAGS) name $@ file { $< }