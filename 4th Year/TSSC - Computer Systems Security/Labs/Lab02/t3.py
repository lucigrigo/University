txt = 'wAyk{mmAwjAuwpz\x7fAwmAqjn'

def convert(c, i):
	return chr(ord(c) ^ i)
	
for i in range(0, 40):
	print(''.join([convert(c, i) for c in txt]))
