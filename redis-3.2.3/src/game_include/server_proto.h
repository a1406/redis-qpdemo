#ifndef _SERVER_PROTO_H__
#define _SERVER_PROTO_H__

#include <stdint.h>
#include "comm_define.h"
#pragma pack(1)
enum SERVER_PROTO
{
	SERVER_PROTO_BROADCAST = 1000,
	SERVER_PROTO_BROADCAST_ALL = 1001,
	
	SERVER_PROTO_LOGIN,							//帐号登录,login srv 通知conn srv放行
	SERVER_PROTO_ENTER_GAME_REQUEST,			//进入游戏请求，login_srv --> conn_srv --> game_srv --> db_srv
	SERVER_PROTO_ENTER_GAME_ANSWER,				//选择角色进入游戏, db_srv --> game_srv
	SERVER_PROTO_SAVE_PLAYER,					//保存玩家信息

	SERVER_PROTO_PLAYER_ONLINE_NOTIFY,			// 用户上线通知
	SERVER_PROTO_KICK_ROLE_NOTIFY,				//踢人
	SERVER_PROTO_KICK_ROLE_ANSWER,				//重新选角踢人，game_srv --> conn_srv
	SERVER_PROTO_RENAME_ANSWER,				    //改名应答，db_srv --> game_srv

	SERVER_PROTO_GAME_TO_FRIEND,     //游戏服通过网关转好友服
	SERVER_PROTO_REFRESH_PLAYER_REDIS_INFO,     //更新redis缓存用户信息
	SERVER_PROTO_TEAM_LIST_INFO,     //

	SERVER_PROTO_GAMESRV_START,                 //游戏服启动通知
	SERVER_PROTO_MAIL_INSERT,                   //插入新邮件
	SERVER_PROTO_MAIL_GIVE_ATTACH_REQUEST,      //邮件发放邮件附件请求 mail_srv --> game_srv
	SERVER_PROTO_MAIL_GIVE_ATTACH_ANSWER,       //邮件发放邮件附件应答 game_srv --> mail_srv

	SERVER_PROTO_ADD_WANYAOKA,       //添加万妖卡信息	
	SERVER_PROTO_SAVE_WANYAOKA,       //保存万妖卡信息
	SERVER_PROTO_LIST_WANYAOKA,       //读取万妖卡信息	

	SERVER_PROTO_GET_USER_INFO = 9033,          // 后台管理端获取用户信息
	SERVER_PROTO_ADD_ITEM_REQUESRT = 9034,		// 后台管理端增加物品
	SERVER_PROTO_RELOAD_CONFIG_REQUEST,			// game srv重读配置
	SERVER_PROTO_RELOAD_ACTIVE_REQUEST,			// active srv重读配置
	SERVER_PROTO_RELOAD_ACTIVE_ANSWER,			// active srv重读配置的回复
	SERVER_PROTO_GET_OFFLINE_RECHARGE_REQUEST,	// 获取离线充值请求
	SERVER_PROTO_OFFLINE_RECHARGE_LIST_REQUEST,	// 获取离线充值列表请求
	SERVER_PROTO_OFFLINE_RECHARGE_LIST_ANSWER,	// 获取离线充值列表应答

	SERVER_PROTO_TIREN_LIST_NOTIFY,				// 外挂踢人
};


//除了broadcast的所有消息，第一个字段都是PROTO_HEAD, 最后一个字段都是EXTERN_DATA

typedef struct st_proto_head
{
	uint32_t len;		//长度
	uint16_t msg_id;	//消息ID
	uint16_t seq;		//序号
//	uint32_t crc;		//crc校验
	char data[0];		//PROTO 内容
} PROTO_HEAD;

typedef struct proto_head_conn_broadcast
{
	uint32_t len;
	uint16_t msg_id;
	uint16_t seq;
	uint16_t num_player_id;
	PROTO_HEAD proto_head;
	uint64_t player_id[0];
} PROTO_HEAD_CONN_BROADCAST;

//server之间外带的数据
typedef struct extern_data   
{
	uint64_t player_id;
	uint32_t open_id;
	uint16_t fd;
	uint16_t port;	
} EXTERN_DATA;

typedef struct proto_role_login
{
	PROTO_HEAD head;
	uint32_t result;
	uint16_t login_seq;
} PROTO_ROLE_LOGIN;

typedef struct proto_save_player_req
{
	PROTO_HEAD head;	
	uint16_t level;
	uint32_t plug;
	uint16_t data_size;
	char     name[50];
	uint32_t again; //是否重新选角
	uint8_t data[0];
} PROTO_SAVE_PLAYER_REQ;

typedef struct proto_save_player_resp
{
	PROTO_HEAD head;
	uint32_t again; //是否重新选角
	uint32_t result;
} PROTO_SAVE_PLAYER_RESP;

typedef struct proto_role_kick
{
	PROTO_HEAD head;
	uint32_t reason;
	uint32_t again; //是否重新选角
	EXTERN_DATA extern_data; //要放到最后
} PROTO_ROLE_KICK;

typedef struct proto_enter_game_req
{
	PROTO_HEAD	head;
	uint64_t	player_id;
} PROTO_ENTER_GAME_REQ;

typedef struct proto_enter_game_resp
{
	PROTO_HEAD head;
	uint8_t job;
	char name[MAX_PLAYER_NAME_LEN];
	uint16_t lv;
	uint64_t player_id;
	uint8_t avata_id;
	uint32_t platform;
	uint32_t ad_channel;
	uint32_t plug;
	uint32_t create_time;
	uint32_t logout_time;
	char    open_id[50];
	char    channel[50];
	uint16_t data_size; //数据库blob最大64K
	uint8_t data[0];
} PROTO_ENTER_GAME_RESP;

typedef struct player_rename_db_answer
{
	PROTO_HEAD head;
	uint32_t result;
	char name[MAX_PLAYER_NAME_LEN];
} PLAYER_RENAME_DB_ANSWER;

typedef struct show_item_to_itemsrv
{
	PROTO_HEAD head;
	uint32_t type;
	uint16_t data_size;
	uint8_t data[0];
} SHOW_ITEM_TO_ITEMSRV;

/*
typedef struct refresh_player_redis_info
{
	PROTO_HEAD head;
	uint64_t player_id;
	uint16_t data_size;
	uint8_t data[0];
} REFRESH_PLAYER_REDIS_INFO;
*/

//插入一封新邮件
typedef struct proto_mail_insert
{
	PROTO_HEAD head;
	uint64_t player_id;
	uint32_t data_size;
	uint8_t data[0];
} PROTO_MAIL_INSERT;

#define MAX_WANYAOKA_EACH_TIME 10
typedef struct proto_add_wanyaoka
{
	uint64_t player_id;
	uint32_t wanyaoka[MAX_WANYAOKA_EACH_TIME];
} PROTO_ADD_WANYAOKA;

#pragma pack() 
#endif

