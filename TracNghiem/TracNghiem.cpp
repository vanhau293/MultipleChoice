#include <iostream>
#include<stdio.h>
#include <conio.h>
#include "Function.h"
#include "ThuVienDoHoa.h"
#define FALSE 0
#define TRUE 1
using namespace std;
//---------------------------------
// xóa ds mon hoc,ds lop, 

int main() {
	int a;
	DSLop dsl;
	treemh dsmh = NULL;
	loadFileDSLop(dsl,"lop.txt");
	loadDSMonHocTuFile(dsmh,"monhoc.txt");
	loadDiemThiTuFile(dsl,"diemthi.txt");
	
	string user, pass;
	resizeConsole(1000, 600);
	
	docFiledau("gioithieu.txt");
	Sleep(1000);
	manHinhLoading();
	system("cls");
	a = nhapDangNhap(user, pass, dsl);
	Nocursortype(FALSE);
	if(a==0){
		RunMenu(user, dsl,dsmh);
	}
	else if(a==1)
	{
		thucThiThiTracNghiem(user, dsl,dsmh);
	}

	xoaDSLop(dsl);
	xoaCayMonHoc(dsmh);
	
	docFiledau("goodbye.txt");
	Sleep(1000);
	system("pause");
	return 0;
}
