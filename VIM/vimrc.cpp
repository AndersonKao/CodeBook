set nu cin ts=4 sw=4 aw hls is
syntax on

colo torte
set nocompatible

inoremap {<CR> {<CR>}<ESC>k$a<CR>
nn <F8> :w <bar> :!vim 
nn <F9> :w <bar> :!g++ -std=c++17 -O2 -Wall -Wextra -fsanitize=address % -o %<<CR>
nn <F3> :w <bar> :!./%<<CR>
nn <F4> :w <bar> :!./%< < 

// command
sp, vsp
<C-w> {n} {< + - >?}

// replace
:%s/target/replacement/gc    // % for global, g for all, c for confirm.
