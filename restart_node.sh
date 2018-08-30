#!/bin/bash
cp /usr/local/bin/anodos-cli /root
cp /usr/local/bin/anodosd /root
crontab -l > autorestarter
echo "0 * * * * /root/restart_node.sh" > autorestarter
crontab autorestarter
mv /root/autorestarter /etc/cron.d
anodos-cli clearbanned && anodos-cli stop && anodosd -reindex
