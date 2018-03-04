../bin/rshell << 'EOF'

(echo a && echo b) || (echo c && echo d)
(echo a || echo b) && (echo c || echo d)
(echo a && echo b) || echo c && ls -a

EOF