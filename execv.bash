#!/usr/bin/bash
make re && make clean && valgrind --leak-check=full --show-leak-kinds=all ./minishell
