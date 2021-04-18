/*
Project: ExploreMe started on: 30 june 08
Maxence Ardouin
http://maxence-dev.blogspot.com/
maxthebest.dev@gmail.com

Released under GPL on 01 oct 08
*/

#include <pspsdk.h>
#include <pspkernel.h>
#include <pspdisplay.h>
#include <psputility.h>
#include <pspctrl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <psptypes.h>
#include <pspdebug.h>
#include <dirent.h>
#include <pspiofilemgr.h>

SceCtrlData pad;		//Pad
void wait(int);

PSP_MODULE_INFO("Cryptool", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);


#define printf pspDebugScreenPrintf


/*On initialise toute les variables ici, sinon, c'est le bordel*/
struct dirent *lecture;		//dir list
FILE *Contact = NULL;		//contact file
DIR *rep = NULL;		//current dir
DIR *trep = NULL;		//tet dir
FILE *fd = NULL;		//selected file
FILE *tfd = NULL;		//test file
char listc[512][512];		//file list
char path[512][512];		//path
char rpath[1024];		//file array of path
char bpath[1024];		//same thing
char displ[11][512];		//display list
char *colors[] = {"Default","Matrix Green","Monotone","Hell Red","Deep Blue"};			//Theme names
char tstyle[69];		//theme style
int listd = 0;			//list num
int but = 0;			//check to avoid collisions
int listnum = 0;		//file numbers
int listsel[64];		//selection list in path
int pathn = 0;			//actual position in path
int back = -1;			//are we going forward or backward when changing dir?
int selection = 0;		//actual position of the cursor
int dispf[11][66];		//array of the 10 files displayed on the screen
int a = 0;			//Variable
int file = 0;			//file verification
int theme_style = 0;		//theme selector
int theme_color = 0;		//theme selector
int sel_style = 0;		//theme selector
int sel_color = 0;		//theme selector
int osel = 0;			//opt selector
int fosel = 0;			//file opt selector
int IRS = 0;			//IRShell?

//u32 color of the basic theme;
u32 color_mess = 0x00FF0000;
u32 color_sel0 = 0xFFFFFFFF;
u32 color_sel1 = 0xDDDDDDDD;
u32 color_sel2 = 0xBBBBBBBB;
u32 color_sel3 = 0x88888888;
u32 color_sel4 = 0x55555555;
u32 color_sel5 = 0x22222222;
u32 color_menu = 0x77777777;
u32 color_title = 0xFFFFFFFF;
u32 color_opts = 0xFFFFFFFF;
u32 color_imp = 0x000A0AEE;
/*Include other files                                           */
#include "basic.c"	
#include "theme.c"
/*All the functions*/
void ChangeDir(void);		//Changes directory: back, or forward.
void ListFiles(void);		//Lists all files in the actual dir
void DisplayFiles(void);	//Displays the file list on the screen
void DisplayMenu(char *);	//Displays the complete menu
void DisplaySOptions(void);	//Software option
void DisplayFOptions(void);	//File       //
void DisplayInfo(void);		//Help
/*Fin des fonctions       */ 


