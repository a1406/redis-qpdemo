#include "server.h"
#include "anet.h"
#include "ae.h"
#include <stdio.h>
#include <stdint.h>

int connect_conn_srv()
{
	return anetTcpConnect(NULL, "127.0.0.1", 7778);
}

void read_from_connsrv(aeEventLoop *el, int fd, void *privdata, int mask)
{
    UNUSED(el);
    UNUSED(fd);
    UNUSED(privdata);
    UNUSED(mask);
}

int gamesrv_main(int argc, char *argv[])
{
	UNUSED(argc);
	UNUSED(argv);
	
	int fd = connect_conn_srv();
	if (aeCreateFileEvent(server.el,fd,AE_READABLE,read_from_connsrv, NULL) == AE_ERR)
	{
		close(fd);
		return -1;
	}

	return (0);
}


