#!/bin/sh

redis="redis-cli -h vmeserver1"

$redis < connect.txt
sleep 1
$redis < inittask.txt
sleep 1
$redis < start.txt
