#pragma once
#include "ThuVienDoHoa.h"
#define MAXCAUHOI 200
#define MAXLOP 100
using namespace std;
struct CauHoi {
	int maCauHoi;
	string cauHoi;
	string cauA;
	string cauB;
	string cauC;
	string cauD;
	char dapAn;
	bool daThi = false; //co danh dau cau hoi nay da duoc thi chua
};
struct DSCauHoi {
	CauHoi ds[MAXCAUHOI];
	int sl=0;
};
//---------------------------------
struct CT_DeThi {
	int maCauHoi;
	char svChon;
};

//---------------------------------

struct MonHoc {
	char maMonHoc[15];
	string tenMonHoc;
	DSCauHoi ds;
};
struct NodeMonHoc {
	MonHoc data;
	NodeMonHoc* left, * right;
};
NodeMonHoc* KhoiTao(MonHoc mh){
	NodeMonHoc* x = new NodeMonHoc();
	if (x == NULL)
	{
		thongbao("KHONG DU BO NHO !!!",40,28,4,7);
		Sleep(1000);
		xoahang(28);
		return NULL;
	}
	x->data = mh;
	x->left = NULL;
	x->right = NULL;
	return x;
}
typedef NodeMonHoc* treemh;

//---------------------------------
// Dung Sap xep mon hoc theo ten
struct Node{
	char maMonHoc[15];
	string tenMonHoc;
	Node* next;
};
struct DStheoTen{
	Node* phead = NULL;
};
Node* createNode(char* ma, string ten){
	Node *node = new Node();
	strcpy(node->maMonHoc,ma);
	node->tenMonHoc = ten;
	node->next = NULL;
	return node;
}
//---------------------------------
//DUNG Sap xep bang diem theo ten truoc, ma sau
struct NodeSapXep{
	string maSinhVien;
	string tenSinhVien;
	NodeSapXep* next;
};
struct DSSapXep{
	NodeSapXep* phead = NULL;
};
//---------------------------------
struct DiemThi {
	char maMonHoc[15];
	float diem;
	int soCau;
	CT_DeThi* chiTietDe;
};
struct  NodeDiemThi {
	DiemThi data;
	NodeDiemThi* next;
};
struct DSDiemThi {
	NodeDiemThi* phead = NULL;
};
//---------------------------------
struct SinhVien {
	string maSinhVien;
	string ho;
	string ten;
	string phai;
	string matKhau;
	DSDiemThi dsDiem;
};
struct NodeSinhVien {
	SinhVien data;
	NodeSinhVien* next;
};
struct DSSinhVien {
	NodeSinhVien* phead = NULL;
};
//---------------------------------
struct Lop {
	string maLop;
	string tenLop;
	DSSinhVien dsSinhVien;
};
struct DSLop {
	Lop* dsLop[MAXLOP];
	int sl = 0;
};
//---------------------------------
