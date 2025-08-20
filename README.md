# minishell

## Overview
Minishell is a lightweight shell implementation designed to provide basic command-line functionality.

## Features
- Command execution
- Environment variable management
- Input/output redirection
- Built-in commands

## Installation
Clone the repository and build the project:

# test_of_commands
COMPREHENSIVE TEST CASES FOR echo COMMAND WITH -n OPTION:

1. BASIC FUNCTIONALITY:
   - echo -n "hello world"
       -> prints "hello world" without trailing newline
   - echo -n ""
       -> prints nothing, no newline
   - echo -n "text with spaces"
       -> prints text exactly as given, no newline

2. NO -n OPTION:
   - echo "hello"
       -> prints "hello" with trailing newline

3. MIXED OPTIONS AND ARGUMENTS:
   - echo -n hello world
       -> prints "hello world" without newline
   - echo -n -e hello
       -> treats "-e" as text, prints "-e hello" without newline

4. EMPTY ARGUMENTS:
   - echo -n
       -> prints nothing, no newline

5. SPECIAL CHARACTERS:
   - echo -n "line1\nline2"
       -> prints literally "line1\nline2" (no interpretation)

EXPECTED OUTPUT EXAMPLES:

Success cases:
$ echo -n "hello world"
hello world$    (no newline after output)

$ echo -n
$               (no output, no newline)

$ echo -nnn "test"
test$           (no newline)

Error cases:
- None expected for -n option; any arguments after -n treated as text
- 
COMPREHENSIVE TEST CASES FOR pwd COMMAND:

1. Basic functionality:
   pwd                    -> prints current working directory
   pwd arg1                -> ignores arguments and prints current directory
   pwd ""                  -> prints current directory (empty string argument ignored)

2. Edge cases:
   Current directory deleted while running:
      mkdir /tmp/test_dir
      cd /tmp/test_dir
      # In another terminal: rm -rf /tmp/test_dir
      pwd                   -> should handle ENOENT gracefully with an error message

   Permission denied on parent directory:
      mkdir /tmp/test_perm
      chmod 000 /tmp/test_perm
      cd /tmp/test_perm
      pwd                   -> should print permission denied error (EACCES)

   Very long path (approaching PATH_MAX):
      # Create deeply nested directories and cd into it
      pwd                   -> should print full path or error if too long (ENAMETOOLONG)

3. Memory allocation failures:
   pwd                    -> if system out of memory, should print an error message (ENOMEM)

4. Argument handling:
   pwd arg1 arg2          -> should ignore all arguments and print current directory

5. Unknown errors:
   pwd                    -> any unexpected getcwd() failure should print a generic error with strerror(errno)

EXPECTED OUTPUT EXAMPLES:

Success cases:
$ pwd
/home/user

$ pwd arg1 arg2
/home/user

Error cases:
$ pwd
pwd: Current directory was deleted (ENOENT)

$ pwd
pwd: Permission denied while accessing parent directory (EACCES)

$ pwd
pwd: Path name too long (ENAMETOOLONG)

$ pwd
pwd: Out of memory (ENOMEM)

$ pwd
pwd: Unknown error: <error message>

COMPREHENSIVE TEST CASES FOR cd COMMAND::

1. Basic functionality:
   cd                    -> goes to $HOME
   cd ~                  -> goes to $HOME  
   cd /path/to/dir       -> goes to absolute path
   cd relative/path      -> goes to relative path
   cd ..                 -> goes to parent directory
   cd -                  -> goes to $OLDPWD and prints it

2. Edge cases:
   cd ~/Documents        -> expands ~ to $HOME/Documents
   cd nonexistent        -> error: No such file or directory
   cd /etc/shadow        -> error: Permission denied (if no read access)
   cd /etc/passwd        -> error: Not a directory
   cd arg1 arg2          -> error: too many arguments

3. Environment variable edge cases:
   unset HOME; cd        -> error: HOME not set
   unset OLDPWD; cd -    -> error: OLDPWD not set
   
4. Symbolic link handling:
   cd /path/to/symlink   -> follows the symlink (logical resolution)

5. Error conditions:
   cd ""                 -> goes to current directory (empty string)
   cd " "                -> error: No such file or directory (space)

