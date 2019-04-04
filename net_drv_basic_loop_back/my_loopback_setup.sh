echo "rebuild"
#	make clean && make all
echo "insert kernel module"
echo "sudo insmod main.ko"
	sudo insmod main.ko
echo "config up my loopback and setup ip"
echo "sudo ifconfig longvh up 10.207.219.146" 
	sudo ifconfig longvh up 10.207.219.146

echo "run test server and client over ip'new loopback"
echo "now open new terminal and run ./test_socket/c"
echo "./test_socket/s"
	./test_socket/s



