all: client server

client: mpclient.cpp TcpClient.cpp 
	g++ -g -o mpclient mpclient.cpp TcpClient.cpp

server: mpserver.cpp TcpServer.cpp CLogFile.cpp
	g++ -g -o mpserver mpserver.cpp TcpServer.cpp CLogFile.cpp 

clean:
	rm -f *.o
	rm -f mpclient mpserver
