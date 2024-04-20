From ubuntu:16.04
	LABEL mainteiner serg.021@yandex.ru
	RUN apt-get update
	RUN apt-get install -y g++ mc
	WORKDIR /root/Client_queue
	COPY Client_queue.cpp .
	RUN g++ -std=c++11 Client_queue.cpp -lpthread -o Client_queue
	CMD ["./Client_queue"]
