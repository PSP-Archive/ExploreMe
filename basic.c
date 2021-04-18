#include "basic.h"

void Aff_Interface()//Just displays the interface ... it's the same one as in protect me, and other HBs I made.
{
	pspDebugScreenSetTextColor(color_menu);
	pspDebugScreenSetXY(0,0);
	printf("%s",tstyle);//68
	pspDebugScreenSetXY(0,1);
	printf("%c%c                                                                %c%c",tstyle[0],tstyle[0],tstyle[0],tstyle[0]);
	pspDebugScreenSetTextColor(color_title);
	pspDebugScreenSetXY(centert(NV),1);
	printf("%s",NV);
	pspDebugScreenSetTextColor(color_menu);
	pspDebugScreenSetXY(0,2);
	printf("%s",tstyle);//68
	pspDebugScreenSetTextColor(color_mess);
	pspDebugScreenSetXY(0,3);
	printf("%s",tstyle);//68
	pspDebugScreenSetXY(0,6);
	printf("%s",tstyle);//68
	pspDebugScreenSetTextColor(color_mess);
	pspDebugScreenSetXY(0,22);
	printf("%s",tstyle);//68
	pspDebugScreenSetXY(0,24);
	printf("%s",tstyle);//68
	
	pspDebugScreenSetTextColor(color_menu);
	pspDebugScreenSetXY(0,25);
	printf("%s",tstyle);//68
	pspDebugScreenSetXY(0,32);
	printf("%s",tstyle);//68//Last one ^^
}

/*Useful functions*/
int exit_callback(int arg1, int arg2, void *common){ 
  sceKernelExitGame(); 
  return 0; 
}

int CallbackThread(SceSize args, void *argp){ 
  int cbid; 
 
  cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL); 
  sceKernelRegisterExitCallback(cbid); 
  
  sceKernelSleepThreadCB(); 
  
  return 0; 
} 

int SetupCallbacks(void){ 
  int thid = 0; 
  
  thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0); 
  if(thid >= 0) { 
    sceKernelStartThread(thid, 0, 0); 
  } 
  
  return thid; 
} 

/*Little function to center a text horizontaly (it returns the x value of the text)*/
int centert(char *chaine){
	int x1 = -1;
	int length = 0;
	length = strlen(chaine);
	 x1 = 34-(length/2);
	return x1;
}



/*Splash screen, will only be displayed on the first use of the homebrew... checking that with the conf file*/
int Display_Splash_Iso(void){
	FILE *fd = NULL;
	fd = fopen("app.conf","r");
	if(fd==NULL)
	{
		fclose(fd);
		fd = fopen("app.conf","w+");
		fclose(fd);
		fd = NULL;
	}
	else
	{
		fclose(fd);
		fd = NULL;
		return 0;
	}
	int i = 0;
	int x = 0;
	char *web1 = "Visit my website:";
	char *web2 = "http://maxence-dev.blogspot.com/";
	char *title1 = "Maxence Ardouin Presents:";
	char *iso_prev = "";//if you want to display any message here... I had no idea so, just left it blank
	pspDebugScreenSetBackColor(0x00000000);
	pspDebugScreenSetTextColor(0xffffffff);
	
	
	while(x<=centert(title1))
	{
		if(x!=0)
		{
			pspDebugScreenSetXY(x-2,5);
			printf("  ");
		}
		pspDebugScreenSetXY(x,5);
		printf("%s",title1);
		wait(1.5);
		x++;
	}
	x = 0;
	wait(5);
	
	
	
	while(x<=centert(NV))
	{
		if(x!=0)
		{
			pspDebugScreenSetXY(x-2,10);
			printf("  ");
		}
		pspDebugScreenSetXY(x,10);
		printf("%s",NV);
		wait(1.5);
		x++;
	}
	x=0;
	wait(5);
	
	
	pspDebugScreenSetTextColor(color_imp);
	
	
	while(x<=centert(iso_prev))
	{
		if(x!=0)
		{
			pspDebugScreenSetXY(x-2,16);
			printf("  ");
		}
		pspDebugScreenSetXY(x,16);
		printf("%s",iso_prev);
		wait(1.5);
		x++;
	}
	x=0;
	pspDebugScreenSetTextColor(color_mess);
	while(x<=centert(web1))
	{
		if(x!=0)
		{
			pspDebugScreenSetXY(x-2,20);
			printf("  ");
		}
		pspDebugScreenSetXY(x,20);
		printf("%s",web1);
		wait(1.5);
		x++;
	}
	x=0;
	
	while(x<=centert(web2))
	{
		if(x!=0)
		{
			pspDebugScreenSetXY(x-2,22);
			printf("  ");
		}
		pspDebugScreenSetXY(x,22);
		printf("%s",web2);
		wait(1.5);
		x++;
	}
	x=0;
	wait(5);
	while(1){
		 sceCtrlPeekBufferPositive(&pad, 1);
		 if(pad.Buttons & PSP_CTRL_START)
		 {
			 break;
		 }
		 i++;
		 if(i<=7500)
		 {
			 pspDebugScreenSetTextColor(0xffffffff);
			 pspDebugScreenSetXY(centert("Press START."),28);
			 printf("Press START.");
		 }
		 if(i>=7500)
		 {
			  pspDebugScreenSetTextColor(0x00000000);
			  pspDebugScreenSetXY(centert("Press START."),28);
			  printf("Press START.");
			  if(i>=10000)(i = 0);
		 }
		 sceCtrlPeekBufferPositive(&pad, 1);
	}
	x = 0;
	while(1)
	{
		sceCtrlPeekBufferPositive(&pad, 1);
		if(!pad.Buttons)
		{
			break;
		}
		if(x>=1000*1000)
		{
			pspDebugScreenSetTextColor(0xffffffff);
			pspDebugScreenSetXY(centert("Please, release this Button."),30);
			printf("Please, release this Button.");
		}
		x++;
	}
	title1 = NULL;
	iso_prev = NULL;
	pspDebugScreenClear();
	return 1;
}


void Credits(int end)
{
	pspDebugScreenClear();
	Aff_Interface();
	pspDebugScreenSetXY(2,7);
	pspDebugScreenSetTextColor(0x000A0AEE);
	printf("Open Source File Browser");
	pspDebugScreenSetXY(5,11);
	pspDebugScreenSetTextColor(0xffffffff);
	printf("By Maxence Ardouin");
	pspDebugScreenSetXY(5,13);
	printf("01 oct 2008");
	pspDebugScreenSetXY(5,15);
	printf("Released under GPL");
	pspDebugScreenSetXY(5,17);
	printf("http://maxence-dev.blogspot.com/");
	pspDebugScreenSetXY(5,18);
	printf("maxthebest.dev@gmail.com");
	SceCtrlData pad;
	if(end==0)
	{
		while(1){
			sceCtrlReadBufferPositive (&pad, 1);
			if(pad.Buttons & PSP_CTRL_START)
			{
				break;
			}
			if(pad.Buttons & PSP_CTRL_TRIANGLE)
			{
				break;
			}
			if(pad.Buttons & PSP_CTRL_CIRCLE)
			{
				break;
			}
		}
	}
	else if (end==1)
	{
		wait(10);
	}
	pspDebugScreenClear();
}
