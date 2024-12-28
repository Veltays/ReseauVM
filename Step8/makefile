all: admin TCPEchoClient TCPEchoServer

admin: data.h admin.c LibSerHV.o    
	@echo "Compilation de admin"
	gcc -o admin admin.c LibSerHV.o 

LibSerHV.o: LibSerHV.c LibSerHV.h data.h    
	@echo "Compilation de LibSerHV.o"
	gcc -c LibSerHV.c

LibSer.o: LibSer.c LibSer.h
	@echo "Compilation de LibSer.o"
	gcc -c LibSer.c

HandleTCPClient.o: HandleTCPClient.c HandleTCPClient.h Requete.h data.h LibSerHV.h
	@echo "Compilation de HandleTCPClient.o"
	gcc -c HandleTCPClient.c

TCPEchoServer: TCPEchoServer.c HandleTCPClient.o LibSerHV.o LibSer.o
	@echo "Compilation de TCPEchoServer"
	gcc -o TCPEchoServer TCPEchoServer.c HandleTCPClient.o LibSerHV.o LibSer.o

TCPEchoClient: TCPEchoClient.c Requete.h
	@echo "Compilation de TCPEchoClient"
	gcc -o TCPEchoClient TCPEchoClient.c

clean:
	@echo "Suppression des fichiers objets et exécutables"
	rm -f *.o admin TCPEchoClient TCPEchoServer
