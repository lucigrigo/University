# Grigore Lucian-Florin - 336CA - SO Tema 4 Windows
build: so_scheduler.obj
	link /DEBUG /nologo /dll /out:libscheduler.dll so_scheduler.obj

so_scheduler.obj: so_scheduler.c
	cl /Zi /nologo /W3 /DDLL_EXPORTS /MD /D_CRT_SECURE_NO_WARNINGS /c so_scheduler.c

clean:
	del so_scheduler.obj
	del libscheduler.dll