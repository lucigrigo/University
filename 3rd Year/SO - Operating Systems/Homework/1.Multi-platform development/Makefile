# Grigore Lucian-Florin
# 336CA
# Sisteme de Operare
# Tema 1 - Multi-platform development
LINK=link.exe
default=build

build: tema1.obj utils.obj hashmap.obj strtok_saved.obj
	cl.exe /Zi tema1.obj utils.obj hashmap.obj strtok_saved.obj /Feso-cpp.exe

tema1.obj: tema1.c
	cl.exe /MD /nologo /W4 /wd4996 /c tema1.c /Fotema1.obj

utils.obj: utils.c
	cl.exe /MD /nologo /W4 /wd4996 /c utils.c /Foutils.obj

hashmap.obj: hashmap.c
	cl.exe /MD /nologo /W4 /wd4996 /c hashmap.c /Fohashmap.obj

strtok_saved.obj: strtok_saved.c
	cl.exe /MD /nologo /W4 /wd4996 /c strtok_saved.c /Fostrtok_saved.obj

clean:
	del *.obj
	del so-cpp.exe
