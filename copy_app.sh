#/bin/sh
echo "Copy App file Ev3Car to BrickEv3 as binary."

src_file="Ev3Car"
dst_path="/Volumes/NO NAME/ev3rt/apps"

if [ ! -e ${src_file} ]; then
	echo "Binary file ${Ev3Car} does not exitst."
	echo "Please verifying the binary file existence."

	exit 1
fi

if [ ! -e "${dst_path}" ]; then
	echo "Ev3Brick maybe is not connected to this PC."
	
	exit 2
fi

echo "Copy ${src_file} into ${dst_path}"
cp ${src_file} "${dst_path}"

exit 0

