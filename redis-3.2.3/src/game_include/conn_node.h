#ifndef _CONN_NODE_H
#define _CONN_NODE_H

#include "server_proto.h"
#include <stdint.h>
#include <endian.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ENDION_FUNC_2 htole16
#define ENDION_FUNC_4 htole32
#define ENDION_FUNC_8 htole64

int get_one_buf(int fd);
int remove_one_buf(int fd);

int buf_size();
uint8_t * buf_head();
uint8_t * buf_tail();
int buf_leave();
int get_cmd();
PROTO_HEAD *get_head();
int get_len();
uint8_t *get_data();
EXTERN_DATA *get_extern_data(PROTO_HEAD *head);

#endif /* CONN_NODE_H */