EXPECTED OUTPUT EXAMPLES:
Success cases:
$ cd
$ pwd
/home/user

$ cd -
/previous/directory
$ pwd  
/previous/directory

Error cases:
$ cd nonexistent
cd: nonexistent: No such file or directory

$ unset HOME
$ cd
cd: HOME not set

$ unset OLDPWD  
$ cd -
cd: OLDPWD not set

$ cd arg1 arg2
cd: too many arguments

$ cd /etc/passwd
cd: /etc/passwd: Not a directory

COMPREHENSIVE TEST CASES FOR exit COMMAND:

1. Basic functionality:
   exit                   -> exits shell with last command status (0 if first command)
   exit 0                 -> exits shell with status 0
   exit 42                -> exits shell with status 42
   exit 256               -> exits shell with status 0 (256 % 256)
   exit -1                -> exits shell with status 255
   exit +42               -> exits shell with status 42

2. Error handling for invalid numeric arguments:
   exit abc               -> prints error: numeric argument required, exits with status 255
   exit 42abc             -> prints error: numeric argument required, exits with status 255
   exit 2147483648        -> prints error: numeric argument required (overflow), exits with status 255
   exit ""                -> prints error: numeric argument required, exits with status 255
   exit "  42  "          -> trims spaces and exits with status 42

3. Argument count handling:
   exit 42 extra          -> prints error: too many arguments, returns 1 and DOES NOT exit
   exit abc extra         -> prints error: numeric argument required, exits with status 255

EXPECTED OUTPUT EXAMPLES:

Success cases:
$ exit
(exit with last status or 0)

$ exit 0
(exit with status 0)

$ exit 42
(exit with status 42)

$ exit 256
(exit with status 0)

$ exit -1
(exit with status 255)

$ exit +42
(exit with status 42)

Error cases:
$ exit abc
exit: abc: numeric argument required
(exit with status 255)

$ exit 42abc
exit: 42abc: numeric argument required
(exit with status 255)

$ exit 2147483648
exit: 2147483648: numeric argument required
(exit with status 255)

$ exit ""
exit: : numeric argument required
(exit with status 255)

$ exit 42 extra
exit: too many arguments
(does not exit, returns 1)

$ exit abc extra
exit: abc: numeric argument required
(exit with status 255)

COMPREHENSIVE TEST CASES FOR export COMMAND:

1. VALID IDENTIFIERS:
   export VAR
   export _VAR
   export VAR123
   export _123
   export __VAR__

2. INVALID IDENTIFIERS:
   export 123VAR          (starts with digit - invalid)
   export VAR-NAME        (contains hyphen - invalid)
   export VAR.NAME        (contains dot - invalid)
   export VAR@NAME        (contains special char - invalid)
   export ""              (empty string)
   export "123"           (quoted number - invalid)

3. ASSIGNMENT FORMATS:
   export VAR=value
   export VAR=""          (empty value)
   export VAR="quoted value"
   export VAR='single quoted'
   export VAR=value1 VAR2=value2  (multiple assignments)

4. APPEND OPERATION:
   export VAR+=value      (append to existing variable)
   export NEWVAR+=value   (append to non-existing variable, behaves like assignment)
   export VAR+=           (append empty string)

5. SPECIAL VALUES:
   export VAR=$OTHER      (variable expansion if implemented)
   export VAR="$OTHER"    (quoted expansion)
   export PATH=/bin:$PATH (path manipulation)

6. NO ARGUMENTS:
   export                 (prints all exported variables in sorted order)

7. MIXED VALID/INVALID ARGUMENTS:
   export VALID=1 123INVALID=2 VALID2=3
   - Should set VALID=1
   - Print error for 123INVALID=2 (invalid identifier)
   - Set VALID2=3
   - Return exit status 1 (due to at least one failure)

8. WHITESPACE & QUOTES:
   export VAR="value with spaces"
   export VAR='value with spaces'
   export VAR=value\ with\ spaces

9. EXISTING VARIABLES:
   export existing_var    (no change if variable exists)
   export existing_var=new_value (updates existing variable)
   export new_var existing_var=value (mixed new and existing variables)

10. RETURN STATUS:
    - If all arguments valid and assignments succeed: return 0
    - If any argument invalid: print errors and return 1
    - Multiple arguments with some failures: return 1

