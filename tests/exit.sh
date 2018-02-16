../bin/rshell << 'EOF'

ls -a; echo hello && exit
../bin/rshell
ls -a; # exit
exite

EOF