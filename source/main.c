#include <string.h>
#include <stdio.h>

#include <switch.h>

int main(int argc, char **argv)
{
    consoleInit(NULL);
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);
    PadState pad;
    padInitializeDefault(&pad);

    printf("Hello World!\n");

    Result rc=0;

    FILE *file;
    
    if (file = fopen("/config.log", "r")) 
    {
        fclose(file);
        printf("file exists\n");
    }
    else
    {
        printf("file doesn't exist\n");
    }

    rc = fsdevUnmountAll();
    printf("fsdevUnmountAll(): 0x%x\n", rc);

    if (file = fopen("/config.log", "r")) 
    {
        fclose(file);
        printf("file exists\n");
    }
    else
    {
        printf("file doesn't exist\n");
    }

    rc = romfsInit();
    printf("romfsInit(): 0x%x\n", rc);

    if (file = fopen("/config.log", "r")) 
    {
        fclose(file);
        printf("file exists\n");
    }
    else
    {
        printf("file doesn't exist\n");
    }

    while(appletMainLoop())
    {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);
        if (kDown & HidNpadButton_Plus) break;
        consoleUpdate(NULL);
    }
    consoleExit(NULL);
    return 0;
}