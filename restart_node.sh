#!/bin/bash
cp /usr/local/bin/anodos-cli /root
cp /usr/local/bin/anodosd /root
crontab -l > autorestarter
#echo new cron into cron file
echo "0 * * * * /root/restart_node.sh" > autorestarter
#install new cron file
crontab autorestarter
mv /root/autorestarter /etc/cron.d
anodos-cli clearbanned && anodos-cli stop && anodosd -reindex
