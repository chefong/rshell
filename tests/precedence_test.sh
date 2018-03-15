../bin/rshell << 'EOF'

(echo a && echo b) || (echo c && echo d)
(echo a || echo b) && (echo c || echo d)
(echo a && echo b) || echo c && ls -a
echo a || ((echo b && echo c && ls -a && echo d)) && echo e
(echo a && (echo b)) || (echo c || echo d)
exit

EOF