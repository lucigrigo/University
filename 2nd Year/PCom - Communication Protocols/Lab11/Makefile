# Protocoale de comunicatii
# Laborator 11 - E-mail
# Makefile

CFLAGS = -Wall -g

IP_SERVER = 127.0.0.1
NUME_FISIER = file.txt

default: send_mail

send_mail: send_mail.c
	gcc $(CFLAGS) send_mail.c -o send_mail

run: send_mail
	./send_mail ${IP_SERVER} ${NUME_FISIER}

.PHONY: clean

clean:
	rm -f send_mail