EXPECTED OUTPUT EXAMPLES:

Success cases:
$ export VAR=value
$ export _VAR
$ export VAR1 VAR2=value2
$ export VAR+="append"
$ export                  # prints all exported variables

Error cases:
$ export 123VAR
export: `123VAR': not a valid identifier

$ export VAR-NAME=value
export: `VAR-NAME': not a valid identifier

$ export VALID=1 123INVALID=2
export: `123INVALID': not a valid identifier
(exit status 1)

COMPREHENSIVE TEST CASES FOR unset COMMAND:

1. VALID VS INVALID VARIABLE NAMES:
   - Valid: Must start with letter or underscore, followed by alphanumeric or underscore
       unset VAR_1
       unset _var
   - Invalid: Starts with number, contains spaces or special chars
       unset 1VAR         (invalid)
       unset VAR-NAME     (invalid)
       unset "VAR NAME"   (invalid)

2. MATCHING RULES:
   - Exact match only: 
       unset PATH          (removes PATH)
       unset PATHNAME      (does not remove PATH)
   - Case sensitive:
       unset PATH          (removes PATH)
       unset path          (does not remove PATH)

3. MULTIPLE VARIABLES:
   - Process all args:
       unset VAR1 VAR2 VAR3
   - Continue on error:
       unset VAR1 invalid-var VAR2
   - Return exit code 0 if all succeed, 1 if any invalid names

4. NON-EXISTENT VARIABLES:
   - Not an error to unset non-existent variables:
       unset NON_EXISTENT_VAR  (no error, success)

5. READ-ONLY / SPECIAL VARIABLES:
   - Prevent unsetting critical variables like PATH, HOME
   - Prints error message if attempted:
       unset PATH             (error: read-only variable)
   - Configurable list of protected vars

6. MEMORY MANAGEMENT:
   - Frees removed variable strings properly
   - Shifts remaining variables in-place (no realloc)
   - Maintains null-termination of environment array

7. EMPTY ENVIRONMENT / NO ARGUMENTS:
   - No arguments: valid, returns success (0)
       unset
   - Empty environment handled gracefully
   - Null pointers safely handled

8. OPTION HANDLING:
   - Rejects options starting with '-':
       unset -v              (error: invalid option)
       unset -              (error: invalid identifier)
   - Prints usage/help message on invalid options

9. ERROR REPORTING:
   - Clear error messages to stderr:
       unset: `123VAR': not a valid identifier
       unset: `PATH': read-only variable
   - Exit codes:
       0 - success (all valid)
       1 - general error (invalid identifiers)
       2 - usage error (invalid options)

10. POSIX COMPLIANCE:
    - Follows POSIX variable naming rules
    - Behavior matches bash/POSIX shells
    - Uses standard shell exit codes

EXPECTED OUTPUT EXAMPLES:

Success cases:
$ unset VAR1 VAR2
$ unset NON_EXISTENT_VAR

Error cases:
$ unset 123VAR
unset: `123VAR': not a valid identifier

$ unset VAR-NAME
unset: `VAR-NAME': not a valid identifier

$ unset PATH
unset: `PATH': read-only variable

COMPREHENSIVE TEST CASES FOR env COMMAND:

1. BASIC FUNCTIONALITY:
   - env
       -> prints all current environment variables exactly as provided

2. ENVIRONMENT MODIFICATION:
   - None applied, since no options or arguments given

3. INVALID OPTIONS & ARGUMENTS:
   - Not applicable (no options or arguments)

4. NO COMMAND GIVEN:
   - env alone prints current environment variables

5. EMPTY ENVIRONMENT:
   - If environment is empty, env prints nothing

6. COMMAND EXECUTION:
   - Not applicable (no command supplied)

7. MULTIPLE ASSIGNMENTS & UNSETS:
   - Not applicable

8. ENVIRONMENT PERSISTENCE:
   - No changes; env just prints current environment

9. SPECIAL CASES:
   - env "" or empty string argument not provided, so no effect

EXPECTED OUTPUT EXAMPLES:
Success cases:
$ env
USER=user
PATH=/usr/bin:/bin
HOME=/home/user
...

Error cases:
- None expected since no options/arguments given
