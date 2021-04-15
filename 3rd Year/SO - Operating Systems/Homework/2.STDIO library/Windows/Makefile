# Grigore Lucian-Florin 336 CA SO Tema 2 Windows
build: so_stdio.obj
	link /DEBUG /nologo /dll /out:so_stdio.dll so_stdio.obj

so_stdio.obj: so_stdio.c
	cl /Zi /nologo /W3 /DDLL_EXPORTS /MD /D_CRT_SECURE_NO_WARNINGS /c so_stdio.c

clean:
	del so_stdio.obj
	del so_stdio.dll
