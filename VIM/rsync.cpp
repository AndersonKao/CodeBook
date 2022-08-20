#!/bin/bash

while true; do
	rsync -zavh ~/Desktop/*.cpp /media/readleaf/backup
	sleep 10
done
