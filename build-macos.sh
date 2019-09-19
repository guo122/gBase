
cmakeImpl() {
	cmake -E make_directory "Solution/macos" && cmake -E chdir "Solution/macos" cmake -G "Xcode" ../../ -DTHE_PROJECT_PREFIX="$1"
}

if [ "$1" == "" ] ; then
    cmakeImpl "gBase"
else
    cmakeImpl "$1"
fi

if [ "$?" == 0 ] ; then
	open ./Solution/macos/*.xcodeproj 2>/dev/null
fi
