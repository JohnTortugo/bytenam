function f() {
	count=`ls /wf/tmp/jars/*.jar | wc -l`
	i=0

	for f in `ls /wf/tmp/jars/*.jar` ; do 
		echo "$i / $count ) $f"
		./build/bytenam $f 2>/dev/null
		
		if [[ "$?" != "0" ]] ; then	
			echo $f
			return 
		fi
		i=$(( i + 1 ))
	done
}

f
