SRCDATE = "20200624"

require maxytec-dvb-modules.inc

SRC_URI[md5sum] = "90a6b44cf566df2fa1d884e687604bbf"
SRC_URI[sha256sum] = "fa334396eef8d37f0c57163afb08a2f8deb1010c77bec34bbc3089f7e89642d9"

COMPATIBLE_MACHINE = "^(multiboxplus)$"

MACHINETYPE = "plus"

# Generate a simplistic standard init script
do_compile_append () {
	cat > suspend << EOF
#!/bin/sh

runlevel=runlevel | cut -d' ' -f2

if [ "\$runlevel" != "0" ] ; then
	exit 0
fi

mount -t sysfs sys /sys

/usr/bin/turnoff_power
EOF
}
