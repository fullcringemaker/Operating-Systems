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
        printf("Trofimenko Dmitriy: Starting process list...\n");

        if (!mutex_owned(&proc_lock)) {
            mutex_enter(&proc_lock);
        }

        PROCLIST_FOREACH(p, &allproc) {
            uprintf("Image: %s, PID: %d, PPID: %d\n",
                   p->p_comm,
                   p->p_pid,
                   p->p_ppid ? p->p_ppid->p_pid : 0);
        }

        if (mutex_owned(&proc_lock)) {
            mutex_exit(&proc_lock);
        }
        break;

    case MODULE_CMD_FINI:
        printf("Trofimenko Dmitriy: Module unloaded\n");
        break;

    default:
        return ENOTTY;
    }

    return 0;
}
