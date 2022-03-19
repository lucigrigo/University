with open('isc-lab02-encrypted.bmp', 'rb') as f:
	import os
	dest = open('img.bmp', 'wb')
	for idx, line in enumerate(f):
		if idx == 0:
			dest.write('42 4D 66 CA D7 00 00 00 00 00 36 00 00 00 28 00 00 00 D0 07 00 00 35 09 00 00 01 00 18 00 00 00 00 00 30 CA D7 00 74 12 00 00 74 12 00 00 00 00 00 00 00 00 00 00' + os.linesep)
			continue
		dest.write(line + os.linesep)
