/*Theme manager*/


int ThemeSave(int t){
	FILE *fd = NULL;
	if(t==0){
		fd = fopen("EBOOT.CFG","r");
		if(fd!=NULL){
			fscanf(fd,"%i;%i",&theme_style,&theme_color);
			if(theme_style>=0 && theme_color>=0){
				fclose(fd);
				return 1;
			}
			fclose(fd);
		}
		fd = fopen("EBOOT.CFG","w");
		fprintf(fd,"0;0");
		fclose(fd);
		theme_style = 0;
		theme_color = 0;
	}
	else if(t==1){
		fd = fopen("EBOOT.CFG","w");
		fprintf(fd,"%i;%i",theme_style,theme_color);
		fclose(fd);
	}
	return 0;
}

void ThemeColor(t){
	if(t==0){//Basic
		color_mess = 0x00FF0000;
		color_sel0 = 0xFFFFFFFF;
		color_sel1 = 0xDDDDDDDD;
		color_sel2 = 0xBBBBBBBB;
		color_sel3 = 0x88888888;
		color_sel4 = 0x55555555;
		color_sel5 = 0x22222222;
		color_menu = 0x77777777;
		color_title = 0xFFFFFFFF;
		color_opts = 0xFFFFFFFF;
		color_imp = 0x000A0AEE;
	}
	if(t==1){//Vert
		color_mess = 0x0000E000;     	//RGB(0,255,0);
		color_sel0 = 0x0000FF00;	//RGB(0,255,0);
		color_sel1 = 0x0000D200;	//RGB(0,210,0);
		color_sel2 = 0x0000AF00;	//RGB(0,175,0);
		color_sel3 = 0x00007000;	//RGB(0,120,0);
		color_sel4 = 0x00004000;	//RGB(0,80,0);
		color_sel5 = 0x00001D00;	//RGB(0,50,0);
		color_menu = 0x00003200;	//RGB(0,100,0);
		color_title = 0x0000FF00;
		color_opts = 0x00008200;	//RGB(0,130,0);
		color_imp = 0x0000FF00;		//RGB(0,255,0);
	}
	if(t==2){//Tons de gris
		color_mess = 0xE0E0E0E0;
		color_sel0 = 0xFFFFFFFF;
		color_sel1 = 0xBBBBBBBB;
		color_sel2 = 0x99999999;
		color_sel3 = 0x66666666;
		color_sel4 = 0x33333333;
		color_sel5 = 0x11111111;
		color_menu = 0x22222222;
		color_title = 0xFFFFFFFF;
		color_opts = 0xEEEEEEEE;
		color_imp = 0xFFFFFFFF;
	}
	if(t==3){//Hell
		color_mess = 0x000452D8;
		color_sel0 = 0x000000FF;
		color_sel1 = 0x000000A9;
		color_sel2 = 0x00000076;
		color_sel3 = 0x00000050;
		color_sel4 = 0x00000030;
		color_sel5 = 0x00000015;
		color_menu = 0x000000AA;
		color_title = 0x000000FF;
		color_opts = 0x000000FF;
		color_imp = 0x000091FF;
	}
	if(t==4){//Blue
		color_mess = 0x00FF2F00;
		color_sel0 = 0x00FF0000;
		color_sel1 = 0x00a90000;
		color_sel2 = 0x00760000;
		color_sel3 = 0x00500000;
		color_sel4 = 0x00300000;
		color_sel5 = 0x00150000;
		color_menu = 0x00300000;
		color_title = 0x00FF0000;
		color_opts = 0x00FF0000;
		color_imp = 0x00FF7811;
	}
}

void ThemeStyle(int t){
	if(t==0){
		sprintf(tstyle,"--------------------------------------------------------------------");
	}
	else if(t==1){
		sprintf(tstyle,"********************************************************************");
	}
	else if(t==2){
		sprintf(tstyle,"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo");
	}
	else if(t==3){
		sprintf(tstyle,"####################################################################");
	}
	else if(t==4){
		sprintf(tstyle,"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
	}
	else if(t==5){
		sprintf(tstyle,"....................................................................");
	}
	else if(t==6){
		sprintf(tstyle,"////////////////////////////////////////////////////////////////////");
	}
	else if(t==7){
		sprintf(tstyle,"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");
	}
	else if(t==8){
		sprintf(tstyle,"____________________________________________________________________");
	}
	else if(t==9){
		sprintf(tstyle,"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
	}
	else if(t==10){
		sprintf(tstyle,"====================================================================");
	}
	
}
