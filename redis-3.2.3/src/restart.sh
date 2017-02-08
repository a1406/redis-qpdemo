#!/bin/sh
cd `dirname $0`
ulimit -c unlimited

./stop.sh

cd conn_srv
./conn_srv -d
sleep 2

cd ../login_srv
./login_srv -d

cd ../
./show_all_pid.sh 
./check_srv_alive.sh

