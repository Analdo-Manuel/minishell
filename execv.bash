#!/usr/bin/bash
make re && make clean && valgrind --leak-check=full ./minishell