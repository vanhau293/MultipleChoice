#pragma once
//#include "mylib.h"
#include <iostream>
#define Max_ND 50
#define ButtonON 1
#define ButtonOFF 0
#include "KhaiBao.h"
#include "ThuVienDoHoa.h"
struct ButtonMH{
	int dai;
	int rong;
	MonHoc mh;
};
struct Button{
	int dai;
	int rong;
	char noiDung[Max_ND];
};
void ButtonNormalCH(){
	SetColor(7);
	SetBGColor(0);
}
void ButtonHighLightCH(){
	SetColor(7);
	SetBGColor(10);
}
void ButtonNormal2(){
	SetColor(6);
	SetBGColor(15);
}
void ButtonNormal(){
	SetColor(6);
	SetBGColor(0);
}
void ButtonHighLight(){
	SetColor(14);
	SetBGColor(6);
}
Button CreateButton(int dai,int rong,char *ND)
{
	
	Button tmp;
	tmp.dai=dai;
	tmp.rong=rong;
	strcpy(tmp.noiDung,ND);
	return tmp;
}
void Canbangchuoi(char*s,int x0,int x1,int y)//x0 = vi tri dau//x2 vi tri cuoi
{
	gotoxy(((x0+x1)/2-(strlen(s)/2)),y);cout<<s; // noi dung nam giua
}
void DrawButton(Button button,int x,int y,bool status)
{
	gotoxy(x,y);
	if(status==ButtonON){
		ButtonHighLight();
	}else ButtonNormal2();
	for(int i=y;i<y+button.dai;i++)
	{	
		gotoxy(x,i);
		for(int j=x;j<x+button.rong;j++)
		{
			cout<<" ";
		}
		cout<<'\n';
	}
	//box(x,y,button.rong,button.dai,11,1);
	Canbangchuoi(button.noiDung,x+1,x+button.rong,y+1);
}
ButtonMH CreateButtonMH(int dai,int rong,MonHoc mh)
{
	ButtonMH tmp;
	tmp.dai=dai;
	tmp.rong=rong;
	tmp.mh = mh;
	return tmp;
}
void inThongTin(MonHoc mh, int y, int stt){
		gotoxy(15,y);
		cout<<stt;
		gotoxy(23,y);
		cout<<mh.maMonHoc;
		gotoxy(37,y);
		cout<<mh.tenMonHoc;
		gotoxy(85,y);
		cout<<mh.ds.sl;
		textcolor(10);
		gotoxy(13,y);
	  	printf("%c",186);
		gotoxy(18,y);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(35,y);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(80,y);
	  	printf("%c",186); // dong thang giua
		
		gotoxy(90,y);
	  	printf("%c",186);
}
void inLop(Lop lop, int y, int stt){
		gotoxy(16,y);
		cout<<stt;
		gotoxy(25,y);
		cout<<lop.maLop;
		gotoxy(43,y);
		cout<<lop.tenLop;
		textcolor(10);
		gotoxy(13,y);
	  	printf("%c",186);
		gotoxy(20,y);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(40,y);
	  	printf("%c",186); // dong thang giua
		
		gotoxy(90,y);
	  	printf("%c",186);
}
void inSinhVien(SinhVien sv, int y, int stt){
		gotoxy(16,y);
		if(stt>9) gotoxy(15,y);
		cout<<stt;
		gotoxy(22,y);
		cout<<sv.maSinhVien;
		gotoxy(38,y);
		cout<<sv.ho;
		gotoxy(62,y);
		cout<<sv.ten;
		gotoxy(72,y);
		cout<<sv.phai;
		gotoxy(79,y);
		cout<<sv.matKhau;
		textcolor(10);
		gotoxy(13,y);
	  	printf("%c",186);
		gotoxy(19,y);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(36,y);
	  	printf("%c",186); // dong thang giua
		gotoxy(70,y);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(77,y);
	  	printf("%c",186); // dong thang giua
		gotoxy(90,y);
	  	printf("%c",186);
}
void inThongTin2(MonHoc mh, int y, int stt){
		gotoxy(15,y);
		cout<<stt;
		gotoxy(24,y);
		cout<<mh.maMonHoc;
		gotoxy(40,y);
		cout<<mh.tenMonHoc;
		textcolor(10);
		gotoxy(13,y);
	  	printf("%c",186);
		gotoxy(18,y);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(35,y);
	  	printf("%c",186); // dong thang giua
		
		gotoxy(90,y);
	  	printf("%c",186);
}
void DrawButtonCH(char kytu,int x,int y,bool status )
{
	gotoxy(x,y);
	if(status==ButtonON){
		ButtonHighLightCH();
	}else ButtonNormalCH();
	gotoxy(x,y);
	cout<<"[ "<<kytu<<" ]";
}
void DrawButtonMH2(ButtonMH button,int x,int y, int stt,bool status )
{
	gotoxy(x,y);
	if(status==ButtonON){
		ButtonHighLight();
	}else ButtonNormal();
	for(int i=y;i<y+button.dai;i++)
	{	
		gotoxy(x,i);
		for(int j=x;j<x+button.rong-1;j++)
		{
			cout<<" ";
		}
		cout<<"\n";
	}
	inThongTin2(button.mh, y, stt);
}
void DrawButtonMH(ButtonMH button,int x,int y, int stt,bool status )
{
	gotoxy(x,y);
	if(status==ButtonON){
		ButtonHighLight();
	}else ButtonNormal();
	for(int i=y;i<y+button.dai;i++)
	{	
		gotoxy(x,i);
		for(int j=x;j<x+button.rong-1;j++)
		{
			cout<<" ";
		}
		cout<<"\n";
	}
	inThongTin(button.mh, y, stt);
}
void DrawButtonLop(Lop* lop,int x,int y, int stt,bool status )
{
	gotoxy(x,y);
	if(status==ButtonON){
		ButtonHighLight();
	}else ButtonNormal();
	for(int i=y;i<y+1;i++)
	{	
		gotoxy(x,i);
		for(int j=x;j<x+76;j++)
		{
			cout<<" ";
		}
		cout<<"\n";
	}
	inLop(*lop, y, stt);
}
void DrawButtonSinhVien(NodeSinhVien* sv,int x,int y, int stt,bool status )
{
	gotoxy(x,y);
	if(status==ButtonON){
		ButtonHighLight();
	}else ButtonNormal();
	for(int i=y;i<y+1;i++)
	{	
		gotoxy(x,i);
		for(int j=x;j<x+76;j++)
		{
			cout<<" ";
		}
		cout<<"\n";
	}
	inSinhVien(sv->data, y, stt);
}


