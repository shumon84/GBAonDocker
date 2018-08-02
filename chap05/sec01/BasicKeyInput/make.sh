#!/bin/bash
# make.sh
LOCAL=$(cd $(dirname $0) && pwd)
WORK=/home/$(basename $LOCAL)
CONTAINER=shumon84/gba
COMMAND=make
docker run -v $LOCAL:$WORK -w $WORK $CONTAINER $COMMAND
