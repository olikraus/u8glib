cat device.pre > device.wiki
../tools/table2html/table2html device.table >> device.wiki
cat device.post >> device.wiki
cp device.wiki ../../wiki/.