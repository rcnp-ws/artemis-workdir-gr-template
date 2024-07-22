#!/bin/sh


redis="redis-cli -h vmeserver1 "

$redis incr run_info:run_number