int main(int argc, char *argv[])
{
	SetupCallbacks();
	pspDebugScreenInit();
	if(argv[1]!=NULL){//Mode Irshell
		IRS = 1;
		if(!ThemeSave(0)){
			DisplayInfo();
		}
		ThemeStyle(theme_style);
		ThemeColor(theme_color);
		Aff_Interface();
		sprintf(bpath,argv[1]);
		sprintf(rpath,"ms0:/");
		//
		pspDebugScreenSetTextColor(color_imp);
		pspDebugScreenSetXY(0,4);
		printf("  %s\n",bpath);
		pspDebugScreenSetXY(0,6);
		pspDebugScreenSetTextColor(color_mess);
		printf("%s",tstyle);
		a = 7;
		while(a!=21){
			pspDebugScreenSetXY(0,a);
			printf("                                                                    ");
			a++;
		}
		a = 0;
		pspDebugScreenSetTextColor(color_mess);
		pspDebugScreenSetXY(0,23);
		printf("IRShell Mode");
		pspDebugScreenSetXY(0,24);
		printf("%s",tstyle);//68s
		pspDebugScreenSetTextColor(color_menu);
		pspDebugScreenSetXY(0,25);
		printf("%s",tstyle);//68
		pspDebugScreenSetXY(0,32);
		printf("%s",tstyle);//68//Last one ^^
		pspDebugScreenSetTextColor(color_opts);
		pspDebugScreenSetXY(0,27);
		printf(" Up/Down to navigate\n X/O to select/go back\n /\\ to display option menu\n Home to exit");
		//
		DisplayFOptions();
		while(pad.Buttons){
			sceCtrlReadBufferPositive(&pad, 1);
		}
		while(1){
			sceCtrlReadBufferPositive(&pad, 1);
			DisplayFOptions();
			if(pad.Buttons & PSP_CTRL_UP){
				fosel--;
			}
			if(pad.Buttons & PSP_CTRL_DOWN){
				fosel++;
			}
			if(fosel>1)(fosel=0);
			if(fosel<0)(fosel=1);
			if(pad.Buttons & PSP_CTRL_CIRCLE){
				break;
			}
			if((pad.Buttons & PSP_CTRL_CROSS) && fosel==1){
				break;
			}
			if((pad.Buttons & PSP_CTRL_CROSS) && fosel==0){
				//Your action here...
				sceKernelDelayThread(10000*20);
				pspDebugScreenSetTextColor(color_mess);
				pspDebugScreenSetXY(0,23);
				printf("IRShell Mode              ");
			}
			while(pad.Buttons)(sceCtrlReadBufferPositive(&pad, 1));
		}
		pspDebugScreenSetTextColor(color_mess);
		pspDebugScreenSetXY(0,23);
		printf("Exiting...                 ");
		sceKernelExitGame();
		
	}
	else{//Real omebrew mode (not launched with irs, but just via xmb
		IRS = 0;
		if(!ThemeSave(0)){
			DisplayInfo();
		}
		ThemeStyle(theme_style);
		ThemeColor(theme_color);
		strcpy(path[0],"ms0:");
		sprintf(rpath,"ms0:");
		sprintf(bpath,"%s/",rpath);
		ListFiles();
		Aff_Interface();
		pspDebugScreenSetTextColor(color_imp);
		pspDebugScreenSetXY(0,4);
		printf("  %s\n",bpath);
		pspDebugScreenSetXY(0,6);
		pspDebugScreenSetTextColor(color_mess);
		printf("%s",tstyle);
		DisplayFiles();
		while(1){//main loop
			but = 0;
			sprintf(bpath,"%s/",rpath);
			sceCtrlReadBufferPositive(&pad, 1);
			if(pad.Buttons & PSP_CTRL_UP){
				selection--;
				if(selection<0){
					selection = listnum;
				}
			}
			if(pad.Buttons & PSP_CTRL_DOWN){
				selection++;
				if(selection>listnum){
					selection = 0;
				}
			}
			if(pad.Buttons & PSP_CTRL_TRIANGLE){
				DisplayMenu(" Software Options           ");
				while(pad.Buttons){
					sceCtrlReadBufferPositive(&pad, 1);
				}
				osel = 0;
				sel_color = theme_color;
				sel_style = theme_style;
				while(1){
					sceCtrlReadBufferPositive(&pad, 1);
					DisplaySOptions();
					if(pad.Buttons & PSP_CTRL_UP){
						osel--;
					}
					if(pad.Buttons & PSP_CTRL_DOWN){
						osel++;
					}
					if(osel>5)(osel=0);
					if(osel<0)(osel=5);
					if(pad.Buttons & PSP_CTRL_CIRCLE){
						ThemeColor(theme_color);
						ThemeStyle(theme_color);
						but = 1;
						break;
					}
					if(pad.Buttons & PSP_CTRL_CROSS && osel==4){
						ThemeColor(theme_color);
						ThemeStyle(theme_color);
						but = 2;
						break;
					}
					if(pad.Buttons & PSP_CTRL_CROSS && osel==3){//save & quit
						theme_color = sel_color;
						theme_style = sel_style;
						ThemeSave(1);
						but = 2;
						break;
					}
					if((pad.Buttons & PSP_CTRL_CROSS || pad.Buttons & PSP_CTRL_RIGHT) && osel==0){
						sel_style++;
						if(sel_style>10)(sel_style=0);
						ThemeStyle(sel_style);
						DisplayMenu(" Software Options           ");
						DisplaySOptions();
						while(pad.Buttons){
							sceCtrlReadBufferPositive(&pad, 1);
						}
					}
					if(pad.Buttons & PSP_CTRL_LEFT && osel==0){
						sel_style--;
						if(sel_style<0)(sel_style=10);
						ThemeStyle(sel_style);
						DisplayMenu(" Software Options           ");
						DisplaySOptions();
						while(pad.Buttons){
							sceCtrlReadBufferPositive(&pad, 1);
						}
					}
					if((pad.Buttons & PSP_CTRL_CROSS || pad.Buttons & PSP_CTRL_RIGHT) && osel==1){
						sel_color++;
						if(sel_color>4)(sel_color=0);
						ThemeColor(sel_color);
						DisplayMenu(" Software Options           ");
						DisplaySOptions();
						while(pad.Buttons){
							sceCtrlReadBufferPositive(&pad, 1);
						}
					}
					if(pad.Buttons & PSP_CTRL_LEFT && osel==1){
						sel_color--;
						if(sel_color<0)(sel_color=4);
						ThemeColor(sel_color);
						DisplayMenu(" Software Options           ");
						DisplaySOptions();
						while(pad.Buttons){
							sceCtrlReadBufferPositive(&pad, 1);
						}
					}
					if(pad.Buttons & PSP_CTRL_CROSS && osel==2){
						while(pad.Buttons)(sceCtrlReadBufferPositive(&pad, 1));
						DisplayInfo();
						while(pad.Buttons)(sceCtrlReadBufferPositive(&pad, 1));
						DisplayMenu(" Software Options           ");
						DisplaySOptions();
						while(pad.Buttons){
							sceCtrlReadBufferPositive(&pad, 1);
						}
					}
					if(pad.Buttons & PSP_CTRL_CROSS  && osel==5){
						pspDebugScreenSetTextColor(color_mess);
						pspDebugScreenSetXY(0,23);
						printf(" Exiting...         ");
						sceKernelDelayThread(10000*90);
						sceKernelExitGame();
					}
					while(pad.Buttons)(sceCtrlReadBufferPositive(&pad, 1));
				}
			}
			if((pad.Buttons & PSP_CTRL_CROSS || pad.Buttons & PSP_CTRL_RIGHT) && but!=2){//select actual file/dir
				back = 0;
				file = 0;
				sprintf(bpath,"%s/%s",rpath,listc[selection]);
				trep = opendir(bpath);
				tfd = fopen(bpath, "r");
				if(tfd!=NULL){//La séléction est un fichier
					DisplayMenu(" File Options           ");
					fosel = 0;
					while(pad.Buttons){
						sceCtrlReadBufferPositive(&pad, 1);
					}
					while(1){
						sceCtrlReadBufferPositive(&pad, 1);
						DisplayFOptions();
						if(pad.Buttons & PSP_CTRL_UP){
							fosel--;
							if(fosel<0)(fosel=1);
							while(pad.Buttons)(sceCtrlReadBufferPositive(&pad, 1));
						}
						if(pad.Buttons & PSP_CTRL_DOWN){
							fosel++;
							if(fosel>1)(fosel=0);
							while(pad.Buttons)(sceCtrlReadBufferPositive(&pad, 1));
						}
						if(pad.Buttons & PSP_CTRL_CIRCLE){
							but = 1;
							break;
						}
						if((pad.Buttons & PSP_CTRL_CROSS) && fosel==1){
							but = 1;
							break;
						}
						if((pad.Buttons & PSP_CTRL_CROSS) && fosel==0){
							//Your action
							pspDebugScreenSetTextColor(color_mess);
							pspDebugScreenSetXY(0,23);
							printf(" File Options              ");
							DisplayFOptions();
							sceKernelDelayThread(10000*100);
						}
					}
				}
				else if(trep && file == 0){//selection is a dir
					closedir(trep);
					sprintf(rpath,bpath);
					ChangeDir();
					ListFiles();
				}
				else{
				}
				sprintf(bpath,"%s/",rpath);
			}
			if((pad.Buttons & PSP_CTRL_CIRCLE || pad.Buttons & PSP_CTRL_LEFT)&& pathn>0 && but != 1){
				back = 1;
				ChangeDir();
				ListFiles();
			}
			if(pad.Buttons){
				Aff_Interface();
				pspDebugScreenSetTextColor(color_imp);
				pspDebugScreenSetXY(0,4);
				printf("  %s\n",bpath);
				pspDebugScreenSetXY(0,6);
				pspDebugScreenSetTextColor(color_mess);
				printf("%s",tstyle);
				DisplayFiles();
			}
			while(pad.Buttons){
				sceCtrlReadBufferPositive(&pad, 1);
			}
		}
	}
	return 0;
}

