#!/bin/sh
cd `dirname $0`

# conn_srv退出
kill -9 `cat conn_srv/pid.txt`
#kill -9 `cat game_srv/pid.txt`
kill -9 `cat login_srv/pid.txt`


