#pragma once
//#include"mylib.h"
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include<conio.h>

using namespace std;
void gotoxy(int x,int y)
{    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1,y-1};   
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
//to mau BG
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
 
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
 
    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;
 
    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
// tat hien con tro chuot
void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}
int wherey()
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
//to mau
void textcolor(int x)
{
	HANDLE mau;
	mau=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}
void ToMau(int x, int y, char *a, int color) // x, y là t?a d? con tr? c?n nh?y d?n d? vi?t, a là chu?i c?n truy?n vào, color là màu truy?n vào.
{
	gotoxy(x, y);
	textcolor(color);
	cout << a;
	textcolor(7);
}
//mau
//mau
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void docFile(int x,string tenfile){
	string s;
	int dem=0;
	ifstream fin(tenfile);
	while( getline( fin , s )){
		if(dem==0||dem==1) textcolor(15);
		else if(dem==2) textcolor(10);
		else textcolor(2);
		gotoxy(x,dem+1);
		cout<<s<<endl;
		dem++;
	}
	fin.close();
}
void docFiledau(string tenfile){
	system("cls");
	string s;
	int dem;
	ifstream fin(tenfile);
	while (getline(fin, s)){
		if(dem==1||dem==16) textcolor(10);
		else if(dem==13) textcolor(6);
		else textcolor(14);
		gotoxy(20, 5+dem);
		cout<<s<<endl;
		dem++;
		Sleep(200);		
	}
	fin.close();
}
void khungNhap(string ten, int x , int y, int dai, int rong, int maukhung, int maunen){
	textcolor(maukhung);
	SetBGColor(maunen);
	for(int i = y;i<=y+rong;i++){
		for(int j = x; j<=x+dai; j++){
			gotoxy(j,i);
			cout<<" ";
		}
	}
	gotoxy(x+1,y+1);
	cout<<ten;
	
	for(int i=x; i<x+dai; i++){  
		gotoxy(i,y);
		printf("%c",196);
		gotoxy(i,y+rong+1);
		printf("%c",196);
	}
	for(int j=0;j<rong;j++)  // dong ke thang dung
	{
	  	gotoxy(x,y+1+j);
		printf("%c",179); // gach xuong bên hông
		gotoxy(x+dai,y+1+j);
		printf("%c",179); // gach xuong bên hông
	}
	
	gotoxy(x,y);
	printf("%c",218); // goc trai tren
	gotoxy(x+dai,y);
	printf("%c",191); // goc phai tren
	gotoxy(x,y+1+rong);
	printf("%c",192); // goc trai duoi
	gotoxy(x+dai,y+1+rong);
	printf("%c",217); // goc phai duoi
	
}
void bangMonHoc(int n){
	textcolor(10);
	for(int i=13;i<90;i++){ // tao dong ngang
		gotoxy(i,n+13);
		printf("%c",205);  // dong ngang duoi
		
	}
	for(int j=14;j<n+14;j++)  // dong ke thang dung
	{
	  	gotoxy(13,j);
	  	printf("%c",186); // dong thang ben trai
	  	gotoxy(18,j);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(35,j);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(80,j);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(90,j);	  	
	 	printf("%c",186);// dong thang ben phai
	}
	gotoxy(18,n+13);
	printf("%c",202);
	gotoxy(35,n+13);
	printf("%c",202);
	gotoxy(80,n+13);
	printf("%c",202);
	gotoxy(90,n+13);
	printf("%c",188); // cai moc cau ben phai ben duoi
	gotoxy(13,n+13);
	printf("%c",200); // moc cau ben trai duoi
}
void bangMonHoc2(int n){
	textcolor(10);
	for(int i=13;i<90;i++){ // tao dong ngang
		gotoxy(i,n+13);
		printf("%c",205);  // dong ngang duoi
		
	}
	for(int j=14;j<n+14;j++)  // dong ke thang dung
	{
	  	gotoxy(13,j);
	  	printf("%c",186); // dong thang ben trai
	  	gotoxy(18,j);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(35,j);
	  	printf("%c",186); // dong thang giua
	  	gotoxy(90,j);	  	
	 	printf("%c",186);// dong thang ben phai
	}
	gotoxy(18,n+13);
	printf("%c",202);
	gotoxy(35,n+13);
	printf("%c",202);
	gotoxy(90,n+13);
	printf("%c",188); // cai moc cau ben phai ben duoi
	gotoxy(13,n+13);
	printf("%c",200); // moc cau ben trai duoi
}

