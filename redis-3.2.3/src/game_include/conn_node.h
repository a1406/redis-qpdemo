#ifndef _CONN_NODE_H
#define _CONN_NODE_H

int get_one_buf();
int remove_one_buf();

uint8_t * buf_head();
int get_cmd();
PROTO_HEAD *get_head();
int get_len();
uint8_t *get_data();
EXTERN_DATA *get_extern_data(PROTO_HEAD *head);

#endif /* CONN_NODE_H */
