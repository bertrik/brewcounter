#include <Arduino.h>
#include <I2S.h>

#include <MiniShell.h>

static MiniShell shell(&Serial);

static void show_help(const cmd_t *cmds)
{
    for (const cmd_t * cmd = cmds; cmd->cmd != NULL; cmd++) {
        printf("%10s: %s\n", cmd->name, cmd->help);
    }
}

static int do_help(int argc, char *argv[]);

const cmd_t commands[] = {
    { "help", do_help, "Show help" },
    { NULL, NULL, NULL }
};

static int do_help(int argc, char *argv[])
{
    show_help(commands);
    return 0;
}

void setup(void)
{
    Serial.begin(115200);

    i2s_rxtx_begin(true, false);
    i2s_set_rate(16000);
}

void loop(void)
{
    // command line processing
    shell.process(">", commands);
}