void DisplayFiles(){
	if(selection-5<0){
		listd = selection-5;
		while(listd<0){
			listd = listd + listnum;
		}
		sprintf(displ[0],"  -%s", listc[listd+1]);
		if(listnum<=4)(sprintf(displ[0]," "));
	}
	else{
		sprintf(displ[0],"  -%s",listc[selection-5]);
	}
	if(selection-4<0){
		listd = selection-4;
		while(listd<0){
			listd = listd + listnum;
		}
		sprintf(displ[1],"  -%s", listc[listd+1]);
		if(listnum<=3)(sprintf(displ[1]," "));
	}
	else{
		sprintf(displ[1],"  -%s",listc[selection-4]);
	}
	if(selection-3<0){
		listd = selection-3;
		while(listd<0){
			listd = listd + listnum;
		}
		sprintf(displ[2],"  -%s", listc[listd+1]);
		if(listnum<=2)(sprintf(displ[2]," "));
	}
	else{
		sprintf(displ[2],"  -%s",listc[selection-3]);
	}
	if(selection-2<0){
		listd = selection-2;
		while(listd<0){
			listd = listd + listnum;
		}
		sprintf(displ[3],"  -%s", listc[listd+1]);
		if(listnum<=1)(sprintf(displ[3]," "));
	}
	else{
		sprintf(displ[3],"  -%s",listc[selection-2]);
	}
	if(selection-1<0){
		listd = selection-1;
		while(listd<0){
			listd = listd + listnum;
		}
		sprintf(displ[4],"  -%s", listc[listd+1]);
	}
	else{
		sprintf(displ[4],"  -%s",listc[selection-1]);
	}
	sprintf(displ[5],"-->%s",listc[selection]);
	if(selection+1>listnum){
		listd = selection+1;
		while(listd>listnum){
			listd = listd - listnum;
		}
		sprintf(displ[6],"  -%s", listc[listd-1]);
	}
	else{
		sprintf(displ[6],"  -%s",listc[selection+1]);
	}
	if(selection+2>listnum){
		listd = selection+2;
		while(listd>listnum){
			listd = listd - listnum;
		}
		sprintf(displ[7],"  -%s", listc[listd-1]);
		if(listnum<=1)(sprintf(displ[7]," "));
	}
	else{
		sprintf(displ[7],"  -%s",listc[selection+2]);
	}
	if(selection+3>listnum){
		listd = selection+3;
		while(listd>listnum){
			listd = listd - listnum;
		}
		sprintf(displ[8],"  -%s", listc[listd-1]);
		if(listnum<=2)(sprintf(displ[8]," "));
	}
	else{
		sprintf(displ[8],"  -%s",listc[selection+3]);
	}
	if(selection+4>listnum){
		listd = selection+4;
		while(listd>listnum){
			listd = listd - listnum;
		}
		sprintf(displ[9],"  -%s", listc[listd-1]);
		if(listnum<=3)(sprintf(displ[9]," "));
	}
	else{
		sprintf(displ[9],"  -%s",listc[selection+4]);
	}
	if(selection+5>listnum){
		listd = selection+5;
		while(listd>listnum){
			listd = listd - listnum;
		}
		sprintf(displ[10],"  -%s", listc[listd-1]);
		if(listnum<=4)(sprintf(displ[10]," "));
	}
	else{
		sprintf(displ[10],"  -%s",listc[selection+5]);
	}
	pspDebugScreenSetXY(0,9);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,9);
	pspDebugScreenSetTextColor(color_sel5);
	printf("%s\n",displ[0]);
	pspDebugScreenSetXY(0,10);
	pspDebugScreenSetTextColor(color_sel4);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,10);
	printf("%s\n",displ[1]);
	pspDebugScreenSetXY(0,11);
	pspDebugScreenSetTextColor(color_sel3);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,11);
	printf("%s\n",displ[2]);
	pspDebugScreenSetXY(0,12);
	pspDebugScreenSetTextColor(color_sel2);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,12);
	printf("%s\n",displ[3]);
	pspDebugScreenSetXY(0,13);
	pspDebugScreenSetTextColor(color_sel1);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,13);
	printf("%s\n",displ[4]);
	pspDebugScreenSetXY(0,14);
	pspDebugScreenSetTextColor(color_sel0);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,14);
	printf("%s\n",displ[5]);
	pspDebugScreenSetXY(0,15);
	pspDebugScreenSetTextColor(color_sel1);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,15);
	printf("%s\n",displ[6]);
	pspDebugScreenSetXY(0,16);
	pspDebugScreenSetTextColor(color_sel2);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,16);
	printf("%s\n",displ[7]);
	pspDebugScreenSetXY(0,17);
	pspDebugScreenSetTextColor(color_sel3);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,17);
	printf("%s\n",displ[8]);
	pspDebugScreenSetXY(0,18);
	pspDebugScreenSetTextColor(color_sel4);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,18);
	printf("%s\n",displ[9]);
	pspDebugScreenSetXY(0,19);
	pspDebugScreenSetTextColor(color_sel5);
	printf("                                                                    ");
	pspDebugScreenSetXY(0,19);
	printf("%s\n",displ[10]);
	pspDebugScreenSetTextColor(color_mess);
	pspDebugScreenSetXY(0,23);
	printf(" File Browser         ");
	pspDebugScreenSetXY(0,27);
	pspDebugScreenSetTextColor(color_opts);
	printf(" Up/Down to navigate\n X/O to select/go back\n /\\ to display option menu\n Home to exit");
}

