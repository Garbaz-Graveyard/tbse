progname=tbse
srcfiles=src/${progname}.c
buildfile=build/${progname}
default:
	if [ ! -e "build" ];then mkdir build;fi
	gcc -O2 -o ${buildfile} ${srcfiles}

debug:
	if [ ! -e "build" ];then mkdir build;fi
	gcc -Wall -g -o ${buildfile} ${srcfiles}

run:
	@${buildfile}
