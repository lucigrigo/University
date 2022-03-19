def decrypt(key, data):
	iv = b'\x00' * 16
	from Crypto.Cipher import AES
	aes = AES.new(key, AES.MODE_CBC, iv)
	data = aes.decrypt(data)
	return data

with open('isc-lab02-secret.enc', 'rb') as f:
	lines = f.readlines()
	key = lines[0]
	encrypted = ''.join(lines[1:])
	decrypted = decrypt(key, encrypted)
	with open('decrypt.enc', 'wb') as f_out:
		f_out.write(decrypted)
