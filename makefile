CC = wcc386
LINKER = wlink
LFLAGS = option quiet

OBJS = ai.obj fool.obj normal.obj testmain.obj

.c.obj : .autodepend
    $(CC) $(CFLAGS) $<

test.exe : $(OBJS)
    $(LINKER) $(LFLAGS) name $@ file { $< }