## General kernel programming

[https://www.kernel.org/doc/html/v4.15/process/adding-syscalls.html]

The following looks very relevant to code movements:
[System calls returning elsewhere](https://www.kernel.org/doc/html/v4.15/process/adding-syscalls.html#system-calls-returning-elsewhere)

[KUnwind: Fast user-space backtrace for Linux (but from the kernel)](https://github.com/giraldeau/kunwind)

[Interesting one, doing task (thread) switch?](https://elixir.bootlin.com/linux/v4.15.18/source/arch/x86/kernel/process_64.c#L397)
[This is about ARM but has pointers to arch agnostic stuff](https://stackoverflow.com/questions/6746344/how-to-get-saved-registers-of-a-process-in-linux-arm-architecture)


## Compiling kernel modules

[https://paguilar.org/?p=7]

## Manipulating tasks

[https://stackoverflow.com/questions/56531880/how-does-the-kernel-use-task-struct]
[https://stackoverflow.com/questions/9071749/an-alternative-for-tasklist-lock-in-a-module]
[https://lore.kernel.org/lkml/20150105104616.GA21260@krava.brq.redhat.com/T/]
