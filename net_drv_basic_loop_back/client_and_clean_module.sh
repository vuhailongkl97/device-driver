echo "run code test, client send message to server over ip'new driver"
	gcc test_socket/client.c -o test_socket/c
	./test_socket/c

echo "remove module form system"
echo "sudo rmmod main"
	sudo rmmod main
