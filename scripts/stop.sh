#!/bin/sh

redis="redis-cli -h vmeserver1 "

$redis < stop.txt
sleep 1
$redis < reset_task.txt
sleep 1
$redis < reset_device.txt

