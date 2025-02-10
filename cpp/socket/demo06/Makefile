all: client server

client: mthclient.cpp TcpClient.cpp 
	g++ -g -o mthclient mthclient.cpp TcpClient.cpp

server: mthserver_temp.cpp TcpServer.cpp CLogFile.cpp 
	g++ -g -o mthserver mthserver_temp.cpp TcpServer.cpp CLogFile.cpp -lpthread
clean:
	rm -f *.o
	rm -f mthclient mthserver
