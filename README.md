# Pipex

A program that simulates Unix shell pipes, enabling the execution of command chains with input/output redirection between processes.

## Overview

Pipex is a system programming project in the 42 curriculum that introduces core Unix concepts like processes, pipes, file descriptors, and command execution. The project replicates the behavior of shell pipes, allowing users to chain commands together with data flowing from one process to another.

## Functionality

### Basic Usage
The program mimics the shell command:
```bash
< infile cmd1 | cmd2 > outfile
```

Using pipex:
```bash
./pipex infile "cmd1" "cmd2" outfile
```

### Bonus Features (here_doc)
Supports heredoc functionality:
```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```
Equivalent to:
```bash
cmd1 << LIMITER | cmd2 >> outfile
```

## Compilation

```bash
make        # Compile pipex
make bonus  # Compile with bonus features
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Recompile everything
```

## Usage Examples

### Basic Pipe Simulation
```bash
# Traditional shell command:
< input.txt grep "hello" | wc -l > output.txt

# Using pipex:
./pipex input.txt "grep hello" "wc -l" output.txt
```

### Multiple Commands
```bash
# Shell equivalent: cat file.txt | grep "pattern" | sort | uniq
./pipex file.txt "cat" "grep pattern" temp1
./pipex temp1 "sort" "uniq" final_output
```

### Here Document (Bonus)
```bash
# Traditional shell:
cat << EOF | grep "pattern" > output.txt
line 1
line 2
line 3
EOF

# Using pipex:
./pipex here_doc "EOF" "cat" "grep pattern" output.txt
# Then input your text until you type "EOF"
```

## Technical Implementation

### Key System Calls Used
- **fork()**: Create child processes
- **pipe()**: Create communication channels between processes
- **execve()**: Execute commands
- **dup2()**: Redirect file descriptors
- **wait()/waitpid()**: Parent process synchronization
- **open()/close()**: File operations
- **access()**: Check file permissions

### Core Algorithm

#### Basic Pipex Flow
1. **Input Validation**: Check arguments and file accessibility
2. **Pipe Creation**: Create pipe for inter-process communication
3. **Fork Process 1**: 
   - Redirect stdin to input file
   - Redirect stdout to pipe write-end
   - Execute first command
4. **Fork Process 2**:
   - Redirect stdin to pipe read-end  
   - Redirect stdout to output file
   - Execute second command
5. **Parent Cleanup**: Wait for children and handle errors

#### Process Communication
```
[Input File] → [Process 1: cmd1] → [Pipe] → [Process 2: cmd2] → [Output File]
```

## Project Structure

```
2-pipex/
├── Makefile
├── inc/
│   └── pipex.h              # Header with structures and prototypes
├── libft/                   # Custom library (if used)
└── src/
    ├── pipex.c              # Main program logic
    ├── child.c              # Child process handling
    ├── init.c               # Initialization functions
    ├── parsing.c            # Command parsing and path resolution
    ├── utils.c              # Utility functions
    └── here_doc.c           # Bonus: heredoc implementation
```

## Key Functions and Components

### Core Functions
- **main()**: Argument parsing and process orchestration
- **child_process()**: Handle child process execution
- **parent_process()**: Handle parent process coordination
- **find_path()**: Locate executable commands in PATH
- **execute_command()**: Execute commands with proper error handling

### Path Resolution
The program must locate executables by:
1. Checking if command contains '/' (absolute/relative path)
2. Searching through PATH environment variable
3. Testing each directory for the executable
4. Handling permissions and access rights

### Error Handling
- **File Access**: Check read/write permissions
- **Command Not Found**: Handle invalid commands gracefully
- **Memory Allocation**: Proper cleanup on allocation failures
- **Process Errors**: Handle fork/exec failures
- **Pipe Errors**: Manage broken pipes and communication failures

## Memory Management

### Key Considerations
- **Process Isolation**: Each child process has its own memory space
- **File Descriptor Management**: Proper closing of unused descriptors
- **Command Arguments**: Dynamic allocation for parsed commands
- **Environment Variables**: PATH parsing and cleanup
- **No Memory Leaks**: All allocated memory must be freed

### Resource Cleanup
```c
// Proper cleanup sequence
close(pipe_fd[0]);
close(pipe_fd[1]);
wait(&status);
free_allocated_memory();
```

## Learning Objectives

### System Programming Concepts
- **Process Creation**: Understanding fork() and process hierarchy
- **Inter-Process Communication**: Using pipes for data transfer
- **File Descriptor Management**: Redirecting input/output streams
- **Command Execution**: Using execve() and environment handling
- **Process Synchronization**: Parent-child coordination

### Unix Environment
- **Shell Behavior**: Understanding how shells process commands
- **PATH Resolution**: Finding executables in system directories
- **File Permissions**: Handling read/write access controls
- **Process States**: Understanding process lifecycle
- **Error Codes**: Proper exit status handling

## Common Challenges

### File Descriptor Management
- Properly closing unused file descriptors
- Avoiding deadlocks in pipe communication
- Handling stdin/stdout redirection

### Command Parsing
- Splitting commands and arguments correctly
- Handling quoted arguments and special characters
- Resolving command paths in environment

### Process Synchronization
- Ensuring proper parent-child coordination
- Handling zombie processes
- Managing multiple process execution order

## Testing Strategies

### Basic Tests
```bash
# Test simple commands
./pipex input.txt "cat" "wc -l" output.txt

# Test with built-in commands
./pipex /etc/passwd "grep root" "cut -d: -f1" result.txt

# Error handling tests
./pipex nonexistent.txt "cat" "wc" output.txt
./pipex input.txt "invalidcmd" "wc" output.txt
```

### Comparison with Shell
Always compare pipex output with equivalent shell commands to ensure correctness:
```bash
# Shell command
< input.txt cmd1 | cmd2 > expected_output.txt

# Pipex command
./pipex input.txt "cmd1" "cmd2" pipex_output.txt

# Compare results
diff expected_output.txt pipex_output.txt
```

This project provides essential understanding of Unix system programming and forms the foundation for more complex projects involving process management and inter-process communication.