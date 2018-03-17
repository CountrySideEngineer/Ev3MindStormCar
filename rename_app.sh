#/bin/bash
echo "Rename App file to Ev3Car."

target_file="Ev3Car"
base_file="app"

if [ ! -e ${base_file} ]; then
	echo "Source file ${base_file} does not exist."
	echo "So, nothing to do."

	exit 1
fi

if [ -e ${target_file} ]; then
	echo "Exist ${target_file}"
	echo "Before rename file, delete old ${target_file}."
	
	rm -rf ./${target_file}	
fi

echo "Execute application binary file ${base_file} into ${target_file}" 
mv ${base_file} ${target_file}

exit 0