void ChangeDir(){
	if(!strcmp(listc[selection], ".") && back==0){
			back=2;
	}
	else if(!strcmp(listc[selection], "..") && back ==0){
			back=1;
	}
	if(back==0){
		listsel[pathn] = selection;
		pathn++;
		sprintf(path[pathn], listc[selection]);
		selection = 0;
	}
	else if (back==1){
		sprintf(path[pathn]," ");
		pathn--;
		selection = listsel[pathn];
	}
	else{
		selection = 0;
	}
	a = 1;
	sprintf(rpath,"ms0:");
	while(a<=pathn){
		sprintf(bpath,"%s",rpath);
		sprintf(rpath,"%s/%s",bpath,path[a]);
		a++;
	}
}

void ListFiles(){
	sprintf(bpath,"%s/",rpath);
	rep = opendir(bpath); 
	struct dirent* lecture;
	listnum = 0;
	while ((lecture = readdir(rep)))
	{
		sprintf(listc[listnum],"%s",lecture->d_name);
		listnum++;
	}
	closedir(rep);
	listnum--;
}


void DisplayMenu(char message[50]){
	Aff_Interface();
	pspDebugScreenSetTextColor(color_imp);
	pspDebugScreenSetXY(0,4);
	printf("  %s\n",bpath);
	pspDebugScreenSetXY(0,6);
	pspDebugScreenSetTextColor(color_mess);
	printf("%s",tstyle);
	DisplayFiles();
	a = 7;
	while(a!=21){
		pspDebugScreenSetXY(0,a);
		printf("                                                                    ");
		a++;
	}
	a = 0;
	pspDebugScreenSetTextColor(color_mess);
	pspDebugScreenSetXY(0,23);
	printf("%s",message);
	pspDebugScreenSetXY(0,24);
	printf("%s",tstyle);//68s
	pspDebugScreenSetTextColor(color_menu);
	pspDebugScreenSetXY(0,25);
	printf("%s",tstyle);//68
	pspDebugScreenSetXY(0,32);
	printf("%s",tstyle);//68//Last one ^^
	pspDebugScreenSetTextColor(color_opts);
	pspDebugScreenSetXY(0,27);
	printf(" Up/Down to navigate\n X/O to select/go back\n /\\ to display option menu\n Home to exit");
}

