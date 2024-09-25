<p align="center">
  <img src="img/pipex.png" width="70%"/>
</p>

## 🚀 SYNOPSIS

The `pipex` project at 42 school challenges students to craft a program emulating the intricacies of shell command pipelines in the C language.

This endeavor necessitates a deep comprehension of process creation, manipulation, and input/output redirection. Students are tasked with orchestrating a sequence of commands, efficiently directing the output of one command as the input for the next.

The project not only hones skills in managing processes but also delves into the nuances of handling file descriptors and executing commands in a seamless chain.

Successfully completing `pipex` showcases a mastery of process manipulation and solidifies the understanding of pivotal system calls in Unix-like operating systems.

## 🛠️ PROGRAM SPECIFICITIES AND CONSIDERATIONS

The program behaves like this :

```
./pipex file1 cmd1 cmd2 file2
```

which mimics the real shell command

```bash
< file1 cmd1 | cmd2 > file2
```

Examples :

```
./pipex infile.txt "ls -l" "wc -l" outfile.txt
```

> [!IMPORTANT]
> The way the project is built means that `pipex` is expecting **COMMANDS AND OPTIONS** grouped in a single argument, surrounded with _"double-quotes"_.

The command :
```bash
./pipex infile.txt ls -l wc -l outfile.txt
```
will actually fail.
 
 
 

## ⚙️ USAGE

### Step 1 :

Clone the project :

```bash
git clone https://github.com/maitreverge/pipex.git && cd pipex
```

### Step 2 :

Build the project in your shell environment running :

```bash
make
```

You'll end up with an `pipex` executable file.

### Step 3 :

Let's make a basic example.
You'll need to create an `infile.txt` from which `pipex` will read in *`STD_IN`* :

```bash
echo "Hello, World\!" > infile.txt
```

### Step 4 :

Execute `pipex` :

```bash
./pipex infile.txt "cat" "rev" outfile.txt
```

This will create an outfile from which you can read :

```bash
cat outfile.txt
```

You should see the bellow result :

```text
!dlroW ,olleH
```

## 🤝 CONTRIBUTION
Contributions are open, make a pull request or open an issue 🚀
