# simple program to disable the Yun Bridge so it can by used by PySerial

# this involves commenting out one line in the file /etc/inittab
# the default file contents are
#     ::sysinit:/etc/init.d/rcS S boot
#     ::shutdown:/etc/init.d/rcS K shutdown
#     ttyATH0::askfirst:/bin/ash --login

# this program adds a # at the start of the line containing
#		ttyATH0::askfirst:/bin/ash --login


import shutil
fName = '/etc/inittab'
fTempName = '/etc/inittab.bak'

shutil.copy(fName, fTempName)

fIn = open(fTempName)
fOut = open(fName, 'w')
for fline in fIn:
	if fline.find('ttyATH0::askfirst:/bin/ash --login') > -1:
		fline = '# ' + fline
	fOut.write(fline)
	print fline
fIn.close()
fOut.close()