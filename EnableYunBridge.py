# simple program to enable the Yun Bridge so it can by used by PySerial

# this involves removing comments from one line in the file /etc/inittab
# the default file contents are
#     ::sysinit:/etc/init.d/rcS S boot
#     ::shutdown:/etc/init.d/rcS K shutdown
#     ttyATH0::askfirst:/bin/ash --login

# this program searches for a line containing
#		ttyATH0::askfirst:/bin/ash --login
# which may or may not be preceded by # 
# it replaces the line with "ttyATH0::askfirst:/bin/ash --login"
# i.e. without any #


import shutil
fName = '/etc/inittab'
fTempName = '/etc/inittab.bak'

shutil.copy(fName, fTempName)

fIn = open(fTempName)
fOut = open(fName, 'w')
for fline in fIn:
	if fline.find('ttyATH0::askfirst:/bin/ash --login') > -1:
		fline = 'ttyATH0::askfirst:/bin/ash --login'
	fOut.write(fline)
	print fline
fIn.close()
fOut.close()