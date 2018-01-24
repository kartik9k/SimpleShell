The program first checks if the command is internal or not. If not then executes via bin/ (folder made by running make) else throws an error.

cd : Can't change to an invalid directory. Throws error
'~' doesn't point to root. To point to root use /home/kartik/

echo : All "" are removed while printing. -n & -e are handled and can be used together. \n, \t, \c are handled by the shell.

pwd : Prints current working directory. 

exit : Exits the shell with exit(-1) status. Type 'exit' to exit.

history : Prints all(executed or failed) prev commands except the most recent 'history' by reading from a file created within the program.

ls : Implemented -a option only. Prints all directories/ files including . and ..
Can display contents of directories other than the current directory. Throws an error if the directory is invalid.

cat : Implemented -n & -b. Prints line number with the lines with slight variation. Throws an error if the file is not valid.

date : Simply prints the current date and time.

rm : Can delete multiple files in one instance.

mkdir : Creates a directory at the said location with 777 permissions. 

TO DO: 1) Implement options for rm & mkdir