./minishell << EOF
ls|"test"
"coucou"
il y a 11 mots|"co<<bizare"<<""|lol
il y a x mots|co<<bizare<<""|lol
il y a x mots|co<<bizare"<<"|lol
<
<<
<<<
//printf("%c\n", cmd_line[i]);
ls -la | echo < "Salut" >> outfile | < infile cat | ls > outfile
cmd1<<arg1|cmd1 "string avec des ntrucs dedans tah les fous <<<|"salut "salut"
"dsfslj||"'salut<<'salut<<
'"clear                                         'salut salut<<<<<<"tes'|<'"
echo "salut" | </dev/fd/0 cat | ls >/dev/fd/1 | cut -d ' ' -f 1 | echo "''<|>><><>''"salut<<



expantion :

bash-5.0$ export VAR='this"$USER"here'
bash-5.0$ echo $VAR
this"$USER"here

bash-5.0$ export VAR=this"$USER"here
bash-5.0$ echo $VAR
thisvahemerehere

bash-5.0$ echo salut$USERsalut
salut

bash-5.0$ echo salut$USER
salutvahemere

bash-5.0$ export VAR="echo salut"
bash-5.0$ $VAR
salut


bash-5.0$ export L="s -la"
bash-5.0$ l$L
total 172
drwxr-xr-x 5 vahemere 2021_paris   4096 May 21 15:55 .
drwxr-xr-x 3 vahemere 2021_paris   4096 May  6 03:23 ..
drwxr-xr-x 8 vahemere 2021_paris   4096 May 20 17:09 .git

bash-5.0$ export l="echo $tss"
bash-5.0$ $l
\0

bash-5.0$ export l="echo 'salut $USER'"
bash-5.0$ $l
'salut vahemere'

bash-5.0$ export l='echo $USER'
bash-5.0$ $l
$USER

vahemere@e3r6p1:~/Desktop/project/Minishell$ export VAR="a b c"
vahemere@e3r6p1:~/Desktop/project/Minishell$ echo $VAR
a b c

vahemere@e3r6p1:~/Desktop/project/Minishell$ export t="$VAR"$VAR"$VAR"
vahemere@e3r6p1:~/Desktop/project/Minishell$ echo $t
a b ca b ca b c

sudo apt-get install libreadline-dev 