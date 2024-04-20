From ubuntu:16.04
	LABEL mainteiner serg.021@yandex.ru
	RUN apt-get update
	RUN apt-get install -y g++ mc
	WORKDIR /root/docker_hello
	COPY docker_hello.cpp .
	RUN g++ docker_hello.cpp -o docker_hello
	CMD ["./docker_hello"]