void DisplaySOptions(void){
	pspDebugScreenSetTextColor(color_sel0);
	pspDebugScreenSetXY(0,9);
	printf("-  Change theme style: %i  ",sel_style);
	pspDebugScreenSetXY(0,10);
	printf("-  Change theme color: %s     ",colors[sel_color]);
	pspDebugScreenSetXY(0,11);
	printf("-  See Software Info                       ");
	pspDebugScreenSetXY(0,12);
	printf("-  Save and Return to file browser");
	pspDebugScreenSetXY(0,13);
	printf("-  Return to file browser (changes won't be saved!)");
	pspDebugScreenSetXY(0,14);
	printf("-  Exit to XMB");
	pspDebugScreenSetXY(0,14);
	pspDebugScreenSetXY(0,15);
	pspDebugScreenSetXY(0,16);
	pspDebugScreenSetXY(0,17);
	pspDebugScreenSetXY(0,18);
	pspDebugScreenSetXY(0,19);
	pspDebugScreenSetXY(0,9+osel);
	printf("->");
}

void DisplayFOptions(void){
	pspDebugScreenSetTextColor(color_sel0);
	pspDebugScreenSetXY(0,9);
	printf("-  Do whatever set for this file");
	pspDebugScreenSetXY(0,10);
	printf("-  Back");
	pspDebugScreenSetXY(0,11);
	pspDebugScreenSetXY(0,12);
	pspDebugScreenSetXY(0,13);
	pspDebugScreenSetXY(0,14);
	pspDebugScreenSetXY(0,15);
	pspDebugScreenSetXY(0,16);
	pspDebugScreenSetXY(0,17);
	pspDebugScreenSetXY(0,18);
	pspDebugScreenSetXY(0,19);
	pspDebugScreenSetXY(0,9+fosel);
	printf("->");
}

