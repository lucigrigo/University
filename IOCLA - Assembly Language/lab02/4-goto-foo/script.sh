if [ $(cat server.c | grep fprintf | wc -l) -eq 1 ]; then
	if [ $(cat client.c | grep fprintf | wc -l) -eq 1 ]; then
		echo "Passed"
		exit 0
	fi

	echo "Fail!"
	exit 1

fi

if [ $(cat client.c | grep fprintf | wc -l) -ne 1 ]; then
	echo "Fail"
	exit 1
fi
