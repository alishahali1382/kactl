set cin aw ai is ts=4 sw=4 nu rnu noeb bg=dark ru cul
set nocp ic scs ws udf so=4
sy on | colo habamax | nn <esc><esc> :noh<return><esc> | no ; :
" Select region and then type :Hash to hash your selection.
" Useful for verifying that there aren't mistypes.
ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
 \| md5sum \| cut -c-6