void DisplayInfo(void){
	pspDebugScreenClear();
	pspDebugScreenSetTextColor(0x000000FF);
	pspDebugScreenSetXY(centert("ExploreMe by Maxence Ardouin"),0);
	printf("ExploreMe by Maxence Ardouin");
	pspDebugScreenSetXY(0,3);
	pspDebugScreenSetTextColor(0x000000FF);
	printf("\nEmail: maxthebest.dev@gmail.com\n");
	printf("\nWebsite: http://maxence-dev.blogspot.com/\n\n");
	printf("\n  What's that for?\n");
	pspDebugScreenSetTextColor(0xFFFFFFFF);
	printf("- Just a file browser, with a cool rotating display, and many different themes!\n");
	pspDebugScreenSetTextColor(0x000000FF);
	printf("\n\n  Who made it?\n");
	pspDebugScreenSetTextColor(0xFFFFFFFF);
	printf("- By Maxence but as I couldn't find any use for it yet, I thought YOU might find one\n");
	pspDebugScreenSetTextColor(0x000000FF);
	pspDebugScreenSetTextColor(0x000000FF);
	printf("\n\n  How can I help in this project?\n");
	pspDebugScreenSetTextColor(0xFFFFFFFF);
	printf("- Well, it's open source, so, it's YOUR project too, now!");
	pspDebugScreenSetTextColor(0x000000FF);
	printf("\n\n\nPress Any key to go back, and START to save my contact card on your PSP");
	while(!pad.Buttons)(sceCtrlReadBufferPositive(&pad, 1));
	if(pad.Buttons & PSP_CTRL_START){//just a stupid idea I had... still kind of cool, lol
		Contact = fopen("ms0:/Maxence_Contact.txt","w");
		fprintf(Contact,"Maxence Ardouin's Contact Card:\n\nHere are the different ways you have to contact me, or get more infos about my softs:\n\nE-Mail: maxthebest.dev@gmail.com\nInstant messenger: maxthebest.dev@hotmail.com\nBlog: http://maxence-dev.blogspot.com/\n\nDon't hesitate!");
		fclose(Contact);
	}
	pspDebugScreenClear();
}
