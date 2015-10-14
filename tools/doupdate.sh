#! /bin/sh
# 执行跟新操作
cp /etc/tmsxx.db.new /etc/tmsxx.db
cp /usr/MenglongWu/bin/tms4412.elf.new /usr/MenglongWu/bin/tms4412.elf
cp /usr/MenglongWu/bin/targetExe-r.new /usr/MenglongWu/bin/targetExe-r

rm /etc/tmsxx.db.new
rm /usr/MenglongWu/bin/tms4412.elf.new
rm /usr/MenglongWu/bin/targetExe-r.new