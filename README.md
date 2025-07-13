# pipex
pipex project for 42

next to do:
* fully iron out the get_path series of functions ✓ - correct but need to fix line
	* especially make sure that all the memory is freed and that the functions < 25 line
* once this is done move up and finish the wrapper_execve <-- this is finished
* then finish making children <-- this is finished
* look again at how the here_we_are function works <-- ✓ this works in theory
* then get a pipex tester online and profit

Next:
* fix the line counts for all the functions
* I think the memory allocations are correct, but make a chatGPT tester 
* Make sure to remove the specific ft_fail()s in the int main() when you done.


Things to ask people as 42 before handing in: 
* the buffer size in the pipex_rd_nxt_lne()
-- I put as 9999, however IDK if that is good, i put as INT_MAX earlier, however chat said it would fail. 
* Makefile good ? (both the root/tpipex  Makefile and the includes/libft makefile)
* think about integrating the gnl function in your libft --> (just so that you can move the librairy w/ everything in the future)




