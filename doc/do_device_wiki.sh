cat device.pre > device.wiki
../tools/table2html/table2html device.table >> device.wiki
cat device.post >> device.wiki
cp device.wiki ../../wiki/.
pushd .
cd ../../wiki
hg pull
hg update
hg commit -m "device table update"
hg push
popd