void xoaBangMH(){
	for(int i =14; i<=30;i++){
		for(int j = 13; j <=90; j++){
			gotoxy(j,i);
			cout<<" ";
		}
	}
}
void xoaBangCH(){
	for(int i =7; i<=29;i++){
		for(int j = 14; j <=89; j++){
			gotoxy(j,i);
			cout<<" ";
		}
	}
}
void xoaTenMH(int chon){
	SetBGColor(0);
	for(int i=36;i<=79;i++){ 
		gotoxy(i,chon+10);
		cout<<" ";  	
	}
}
void xoahang(int n){
	SetBGColor(0);
	for(int i=13;i<=98;i++){ 
		//if(i == 18 || i==35 || i == 80) continue;
		gotoxy(i,n);
		cout<<" ";  	
	}
}
void thongbao(string t, int x, int y, int mauchu, int maunen){
	textcolor(mauchu);
	SetBGColor(maunen);
	for(int i = x-2; i<= t.length() + x+2; i++){
		gotoxy(i,y);
		cout<<" ";
	}
	gotoxy(x,y); 
	cout<<t;
	SetBGColor(0);
	textcolor(10);
}
void hoTroSuaMonHoc(){
	textcolor(4);
	khungNhap("",100,11, 26,8,6,0);
	khungNhap("Enter", 103, 13, 6, 1, 6,0);
	khungNhap("Esc",105,16, 4,1,6,0);	
	// cac phim mui ten
	
	 
	textcolor(10);
	SetBGColor(0);
	gotoxy(108,11);
	cout<<" HO TRO ";
	gotoxy(111,14);
	cout<<"Luu";
	gotoxy(111,17);
	cout<<"Thoat";
}
void hoTroThem(){
	khungNhap("",92+8,8+2, 26,10,6,0);
	khungNhap("Enter", 95+8, 13+2, 6, 1, 6,0);
	khungNhap("Esc",97+8,16+2, 4,1,6,0);	
	// cac phim mui ten
	
	gotoxy(102+8,11+2);
	printf("%c",17); 
	gotoxy(106+8,11+2);
	printf("%c",16);
	
	 
	textcolor(10);
	SetBGColor(0);
	gotoxy(110,8+2);
	cout<<" HO TRO ";
	gotoxy(93+8,11+2);
	cout<<"Qua trai";
	gotoxy(109+8,11+2);
	cout<<"Qua phai";
	gotoxy(103+8,14+2);
	cout<<"Luu ";
	gotoxy(103+8,17+2);
	cout<<"Thoat";
}
void xoaBangHoTro(){
	SetBGColor(0);
	for(int i = 7; i<=35;i++){
		for(int j = 100; j<=130;j++){
			gotoxy(j,i);
			cout<<" ";
		}
	}
}
void khungConfirm(string t, int maunen, int mauchu){
	int x= 38;
	int y =31;
	textcolor(mauchu);
	SetBGColor(maunen);
	for(int i =y; i<=y+3;i++){
		for(int j=x-2; j <= t.length()+x+2; j++){
			gotoxy(j,i);
			cout<<" ";
		}
	}
	gotoxy(x,y);
	cout<<t;
	khungNhap("Y-Yes", x+t.length()-15, y+1,7,1,4,7);
	khungNhap("N-No", x+t.length()-5, y+1,5,1,4,7);
	SetBGColor(0);
	textcolor(10);
}
void xoaKhungConfirm(){
	SetBGColor(0);
	for(int i =31; i<=34;i++){
		for(int j=35; j <= 92; j++){
			gotoxy(j,i);
			cout<<" ";
		}
	}
}
void hoTroMonHoc2(){
	khungNhap("",100,8, 26,16,6,0);
	khungNhap("Ctrl+F",102,16, 7,1,6,0);
	khungNhap("Enter", 103, 19, 6, 1, 6,0);
	khungNhap("Esc",105,22, 4,1,6,0);
	gotoxy(114,11); // cac phim mui ten
	printf("%c",30);
	gotoxy(114,13);
	printf("%c",31); 
	gotoxy(112,12);
	printf("%c",17); 
	gotoxy(116,12);
	printf("%c",16);
	
	 
	textcolor(10);
	SetBGColor(0);
	gotoxy(110,8);
	cout<<" HO TRO";
	gotoxy(113,10);
	cout<<"Len";
	gotoxy(112,14);
	cout<<"Xuong";
	gotoxy(101,12);
	cout<<"Trang truoc";
	gotoxy(117,12);
	cout<<"Trang sau";
	gotoxy(111,17);
	cout<<"Tim kiem";
	gotoxy(111,20);
	cout<<"Chon mon hoc";
	gotoxy(111,23);
	cout<<"Thoat";
}
void hoTroMonHoc(string s){
	khungNhap("",92+8,7, 26,24,6,0);
	khungNhap("Insert",94+8,14, 7,1,6,0);
	khungNhap("Delete",94+8,17, 7,1,6,0);
	khungNhap("F4",98+8,20, 3,1,6,0);
	khungNhap("Ctrl+F",94+8,23, 7,1,6,0);
	khungNhap("Enter", 95+8, 26, 6, 1, 6,0);
	khungNhap("Esc",97+8,29, 4,1,6,0);
	gotoxy(106+8,10); // cac phim mui ten
	printf("%c",30);
	gotoxy(106+8,12);
	printf("%c",31); 
	gotoxy(104+8,11);
	printf("%c",17); 
	gotoxy(108+8,11);
	printf("%c",16);
	
	 
	textcolor(10);
	SetBGColor(0);
	gotoxy(98+8,7);
	cout<<" HO TRO ";
	if(s == "mh") cout<<"MON HOC ";
	else if(s == "sv") cout<<"SINH VIEN";
	else cout<<"LOP ";
	gotoxy(105+8,9);
	cout<<"Len";
	gotoxy(104+8,13);
	cout<<"Xuong";
	gotoxy(93+8,11);
	cout<<"Trang truoc";
	gotoxy(109+8,11);
	cout<<"Trang sau";
	gotoxy(103+8,15);
	cout<<"Them ";
	if(s == "mh") cout<<"mon hoc";
	else if(s == "sv") cout<<"sinh vien";
	else cout<<"lop";
	gotoxy(103+8,18);
	cout<<"Xoa ";
	if(s == "mh") cout<<"mon hoc";
	else if(s == "sv") cout<<"sinh vien";
	else cout<<"lop";
	gotoxy(103+8,21);
	cout<<"Sua ";
	if(s == "mh") cout<<"mon hoc";
	else if(s == "sv") cout<<"sinh vien";
	else cout<<"lop";
	gotoxy(103+8,24);
	cout<<"Tim kiem";
	gotoxy(103+8,27);
	cout<<"Xem ";
	if(s == "mh") cout<<"cau hoi";
	else if(s == "sv") cout<<"lich su thi";
	else cout<<"sinh vien";
	gotoxy(103+8,30);
	cout<<"Thoat";
}
void hoTroCauHoi(){
	khungNhap("",92+8,10, 26,13,6,0);
	khungNhap("Insert", 94+8, 15,7,1,6,0 );
	khungNhap("Delete", 102, 18,7,1,6,0 );
	khungNhap("Esc",97+8,21, 4,1,6,0);	
	// cac phim mui ten
	
	gotoxy(102+8,13);
	printf("%c",17); 
	gotoxy(106+8,13);
	printf("%c",16);
	
	 
	textcolor(10);
	SetBGColor(0);
	gotoxy(96+8,10);
	cout<<" HO TRO CAU HOI";
	gotoxy(93+8,13);
	cout<<"Qua trai";
	gotoxy(109+8,13);
	cout<<"Qua phai";
	gotoxy(103+8,16);
	cout<<"Them cau hoi";
	gotoxy(111,19);
	cout<<"Xoa cau hoi";
	gotoxy(103+8,22);
	cout<<"Thoat";
}
void hoTroNhapThi(){
	khungNhap("",100,11, 26,12,6,0);
	
	khungNhap("Enter", 95+8, 18, 6, 1, 6,0);
	khungNhap("Esc",97+8,21, 4,1,6,0);
	gotoxy(106+8,14); // cac phim mui ten
	printf("%c",30);
	gotoxy(106+8,15);
	printf("%c",31); 
	
	 
	textcolor(10);
	SetBGColor(0);
	gotoxy(102+8,11);
	cout<<" HO TRO ";
	gotoxy(105+8,13);
	cout<<"Len";
	gotoxy(104+8,16);
	cout<<"Xuong";
	
	gotoxy(103+8,19);
	cout<<"Vao thi";
	gotoxy(103+8,22);
	cout<<"Thoat";
}
void hoTroThemCauHoi(){
	khungNhap("",100,8+3, 26,12,6,0);
	
	khungNhap("Enter", 95+8, 15+3, 6, 1, 6,0);
	khungNhap("Esc",97+8,18+3, 4,1,6,0);
	gotoxy(106+8,11+3); // cac phim mui ten
	printf("%c",30);
	gotoxy(106+8,12+3);
	printf("%c",31); 
	
	 
	textcolor(10);
	SetBGColor(0);
	gotoxy(108,8+3);
	cout<<" HO TRO";
	gotoxy(105+8,10+3);
	cout<<"Len";
	gotoxy(104+8,13+3);
	cout<<"Xuong";
	
	gotoxy(103+8,16+3);
	cout<<"Luu cau hoi";
	gotoxy(103+8,19+3);
	cout<<"Thoat";
}
void xoaKhungXoaCH(){
	SetBGColor(0);
	for(int i = 31; i<=35;i++){
		for(int j = 24; j <=80; j++){
			gotoxy(j,i);
			cout<<" ";
		}
	}
}
void xoaCauHoiThi(){
	SetBGColor(0);
	for(int i =14; i <76; i++ ){
		gotoxy(i,18);
		cout<<" ";
		gotoxy(i,20);
		cout<<" ";
		gotoxy(i,22);
		cout<<" ";
		gotoxy(i,24);
		cout<<" ";
		gotoxy(i,26);
		cout<<" ";
	}
	for(int i= 77; i<96;i++){
		gotoxy(i,18);
		cout<<" ";
	}
}
void khungXoaCauHoi(){
	
	khungNhap("", 24, 31,56,3,4,7);
	gotoxy(30, 32);
	cout<<"NHAP THU TU CAU HOI MUON XOA";
	gotoxy(30,34);
	cout<<"Enter - Xoa      Esc - Thoat";
	khungNhap("", 65, 32, 10,1,4,7);
	
}
void giaoDienNhapThi(){
	docFile(25,"logotracnghiem2.txt");
	textcolor(6);
	
	gotoxy(14,13);
	cout<<"*** NHAP THONG TIN DE VAO THI";
	textcolor(6);
	for(int i=13; i<90; i++){   // dong gach ngang
		gotoxy(i,15);
		printf("%c",205);
		gotoxy(i,17);
		printf("%c",196);
		gotoxy(i,19);
		printf("%c",196);
		gotoxy(i,21);
		printf("%c",205);
	}
	for(int j=15;j<21;j++)  // dong ke thang dung
	{
	  	gotoxy(13,j);
		printf("%c",186); // gach xuong bên hông
		gotoxy(35,j);
		printf("%c",179);
		gotoxy(90,j);
		printf("%c",186); // gach xuong bên hông
	}
	
	gotoxy(90,15);
	printf("%c",187); // cai moc cau ben phai ben tre^n
	gotoxy(35,15);
	printf("%c",209);
	gotoxy(13,15);
	printf("%c",201); // cai moc cau ben trai tren
	
	gotoxy(13,17);
	printf("%c",199);
	gotoxy(35,17);
	printf("%c",197);
	gotoxy(90,17);
	printf("%c",182);
	
	gotoxy(13,19);
	printf("%c",199);
	gotoxy(35,19);
	printf("%c",197);
	gotoxy(90,19);
	printf("%c",182);

	gotoxy(90,21);
	printf("%c",188); // cai moc cau ben phai ben duoi
	gotoxy(35,21);
	printf("%c",207);
	gotoxy(13,21);
	printf("%c",200); // moc cau ben trai duoi
	
	textcolor(10);
	gotoxy(17, 16);
	cout<<"Ma mon hoc";
	gotoxy(17, 18);
	cout<<"So cau hoi";
	gotoxy(17, 20);
	cout<<"So phut thi";
	hoTroNhapThi();
}
void giaoDienThemCauHoi(){
	textcolor(6);
	gotoxy(14,3);
	cout<<"Ma mon hoc:";
	gotoxy(14,4);
	cout<<"Ten mon hoc:";
	gotoxy(14,5);
	cout<<"So cau hoi hien tai:";
	gotoxy(14,9);
	cout<<"*** NHAP THONG TIN CAU HOI";
	textcolor(6);
	for(int i=13; i<90; i++){   // dong gach ngang
		gotoxy(i,11);
		printf("%c",205);
		gotoxy(i,15);
		printf("%c",196);
		gotoxy(i,18);
		printf("%c",196);
		gotoxy(i,21);
		printf("%c",196);
		gotoxy(i,24);
		printf("%c",196);
		gotoxy(i,27);
		printf("%c",196);
		gotoxy(i,29);
		printf("%c",205);
	}
	for(int j=11;j<29;j++)  // dong ke thang dung
	{
	  	gotoxy(13,j);
		printf("%c",186); // gach xuong bên hông
		gotoxy(28,j);
		printf("%c",179);
		gotoxy(90,j);
		printf("%c",186); // gach xuong bên hông
	}
	
	gotoxy(90,11);
	printf("%c",187); // cai moc cau ben phai ben tre^n
	gotoxy(28,11);
	printf("%c",209);
	gotoxy(13,11);
	printf("%c",201); // cai moc cau ben trai tren
	
	gotoxy(13,15);
	printf("%c",199);
	gotoxy(28,15);
	printf("%c",197);
	gotoxy(90,15);
	printf("%c",182);
	
	gotoxy(13,18);
	printf("%c",199);
	gotoxy(28,18);
	printf("%c",197);
	gotoxy(90,18);
	printf("%c",182);

	gotoxy(13,21);
	printf("%c",199);
	gotoxy(28,21);
	printf("%c",197);
	gotoxy(90,21);
	printf("%c",182);

	gotoxy(13,24);
	printf("%c",199);
	gotoxy(28,24);
	printf("%c",197);
	gotoxy(90,24);
	printf("%c",182);

	gotoxy(13,27);
	printf("%c",199);
	gotoxy(28,27);
	printf("%c",197);
	gotoxy(90,27);
	printf("%c",182);
	
	gotoxy(90,29);
	printf("%c",188); // cai moc cau ben phai ben duoi
	gotoxy(28,29);
	printf("%c",207);
	gotoxy(13,29);
	printf("%c",200); // moc cau ben trai duoi
	
	textcolor(10);
	gotoxy(17, 12);
	cout<<"CAU HOI";
	gotoxy(17, 16);
	cout<<"Dap an A";
	gotoxy(17, 19);
	cout<<"Dap an B";
	gotoxy(17, 22);
	cout<<"Dap an C";
	gotoxy(17, 25);
	cout<<"Dap an D";
	gotoxy(15, 28);
	cout<<"Dap an dung";
	
	hoTroThemCauHoi();
}
void giaoDienCauHoi(){
	textcolor(6);
	gotoxy(14,2);
	cout<<"Ma mon hoc:";
	gotoxy(14,3);
	cout<<"Ten mon hoc:";
	gotoxy(14,4);
	cout<<"So cau hoi hien tai:";
	for(int i=13; i<90; i++){   // dong gach ngang
		gotoxy(i,6);
		printf("%c",205);
		gotoxy(i,30);
		printf("%c",205);
	}
	for(int j=6;j<30;j++)  // dong ke thang dung
	{
	  	gotoxy(13,j);
		printf("%c",186); // gach xuong bên hông
		gotoxy(90,j);
		printf("%c",186); // gach xuong bên hông
	}
	gotoxy(90,6);
	printf("%c",187); // cai moc cau ben phai ben tre^n
	gotoxy(13,6);
	printf("%c",201); // cai moc cau ben trai tren
	gotoxy(90,30);
	printf("%c",188); // cai moc cau ben phai ben duoi
	gotoxy(13,30);
	printf("%c",200); // moc cau ben trai duoi
	hoTroCauHoi();
}
void giaodienXemMonHoc(){
	textcolor(6);
	gotoxy(18,8);
	cout<<"Tim kiem:";
	gotoxy(14,12);
	cout<<"STT";
	gotoxy(22,12);
	cout<<"Ma Mon Hoc";
	gotoxy(55,12);
	cout<<"Ten Mon Hoc";
	khungNhap("",32,7,50,1,10,0); // Khung tim kiêm	
	
	for(int i=13;i<90;i++) // tao dong ngang
	{
	  	gotoxy(i,11);
	  	printf("%c",205); // dong ngang tren cùng
		gotoxy(i,13);
	  	printf("%c",205); // dong ngang giua
	}
	
	// NHUNG NÚT GIAO GIUA CAC DONG KE PHHIA TREN
	gotoxy(18,13);
	printf("%c",206);
	gotoxy(18,12);
	printf("%c",186);
	gotoxy(18,11);
	printf("%c",203);
	
	gotoxy(35,13);
	printf("%c",206);
	gotoxy(35,12);
	printf("%c",186);
	gotoxy(35,11);
	printf("%c",203);
	
	gotoxy(90,13);
	printf("%c",185);
	gotoxy(90,12);
	printf("%c",186);
	gotoxy(90,11);
	printf("%c",187); // cai moc cau ben phai ben tre^n
	
	gotoxy(13,13);
	printf("%c",204);
	gotoxy(13,12);
	printf("%c",186);
	gotoxy(13,11);
	printf("%c",201); // cai moc cau ben trai tren
	
	hoTroMonHoc2();
	
}
void giaoDienSinhVien(){
	docFile(15,"logolop.txt" );
	int i,j;
	textcolor(6);
	gotoxy(33,6);
	cout<<"LOP:";
	gotoxy(18,8);
	cout<<"Tim kiem:";
	
	gotoxy(15,12);
	cout<<"STT";
	gotoxy(22,12);
	cout<<"Ma Sinh Vien";
	gotoxy(48,12);
	cout<<"Ten Sinh Vien";
	gotoxy(72,12);
	cout<<"Phai";
	gotoxy(80,12);
	cout<<"Mat khau";
	khungNhap("",32,7,50,1,10,0); // Khung tim kiêm	
	
	for(i=13;i<90;i++) // tao dong ngang
	{
	  	gotoxy(i,11);
	  	printf("%c",205); // dong ngang tren cùng
		gotoxy(i,13);
	  	printf("%c",205); // dong ngang giua
	}
	
	// NHUNG NÚT GIAO GIUA CAC DONG KE PHHIA TREN
	gotoxy(19,13);
	printf("%c",206);
	gotoxy(19,12);
	printf("%c",186);
	gotoxy(19,11);
	printf("%c",203);
	
	gotoxy(36,13);
	printf("%c",206);
	gotoxy(36,12);
	printf("%c",186);
	gotoxy(36,11);
	printf("%c",203);
	
	gotoxy(70,13);
	printf("%c",206);
	gotoxy(70,12);
	printf("%c",186);
	gotoxy(70,11);
	printf("%c",203);
	
	gotoxy(77,13);
	printf("%c",206);
	gotoxy(77,12);
	printf("%c",186);
	gotoxy(77,11);
	printf("%c",203);
	
	gotoxy(90,13);
	printf("%c",185);
	gotoxy(90,12);
	printf("%c",186);
	gotoxy(90,11);
	printf("%c",187); // cai moc cau ben phai ben tre^n
	
	gotoxy(13,13);
	printf("%c",204);
	gotoxy(13,12);
	printf("%c",186);
	gotoxy(13,11);
	printf("%c",201); // cai moc cau ben trai tren
	
	hoTroMonHoc("sv");
	
}
void bangSinhVien(int n){
	textcolor(10);
	for(int i=13;i<90;i++){ // tao dong ngang
		gotoxy(i,n+13);
		printf("%c",205);  // dong ngang duoi
		
	}
	if(n>1){
		gotoxy(13,n+12);
		printf("%c",186);
		gotoxy(19,n+12);
		printf("%c",186);
		gotoxy(36,n+12);
		printf("%c",186);
		gotoxy(70,n+12);
		printf("%c",186);
		gotoxy(77,n+12);
		printf("%c",186);
		gotoxy(90,n+12);
		printf("%c",186);
	}
	
	gotoxy(13,n+13);
	printf("%c",200);
	gotoxy(19,n+13);
	printf("%c",202);
	gotoxy(36,n+13);
	printf("%c",202);
	gotoxy(70,n+13);
	printf("%c",202);
	gotoxy(77,n+13);
	printf("%c",202);
	gotoxy(90,n+13);
	printf("%c",188); // cai moc cau ben phai ben duoi
	gotoxy(13,n+13);
	printf("%c",200); // moc cau ben trai duoi
}
void giaoDienLop(){
	int i,j;
	docFile(15,"logolop.txt");
	textcolor(6);
	gotoxy(18,8);
	cout<<"Tim kiem:";
	gotoxy(15,12);
	cout<<"STT";
	gotoxy(27,12);
	cout<<"Ma Lop";
	gotoxy(63,12);
	cout<<"Ten Lop";
	khungNhap("",32,7,50,1,10,0); // Khung tim kiêm	
	
	for(i=13;i<90;i++) // tao dong ngang
	{
	  	gotoxy(i,11);
	  	printf("%c",205); // dong ngang tren cùng
		gotoxy(i,13);
	  	printf("%c",205); // dong ngang giua
	}
	
	// NHUNG NÚT GIAO GIUA CAC DONG KE PHHIA TREN
	gotoxy(20,13);
	printf("%c",206);
	gotoxy(20,12);
	printf("%c",186);
	gotoxy(20,11);
	printf("%c",203);
	
	gotoxy(40,13);
	printf("%c",206);
	gotoxy(40,12);
	printf("%c",186);
	gotoxy(40,11);
	printf("%c",203);
	
	
	
	gotoxy(90,13);
	printf("%c",185);
	gotoxy(90,12);
	printf("%c",186);
	gotoxy(90,11);
	printf("%c",187); // cai moc cau ben phai ben tre^n
	
	gotoxy(13,13);
	printf("%c",204);
	gotoxy(13,12);
	printf("%c",186);
	gotoxy(13,11);
	printf("%c",201); // cai moc cau ben trai tren
	
	hoTroMonHoc("l");
	
}
void bangLop(int n){
	textcolor(10);
	for(int i=13;i<90;i++){ // tao dong ngang
		gotoxy(i,n+13);
		printf("%c",205);  // dong ngang duoi
		
	}
	gotoxy(13,n+12);
	printf("%c",186);
	gotoxy(20,n+12);
	printf("%c",186); // dong thang giua
	gotoxy(40,n+12);
	printf("%c",186); // dong thang giua
	gotoxy(90,n+12);
	printf("%c",186);
	gotoxy(20,n+13);
	printf("%c",202);
	gotoxy(40,n+13);
	printf("%c",202);
	gotoxy(90,n+13);
	printf("%c",188); // cai moc cau ben phai ben duoi
	gotoxy(13,n+13);
	printf("%c",200); // moc cau ben trai duoi
}
void giaoDienMonHoc(){
	int i,j;
	textcolor(4);
	docFile(15,"logomonhoc.txt");
	textcolor(6);
	gotoxy(18,8);
	cout<<"Tim kiem:";
	gotoxy(14,12);
	cout<<"STT";
	gotoxy(22,12);
	cout<<"Ma Mon Hoc";
	gotoxy(53,12);
	cout<<"Ten Mon Hoc";
	gotoxy(83,12);
	cout<<"SLCH";
	khungNhap("",32,7,50,1,10,0); // Khung tim kiêm	
	
	for(i=13;i<90;i++) // tao dong ngang
	{
	  	gotoxy(i,11);
	  	printf("%c",205); // dong ngang tren cùng
		gotoxy(i,13);
	  	printf("%c",205); // dong ngang giua
	}
	
	// NHUNG NÚT GIAO GIUA CAC DONG KE PHHIA TREN
	gotoxy(18,13);
	printf("%c",206);
	gotoxy(18,12);
	printf("%c",186);
	gotoxy(18,11);
	printf("%c",203);
	
	gotoxy(35,13);
	printf("%c",206);
	gotoxy(35,12);
	printf("%c",186);
	gotoxy(35,11);
	printf("%c",203);
	
	gotoxy(80,13);
	printf("%c",206);
	gotoxy(80,12);
	printf("%c",186);
	gotoxy(80,11);
	printf("%c",203);
	
	
	gotoxy(90,13);
	printf("%c",185);
	gotoxy(90,12);
	printf("%c",186);
	gotoxy(90,11);
	printf("%c",187); // cai moc cau ben phai ben tre^n
	
	gotoxy(13,13);
	printf("%c",204);
	gotoxy(13,12);
	printf("%c",186);
	gotoxy(13,11);
	printf("%c",201); // cai moc cau ben trai tren
	
	hoTroMonHoc("mh");
	
}
void hoTroThiTracNghiem(){
	khungNhap("",92+8,8, 26,13,6,0);
	khungNhap("Enter", 95+8, 16, 6, 1, 6,0);
	khungNhap("Esc",97+8,19, 4,1,6,0);
	gotoxy(106+8,11); // cac phim mui ten
	printf("%c",30);
	gotoxy(106+8,13);
	printf("%c",31); 
	gotoxy(104+8,12);
	printf("%c",17); 
	gotoxy(108+8,12);
	printf("%c",16);
	
	 
	textcolor(10);
	SetBGColor(0);
	gotoxy(98+8,8);
	cout<<" HO TRO MON HOC";
	gotoxy(105+8,10);
	cout<<"Len";
	gotoxy(104+8,14);
	cout<<"Xuong";
	gotoxy(94+8,12);
	cout<<"Cau truoc";
	gotoxy(110+8,12);
	cout<<"Cau sau";
	gotoxy(103+8,17);
	cout<<"Chon dap an";
	gotoxy(103+8,20);
	cout<<"Nop bai";
}
void giaoDienThiTracNghiem(){
	docFile(25,"logotracnghiem2.txt");
	textcolor(6);
	gotoxy(79,9);
	cout<<"Da hoan thanh: ";
	gotoxy(77, 12);
	cout<<"Thoi gian con lai: ";
	for(int i=2; i<96; i++){   // dong gach ngang
		gotoxy(i,8);
		printf("%c",205);
		gotoxy(i,16);
		printf("%c",196);
		gotoxy(i,28);
		printf("%c",205);
	}
	for(int j=9;j<28;j++)  // dong ke thang dung
	{
	  	gotoxy(2,j);
		printf("%c",186); // gach xuong bên hông
		gotoxy(76,j);
		printf("%c",179);
		gotoxy(96,j);
		printf("%c",186); // gach xuong bên hông
	}
	gotoxy(96,8);
	printf("%c",187); // cai moc cau ben phai ben tre^n
	gotoxy(76,8);
	printf("%c",209);
	gotoxy(2,8);
	printf("%c",201); // cai moc cau ben trai tren
	
	gotoxy(2,16);
	printf("%c",199);
	gotoxy(76,16);
	printf("%c",197);
	gotoxy(96,16);
	printf("%c",182);
	
	gotoxy(96,28);
	printf("%c",188); // cai moc cau ben phai ben duoi
	gotoxy(76,28);
	printf("%c",207);
	gotoxy(2,28);
	printf("%c",200); // moc cau ben trai duoi
	hoTroThiTracNghiem();
}
void khungDuoiLSThi(int n){
	textcolor(7);
	for(int i=8; i<125; i++){   // dong gach ngang
		gotoxy(i,19+(n-1)*7);
		printf("%c",205);
	}
	for(int j=11;j<19+(n-1)*7;j++)  // dong ke thang dung
	{
	  	gotoxy(8,j);
		printf("%c",186); // gach xuong bên hông
		gotoxy(125,j);
		printf("%c",186); // gach xuong bên hông
	}
	
	gotoxy(125,19+(n-1)*7);
	printf("%c",188); // cai moc cau ben phai ben duoi
	gotoxy(8,19+(n-1)*7);
	printf("%c",200); // moc cau ben trai duoi
	textcolor(6);
	gotoxy(60,18+(n-1)*7 );
	cout<<"____Het____";
}
void giaoDienLichSuThi(){
	textcolor(7);
	for(int i=8; i<125; i++){   // dong gach ngang
		gotoxy(i,1);
		printf("%c",205);
		gotoxy(i,5);
		printf("%c",196);
	}
	for(int j=2;j<=10;j++)  // dong ke thang dung
	{
	  	gotoxy(8,j);
		printf("%c",186); // gach xuong bên hông
		gotoxy(125,j);
		printf("%c",186); // gach xuong bên hông
	}
	gotoxy(110,2);
	printf("%c",179);
	gotoxy(110,3);
	printf("%c",179);
	gotoxy(110,4);
	printf("%c",179);
	gotoxy(110,5);
	printf("%c",193);

	gotoxy(125,1);
	printf("%c",187); // cai moc cau ben phai ben tre^n
	gotoxy(110,1);
	printf("%c",209); 
	gotoxy(8,1);
	printf("%c",201); // cai moc cau ben trai tren
	gotoxy(8,5);
	printf("%c",199);
	gotoxy(125,5);
	printf("%c",182);
	gotoxy(50,8);
	cout<<"________________________________";
	gotoxy(10,2);
	cout<<"TEN SINH VIEN:";
	gotoxy(10,3);
	cout<<"MA SINH VIEN:";
	gotoxy(10,4); 
	cout<<"LOP:";
	gotoxy(116,2);
	cout<<"DIEM";
	gotoxy(44,7);
	cout<<"BAI THI MON:";
}
void giaoDienBangDiem(int n){
	textcolor(15);
	gotoxy(4,2);
	cout<<"HOC VIEN CONG NGHE BUU CHINH VIEN THONG";
	gotoxy(8,3);
	cout<<"CO SO TAI THANH PHO HO CHI MINH";
	gotoxy(16,4);
	cout<<"______________";
	
	gotoxy(84,2);
	cout<<"CONG HOA XA HOI CHU NGHIA VIET NAM";
	gotoxy(88,3);
	cout<<"Doc lap - Tu do - Hanh phuc";
	gotoxy(95,4);
	cout<<"______________";
	
	
	for(int i = 15; i<=105;i++){
		gotoxy(i,11);
		printf("%c",196);
		gotoxy(i,13);
		printf("%c",196);
		gotoxy(i,13+n);
		printf("%c",196);
	}
	for(int i = 12; i<=13+n;i++){
		gotoxy(15,i);
		printf("%c",179);
		gotoxy(22,i);
		printf("%c",179);
		gotoxy(43,i);
		printf("%c",179);
		gotoxy(87,i);
		printf("%c",179);
		gotoxy(105,i);
		printf("%c",179);
	}
	gotoxy(15,11);
	printf("%c",218);
	gotoxy(22,11);
	printf("%c",194);
	gotoxy(43,11);
	printf("%c",194);
	gotoxy(87,11);
	printf("%c",194);
	gotoxy(105,11);
	printf("%c",191);
	
	gotoxy(15,13);
	printf("%c",195);
	gotoxy(22,13);
	printf("%c",197);
	gotoxy(43,13);
	printf("%c",197);
	gotoxy(87,13);
	printf("%c",197);
	gotoxy(105,13);
	printf("%c",180);
	
	gotoxy(15,13+n);
	printf("%c",192);
	gotoxy(22,13+n);
	printf("%c",193);
	gotoxy(43,13+n);
	printf("%c",193);
	gotoxy(87,13+n);
	printf("%c",193);
	gotoxy(105,13+n);
	printf("%c",217);
	
	textcolor(14);
	gotoxy(55, 6);
	cout<<"BANG DIEM MON HOC";
	gotoxy(40,8);
	cout<<"Lop:";
	gotoxy(40, 9);
	cout<<"Mon hoc:";
	gotoxy(17,12);
	cout<<"STT";
	gotoxy(27,12);
	cout<<"Ma sinh vien";
	gotoxy(60,12);
	cout<<"Ho va ten";
	gotoxy(94,12);
	cout<<"Diem";
	textcolor(10);
	gotoxy(55,16+n);
	cout<<"Esc - de thoat";
}
void VEKHUNGMAIN(int x, int y, string filename) {
	string str;
	ifstream FileIn;
	FileIn.open(filename, ios::in);
	int mamau;
	int i=0;
	while (true)
	{
		getline(FileIn, str);
		if(i == 0 || i==1 ) mamau = 15;
		if(i == 2 ) mamau = 14;
		if(i == 3 ) mamau = 6;
		if(i>3) mamau = 14;
		SetColor(mamau);
		gotoxy(x, y++);
		cout << str << endl;
		i++;
		if (FileIn.eof())
		{
			break;
		}
	}
	FileIn.close();



//	//------VE VIEN------
	textcolor(6);
	SetBGColor(0);
	for(int ix=2; ix<=130;ix++) {
		gotoxy(ix,7); cout<<char(205); // duong ngang
		gotoxy(ix, 35); cout<<char(205); 
	}
	for(int iy=7; iy<=35;iy++) {
		gotoxy(2, iy); cout<<char(186); // duong doc
		gotoxy(130, iy); cout<<char(186);
	}
	gotoxy(2,7); cout<<char(201);
	gotoxy(130,7); cout<<char(187);
	gotoxy(2,35); cout<<char(200);
	gotoxy(130,35); cout<<char(188);
}
void Ve_Vien_Doi(int vitrix, int vitriy, int rong, int dai1, int dai2, string TEXT)
{
	int vitriy1 = vitriy, vitriy2 = vitriy;
	for (int i = 0; i < dai1; i++)
	{
		gotoxy(vitrix, vitriy);
		for (int j = 0; j < rong; j++)
		{
			if (i == 0 && j == 0) cout << char(201);//góc trên trái
			else if (i == 0 && j == rong - 1) cout << char(187);//góc trên phai
			else if (i == dai1 - 1 && j == 0) cout << char(200);//góc duoi trai
			else if (i == dai1 - 1 && j == rong - 1) cout << char(188);//goc duoi phai
			else if (i == 0 || i == dai1 - 1) cout << char(205);//gach nam
			else if (j == 0 || j == rong - 1) cout << char(186);//gach dung
			else cout << " ";
		}
		vitriy++;
	}

	for (int i = 0; i < dai2; i++)
	{
		gotoxy(vitrix, vitriy1 + dai1 - 1);
		for (int j = 0; j < rong; j++)
		{
			if (i == 0 && j == 0) cout << char(204);
			else if (i == 0 && j == rong - 1) cout << char(185);
			else if (i == dai2 - 1 && j == 0) cout << char(200);
			else if (i == dai2 - 1 && j == rong - 1) cout << char(188);
			else if (i == 0 || i == dai2 - 1) cout << char(205);
			else if (j == 0 || j == rong - 1) cout << char(186);
			else cout << " ";
		}
		vitriy1++;
	}
	int s = TEXT.length();
	gotoxy(vitrix + ((rong - s) / 2), (vitriy2 + dai1 / 2)); cout << TEXT;

}
void manHinhLoading()
{
	system("cls");
 	textcolor(7);
	gotoxy(60,15);cout << "LOADING...";
	for( int i = 0 ; i <= 50 ; i++ ){
		textcolor(6);
		gotoxy(43 + i,16);cout << char(175);
		textcolor(10);
		gotoxy(64,17);cout << i * 2 << "%";
			Sleep(30);
		}
}
// tao khung hinh
void KhungHinh( int x , int y , int w ){
	gotoxy(x,y);
	SetBGColor(10);
	for(int i = 0 ; i < w ; i++ ){
		if( i == 0 ){
			cout << char(218);
		}
		else if( i == w - 1 ){
			cout << char(191);
		}
		else{ 
			cout << char(196);
		}
	}
	gotoxy(x,y + 1);
	cout << char(179);
	gotoxy(x + w - 1,y + 1);
	cout << char(179);
	gotoxy(x,y + 2);
	for( int i = 0 ; i < w ; i++ ){
		if( i == 0 ){
			cout << char(192);
		}
		else if( i == w - 1 ){
			cout << char(217);
		}
		else{ 
			cout << char(196);
		}
	}
	gotoxy(x + 1,y + 1);
}
void BangThongTinSV(int x,int y)
{
	textcolor(15);
	gotoxy(x,y);
	cout<<"Ten sinh vien : NGUYEN THI THAO NGUYEN";
	gotoxy(x,y+1);
	cout<<"MSSV          : N18DCCN133";
	gotoxy(x,y+3);
	cout<<"Ten sinh vien : CHAU VAN HAU";
	gotoxy(x,y+4);
	cout<<"MSSV          : N18DCCN058";
	gotoxy(x,y+6);
	cout<<"Lop           : D18CQCN01-N";
	gotoxy(x,y+7);
	cout<<"Mon hoc       : Cau truc du lieu va giai thuat";
}
void BangChuThich(int x,int y)
{
	textcolor(10);
	gotoxy(x,y);
	cout<<"Chu Thich: ";
	gotoxy(x+15,y);
	printf("%c",30);
	cout<<" - Len";
	gotoxy(x+30,y);
	printf("%c",31);
	cout<<" - Xuong";
	gotoxy(x+45,y);
	cout<<" ENTER - chon";
	gotoxy(x+60,y);
	cout<<"	ESC - Thoat";
}
void Nocursortype(bool a) // ham set hien thi con tro
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = a;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void resizeConsole(int width, int height) // ham set size console
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
int wherex()
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}



