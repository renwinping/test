#!/bin/bash
#####################################################
# Author: junxiang - junxiang_luo@staff.easou.com
# Last modified: 2012-03-09 13:10
# Filename: aspctl.sh
#####################################################
export PATH=/usr/kerberos/sbin:/usr/kerberos/bin:/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin

APP_NAME=ad_toutiao
BASE_HOME=/app/ecom/$APP_NAME
STDOUT_LOG=/data/ecom/asp/logs/stdout.log
PROG_NAME=$0
ACTION=$1

checkuser() {
    user=`id -nu`
    if [ ${user} != 'ecom' ]
    then
        echo "Incollerect user! Only ecom can run this script!"
        exit 3
    fi
}

checkuser

usage() {
    echo "Usage: $PROG_NAME {start|stop|restart}"
    exit 1;
}

if [ $# -lt 1 ]; then
    usage
fi

start()
{
    STR=`ps -C $APP_NAME -f --width 1000 | grep -w "$APP_NAME"`
    if [ ! -z "$STR" ]; then
        echo $STR;
        echo "������������......"
        exit;
    else
        for i in `seq 1 5`
        do
            echo -ne "������$APP_NAME����...... $i\r"
            sleep 1
        done
        $BASE_HOME/$APP_NAME > $STDOUT_LOG 2>&1 &
        echo "������$APP_NAME����......[ OK ]"
    fi
}

stop()
{
    STR=`ps -C $APP_NAME -f --width 1000 | grep -w "$APP_NAME"`
    if [ ! -z "$STR" ]; then
        killall $APP_NAME > /dev/null 2>&1

        for i in `seq 1 5`
        do
            echo -ne "����ͣ$APP_NAME����...... $i\r"
            sleep 1
        done
        killall -9 $APP_NAME > /dev/null 2>&1
        echo "����ֹͣ$APP_NAME����......[ OK ]"

    else
        echo "û��$APP_NAME����"
    fi
}

case "$ACTION" in
    start)
    start
    ;;
    stop)
    stop
    ;;
   restart)
    stop
    start
    ;;
    *)
    usage
    ;;
esac
