#!/bin/bash

# case "$OSTYPE" in
#   solaris*) echo "SOLARIS" ;;
#   darwin*)  echo "OSX" ;; 
#   linux*)   echo "LINUX" ;;
#   bsd*)     echo "BSD" ;;
#   msys*)    echo "WINDOWS" ;;
#   cygwin*)  echo "ALSO WINDOWS" ;;
#   *)        echo "unknown: $OSTYPE" ;;
# esac


if [[ "$OSTYPE" == "linux-gnu"* ]]
then
	# echo "LINUX"

	# sudo -n true
	# test $? -eq 0 || exit 1 "you should have sudo privilege to run this script"

	declare -A osInfo;
	osInfo[/etc/debian_version]="apt-get install -y"
	osInfo[/etc/alpine-release]="apk --update add"
	osInfo[/etc/centos-release]="yum install -y"
	osInfo[/etc/fedora-release]="dnf install -y"

	for f in ${!osInfo[@]}
	do
		if [[ -f $f ]];then
			package_manager=${osInfo[$f]}
		fi
	done

	package="git cmake libX11 libXmu-devel libX11-devel libXrandr-devel"

	${package_manager} ${package}

	cmake .
	make

	# read -p "Press [Enter] key to resum..."
elif [[ "$OSTYPE" == "darwin"* ]]
then
	# echo "OSX"

	cmake .
	make

	# read -p "Press [Enter] key to resum..."
fi

if [[ "$OSTYPE" == "msys"* || "$OSTYPE" == "cygwin"* ]]
then
	# echo "WINDOWS"
	# read -p "Press [Enter] key to resum..."
	cmake .
else
	:
fi


# echo -n "Enter a number: "
# read VAR

# if [[ $VAR -gt 10 ]]
# then
#   echo "The variable is greater than 10."
# fi
