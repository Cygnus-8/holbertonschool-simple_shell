# hsh - Simple Shell 

A simple UNIX command interpreter written in the context of a low-level programming  and algorithm program at Holberton School Toulouse, France.

## Description

**hsh** is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

### Invocation

Usage: **hsh** [filename]

To use  **hsh** like a program, compile all `.c` files in the repository and run the resulting executable:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

./hsh
```

**hsh** can be used both interactively and *non-interactively*. If **hsh** is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:
```
$ echo "echo 'hello'" | ./hsh
'hello'
$
```

If **hsh** is invoked with standard input connected to a terminal (as determined by [isatty](http://manpagesfr.free.fr/man/man3/isatty.3.html)), an *interactive* shell is opened. When executing interactively, **hsh** displays the prompt `$ ` when it is ready to read a command.

Example:
```
$./hsh
$
```

Alternatively, if command line arguments are supplied on the call, **hsh** treats the first argument as an executable file from which to read commands. The file provided must contain one command per line. **hsh** executes each of the commands in the file in order before terminating.

Example:
```
$ cat test
echo 'hello'
$ ./hsh test
hello
$
```

### Environment

When called, **hsh** receives and copies the environment of the parent process in which it was executed. This environment is an array of strings of type *name-value* describing variables in the format *NAME=VALUE*. Some important environmental variables are :

#### HOME
It's the home directory of the current user and the default directory argument for the **cd** builtin command.

```
$ echo "echo $HOME" | ./hsh
/home/Ubuntu
```

#### PWD
It's the current working directory as set by the **cd** command.

```
$ echo "echo $PWD" | ./hsh
/home/Ubuntu/holberton-simple_shell
```

#### OLDPWD
It's the previous working directory as set by the **cd** command.

```
$ echo "echo $OLDPWD" | ./shellby
/home/Ubuntu/holberton-test-repo
```

#### PATH
A colon-separated list of directories which contains commands that the shell looks for. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.

```
$ echo "echo $PATH" | ./hsh
/home/Ubuntu/.cargo/bin:/home/Ubuntu/.local/bin:/home/Ubuntu/.rbenv/plugins/ruby-build/bin:/home/Ubuntu/.rbenv/shims:/home/vagrant/.rbenv/bin:/home/vagrant/.nvm/versions/node/v10.15.3/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/Ubuntu/.cargo/bin:/home/Ubuntu/workflow:/home/Ubuntu/.local/bin
```

### Execution

After receiving a command, **hsh** tokenizes it into words using `" " and  \n` as a delimiter. The first word is considered as command and all remaining words are considered as arguments to that command. **hsh** then proceeds with the following actions:
1. If the first character of the command is neither a slash (`\`) nor dot (`.`), the shell searches for it in the list of shell builtins. If there exists a builtin by that name, the builtin is invoked.
2. If the first character of the command is none of a slash (`\`), dot (`.`), nor builtin, **hsh** searches each element of the **PATH** environmental variable for a directory containing an executable file by that name.
3. If the first character of the command is a slash (`\`) or dot (`.`) or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.




### Signals 

While running in interactive mode, **hsh** ignores the keyboard input `Ctrl+c`. Alternatively, an input of end-of-file (`Ctrl+d`) will exit the program.

User hits `Ctrl+d` in the third line.
```
$ ./hsh
$ ^C
$ ^C
$
```
***P.S*** :  Implementation of feature `Ctrl+d` as the only way to exit, in interactive mode are in progress, we're sorry for the wait.  



## Authors 

* Chris Monfort Muryango <[Cygnus-8](https://github.com/Cygnus-8)>
* Adel Otmani <[AdelOtmani](https://github.com/AdelOtmani)>
* Myriam Belkhiri <[MyriamHolberton](https://github.com/MyriamHolberton)>


