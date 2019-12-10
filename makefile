all: netcalc

netcalc:
	@g++ src/*.cpp src/*.c -Wall -Wextra -pedantic -o netcalc

install:
	@cp netcalc /usr/bin/

uninstall:
	@rm -f /usr/bin/netcalc

clean:
	@rm netcalc