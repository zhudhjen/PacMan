CC = wcc386
LINKER = wlink
LFLAGS = option quiet

OBJS = ai.obj fool.obj normal.obj expert.obj draw.obj main.obj

.c.obj : .autodepend
    $(CC) $(CFLAGS) $<

pacman.exe : $(OBJS)
    $(LINKER) $(LFLAGS) name $@ file { $< }