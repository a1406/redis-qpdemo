#include <stdio.h>
#include <stdint.h>
#include "anet.h"

int connect_conn_srv()
{
	return anetTcpConnect(NULL, "127.0.0.1", 7778);
}

int gamesrv_main(int argc, char *argv[])
{
	connect_conn_srv();
	return (0);
}


