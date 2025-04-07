#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/proc.h>
#include <sys/systm.h>

MODULE(MODULE_CLASS_MISC, lab3, NULL);

static int
lab3_modcmd(modcmd_t cmd, void *arg)
{
    struct proc *p;

    switch (cmd) {
    case MODULE_CMD_INIT:
        printf("Lab3: Process list (Trofimenko Dmitriy)\n");
        mutex_enter(&proc_lock);
        PROCLIST_FOREACH(p, &allproc) {
            printf("Image: %s, PID: %d, PPID: %d\n",
                   p->p_comm, p->p_pid, p->p_pptr->p_pid);
        }
        mutex_exit(&proc_lock);
        return 0;

    case MODULE_CMD_FINI:
        printf("Lab3: Module unloaded\n");
        return 0;

    default:
        return ENOTTY;
    }
}
