[READLINE]

    https://tiswww.case.edu/php/chet/readline/readline.html

    #include <stdio.h>
    #include <readline/readline.h>
    #include <readline/history.h>

char    *readline(const char *prompt)

    readline will read a line from the terminal and return it. If a prompt
    is provided it will display the prompt.
    the returned line is allocated with malloc and must be freed by the
    caller. the returned line has the final newline removed, so only the
    text of the line remains.

    a blank line returns an empty string. an EOF on a empty line returns
    NULL. an EOF on a non-empty line is treated as a newline.

    [INITIALIZATION]
    
    readline can be initialized with an inputrc file. the default path is
    "~/.inputrc" and "/etc/inputrc".

    [READLINE INTERNALS]

    void    rl_clear_history(void)

        Clear the history list by deleting all of the entries. Also frees
        private data readline stores in the history list.

    int rl_on_new_line(void)

        Tell update routines we have moved onto a new (empty) line, usually
        after outputtign a newline.

    void    rl_replace_line(const char *test, int clear_undo)

        Replaces the contents of rl_line_buffer with text. The point and mark
        are preserved, if possible. If clear_undo is non-zero, the undo list
        asscoiated with the current line is cleared.

    void    rl_redisplay(void)

        Change current display on screen to reflect contents of rl_line_buffer.

    [HISTORY INTERNALS]

    void    add_history(const char *string)

        Place string at the end of the history list. The associated data field
        (if any) is set to NULL.

[WAIT]

    #include <sys/wait.h>

    [WSTATUS]

        Wstatus vaiables are optional arguments for wait functions that can
        store the return value of chil processes. Wstatus should be examined
        with the approriate MACROS:

        [WSTATUS MACROS]

            Wstatus macros take an integer wstatus as argument instead of an
            integer pointer like the wait functions.

            WIFEXITED(wstatus)

                Returns true (1) if the child process terminated normally,
                through return from main or exit.

            WEXITSTATUS(wstatus)
                
                Only use after checking for a normal termination with WIFEXITED!

                Returns the exit status of the child process. Consists of the
                least significant 8 buts of the status argument that the child
                specified in return fro mmain or exit.

            WIFSIGNALED(wstatus)

                Returns true if the child process was terminated by a signal.

            WTERMSIG(wstatus)

                Only use after checking for a signal termiantion with WIFSIGNALED!

                Returns the number of the signal that caused the child process
                to terimnate.

            WCOREDUMP(wstatus)

                Only use after checking for a signal termiantion with WIFSIGNALED!
                
                Return true if the child produced a core dump.

            WIFSTOPPED(wstatus)

    pid_t   wait(int *_Nullable wstatus)

        Suspends execution of the calling thread until one of it's children
        terminates.

        On success, returns the process ID of the terminated child; On failure
        returns -1.

        wait is equal to waitpid(-1, wstatus, 0).

    pid_t   waitpid(pid_t pid, int *_Nullable wstatus, int options)

        Suspends execution of the calling thread until a child specified by the
        pid argument has changed state. By default waitpid only waits for
        terminated children, but this behavior is modifiable via the options
        argument.

        The value of pid can be:

            < -1    meaning wait for any child process whose process group ID
                    is equal to the absolute value of pid.

            -1      meaning wait for any child process.

            0       meaning wait for any child process, whose process group ID
                    is equal to that of the calling process at the time of the
                    call to waitpid. (???)

            > 0     meaning wait for the child process whose ID is equal to the
                    value of pid.

        [OPTIONS]

            WNOHANG:
                return immediately if no child has exited.

            WUNTRACED:
                also return if a child has stopped (but not traced via ptrace).
                Status for traced children which have stopped is provided even
                if this option is not specified.

            WCONTINUED:
                also return if a stopped child hs been resumed by delivery of
                SIGCONT.

    #include <sys/types.h>
    #include <sys/time.h>
    #include <sys/resource.h>

    pid_t   wait3(int *_Nullable wstatus, int options, struct rusage *rusage)
    pid_t   wait4(pid_t pid, int *_Nullable wstatus, int options, struct rusage *rusage)

        These functions are obsolete use waitpid or waitid in new programs.

        wait3 is equal to waitpid(-1, wstatus, options).

        wait4 is equal to waitpid(pid, wstatus, options).

[DIRECTORIES]

    #include <unistd.h>

    char    *getcwd(char *buf, size_t size)

        Returns as null-terminated string containing an 
