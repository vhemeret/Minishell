# 🐚 Minishell

## 📖 About

Minishell is a project that involves creating a simple shell, similar to bash. This project deepens understanding of processes and file descriptors in Unix systems.

## 🎯 Objectives

- Implement a basic command-line interpreter
- Handle command history
- Manage environment variables
- Implement basic shell built-in commands
- Handle redirections and pipes
- Manage signal handling

## 🛠️ Features

- Display a prompt for new commands
- Implement a working history feature
- Search and launch executables (using PATH variable or relative/absolute path)
- Handle single quotes (') and double quotes (")
- Implement redirections (<, >, <<, >>)
- Implement pipes (|)
- Handle environment variables ($VAR)
- Handle $? for exit status
- Implement ctrl-C, ctrl-D, and ctrl-\ behavior
- Builtin commands: echo, cd, pwd, export, unset, env, exit

## 🚀 Usage

```
./minishell
```

This will start the Minishell prompt, where you can enter commands.

## ⚙️ Installation

1. Clone the repository:
   ```
   git clone https://github.com/your-username/minishell.git
   ```
2. Navigate to the project folder:
   ```
   cd minishell
   ```
3. Compile the project:
   ```
   make
   ```

## 🧰 Implementation Details

- Uses readline for command input and history
- Implements custom parsing for command interpretation
- Manages multiple processes for command execution
- Handles various signal interrupts
- Implements basic shell functionalities without using the built-in shell commands

---

Made with ❤️ as part of the 42 School curriculum.