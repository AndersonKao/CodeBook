syntax enable
set number
set tabstop=4
set shiftwidth=4
set cindent

colo torte
nocompatible
mouse = a

inoremap {<CR> {<CR>}<ESC>k$a<CR>

// command
sp, vsp
<C-w> {n} {< + - >?}

// replace
:%s/target/replacement/gc    // % for global, g for all, c for confirm.