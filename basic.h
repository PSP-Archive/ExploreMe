/*useful defines*/
#define printf pspDebugScreenPrintf
#define mkdir sceIoMkdir

/*Project name*/
#define NV "Open Source File Browser"
/*Headers fonction*/
void Aff_Interface();
void Display(char message[67],int t9);
int Display_Splash_Iso(void);
int centert(char *chaine);
void Credits();
int exit_callback(int arg1, int arg2, void *common);
int CallbackThread(SceSize args, void *argp);
int SetupCallbacks(void);
