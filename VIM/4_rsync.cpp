#!/bin/bash

while true; do
	rsync -zavh ~/Desktop/*.cpp /media/redleaf/backup
	sleep 10
done
