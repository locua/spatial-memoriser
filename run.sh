#make -j8 || while read; do echo "$REPLY"; done
make -j7 && make RunRelease
#while :
#      read -n 1; done
#make RunRelease
#if make -j8 | grep error;
#then
#    #make RunRelease
#    read -p "hi"
#else
#    make RunRelease
#fi

