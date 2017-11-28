#!/bin/sh

#project binary
PROJECT_NAME="server";
PROJECT="/usr/local/bin/$PROJECT_NAME"

#pidfile
PIDFILE_NAME="$PROJECT_NAME.pid"
PIDFILE="/var/run/$PROJECT_NAME.pid"

case "$1" in
    start)
        if [ -x $PROJECT ]; then
            $PROJECT
        else
            echo "Binary file $PROJECT_NAME not found"
        fi
        ;;

    status)
        printf "%-50s" "Checking $PROJECT_NAME..."
        if [ -f $PIDFILE ]; then
            PID=$(cat $PIDFILE)
            if [ -z "`ps axf | grep $PID | grep -v grep`" ]; then
                printf "%s\n" "Process dead but pid file $() exists"
            else
                echo "Running"
            fi
        else
            printf "%s\n" "Service not running"
        fi
        ;;

    stop)
        if [ -f $PIDFILE ]; then
            kill -USR1 $(cat $PIDFILE)
            rm -f $PIDFILE
        else
            echo "$PIDFILE_NAME: No such file"
        fi
        ;;

    restart)
        sh $0 stop
        sh $0 start
        ;;

    *)
        echo "Usage: $0 {status|start|stop|restart}"
        exit 1

esac

exit 0
