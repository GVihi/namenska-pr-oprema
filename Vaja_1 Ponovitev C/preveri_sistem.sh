#/bin/bash

arrayOfTools=( make gcc gdb ldd ld ar strip readelf objdump strace ltrace )

echo "Preverjanje okolja ($(date '+%Y-%m-%d %H:%M:%S')) ..."
echo

echo "sistem: $(uname -i -v -r)"
echo

echo "zaznavanje orodij ..."
echo

for i in "${arrayOfTools[@]}"; do
	
	WHICH_OUT=$(which $i)
	
	if [ -n "$WHICH_OUT" ]; then
		  echo "$i: $WHICH_OUT"
	else
		  echo "$i: manjka"
		  exit
	fi
	
	WHICH_OUT=""
	
done

echo "analiza orodij ..."
echo

for i in "${arrayOfTools[@]}"; do
	echo "$i:"
	echo "$($i --version)"
	echo	
done
