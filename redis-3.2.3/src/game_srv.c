#include "server.h"
#include "game_include/server_proto.h"
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

	serverLog(LL_WARNING,"%s: ", __FUNCTION__);

	EXTERN_DATA *extern_data;
	PROTO_HEAD *head;
//	player_struct *player = NULL;
	for (;;) {
		int ret = get_one_buf();
		if (ret == 0) {
			head = (PROTO_HEAD *)buf_head();
			int cmd = get_cmd();			
			extern_data = get_extern_data(head);
/*			
			switch (cmd)
			{
				case MSG_ID_SAVE_CLIENT_DATA_REQUEST:
				case MSG_ID_LOAD_CLIENT_DATA_REQUEST:
					{
						if (conn_node_dbsrv::connecter.send_one_msg(head, 1) != (int)ENDION_FUNC_4(head->len))
						{
							LOG_ERR("[%s:%d] send to dbsrv failed err[%d]", __FUNCTION__, __LINE__, errno);
						}
					}
					break;
				default:
					{
						player = player_manager::get_player_by_id(extern_data->player_id);
						//				if (player) {
						//					player->update_rtt(head->time_stamp);
						//				}

						//			if (SERVER_PROTO_ENTER  != cmd && SERVER_PROTO_RELOAD_CONFIG_REQUEST != cmd && SERVER_PROTO_PLAYER_ENTER_REQUEST!=cmd && !player){
						//				LOG_INFO("%s %d: get cmd %d but can not find player, playerid: %lu", __FUNCTION__, __LINE__, cmd, extern_data->player_id);						
						//			} else {
						uint64_t times = time_helper::get_micro_time();
						time_helper::set_cached_time(times / 1000);
						//				(this->*all_msg_handler[cmd])(player, extern_data);
						HandleMap::iterator it = m_handleMap.find(cmd);
						if (it != m_handleMap.end())
						{
							(it->second)(player, extern_data);
						}
						else
							default_handle(player, extern_data);
						//			}
					}
					break;
			}
		}
*/		
		if (ret < 0) {
			LOG_INFO("%s %d: connect closed from fd %u, err = %d", __FUNCTION__, __LINE__, fd, errno);
//			return (-1);
/*
			std::map<uint64_t, player_struct *>::iterator it = player_manager::all_players_id.begin();
			for (; it!=player_manager::all_players_id.end(); ++it) {
				player_struct* player = it->second;
				if (!player)
					continue;

				player->data->status = ONLINE;
		//		player->process_kick_player();
				head = (PROTO_HEAD *)buf_head();
	//			extern_data = get_extern_data(head);
				EXTERN_DATA ext_data;
				ext_data.player_id = player->data->player_id;
				player->cache_to_dbserver(false, &ext_data);
			}
*/
			event_del(&event_recv);
			evutil_closesocket(fd);
			exit(0);			
			return (0);
		} else if (ret > 0) {
			break;
		}
		
		ret = remove_one_buf();
	}
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


