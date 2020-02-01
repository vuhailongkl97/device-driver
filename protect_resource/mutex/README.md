description:
	using mutex + timer delay 10s in "init module function"

a. mutex lock key1
b. setup timer after 10s unlock key1
c. mutex try to lock key1 again as soon as setup timer
