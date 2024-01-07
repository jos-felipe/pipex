<h1>Description</h1>
<p>
This project is about hanling pipes.

Your program will be executed as follows:
```bash 
./pipex file1 cmd1 cmd2 file2
```

It must take 4 arguments:
>
> - file1 and file2 are file names.
> - cmd1 and cmd2 are shell commands with their parameters.

It must behave exaclty the same as the shell command below:

```bash 
$> < file1 cmd1 | cmd2 > file2
```
</p>

## Examples
```bash
$ ./pipex infile "ls -l" "wc -l" outfile
``````
Should behave like: 
```bash
$ < infile ls -l | wc -l > outfile
```
```bash
$ ./pipex infile "grep a1" "wc -w" outfile
``````
Should behave like: 
```bash
$ < infile grep a1 | wc -w > outfile
````
## Implementation Reference
<href>https://github.com/ArthurSobreira/42_pipex</href>