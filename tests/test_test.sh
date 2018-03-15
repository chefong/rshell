../bin/rshell << 'EOF'

test -e src #true
test -e assn3.json #true
test -e hi.cpp #false
test -e folder #false
[ -e src ] #true
[ -e hi.cpp ] #false

test -f src #false
test -f assn3.json #true
test -f hello.cpp #false
[ -f src ] #false
[ -f assn3.json ] #true

test -d src #true
test -d assn3.json #false
[ -d src ] #true
[ -d assn3.json ] #false
exit

EOF