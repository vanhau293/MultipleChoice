#include<conio.h>
#include<string>
#include<windows.h>
#include <math.h>
#include<thread>
#include "KhaiBao.h"
#include "Button.h"
#include "ThuVienDoHoa.h"
#include<fstream>
#define MAXCAUHOI 200
#define MAXLOP 100
#pragma warning(disable: 4996)
int stop = 0;
int themMonHoc(treemh &ds, MonHoc mon){
	
	if(ds == NULL){
		NodeMonHoc* mh = KhoiTao(mon);
		if (mh==NULL) return -1;
		ds = mh;
		return 1;
		}
	else if (strcmp(ds->data.maMonHoc,mon.maMonHoc)==0) return 0;
	else if (strcmp(ds->data.maMonHoc,mon.maMonHoc)>0)
	
		return themMonHoc(ds->left, mon);
	else if (strcmp(ds->data.maMonHoc,mon.maMonHoc)<0)
		return themMonHoc(ds->right, mon);
}

void Tim_Node_The_Mang(NodeMonHoc*& x, NodeMonHoc*& y){ // Tim node phai nhat cua cay con trai
	if (y->right != NULL)
	{
		Tim_Node_The_Mang(x, y->right);
	}
	else
	{
		x->data = y->data;
		x = y;
		y = y->left;
	}
}
void xoaMonHoc(treemh &t, char* ma, int &slmh){
	if (t == NULL) return ;
	else
	{
		if (strcmp(ma,t->data.maMonHoc)>0)
		{
			xoaMonHoc(t->right, ma,slmh);
		}
		else if (strcmp(ma,t->data.maMonHoc)<0)
		{
			xoaMonHoc(t->left, ma, slmh);
		}
		else 
		{
			NodeMonHoc* x = t;
			if (t->left == NULL)
			{
				t = t->right;
			}
			else if (t->right == NULL)
			{
				t = t->left;
			}
			else
			{
				Tim_Node_The_Mang(x, t->left);
			}
			slmh--;
			delete x;
		}
	}
}
void CapNhatTenMH(treemh t, char* ma, string ten){
	if (t != NULL) {
		if(strcmp(ma, t->data.maMonHoc)==0) {
			t->data.tenMonHoc = ten;
			return;
		}
		else if(strcmp(ma, t->data.maMonHoc)>0) CapNhatTenMH(t->right,ma, ten);
		else CapNhatTenMH(t->left,ma, ten);
	}
}

void themDiemThi(DSDiemThi &dsdt, DiemThi diemthi){
	NodeDiemThi* node = new NodeDiemThi();
	node->data = diemthi;
	node->next = NULL;
	if (dsdt.phead == NULL){
		dsdt.phead = node;
	}
	else{
		node->next = dsdt.phead;
		dsdt.phead = node;
	}
}

void loadCauHoi(ifstream &filein, CauHoi &ch){
	char s;
	filein >> ch.maCauHoi;
	filein>>s;
	filein>>ch.daThi;
	filein.ignore();
	getline(filein, ch.cauHoi);
	getline(filein, ch.cauA);
	getline(filein, ch.cauB);
	getline(filein, ch.cauC);
	getline(filein, ch.cauD);
	filein>>ch.dapAn;
	
}	
MonHoc loadMonHoc(ifstream &filein){
	MonHoc mh;
	filein.ignore();
	filein.getline(mh.maMonHoc,15,'|');
	getline(filein,mh.tenMonHoc,'|');
	filein >> mh.ds.sl;
	for(int i = 0; i< mh.ds.sl; i++) loadCauHoi(filein,mh.ds.ds[i]);
	return mh;
}
void loadDSMonHocTuFile(treemh &ds, string filename){
	ifstream ifs;
	ifs.open(filename, ios_base::in);
	if(ifs.fail() == true) {
		cout << "Ten file chua dung" << endl;
		return;
	}
	string x;
	int s;
	while (!ifs.eof()) {
		ifs >> x;
		if(!ifs.eof()) {
		s = themMonHoc(ds,loadMonHoc(ifs));
		}
	}
	ifs.close();
}
bool kt_TrungSV(string maSinhVien, DSLop dsl){
	for(int i = 0 ; i< dsl.sl; i++)
		for(NodeSinhVien* k = dsl.dsLop[i]->dsSinhVien.phead; k!=NULL; k=k->next)
			if(k->data.maSinhVien==maSinhVien){
				return true;
			}
	return false;
}
NodeSinhVien* laySinhVien(string maSinhVien, string &maLop, string &tenLop, DSLop dsl){
	for(int i = 0 ; i< dsl.sl; i++)
		for(NodeSinhVien* k = dsl.dsLop[i]->dsSinhVien.phead; k!=NULL; k=k->next)
			if(k->data.maSinhVien==maSinhVien){
				maLop = dsl.dsLop[i]->maLop;
				tenLop = dsl.dsLop[i]->tenLop;
				return k;
			}
	return NULL;
			
}
void loadDiemThiTuFile(DSLop &dslop, string filename){
	ifstream ifs;
	ifs.open(filename, ios_base::in);
	if(ifs.fail() == true) {
		cout << "Ten file chua dung" << endl;
		return ;
	}
	char x;
	int s;
	string maSinhVien;
	NodeSinhVien* sv;
	DiemThi dt;
	string maLop;
	string tenLop;
	while (!ifs.eof()) {
		ifs >> x;
		if(!ifs.eof()) {
			if(x=='=') {
				ifs.ignore();
				getline(ifs,maSinhVien);
				sv = laySinhVien( maSinhVien,maLop,tenLop,dslop);
			}
			else{
				ifs.ignore();
				ifs.getline(dt.maMonHoc,15,'|');
				ifs>>dt.diem;
				ifs>>x;
				ifs>>dt.soCau;
				dt.chiTietDe = new CT_DeThi[dt.soCau];
				for(int i = 0 ; i< dt.soCau; i++){
					ifs>>dt.chiTietDe[i].maCauHoi;
					ifs>>dt.chiTietDe[i].svChon;
					ifs>>x;
				}
				themDiemThi(sv->data.dsDiem,dt);	
			}
		}
	}
	ifs.close();
	
}
void luuFileDiemThi(DiemThi dt, string maSinhVien, string filename){
	ofstream ofs;
	ofs.open(filename, ios_base::app);
	ofs<<"="<<endl;
	ofs<<maSinhVien<<endl;
	ofs<<"*"<<endl;
	ofs<<dt.maMonHoc<<"|"<<dt.diem<<"|"<<dt.soCau<<endl;
	for(int i = 0; i<dt.soCau; i++){
		ofs<<dt.chiTietDe[i].maCauHoi<<" "<<dt.chiTietDe[i].svChon<<"|";	
	}
	ofs<<endl;
	ofs.close();
}
void themSinhVien(DSSinhVien &dssv, SinhVien sv){
	NodeSinhVien* node = new NodeSinhVien();
	node->data = sv;
	node->next = NULL;
	if (dssv.phead == NULL){
		dssv.phead = node;
	}
	else{
		node->next = dssv.phead;
		dssv.phead = node;
	}
}
void moveOut(DSLop &ds, int i) {
	for(int j=ds.sl;j>=i+1;--j) {
		ds.dsLop[j] = ds.dsLop[j-1];
	}
	ds.sl++;
}
int themLop(DSLop &ds, Lop* Class) {
	int i = 0;
	for( i=0;i<ds.sl;i++) {
		if(Class->maLop < ds.dsLop[i]->maLop) {
			moveOut(ds,i);
			ds.dsLop[i]= Class;
			break;
		}
	}
	if(i==ds.sl) {
		ds.sl++;
		ds.dsLop[i]= Class;
	}
	return i+1;
}

void loadFileDSLop(DSLop &dsLop, string filename){
	ifstream ifs;
	ifs.open(filename, ios_base::in);
	if(ifs.fail() == true) {
		cout << "Ten file chua dung" << endl;
		return ;
	}
	char x;
	SinhVien sv;
	int n;
	int s;
	ifs>>s;
	for(int i = 0; i<s; i++){
		Lop* lop = new Lop();
		ifs>>x;
		ifs.ignore();
		getline(ifs, lop->maLop,'|');
		getline(ifs, lop->tenLop,'|');
		ifs>>n;
		ifs.ignore();
		for(int j = 0; j<n; j++){
		 	getline(ifs,sv.maSinhVien,',');
		 	getline(ifs,sv.ho,',');
		 	getline(ifs,sv.ten,',');
		 	getline(ifs,sv.phai,',');
		 	getline(ifs,sv.matKhau);
		 	themSinhVien(lop->dsSinhVien, sv);
		}
		n=themLop(dsLop,lop);
	}
	ifs.close();
		
}
void luuCauHoi(ofstream &fileout, CauHoi &ch){
	fileout<<ch.maCauHoi<<"|"<<ch.daThi<<endl;
	fileout<<ch.cauHoi<<endl;
	fileout<<ch.cauA<<endl;
	fileout<<ch.cauB<<endl;
	fileout<<ch.cauC<<endl;
	fileout<<ch.cauD<<endl;
	fileout<<ch.dapAn<<endl;
}
void luuMonHoc(treemh t, ofstream &fileout){
	if (t != NULL)
	{
		fileout<<"*"<<endl;
		fileout<<t->data.maMonHoc<<"|"<<t->data.tenMonHoc<<"|"<<t->data.ds.sl<<endl;
		for(int i=0; i<t->data.ds.sl;i++){
			luuCauHoi(fileout, t->data.ds.ds[i]);
		}
		luuMonHoc(t->left,fileout);
		luuMonHoc(t->right,fileout);
	}
	
}
void luuDSMonHoc(treemh &ds, string filename){
	ofstream ofs;
	ofs.open(filename, ios_base::out);
	luuMonHoc(ds,ofs);
	//cout<<"Luu thanh cong";
	ofs.close();
}
int laySoLuongSinhVien(DSSinhVien ds){
	int n = 0;
	for(NodeSinhVien* k =ds.phead; k!=NULL; k= k->next) n++;
	return n;
}
void luuDSLop(DSLop dsl, string filename){
	ofstream ofs;
	ofs.open(filename, ios_base::out);
	ofs<<dsl.sl<<endl;
	for(int i=0; i < dsl.sl; i++){
		ofs<<"*"<<endl;
		ofs<<dsl.dsLop[i]->maLop<<"|"<<dsl.dsLop[i]->tenLop<<"|"<<laySoLuongSinhVien(dsl.dsLop[i]->dsSinhVien)<<endl;
		for(NodeSinhVien* k =dsl.dsLop[i]->dsSinhVien.phead; k!=NULL; k= k->next){
			ofs<<k->data.maSinhVien<<","<<k->data.ho<<","<<k->data.ten<<","<<k->data.phai<<","<<k->data.matKhau<<endl;
		}
	}
	ofs.close();
}
Lop* layLop(DSLop dsl, string maLop){
	for(int i = 0 ; i<dsl.sl; i++){
		if(dsl.dsLop[i]->maLop == maLop)
			return dsl.dsLop[i]; 
	}
}
void copyDS(treemh &t, DStheoTen &dskhoa, int &slmh){
	if (t != NULL){
		copyDS(t->left, dskhoa, slmh);
		Node* node = createNode(t->data.maMonHoc, t->data.tenMonHoc);
		if (dskhoa.phead == NULL){
			dskhoa.phead = node;
		}
		else{
			node->next = dskhoa.phead;
			dskhoa.phead = node;
		}
		slmh++;
		copyDS(t->right, dskhoa, slmh);
	}
}
void swap(Node* &a, Node* &b){
	char tam[15];
	string tentam;
	strcpy(tam,a->maMonHoc);
	tentam = a->tenMonHoc;
	strcpy(a->maMonHoc,b->maMonHoc);
	a->tenMonHoc = b->tenMonHoc;
	strcpy(b->maMonHoc, tam);
	b->tenMonHoc = tentam;
}
void sapXepTheoTenMH(DStheoTen &dskhoa){
	string min;
	Node* vt;
	for(Node* k = dskhoa.phead; k->next!= NULL; k = k->next){
		min = k->tenMonHoc;
		vt = k;
		for(Node* l = k->next; l!=NULL; l= l->next){
			if(min>l->tenMonHoc){
				min = l->tenMonHoc;
				vt=l;
			}
		}
		swap(k,vt);
	}
}
void doiCho2SapXep(NodeSapXep* &k, NodeSapXep* &l){
	NodeSapXep tam;
	tam.maSinhVien=k->maSinhVien;
	tam.tenSinhVien = k->tenSinhVien;
	k->maSinhVien= l->maSinhVien;
	k->tenSinhVien = l->tenSinhVien;
	l->maSinhVien= tam.maSinhVien;
	l->tenSinhVien = tam.tenSinhVien;
}
void sapXepDSSapXep(DSSapXep &ds){
	for(NodeSapXep* k = ds.phead; k != NULL && k->next!= NULL; k = k->next){
		for(NodeSapXep* l = k->next; l!=NULL; l= l->next){
			if(strcmp((char*)k->tenSinhVien.c_str(), (char*)l->tenSinhVien.c_str())>0) doiCho2SapXep(k,l);
			else if(strcmp((char*)k->tenSinhVien.c_str(), (char*)l->tenSinhVien.c_str())==0)
				if(strcmp((char*)k->maSinhVien.c_str(), (char*)l->maSinhVien.c_str())>0) doiCho2SapXep(k,l);
		}
	}
}
MonHoc LNR(treemh t, char* ma){
	if (t != NULL) {
		if(strcmp(ma, t->data.maMonHoc)==0) return t->data;
		else if(strcmp(ma, t->data.maMonHoc)>0) return LNR(t->right,ma);
		else return LNR(t->left,ma);
	}
}
void loadDSMH(DStheoTen &ds, treemh &dsmh, int lan){
	xoaBangMH();
	int i = 1; // dem so dong in ra
	int j = 1; // dem môn hoc in ra tu dau toi dau
	for(Node* k=ds.phead; k!=NULL&&i<=15; k=k->next){
		if(j>15*(lan-1) && j<=15*lan){
		MonHoc mh = LNR(dsmh, k->maMonHoc);
		ButtonMH tmp = CreateButtonMH(1,77,mh);
		DrawButtonMH(tmp,13,13+i,j,ButtonOFF);
		i++;
		}
		j++;
	}
	bangMonHoc(i);
}
void loadDSLop(DSSapXep ds, int lan, DSLop dsl){
	xoaBangMH();
	int i = 1;
	int j = 1; // dem môn hoc in ra tu dau toi dau
	for(NodeSapXep* k = ds.phead; k!=NULL;k=k->next){
		if(i>15*(lan-1) && i<=15*lan){
			
			DrawButtonLop(layLop(dsl, k->maSinhVien),14,13+j,i,ButtonOFF);
			j++;
		}
		i++;
	}
	bangLop(j);
}
NodeSinhVien* laySinhVien2(DSSinhVien ds, string maSinhVien){
	for(NodeSinhVien* k = ds.phead; k != NULL; k = k->next){
		if(k->data.maSinhVien == maSinhVien){
			return k;
		}
	}
}
void loadDSSinhVien(DSSapXep ds, int lan, DSSinhVien dssv){
	xoaBangMH();
	int i=1;
	int j = 1; // dem sv in ra tu dau toi dau
	for(NodeSapXep* k = ds.phead; k!=NULL;k=k->next){
		if(i>15*(lan-1) && i<=15*lan){
			DrawButtonSinhVien(laySinhVien2(dssv, k->maSinhVien),13,13+j,i,ButtonOFF);
			j++;
		}
		i++;
	}
	bangSinhVien(j);
}
void loadDSMH2(DStheoTen &ds, treemh &dsmh, int lan){
	xoaBangMH();
	int i = 1; // dem so dong in ra
	int j = 1; // dem môn hoc in ra tu dau toi dau
	for(Node* k=ds.phead; k!=NULL&&i<=15; k=k->next){
		if(j>15*(lan-1) && j<=15*lan){
		MonHoc mh = LNR(dsmh, k->maMonHoc);
		ButtonMH tmp = CreateButtonMH(1,77,mh);
		DrawButtonMH2(tmp,13,13+i,j,ButtonOFF);
		i++;
		}
		j++;
	}
	bangMonHoc2(i);
}

string layTenMH(treemh t, char* ma){
	if (t != NULL) {
		if(strcmp(ma, t->data.maMonHoc)==0) return t->data.tenMonHoc;
		else if(strcmp(ma, t->data.maMonHoc)>0) return layTenMH(t->right,ma);
		else return layTenMH(t->left,ma);
	}
}
int laySoCauHoi(treemh t, char* ma){
	if (t != NULL) {
		if(strcmp(ma, t->data.maMonHoc)==0) return t->data.ds.sl;
		else if(strcmp(ma, t->data.maMonHoc)>0) return laySoCauHoi(t->right,ma);
		else return laySoCauHoi(t->left,ma);
	}
}
void loadCH(DSCauHoi dsch, int lan){
	xoaBangCH();
	int j=0; // dem soluong cau duoc in ra
	for(int i = 0; i<dsch.sl; i++){
		if(i+1>4*(lan-1) && i+1<=4*lan){
			textcolor(6);
			gotoxy(18,7+6*j);
			cout<<"Cau "<<i+1<<": "<< dsch.ds[i].cauHoi;
			textcolor(7);
			gotoxy(15,8+6*j);
			cout<<"A. "<<dsch.ds[i].cauA;
			gotoxy(15,9+6*j);
			cout<<"B. "<<dsch.ds[i].cauB;
			gotoxy(15,10+6*j);
			cout<<"C. "<<dsch.ds[i].cauC;
			gotoxy(15,11+6*j);
			cout<<"D. "<<dsch.ds[i].cauD;
			textcolor(10);
			if(dsch.ds[i].dapAn=='A'){
				gotoxy(15,8+6*j);
				cout<<"A. ";
			}
			else if(dsch.ds[i].dapAn=='B'){
				gotoxy(15,9+6*j);
				cout<<"B. ";
			}
			else if(dsch.ds[i].dapAn=='C'){
				gotoxy(15,10+6*j);
				cout<<"C. ";
			}
			else{
				gotoxy(15,11+6*j);
				cout<<"D. ";
			}
			j++;
		}
	}
}

void xoaCauHoi(NodeMonHoc* mh, int stt){
	for(int i = stt; i <mh->data.ds.sl; i++)
		mh->data.ds.ds[i-1] = mh->data.ds.ds[i];
	mh->data.ds.sl--;
}
char* layMaDuaVaoSTT( DStheoTen &ds, int vitri){
	int i=1;
	for(Node* k=ds.phead; k!=NULL; k=k->next){
		if (i == vitri) return	k->maMonHoc;
		i++;
	}
}
string layMaDuaVaoSTT2( DSSapXep &ds, int vitri){
	int i=1;
	for(NodeSapXep* k=ds.phead; k!=NULL; k=k->next){
		if (i == vitri) return	k->maSinhVien;
		i++;
	}
}
string layTenDuaVaoSTT( DStheoTen &ds, int vitri){
	int i=1;
	for(Node* k=ds.phead; k!=NULL; k=k->next){
		if (i == vitri) return	k->tenMonHoc;
		i++;
	}
}
bool kt_TrungMaMH(treemh t, char* ma){
	if (t == NULL) return false;
	else {
		if(strcmp(ma, t->data.maMonHoc)==0) return true;
		else if(strcmp(ma, t->data.maMonHoc)>0) return kt_TrungMaMH(t->right,ma);
		else return kt_TrungMaMH(t->left,ma);
	}
}
bool kt_TrungMaLop(DSLop dsl, string ma){
	for(int i = 0; i< dsl.sl; i++)
		if(dsl.dsLop[i]->maLop == ma) return true; // ma da ton tai
	return false;
}
void ChuanHoaTen(string& s, string a){
	while (s[0] == ' ') s.erase(s.begin() + 0); // xoa dau cach dau
	while (s[s.length() - 1] == ' ') s.erase(s.begin() + (s.length() - 1)); // xoa dau  cach cuoi
	if(s.length()>1)
		for (int k = 2; k < s.length() - 2; k++){  // xoa 2 dau cách lien nhau
			if (s[k] == ' ' && s[k + 1] == ' '){
				s.erase(s.begin() + k);
				k--;
			}
		}
	for (int i = 1; i < s.length(); i++){    // chuyen sang chu thuong het
		if (s[i] >= 65 && s[i] <= 90) s[i] = s[i] + 32;
	}
	if (s[0] >= 97 && s[0] <= 122) s[0] = s[0] - 32; // in hoa chu dau
	if(a==""){ // "" la ten mon hoc , kh rong là cau hoi, dap an
		for (int i = 1; i < s.length(); i++){    // in hoa nhung chu o giua
			if (s[i] == ' ' && s[i + 1] >= 97 && s[i + 1] <= 122) s[i + 1] = s[i + 1] - 32;
		}
	}
}
int nhapThongTinMonHoc(int x, int y,MonHoc &mh, treemh dsmh){
	Nocursortype(TRUE);
	strcpy(mh.maMonHoc, "");
	mh.tenMonHoc = "";
	thongbao("*** TOI DA 15 KY TU, BAO GOM KY TU CHU, SO", 35,33,10,7);
	gotoxy(x,y);
	char k;
	int i =0;
	bool t = true; // con tro dang ben ma mon hoc
	
	while(1){
		k = _getch();
		if(k == 13){
			ChuanHoaTen(mh.tenMonHoc,"");
			if(strcmp(mh.maMonHoc,"")==0 ){
				thongbao("MA MON HOC KHONG DUOC RONG!!!", 40,32,4,7);
				Sleep(2000);
				xoahang(32); 
				gotoxy(x,y);
				t=true;
			}
			else if( mh.tenMonHoc == ""){
				thongbao("TEN MON HOC KHONG DUOC RONG!!!", 40,32,4,7);
				Sleep(2000);
				xoahang(32); 
				gotoxy(x+18,y);
				t=false;
			}
			else if(kt_TrungMaMH(dsmh, mh.maMonHoc)==true){
				thongbao("MA MON HOC DA TON TAI !!!", 40,32,4,7);
				Sleep(2000);
				xoahang(32); 
				gotoxy(x,y);
				cout<<mh.maMonHoc;
				t = true;
				}
			
			else {
				xoahang(33); 
				Nocursortype(FALSE);
				return 1;
			}
		}
		else if(k == 27) {
			xoahang(33);
			Nocursortype(FALSE);
			return 0;
		}
		else if(k==75) {
			t = true;
			xoahang(33);
			thongbao("*** TOI DA 15 KY TU, BAO GOM KY TU CHU HOAC SO", 35,33,10,7);
			gotoxy(x,y);
			cout<<mh.maMonHoc;
		}
		else if(k==77) {
			t = false;
			xoahang(33);
			thongbao("*** BAO GOM KY TU CHU, SO HOAC KY TU DAC BIET", 35,33,10,7);
			gotoxy(x+18,y);
			cout<<mh.tenMonHoc;
		}
		else if(k == 8 ){
			if(t == true &&strcmp(mh.maMonHoc,"")>0){
				mh.maMonHoc[i-1] = '\0';
				for(int j = x; j<=x+15;j++){
					gotoxy(j, y);
					cout<<" ";
					if(j==35){
						gotoxy(j,y);
		  				printf("%c",186);
		  			}
				}
				i--;
				gotoxy(x, y);
				cout<<mh.maMonHoc;
			}
			else if(t==false&&mh.tenMonHoc.length()>0){
				mh.tenMonHoc.erase(mh.tenMonHoc.length()-1, 1);
				gotoxy(x+mh.tenMonHoc.length()+18,y);
				cout<<" ";
				gotoxy(x+mh.tenMonHoc.length()+18,y);
			}
		}
		else if((k>=32 && k<=122) && t ==false){
			mh.tenMonHoc.push_back(k); 
			cout<<k;
		}
		else if(k>=97 && k<=122 && t == true){
			if(i == 15) continue;
			k=k-32;
			mh.maMonHoc[i]= k;
			i++;
			cout<<k;
		}
		else if(t==true && ((k>=65 && k <=90) || (k>=48 && k <=57))){
			if(i == 15) continue;
			mh.maMonHoc[i] = k;
			i++;
			cout<<k;
		}	
		
	}
}

int nhapThongTinLop(int x, int y,Lop &lop, DSLop dsl){
	Nocursortype(TRUE);
	xoaBangHoTro();
	hoTroThem();
	lop.maLop = "";
	lop.tenLop = "";
	gotoxy(x,y);
	char k;
	bool t = true; // con tro dang ben ma 
	
	while(1){
		k = _getch();
		if(k == 13){
			ChuanHoaTen(lop.tenLop,"");
			if(lop.maLop==""){
				thongbao("MA LOP KHONG DUOC RONG!!!", 40,32,4,7);
				Sleep(2000);
				xoahang(32); 
				gotoxy(x,y);
				t=true;
			}
			else if( lop.tenLop == ""){
				thongbao("TEN LOP KHONG DUOC RONG!!!", 40,32,4,7);
				Sleep(2000);
				xoahang(32); 
				gotoxy(x+18,y);
				t=false;
			}
			else if(kt_TrungMaLop(dsl,lop.maLop)==true){
				thongbao("MA LOP DA TON TAI !!!", 40,32,4,7);
				Sleep(2000);
				xoahang(32); 
				gotoxy(x+lop.maLop.length(),y);
				t = true;
				}
			
			else {
				Nocursortype(FALSE);
				return 1;
			}
		}
		else if(k == 27) {
			Nocursortype(FALSE);
			return 0;
		}
		else if(k==75&&t==false) { // trai
			t = true;
			gotoxy(x+lop.maLop.length(),y);
		}
		else if(k==77&&t==true) { // phai
			t = false;
			gotoxy(x+18+lop.tenLop.length(),y);
		}
		else if(k == 8){
			if(t == true &&lop.maLop.length()>0){
				lop.maLop.pop_back();
				gotoxy(x+lop.maLop.length(),y);
				cout<<" ";
				gotoxy(x+lop.maLop.length(),y);
			}
			else if(t==false&&lop.tenLop.length()>0){
				lop.tenLop.erase(lop.tenLop.length()-1, 1);
				gotoxy(x+lop.tenLop.length()+18,y);
				cout<<" ";
				gotoxy(x+lop.tenLop.length()+18,y);
			}
		}
		else if((k>=32 && k<=122) && t ==false && lop.tenLop.length()<58){
			lop.tenLop.push_back(k); 
			cout<<k;
		}
		else if(k>=97 && k<=122 && t == true && lop.maLop.length()<15){
			k=k-32;
			lop.maLop.push_back(k);
			cout<<k;
		}
		else if(t==true && lop.maLop.length()<15 && ((k>=65 && k <=90) || (k>=48 && k <=57))){
			lop.maLop.push_back(k);
			cout<<k;
		}	
		
	}
}

bool nhapTenMonHoc (string &ten, int x, int y){
	Nocursortype(TRUE);
	thongbao("*** BAO GOM KY TU CHU, SO HOAC KY TU DAC BIET", 35,35,10,7);
	gotoxy(x+ten.length(),y);	
	char k;
	while(1){
		k = _getch();
		if( k==13 ){
			ChuanHoaTen(ten,"");
			if( ten==""){
				thongbao("TEN KHONG DUOC RONG !!!", 40,32,4,7);
				Sleep(2000);
				xoahang(32); 
				gotoxy(x,y);
				continue;
			}
			
			else {
				xoahang(34);
				xoahang(35); 
				Nocursortype(FALSE);
				return true;
			}
		}
		if(k==27) {
			xoahang(34);
			xoahang(35);
			Nocursortype(FALSE);
			return false;
		}
		if(k==8&&ten.length()>0){
			ten.erase(ten.length()-1, 1);
			gotoxy(x+ten.length(),y);
			cout<<" ";
			gotoxy(x+ten.length(),y);
			continue;
		}
		if((k>=32 && k<=122)){
			ten.push_back(k); 
			cout<<k;
			continue;
		}
		
	}
}

void xoaDSSapxep(DStheoTen &ds){
	Node* p;
	while(ds.phead!= NULL){
		p = ds.phead;
		ds.phead = ds.phead->next;
		delete p;
	}
}
void xoaDSSapxep2(DSSapXep &ds){
	NodeSapXep* p;
	while(ds.phead!= NULL){
		p = ds.phead;
		ds.phead = ds.phead->next;
		delete p;
	}
}
void xoaCayMonHoc(treemh &t){
	if(t!=NULL){
		xoaCayMonHoc(t->left);
		xoaCayMonHoc(t->right);
		NodeMonHoc* p = t;
		t= NULL;
		delete p;
	}
}
void xoaDSLop(DSLop &dsl){
	NodeSinhVien* p;
	for(int i = 0; i<dsl.sl; i++){
		while(dsl.dsLop[i]->dsSinhVien.phead != NULL){
			p=dsl.dsLop[i]->dsSinhVien.phead;
			dsl.dsLop[i]->dsSinhVien.phead = dsl.dsLop[i]->dsSinhVien.phead->next;
			delete p;
		}
		delete dsl.dsLop[i];
	}
}
int demso(int n){
	int dem = 0;
	while(n>0){
		n=n/10;
		dem++;
	}
	return dem;
}
void ChuyenSangChuThuong(string &s){
	for (int i = 0; i < s.length(); i++){
		if (s[i] >= 65 && s[i] <= 90) s[i] = s[i] + 32;
	}
}	
bool kt_S1chuaS2(string s1, string s2){ // S1 là ten mon hoc co san, s2 do ng dung nhap tim kiem
	ChuanHoaTen(s2,"");
	ChuyenSangChuThuong(s1);
	ChuyenSangChuThuong(s2);
	if(strstr(s1.c_str(),s2.c_str()))
	{
	   return true;
	}
	return false;
}
NodeMonHoc* layMonHoc(treemh t, char* ma){
	if (t != NULL) {
		if(strcmp(ma, t->data.maMonHoc)==0) return t;
		else if(strcmp(ma, t->data.maMonHoc)>0) return layMonHoc(t->right,ma);
		else return layMonHoc(t->left,ma);
	}
}
void taoDSTmKiem(treemh t,DStheoTen &ds, string ten, int &n){
	if (t != NULL){
		taoDSTmKiem(t->left, ds, ten,n);
		if (kt_S1chuaS2(t->data.tenMonHoc, ten)==true){
			Node* node = createNode(t->data.maMonHoc, t->data.tenMonHoc);
			if (ds.phead == NULL){
				ds.phead = node;
			}
			else{
				node->next = ds.phead;
				ds.phead = node;
			}
			n++;
			
		}
		taoDSTmKiem(t->right, ds, ten,n);
	}
	else return;
}
void taoDSTmKiem2(DStheoTen dsg, DStheoTen &ds, string ten, int &n){
	xoaDSSapxep(ds);
	n=0;
	for(Node* k = dsg.phead; k!= NULL; k = k->next){
		if (kt_S1chuaS2(k->tenMonHoc, ten)==true){
			Node* node = createNode(k->maMonHoc, k->tenMonHoc);
			if (ds.phead == NULL){
				ds.phead = node;
			}
			else{
				node->next = ds.phead;
				ds.phead = node;
			}
			n++;
		}
	}
}
void taoDSTmKiemLop(DSLop dsl,DSSapXep &ds, string ten, int &n){
	xoaDSSapxep2(ds);
	n=0;
	for(int i = 0; i<dsl.sl; i++){
		if (kt_S1chuaS2(dsl.dsLop[i]->tenLop, ten)==true || kt_S1chuaS2(dsl.dsLop[i]->maLop, ten)==true){
			NodeSapXep* nodeSX = new NodeSapXep();
			nodeSX->maSinhVien= dsl.dsLop[i]->maLop;
			nodeSX->tenSinhVien= dsl.dsLop[i]->tenLop;
			nodeSX->next = NULL;
			if (ds.phead == NULL){
				ds.phead = nodeSX;
			}
			else{
				nodeSX->next = ds.phead;
				ds.phead = nodeSX;
			}
			n++;
		}
	}
	if (n!=0)sapXepDSSapXep(ds);
}
void taoDSTmKiemSV(DSSinhVien dssv,DSSapXep &ds, string ten, int &n){
	xoaDSSapxep2(ds);
	n=0;
	for(NodeSinhVien* k = dssv.phead; k!=NULL; k = k->next){
		if (kt_S1chuaS2(k->data.ho+" "+ k->data.ten, ten)==true || kt_S1chuaS2(k->data.maSinhVien, ten)==true){
			NodeSapXep* nodeSX = new NodeSapXep();
			nodeSX->maSinhVien= k->data.maSinhVien;
			nodeSX->tenSinhVien= k->data.ten;
			nodeSX->next = NULL;
			if (ds.phead == NULL){
				ds.phead = nodeSX;
			}
			else{
				nodeSX->next = ds.phead;
				ds.phead = nodeSX;
			}
			n++;
		}
	}
	if (n!=0)sapXepDSSapXep(ds);
}
int laySTTMonHocNew(DStheoTen &ds, char* ma){ // lay stt mon hoc moi them vao dua vao mã
	int i=1;
	for(Node* k=ds.phead; k!=NULL; k=k->next){
		if (strcmp(ma,k->maMonHoc) == 0) return	i;
		i++;
	}
}
bool kt_CauHoi(NodeMonHoc* mh, string ch){ // kt cau hoi da ton tai hay chua
	for(int i = 0 ; i< mh->data.ds.sl; i++){
		if(mh->data.ds.ds[i].cauHoi == ch) return false; // cau hoi da ton tai
	}
	return true; // cau hoi chua ton tai
}
bool kt_TonTaiCauHoi(treemh t, char* ma){
	if (t != NULL) {
		if(strcmp(ma, t->data.maMonHoc)==0) {
			if(t->data.ds.sl>0) return true; // da ton tai cau hoi
			return false; // chua ton tai cau hoi
		}
		else if(strcmp(ma, t->data.maMonHoc)>0) return kt_TonTaiCauHoi(t->right,ma);
		else return kt_TonTaiCauHoi(t->left,ma);
	}
}

bool kt_SVChuaThi(NodeSinhVien* sv, char* maMonHoc){
	for(NodeDiemThi* k = sv->data.dsDiem.phead; k!=NULL; k = k->next)
		if(strcmp(k->data.maMonHoc,maMonHoc)==0) return false;
	
	return true;
}
void xoaPhanTuMangDong(int* &p,int &n, int vt){
	for(int i=vt;i<=n;i++)	*(p+i)=*(p+1+i);
	n--;
}
void layNgauNhien(int* &s,int bd, int kt, int sl){ // bd = 0 kt = slch - 1
	int n = kt-bd+1; // so luong phan tu cua khong gian mau
	int* p = new int[n];
	s = new int[sl];
	int x;
	for(int i = 0; i<  n; i++){
		*(p+i) = bd;
		bd++;
	}
	for(int i=0;i<sl;i++){
		srand(time(NULL));
		x= rand() % n + 0;
		*(s+i)=*(p + x);
		xoaPhanTuMangDong(p,n,x);
	}
	delete[] p;
}
int demSoCauDaLam(char* cauTraLoi, int soCau){
	int dem = 0;
	for(int i = 0 ; i < soCau; i++)
		if(*(cauTraLoi+i)!='X') dem++;
	return dem;
}
float tinhDiem(DSCauHoi dsch, int* cauNgauNhien,char* cauTraLoi, int soCau, int &soCauDung){
	soCauDung = 0;
	for(int i = 0; i<soCau; i++)
		if(dsch.ds[*(cauNgauNhien+i)].dapAn == *(cauTraLoi+i)) soCauDung++;
	float diem = ((soCauDung*1.0)/(soCau*1.0))*10;
	return roundf(diem * 100) / 100;
}
void thucThiThemCauHoi(NodeMonHoc* mh){
	Nocursortype(TRUE);
	char c = '\0';
	CauHoi ch;
	int tro;// vi tri con tro: 1=cau hoi, 2= A, 3=B, 4 = C, 5 = D, 6 = DAPAN
tieptuc:	
	ch.cauHoi = "";
	ch.cauA = "";
	ch.cauB = "";
	ch.cauC = "";
	ch.cauD = "";
	ch.dapAn = '\0';
	system("cls");
	giaoDienThemCauHoi();
	textcolor(6);
	gotoxy(35,3);
	cout<<mh->data.maMonHoc;
	gotoxy(35,4);
	cout<<mh->data.tenMonHoc;
	
	gotoxy(35,5);
	cout<<mh->data.ds.sl;
	textcolor(10);
	gotoxy(32,12); // KHOI TAO TRO O NHAP CAU HOI
	tro = 1;
	while(c!=27){
		c= _getch();
		switch(c){
			case 13:{
				ChuanHoaTen(ch.cauHoi,"ch");
				ChuanHoaTen(ch.cauA,"ch");
				ChuanHoaTen(ch.cauB,"ch");
				ChuanHoaTen(ch.cauC,"ch");
				ChuanHoaTen(ch.cauD,"ch");
				if(ch.cauHoi == ""){
					thongbao("VUI LONG NHAP NOI DUNG CAU HOI !!!", 40,31, 4,7);
					Sleep(2000);
					xoahang(31);
					gotoxy(32,12);
					tro = 1;
				}
				else if(ch.cauA==""){
					thongbao("VUI LONG NHAP NOI DUNG DAP AN A !!!", 40,31, 4,7);
					Sleep(2000);
					xoahang(31);
					tro = 2;
					gotoxy(32,16+(tro-2)*3);
				}
				else if(ch.cauB==""){
					thongbao("VUI LONG NHAP NOI DUNG DAP AN B !!!", 40,31, 4,7);
					Sleep(2000);
					xoahang(31);
					tro = 3;
					gotoxy(32,16+(tro-2)*3);
				}
				else if(ch.cauC==""){
					thongbao("VUI LONG NHAP NOI DUNG DAP AN C !!!", 40,31, 4,7);
					Sleep(2000);
					xoahang(31);
					tro = 4;
					gotoxy(32,16+(tro-2)*3);
				}
				else if(ch.cauD==""){
					thongbao("VUI LONG NHAP NOI DUNG DAP AN D !!!", 40,31, 4,7);
					Sleep(2000);
					xoahang(31);
					tro = 5;
					gotoxy(32,16+(tro-2)*3);
				}
				else if(ch.dapAn=='\0'){
					thongbao("VUI LONG NHAP DAP AN DUNG !!!", 40,31, 4,7);
					Sleep(2000);
					xoahang(31);
					tro = 6;
					gotoxy(50,28);
				}
				else if(kt_CauHoi(mh, ch.cauHoi)==false){
					thongbao("CAU HOI DA TON TAI !!!", 40,31, 4,7);
					Sleep(2000);
					xoahang(31);
					gotoxy(32+ch.cauHoi.length(),12);
					tro = 1;
				}
				else if(ch.cauA == ch.cauB || ch.cauA == ch.cauC || ch.cauA == ch.cauD || ch.cauB == ch.cauC || ch.cauB == ch.cauD || ch.cauC == ch.cauD){
					thongbao("CAC DAP AN KHONG DUOC TRUNG NHAU !!!", 40,31, 4,7);
					Sleep(2000);
					xoahang(31);
					gotoxy(32+ch.cauA.length(),16);
					tro = 2;
				}
				else{
					ch.maCauHoi = mh->data.ds.ds[mh->data.ds.sl-1].maCauHoi+1;
					mh->data.ds.ds[mh->data.ds.sl]= ch;
					mh->data.ds.sl++;
					thongbao("THEM CAU HOI THANH CONG !!!", 40,31,10,7);
					Sleep(2000);
					xoahang(31);
					Nocursortype(FALSE);
					goto tieptuc;
				}
			}
			break;
			case 72: { // LÊN
				if(tro >1){
					tro--;
					if(tro==1) gotoxy(32+ch.cauHoi.length(),12);
					else if(tro==2) gotoxy(32+ch.cauA.length(),16+(tro-2)*3);
					else if(tro==3) gotoxy(32+ch.cauB.length(),16+(tro-2)*3);
					else if(tro==4) gotoxy(32+ch.cauC.length(),16+(tro-2)*3);
					else if(tro==5) gotoxy(32+ch.cauD.length(),16+(tro-2)*3);
				}
			}
			break;
			case 80: { // XUONG
				if(tro <6){
					tro++;
					if(tro==6) gotoxy(45 + ((ch.dapAn=='\0')? 0:1),16+(tro-2)*3);
					else if(tro==2) gotoxy(32+ch.cauA.length(),16+(tro-2)*3);
					else if(tro==3) gotoxy(32+ch.cauB.length(),16+(tro-2)*3);
					else if(tro==4) gotoxy(32+ch.cauC.length(),16+(tro-2)*3);
					else if(tro==5) gotoxy(32+ch.cauD.length(),16+(tro-2)*3);
				}
			}
			break;
			case 8:{
				if(tro==1&&ch.cauHoi.length()>0){
					ch.cauHoi.erase(ch.cauHoi.length()-1, 1);
					gotoxy(32+ch.cauHoi.length(),12);
					cout<<" ";
					gotoxy(32+ch.cauHoi.length(),12);
				}
				else if(tro==2&&ch.cauA.length()>0){
					ch.cauA.erase(ch.cauA.length()-1, 1);
					gotoxy(32+ch.cauA.length(),16+(tro-2)*3);
					cout<<" ";
					gotoxy(32+ch.cauA.length(),16+(tro-2)*3);
				}
				else if(tro==3&&ch.cauB.length()>0){
					ch.cauB.erase(ch.cauB.length()-1, 1);
					gotoxy(32+ch.cauB.length(),16+(tro-2)*3);
					cout<<" ";
					gotoxy(32+ch.cauB.length(),16+(tro-2)*3);
				}
				else if(tro==4&&ch.cauC.length()>0){
					ch.cauC.erase(ch.cauC.length()-1, 1);
					gotoxy(32+ch.cauC.length(),16+(tro-2)*3);
					cout<<" ";
					gotoxy(32+ch.cauC.length(),16+(tro-2)*3);
				}
				else if(tro==5&&ch.cauD.length()>0){
					ch.cauD.erase(ch.cauD.length()-1, 1);
					gotoxy(32+ch.cauD.length(),16+(tro-2)*3);
					cout<<" ";
					gotoxy(32+ch.cauD.length(),16+(tro-2)*3);
				}
				else if(tro==6&&ch.dapAn!='\0'){
					ch.dapAn = '\0';
					gotoxy(45,16+(tro-2)*3);
					cout<<" ";
					gotoxy(45,16+(tro-2)*3);
				}
			}
			break;
			default:{
				if((c>=32 && c<=122) && (tro>=1 &&tro<=5)){
					if (tro == 1) ch.cauHoi.push_back(c);
					else if (tro == 2) ch.cauA.push_back(c);
					else if (tro == 3) ch.cauB.push_back(c);
					else if (tro == 4) ch.cauC.push_back(c);
					else if (tro == 5) ch.cauD.push_back(c);
					cout<<c;
				}
				else if((c>=65&&c<=68)&&tro==6&&ch.dapAn =='\0' ){
					ch.dapAn = c;
					cout<<c;
				}
				else if((c>=97&&c<=100)&&tro==6&&ch.dapAn == '\0'){
					c = c-32;
					ch.dapAn = c;
					cout<<c;
				}
			}
			break;
				
		}
	}
	Nocursortype(FALSE);
}
void thucThiCauHoi(NodeMonHoc* monHoc){
	system("cls");
	char k;
	int slch; // só luong cau hoi
	int maxTrang;
	int trangHienTai=1;
quay1:	giaoDienCauHoi();
	slch = monHoc->data.ds.sl;
	maxTrang = slch/4 +((slch%4==0) ? 0:1);
	textcolor(6);
	gotoxy(35,2);
	cout<<monHoc->data.maMonHoc;
	gotoxy(35,3);
	cout<<monHoc->data.tenMonHoc;
	gotoxy(35,4);
	cout<< slch;
quay2:	
	textcolor(10);
	gotoxy(48,31);
	cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
	loadCH(monHoc->data.ds,trangHienTai);
	while(k!=27){
		k = _getch();
		switch(k){
			case 75: { //qua trai
				if(trangHienTai>1){
					trangHienTai--;
					goto quay2;
				}
			}
			break;
			case 77: { // qua phai
				if(trangHienTai<maxTrang){
					trangHienTai++;
					goto quay2;
				}
			}
			break;
			case 82: { // insert
				thucThiThemCauHoi(monHoc);
				system("cls");
				goto quay1;
			}
			break;
			case 83: { // delete
				int stt = 0;
				char c;
quay3:			khungXoaCauHoi();
				Nocursortype(TRUE);
				gotoxy(69,33);
				while(1){
					c= _getch();
					if(c==27){
						xoaKhungXoaCH();
						Nocursortype(FALSE);
						textcolor(10);
						gotoxy(48,31);
						cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
						break;
					}
					else if(c==13){
						if(stt>slch||stt==0){
							xoaKhungXoaCH();
							thongbao("KHONG TON TAI THU TU CAU HOI DA NHAP",40,32,4,7);
							Sleep(2000);
							xoahang(32);
							stt = 0;
							goto quay3;
						}
						else{
							trangHienTai = (stt)/4 +(((stt)%4==0) ? 0:1);
							textcolor(10);
							gotoxy(48,31);
							cout<<"Trang "<<trangHienTai<<"/"<<maxTrang<<"    ";
							loadCH(monHoc->data.ds,trangHienTai);
							xoaKhungXoaCH();
							if(monHoc->data.ds.ds[stt-1].daThi == true ){
							xoaKhungXoaCH();
							thongbao("DA CO SINH VIEN THI CAU HOI NAY !!! KHONG THE XOA",35,32,4,7);
							Sleep(2000);
							xoahang(32);
							stt = 0;
							goto quay3;
						}
							//x.insert(x.length()-1, "khong???");
							khungConfirm("Co chac chan muon xoa ???",7,4);
							 
							while(1){
								c = _getch();
								if(c == 89 || c == 121){
									xoaCauHoi(monHoc,stt);
									xoaKhungConfirm();
									thongbao("Xoa cau hoi thanh cong !!!", 40,32,6,7);
									Sleep(2000);
									xoahang(32);
									slch--;
									maxTrang = slch/4 +((slch%4==0) ? 0:1);
									trangHienTai = (stt-1)/4 +(((stt-1)%4==0) ? 0:1);
									Nocursortype(FALSE);
									goto quay2;
								}
								else if(c == 78 || c == 110){
									xoaKhungConfirm();
									Nocursortype(FALSE);
									gotoxy(48,31);
									cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
									break;
								}
							}
							break;
						}
					}
					else if(c==8&&stt>0){
						stt /= 10;
						gotoxy(69,33);
						cout<<"   ";
						gotoxy(69,33);
						if (stt!= 0) cout<<stt;
					}
					else if((c>=48 && c<=57 && stt <20) || (c==48 && stt == 20)) {
						stt = stt*10+(c-48);
						cout<<c;
					}	
				} 
				Nocursortype(FALSE);
			}
			break;
		}
	}
}
void copy2DSTheoTen(DStheoTen dsg, DStheoTen &ds){
	xoaDSSapxep(ds);
	for(Node* k = dsg.phead; k != NULL ; k = k->next){
		Node* node = createNode(k->maMonHoc, k->tenMonHoc);
		if (ds.phead == NULL){
				ds.phead = node;
		}
		else{
			node->next = ds.phead;
			ds.phead = node;
		}
	}
}
char* XemMonHoc(DStheoTen &dsg, int n, treemh dsmh){
	system("cls");
	DStheoTen ds;
	copy2DSTheoTen(dsg, ds);
	char kytu;
	int slmh = n;
	int chon = 1; // lua chontren 1 trang
	string timkiem="";
	int maxTrang; // so trang toi da de chua het mon hoc
	int trangHienTai = 1;  //trang hien tai dang in tren manhinh
	int f = 1; // danh dau co phai dang o trang tim kiem hay khong, co hieu cho nut esc, 1 là man hinh chinh, 2 là man hinh tim kiem, 0 la thoat
	ButtonMH tmp;
	sapXepTheoTenMH(ds);
	giaodienXemMonHoc();
quaylai:	maxTrang = slmh/15 +((slmh%15==0) ? 0:1); // neu chia het cho 15 thi khong cong 1
	loadDSMH2(ds,dsmh,trangHienTai);
	gotoxy(48,31);
	cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
	tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
	DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
	while(kytu!=27 || f !=0){ // neu nhan esc khi o man hinh chinh (khong phai o man hinh tim kiem )
		kytu=_getch();
		switch(kytu){
			case 72:{ // nút lên
				if(trangHienTai>1&&chon ==1){
					chon = 15;
					trangHienTai--;
					loadDSMH2(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;	
					}
				else if(chon>1){
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonOFF);
					chon --;
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					}
				}
				break;
			case 80:{ // nút xuong
				if(chon+15*(trangHienTai-1) == slmh){ // so chon hien tai == so luong mon hoc
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,slmh) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonOFF);
					chon = 1;
					trangHienTai = 1;
					loadDSMH2(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
					}
				else if(chon<15){
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonOFF);
					chon ++;
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					}
				else if(chon == 15) { // nut chon o cuoi trang
					chon = 1;
					trangHienTai++;
					loadDSMH2(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;	
					}
				}
				break;	
			case 75:{ // qua trái
				if(trangHienTai>1){
					chon = 1;
					trangHienTai -- ;
					loadDSMH2(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
					}
				}
				break;	
			case 77:{ // qua phai
				if(trangHienTai<maxTrang){
					chon = 1;
					trangHienTai++ ;
					loadDSMH2(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
					}
				}
				break;	
			
			case 6:{ // CTRL + F: Tim kiem
				thongbao("*** TIM KIEM THEO TEN MON HOC" , 35,34, 10,7);
				if(nhapTenMonHoc(timkiem,33,8)==true){
					taoDSTmKiem2(dsg,ds,timkiem,slmh);
					f = 2; // chuyen sang man hinh tim kiem
					if(slmh==0){
						thongbao("KHONG TON TAI MON HOC !!!",40,31,4,7);
						Sleep(2000);
						xoahang(31);
						gotoxy(33,8);
						for(int m =0;m<timkiem.size();m++ ) cout<<" ";
						timkiem="";
						copy2DSTheoTen(dsg, ds);
						slmh = n;
						f=1;
					}
					sapXepTheoTenMH(ds);
					trangHienTai = 1;
					chon = 1;
					goto quaylai;
				}
				else { // khi dang nhap ma nhan esc
					gotoxy(33,8);   // xoa chu tren o tim kiem
					for(int m =0;m<timkiem.size();m++ ) cout<<" ";
					timkiem="";
					xoahang(34);
					copy2DSTheoTen(dsg, ds);
					slmh = n;
					sapXepTheoTenMH(ds);
					loadDSMH2(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH2(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);	
				}
							
			}
				break;
			case 13:{ // Enter: Chon mon hoc
				system("cls");
				return layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1));
			}
				break;
			case 27: 
				if(f==2) {
					gotoxy(33,8);
					for(int m =0;m<timkiem.size();m++ ) cout<<" ";
					timkiem="";
					copy2DSTheoTen(dsg, ds);
					slmh = n;
					sapXepTheoTenMH(ds);
					chon = 1;
					trangHienTai = 1;
					xoahang(34);
					f=1;
					goto quaylai;
				}
				else if(f==1){
					f=0;
				}
				break;
		}
	}
	system("cls");
	return NULL;
	
}
int nhapThongTinThi(NodeSinhVien* sv, string &maLop,string &tenLop, char* maMonHoc, int &soCau, int &soPhut, treemh t){
	Nocursortype(TRUE);
	
	strcpy(maMonHoc, "");
	soCau = 0;
	soPhut = 0;
	char k;
	int i = 0;
	int tro = 1; // con tro dang ben ma mon hoc, 1: ma, 2: so cau, 3: so phut
quay: system("cls");
	textcolor(14);
	if(sv != NULL){
		gotoxy(14,6);
		cout<<"MA SINH VIEN:  "<<sv->data.maSinhVien;
		gotoxy(14,8);
		cout<<"TEN SINH VIEN: "<<sv->data.ho <<" "<<sv->data.ten;
		gotoxy(14,10);
		cout<<"LOP:           "<<maLop <<" - "<< tenLop;
	}
	else {
		gotoxy(20,8);
		cout<<"GIANG VIEN THI THU";
	}
	giaoDienNhapThi();
	thongbao("*** F5 - XEM DANH SACH MON HOC", 35,22,10,7);
	gotoxy(37, 18);
	if(soCau!=0) cout<<soCau;
	gotoxy(37, 20);
	if(soPhut!=0) cout<<soPhut;
	gotoxy(37, 16);
	cout<<maMonHoc;
	
	while(1){
		k = _getch();
		switch(k){
			case 13:{
				if(strcmp(maMonHoc,"")==0 ){
					thongbao("MA MON HOC KHONG DUOC RONG!!!", 40,31,4,7);
					Sleep(2000);
					xoahang(31); 
					thongbao("*** F5 - XEM DANH SACH MON HOC", 35,22,10,7);
					gotoxy(37,16);
					tro=1;
				}
				else if(kt_TrungMaMH(t, maMonHoc)==false){
					thongbao("MA MON HOC KHONG TON TAI !!!", 40,31,4,7);
					Sleep(2000);
					xoahang(31); 
					thongbao("*** F5 - XEM DANH SACH MON HOC", 35,22,10,7);
					gotoxy(37,16);
					cout<<maMonHoc;
					tro = 1;
				}
				else if(soCau <= 0){
					thongbao("SO CAU HOI PHAI LON HON 0!!!", 40,31,4,7);
					Sleep(2000);
					xoahang(31); 
					xoahang(22);
					gotoxy(37+demso(soCau),18);
					tro=2;
				}
				else if(soCau>laySoCauHoi(t,maMonHoc)){
					textcolor(4);
					SetBGColor(7);
					for(int j = 30; j< 85; j++){
						gotoxy(j, 31);
						cout<<" ";
					}
					gotoxy(35,31);
					cout<<"SO CAU THI LON HON SO CAU TREN BO DE NGUON ["<<laySoCauHoi(t,maMonHoc)<<"]";
					Sleep(2000);
					xoahang(31);
					xoahang(22);
					gotoxy(37+demso(soCau),18);
					tro=2;
				}
				else if(soPhut == 0){
					thongbao("SO PHUT THI PHAI LON HON 0!!!", 40,31,4,7);
					Sleep(2000);
					xoahang(31); 
					xoahang(22);
					gotoxy(37+demso(soPhut),20);
					tro=3;
				}
				else if(sv!=NULL && kt_SVChuaThi(sv,maMonHoc)==false){
					thongbao("SINH VIEN DA THI MON HOC NAY ROI !!!", 40,31,4,7);
					Sleep(2000);
					xoahang(31); 
					thongbao("*** F5 - XEM DANH SACH MON HOC", 35,22,10,7);
					gotoxy(37,16);
					cout<<maMonHoc;
					tro = 1;
				}
				else {
					Nocursortype(FALSE);
					return 1;
				}
			}
			break;
			case 27: {
				Nocursortype(FALSE);
				return 0;
			}
			break;
			case 72: { // LÊN
				if(tro >1){
					tro--;
					if(tro==1){
						thongbao("*** F5 - XEM DANH SACH MON HOC", 35,22,10,7);
						gotoxy(37+i,16);
					}
					else if(tro==2) gotoxy(37+demso(soCau),18);
				}
			}
			break;
			case 80: { // XUONG
				if(tro <3){
					tro++;
					if(tro==2) {
						xoahang(22);
						gotoxy(37+demso(soCau),18);
					}
					else if(tro==3) gotoxy(37+demso(soPhut),20);
				}
			}
			break;
			case 8:{
				if(tro == 1 &&strcmp(maMonHoc,"")>0){
					maMonHoc[i-1] = '\0';
					for(int j = 37; j<=37+i;j++){
						gotoxy(j, 16);
						cout<<" ";
					}
					i--;
					gotoxy(37, 16);
					cout<<maMonHoc;
				}
				else if(tro == 2 &&soCau>0){
					soCau /= 10;
					gotoxy(37+demso(soCau),18);
					cout<<" ";
					gotoxy(37 + demso(soCau),18);
				}
				else if(tro==3&&soPhut>0){
					soPhut /= 10;
					gotoxy(37+demso(soPhut),20);
					cout<<" ";
					gotoxy(37 + demso(soPhut),20);
				}
				
			}
			break;
			case 63:{
				if(tro == 1){
					DStheoTen ds;
					char* matam;
					int slmh = 0;
					xoaDSSapxep(ds);
					copyDS(t, ds, slmh);
					matam = XemMonHoc(ds,slmh, t);
					if(matam != NULL) {
						strcpy(maMonHoc, matam);
						i = strlen(maMonHoc);
					}
					goto quay;	
				}
			}
			break;
			default:{
				if(k>=97 && k<=122 && tro == 1){
					if(i == 15) continue;
					k=k-32;
					maMonHoc[i]= k;
					i++;
					cout<<k;
				}
				else if(tro==1 && ((k>=65 && k <=90) || (k>=48 && k <=57))){
					if(i == 15) continue;
					maMonHoc[i] = k;
					i++;
					cout<<k;
				}	
				else if(tro == 2 &&((k>=48 && k<=57 && soCau <20) || (k==48 && soCau == 20))){
						soCau = soCau*10+(k-48);
						cout<<k;
					}
				else if(tro == 3 &&k>=48 && k<=57 ){
						soPhut = soPhut*10+(k-48);
						cout<<k;
					}
			}
			break;
				
		}
		
	}
}
void dongHo(int soPhut){
	int giay;
	textcolor(10);
	SetBGColor(0);
	gotoxy(84,14);
	cout<<soPhut<<":00";
	
	while(soPhut>0){
		soPhut--;
		for(int giay = 59; giay>=0&&stop==0;giay--){
			textcolor(10);
			SetBGColor(0);
			if(soPhut == 0) {
				textcolor(4);
				SetBGColor(0);
			}
			gotoxy(84,14);
			if(soPhut<10) cout<<"0"<<soPhut<<":";
			else cout<<soPhut<<":";
			gotoxy(87,14);
			if(giay<10) cout<<"0"<<giay;
			else cout<<giay;
			Sleep(980);
		}
	}
	if(stop == 0) thongbao("HET GIO LAM BAI !!!",40,29,4,7);
	thongbao("*Nhan phim bat ky de xem diem*", 34,30,6,0);
	stop = 1;		
}
void hienThiCauHoi(CauHoi ch, int stt, char* cauTraLoi){
	textcolor(6);
	gotoxy(79,18);
	cout<<"CAU "<<stt;
	gotoxy(86,18);
	cout<<" chon ";
	textcolor(7);
	cout<<*(cauTraLoi+stt-1); // vi tri 86,15
	textcolor(10);
	gotoxy(3,18);
	cout<<"CAU "<<stt<<": " <<ch.cauHoi;
	textcolor(7);
	gotoxy(7, 20);
	cout<<"[ A ]  "<<ch.cauA;
	gotoxy(7, 22);
	cout<<"[ B ]  "<<ch.cauB;
	gotoxy(7, 24);
	cout<<"[ C ]  "<<ch.cauC;
	gotoxy(7,26);
	cout<<"[ D ]  "<<ch.cauD;
	
}
void NopBai(NodeSinhVien* &sv, NodeMonHoc* mh, int soCau, int* cauNgauNhien, char* cauTraLoi){
	textcolor(10);
	int soCauDung = 0;
	char kytu2;
	if(sv!= NULL){
		DiemThi diemThi;
		strcpy(diemThi.maMonHoc, mh->data.maMonHoc); 
		diemThi.soCau = soCau;
		diemThi.chiTietDe = new CT_DeThi[soCau];
		for(int i = 0 ;i<soCau; i++){
			mh->data.ds.ds[*(cauNgauNhien+i)].daThi = true;
			diemThi.chiTietDe[i].maCauHoi = mh->data.ds.ds[*(cauNgauNhien+i)].maCauHoi;
			diemThi.chiTietDe[i].svChon = *(cauTraLoi+i); 
		}
		diemThi.diem = tinhDiem(mh->data.ds, cauNgauNhien, cauTraLoi, soCau, soCauDung);
		themDiemThi(sv->data.dsDiem,diemThi);
		luuFileDiemThi(diemThi,sv->data.maSinhVien,"diemthi.txt");
		for(int j = 35; j<66; j++){
			SetBGColor(14);
			gotoxy(j,29);
			cout<<" ";
			gotoxy(j,30);
			cout<<" ";
			gotoxy(j,31);
			cout<<" ";
			gotoxy(j,32);
			cout<<" ";
		}
		gotoxy(37,30);
		cout<<"BAN DA LAM DUNG "<<soCauDung <<"/"<<soCau;
		gotoxy(42,31);
		cout<<"Diem: "<<diemThi.diem<<"/10";
	}
	else{
		float a = tinhDiem(mh->data.ds, cauNgauNhien, cauTraLoi, soCau, soCauDung);
		for(int j = 35; j<66; j++){
			SetBGColor(14);
			gotoxy(j,30);
			cout<<" ";
			gotoxy(j,31);
			cout<<" ";
			gotoxy(j,32);
			cout<<" ";
		}
		gotoxy(37,31);
		cout<<"BAN DA LAM DUNG "<<soCauDung <<"/"<<soCau;
	}
	SetBGColor(0);
	textcolor(6);
	thongbao("* Nhan phim bat ky de thoat *", 35,33,6,0);
	kytu2= _getch();
}
void thiTracNghiem (NodeSinhVien* &sv, NodeMonHoc* mh, int soCau, int* cauNgauNhien, char* cauTraLoi ){
	char kytu;
	int cauHienTai = 1; // stt cau hoi hien tai
	char chon = 'A';
quay:	hienThiCauHoi(mh->data.ds.ds[*(cauNgauNhien + cauHienTai-1)], cauHienTai, cauTraLoi);
	textcolor(10);
	gotoxy(83,10);
	cout<<demSoCauDaLam(cauTraLoi, soCau)<<" / "<<soCau;
	DrawButtonCH(chon,7,2*chon - 110, ButtonON );
	while(kytu!=27 && stop==0 ){
		kytu = _getch();
		switch (kytu){
			case 72:{ // len
				if(chon>65){
					DrawButtonCH(chon,7,2*chon - 110, ButtonOFF );
					chon--;
					DrawButtonCH(chon,7,2*chon - 110, ButtonON );
				}
			}
			break;
			case 80:{ // xuong
				if(chon<68){
					DrawButtonCH(chon,7,2*chon - 110, ButtonOFF );
					chon++;
					DrawButtonCH(chon,7,2*chon - 110, ButtonON );
				}
			}
			break;
			case 75:{ // trai
				if(cauHienTai>1){
					cauHienTai--;
					xoaCauHoiThi();
					chon = *(cauTraLoi+cauHienTai-1);
					if(chon == 'X') chon = 'A';
					goto quay;
				}
			}
			break;
			case 77:{ // phai
				if(cauHienTai<soCau){
					cauHienTai++;
					xoaCauHoiThi();
					chon = *(cauTraLoi+cauHienTai-1);
					if(chon == 'X') chon = 'A';
					goto quay;
				}
			}
			break;
			case 13:{ // enter
				*(cauTraLoi+cauHienTai-1)=chon;
				textcolor(10);
				gotoxy(92,18);
				cout<<chon;
				gotoxy(83,10);
				cout<<demSoCauDaLam(cauTraLoi, soCau)<<" / "<<soCau;
			}
			break;
			case 27:{ // esc
				khungConfirm("CHUA HET GIO !!! BAN CO MUON NOP BAI ???",7,4);
				while(1){
					kytu = _getch();
					if(kytu == 89 || kytu == 121){
						stop = 1;
						xoaKhungConfirm();
						break;
					}
					else if(kytu == 78 || kytu == 110){
						kytu='\0';
						xoaKhungConfirm();
						break;
					}
				}
			}
			break;
		}
	}
	
}
void thucThiThiTracNghiem(string maSinhVien,  DSLop &dsl, treemh dsmh){
	char maMonHoc[15];
	int soCau;
	int soPhut;
	string maLop;
	string tenLop;
	NodeMonHoc* mh;
	thread luongDongHo;
	NodeSinhVien* sv = NULL;
	if(maSinhVien != "GV")  sv = laySinhVien( maSinhVien, maLop, tenLop, dsl );
quay:	if(nhapThongTinThi(sv, maLop,tenLop, maMonHoc, soCau, soPhut, dsmh)==1){ // nhap thanh cong
		mh = layMonHoc(dsmh,maMonHoc);
		int* cauNgauNhien ;
		char* cauTraLoi = new char[soCau];
		for(int i =0; i<soCau; i++) *(cauTraLoi+i)='X'; // danh dau chua chon cau tra loi 
		layNgauNhien(cauNgauNhien,0 ,mh->data.ds.sl - 1,soCau);
		system("cls");
		textcolor(6);
		gotoxy(15, 10);
		cout<<"MON HOC:  "<<layTenMH(dsmh,maMonHoc);
		textcolor(14);
		if(maSinhVien == "GV"){
			gotoxy(30, 13);
			cout<<"Giang vien thi thu";
		}
		else{
			gotoxy(5, 12);
			cout<<"Ten sinh vien: "<< sv->data.ho<<" "<<sv->data.ten;
			gotoxy(48, 12);
			cout<<"MSV:  "<<sv->data.maSinhVien;
			gotoxy(5, 14);
			cout<<"Lop:  "<<maLop<<" - " <<tenLop;
		}
		giaoDienThiTracNghiem();
		stop = 0;
		luongDongHo = thread(dongHo,soPhut); // tao luong dong ho chay lui
		Sleep(100);
		thiTracNghiem(sv,mh,soCau, cauNgauNhien, cauTraLoi);
		luongDongHo.join();
		NopBai(sv, mh, soCau, cauNgauNhien, cauTraLoi);
		delete[] cauTraLoi;
		delete[] cauNgauNhien;
		goto quay;
	}
	luuDSMonHoc(dsmh,"monhoc.txt");
	
}

void thucThiMonHoc(treemh &dsmh){
	system("cls");
	int slmh=0;
	Lop lop;
	char kytu = '\0';
	int chon = 1; // lua chontren 1 trang
	int sttthem = 1; // stt them moi vao
	string timkiem="";
	MonHoc mh; // luu mon hoc muon thao tac
	int maxTrang; // so trang toi da de chua het mon hoc
	int trangHienTai = 1;  //trang hien tai dang in tren manhinh
	int f = 1; // danh dau co phai dang o trang tim kiem hay khong, co hieu cho nut esc, 1 là man hinh chinh, 2 là man hinh tim kiem, 0 la thoat
	ButtonMH tmp;
	DStheoTen ds;
	xoaDSSapxep(ds);
	copyDS(dsmh, ds, slmh);
	sapXepTheoTenMH(ds);
	giaoDienMonHoc();
quaylai:	maxTrang = slmh/15 +((slmh%15==0) ? 0:1); // neu chia het cho 15 thi khong cong 1
	loadDSMH(ds,dsmh,trangHienTai);
	gotoxy(48,31);
	cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
	tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
	DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
	while(kytu!=27 || f !=0){ // neu nhan esc khi o man hinh chinh (khong phai o man hinh tim kiem )
		kytu=_getch();
		switch(kytu){
			case 72:{ // nút lên
				if(trangHienTai>1&&chon ==1){
					chon = 15;
					trangHienTai--;
					loadDSMH(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);	
					}
				else if(chon>1){
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonOFF);
					chon --;
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					}
				}
				break;
			case 80:{ // nút xuong
				if(chon+15*(trangHienTai-1) == slmh){ // so chon hien tai == so luong mon hoc
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,slmh) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonOFF);
					chon = 1;
					trangHienTai = 1;
					loadDSMH(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
					}
				else if(chon<15){
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonOFF);
					chon ++;
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					}
				else if(chon == 15) { // nut chon o cuoi trang
					chon = 1;
					trangHienTai++;
					loadDSMH(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);	
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
					}
				}
				break;	
			case 75:{ // qua trái
				if(trangHienTai>1){
					chon = 1;
					trangHienTai -- ;
					loadDSMH(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
					}
				}
				break;	
			case 77:{ // qua phai
				if(trangHienTai<maxTrang){
					chon = 1;
					trangHienTai++ ;
					loadDSMH(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
					}
				}
				break;	
			case 82:{ // Insert
				Nocursortype(TRUE);
				xoaBangHoTro();
				hoTroThem();
				loadDSMH(ds,dsmh,maxTrang);  // neu sl kh chia het 15 thì them vào ô cuoi cùng
				gotoxy(48,31);
				cout<<"Trang "<<maxTrang<<"/"<<maxTrang;
				chon = slmh+1-(maxTrang-1)*15;
				xoahang(chon +13); // xóa dòng gach ngang cuoi
				gotoxy(15, 13+chon);
				cout<<slmh+1; //  in san so thu tu
				gotoxy(85, 13+chon);
				cout<<0; //  in san so cau hoi
				bangMonHoc(chon+1); // ke them 1 hàng moi
				
				if(nhapThongTinMonHoc(19, 13+chon,mh,dsmh)==0){ //khi ng dung nhan ESC dung viec them
					xoahang(chon+14);
					bangMonHoc(chon);
					chon = slmh%15;
					if(chon == 0) chon =15;
					trangHienTai = maxTrang;
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
				}
				else{
					if(themMonHoc(dsmh, mh)==1){
						thongbao("THEM MON HOC THANH CONG !!!", 40,32,4,7);
						Sleep(2000);
						xoahang(32);
						gotoxy(33,8);
						for(int m =0;m<timkiem.size();m++ ) cout<<" ";
						timkiem="";
						f=1;
						khungConfirm("Ban co muon them cau hoi khong ???",7,4);
						kytu = '\0';
						while(1){
							kytu = _getch();
							if(kytu == 89 || kytu == 121){
								// giao dien them cau hoi
								thucThiThemCauHoi(layMonHoc(dsmh,layMaDuaVaoSTT(ds, chon+15*(trangHienTai-1))));
								system("cls");
								giaoDienMonHoc();
								break;
							}
							else if(kytu == 78 || kytu == 110){
								xoaKhungConfirm();
								break;
							}
						}
						xoaDSSapxep(ds);
						slmh = 0;
						copyDS(dsmh,ds, slmh);
						sapXepTheoTenMH(ds);
						sttthem = laySTTMonHocNew(ds ,mh.maMonHoc);
						trangHienTai =sttthem/16+1;
						chon = sttthem%15;
						if(chon==0) chon = 15;
						//luuDSMonHoc(dsmh,"monhoc.txt");
						xoaBangHoTro();
						hoTroMonHoc("mh");
						Nocursortype(FALSE);
						goto quaylai;
					}
				}
				xoaBangHoTro();
				hoTroMonHoc("mh");
				Nocursortype(FALSE);
				}
				break;
			case 83:{ // Delete
				if(slmh == 0) break;
				if(kt_TonTaiCauHoi(dsmh,layMaDuaVaoSTT(ds, chon+15*(trangHienTai-1)))==true){
					thongbao("MON HOC DANG TON TAI CAU HOI KHONG THE XOA !!!", 30,32, 4,7);
					Sleep(2000);
					xoahang(32);
					break;
				}
				khungConfirm("Ban co chac chan xoa hay khong ?",7,4);
				kytu='\0';
				while(1){
					kytu = _getch();
					if(kytu == 89 || kytu == 121){
						xoaMonHoc(dsmh,layMaDuaVaoSTT(ds, chon+15*(trangHienTai-1)),slmh);
						
						xoaDSSapxep(ds);
						slmh = 0;
						copyDS(dsmh,ds, slmh);
						sapXepTheoTenMH(ds);
						chon--;
						if(chon==0){
							chon = 1;
							if(chon+15*(trangHienTai-1)>slmh){
								chon=15;
								trangHienTai--;
							}
						}	
						xoaKhungConfirm();
						//luuDSMonHoc(dsmh,"monhoc.txt");
						thongbao("XOA MON HOC THANH CONG !!!",  40,32,4,7);
						Sleep(2000);
						xoahang(32);
						gotoxy(33,8);
						for(int m =0;m<timkiem.size();m++ ) cout<<" ";
						timkiem="";
						f=1;
						goto quaylai;
					}
					else if(kytu == 78 || kytu == 110 ){
						xoaKhungConfirm();
						break;
					}
				}
			}
				break;
			case 62:{ // F4: Sua mon hoc
				if(slmh == 0) break;
				xoaBangHoTro();
				hoTroSuaMonHoc();
				mh = layMonHoc(dsmh ,layMaDuaVaoSTT(ds, chon+15*(trangHienTai-1)))->data;
				xoahang(chon+13);
				inThongTin(mh, chon+13, chon);
				thongbao("CHI CHO PHEP CHINH SUA TEN MON HOC", 40,34,10,7);
				if(nhapTenMonHoc(mh.tenMonHoc,37,13+chon)==true){
					CapNhatTenMH(dsmh, mh.maMonHoc, mh.tenMonHoc);
					thongbao("CHINH SUA MON HOC THANH CONG !!!", 40,32,4,7);
					Sleep(2000);
					xoahang(32);
					gotoxy(33,8);
					for(int m =0;m<timkiem.size();m++ ) cout<<" ";
					timkiem="";
					f=1;
					xoaDSSapxep(ds);
					slmh =0;
					copyDS(dsmh,ds, slmh);
					sapXepTheoTenMH(ds);
					sttthem = laySTTMonHocNew(ds ,mh.maMonHoc);
					trangHienTai = sttthem/15 +((sttthem%15==0) ? 0:1);
					chon = sttthem%15;
					if(chon==0) chon = 15;
					xoaBangHoTro();
					hoTroMonHoc("mh");
					goto quaylai;
				}
				tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
				DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);
				xoaBangHoTro();
				hoTroMonHoc("mh");
			}
				break;
			case 6:{ // CTRL + F: Tim kiem
				thongbao("*** TIM KIEM THEO TEN MON HOC" , 35,34, 10,7);
				if(nhapTenMonHoc(timkiem,33,8)==true){
					xoaDSSapxep(ds);
					slmh=0;
					taoDSTmKiem(dsmh,ds,timkiem,slmh);
					f = 2; // chuyen sang man hinh tim kiem
					if(slmh==0){
						thongbao("KHONG TON TAI MON HOC !!!",40,32,4,7);
						Sleep(2000);
						xoahang(32);
						gotoxy(33,8);
						for(int m =0;m<timkiem.size();m++ ) cout<<" ";
						timkiem="";
						xoaDSSapxep(ds);
						slmh = 0;
						copyDS(dsmh,ds, slmh);
						f=1;
					}
					sapXepTheoTenMH(ds);
					trangHienTai = 1;
					chon = 1;
					goto quaylai;
				}
				else { // khi dang nhap ma nhan esc
					f=1;
					gotoxy(33,8);   // xoa chu tren o tim kiem
					for(int m =0;m<timkiem.size();m++ ) cout<<" ";
					timkiem="";
					xoahang(34);
					xoaDSSapxep(ds); // xoa loi bam ctrl f tim kiem 2 lan
					slmh = 0;
					copyDS(dsmh,ds,slmh);
					sapXepTheoTenMH(ds);
					loadDSMH(ds,dsmh,trangHienTai);
					tmp = CreateButtonMH(1,77,layMonHoc(dsmh,layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)) )->data);
					DrawButtonMH(tmp,14,13+chon,chon+15*(trangHienTai-1),ButtonON);	
				}
							
			}
				break;
			case 13:{ // Enter: Xem cau hoi
				if(slmh == 0) break;
				NodeMonHoc* monHoc = layMonHoc(dsmh, layMaDuaVaoSTT(ds,chon+15*(trangHienTai-1)));
				thucThiCauHoi( monHoc);
				system("cls");
				giaoDienMonHoc();
				goto quaylai;
			}
				break;
			case 27: 
				if(f==2) {
					gotoxy(33,8);
					for(int m =0;m<timkiem.size();m++ ) cout<<" ";
					timkiem="";
					xoaDSSapxep(ds);
					slmh = 0;
					copyDS(dsmh,ds,slmh);
					sapXepTheoTenMH(ds);
					chon = 1;
					trangHienTai = 1;
					xoahang(29);
					f=1;
					goto quaylai;
				}
				else if(f==1){
					f=0;
					luuDSMonHoc(dsmh,"monhoc.txt");
				}
				break;
		}
	}
	xoaDSSapxep(ds);
}

void copyDSDiemThi(DSDiemThi dsdt, DStheoTen &ds, treemh dsmh){
	xoaDSSapxep(ds);
	for(NodeDiemThi* k = dsdt.phead; k != NULL; k=k->next){
		Node* node = createNode(k->data.maMonHoc, layTenMH(dsmh,k->data.maMonHoc));
		if (ds.phead == NULL){
			ds.phead = node;
		}
		else{
			node->next = ds.phead;
			ds.phead = node;
		}
	}
}
int laySoLuongDiemThi(DSDiemThi ds){
	int n = 0;
	for(NodeDiemThi* k = ds.phead; k!=NULL; k = k->next ) n++;
	return n;
}
NodeSinhVien* nhapSinhVien (DSLop dsl, string &maLop, string &tenLop){
	Nocursortype(TRUE);
	system("cls");
	docFile(28, "logoctdethi.txt");
	textcolor(6);
	gotoxy(22,16);
	cout<<"*** Nhap ma so sinh vien:";
	khungNhap("", 50, 15, 40, 1,6,0);
	thongbao("*** MA TOI DA 15 KY TU, BAO GOM KY TU CHU, SO", 43,18,10,7);
	thongbao("Enter - Xem mon hoc da thi         Esc - Tro lai", 35,30,10,0);
	gotoxy(52,16);	
	string ma;
	char k;
	NodeSinhVien* sv;
	int i =0;
	while(1){
		k = _getch();
		if( k==13 ){
			if(ma==""){
				thongbao("MA SINH VIEN KHONG DUOC RONG !!!", 40,27,4,7);
				Sleep(2000);
				xoahang(27); 
				gotoxy(52,16);
				continue;
			}
			else {
				sv = laySinhVien(ma, maLop, tenLop, dsl);
				if(sv==NULL){
					thongbao("MA SINH VIEN KHONG TON TAI !!!", 40,27,4,7);
					Sleep(2000);
					xoahang(27); 
					gotoxy(52,16);
					cout<<ma;
					continue;
				}
				else {
					Nocursortype(FALSE);
					return sv;
				}
			}
		}
		else if(k==27) {
			Nocursortype(FALSE);
			return NULL;
		}
		else if(k==8&&ma.length()>0){
			ma.erase(ma.length()-1, 1);
			gotoxy(52+ma.length(),16);
			cout<<" ";
			gotoxy(52+ma.length(),16);
		}
		else if(k>=97 && k<=122){
			k = k-32;
			ma.push_back(k);
			cout<<k;
		}
		else if((k>=65 && k <=90) || (k>=48 && k <=57)){
			ma.push_back(k);
			cout<<k;
		}
	}
}
void hienThiCauHoiLS(NodeMonHoc* mh, int maCauHoi , int stt){
	int left; // Binary Search
	int right;
	int j;
	left = 0;
	right = mh->data.ds.sl-1;
	while(left<=right){
		j = (left + right)/2;
		if( mh->data.ds.ds[j].maCauHoi == maCauHoi){
			textcolor(6);
			gotoxy(16,10+stt*7);
			cout<<"CAU "<<stt+1<<": "<<mh->data.ds.ds[j].cauHoi;
			textcolor(7);
			gotoxy(13,11+stt*7);
			cout<<"A. "<<mh->data.ds.ds[j].cauA;
			gotoxy(13,12+stt*7);
			cout<<"B. "<<mh->data.ds.ds[j].cauB;
			gotoxy(13,13+stt*7);
			cout<<"C. "<<mh->data.ds.ds[j].cauC;
			gotoxy(13,14+stt*7);
			cout<<"D. "<<mh->data.ds.ds[j].cauD;
			gotoxy(17,15+stt*7);
			cout<<"Dap an: ";
			textcolor(6);
			cout<<mh->data.ds.ds[j].dapAn;
			break;
		}
		if(maCauHoi > mh->data.ds.ds[j].maCauHoi) left = j+1;
		else right = j-1;	
	}
}
void lichSuThi(NodeSinhVien* sv,string maLop, string tenLop ,treemh dsmh){
	if(sv->data.dsDiem.phead == NULL){
		thongbao("SINH VIEN CHUA THAM GIA THI BAT KY MON HOC NAO !!!", 35, 32, 4,15);
		Sleep(2000);
		xoahang(32);
		return;
	}
	DiemThi dt;
	char x;
	DStheoTen ds;
	char* matam;
	int slmh = laySoLuongDiemThi(sv->data.dsDiem);
	xoaDSSapxep(ds);
	copyDSDiemThi(sv->data.dsDiem, ds, dsmh);
quay2:	matam = XemMonHoc(ds,slmh,dsmh);
	if(matam!=NULL){
			for(NodeDiemThi* k = sv->data.dsDiem.phead; k!=NULL;k=k->next)
				if(strcmp(k->data.maMonHoc,matam)==0) {
					dt= k->data;
				}
			giaoDienLichSuThi();
			textcolor(6);
			gotoxy(26, 2);
			cout<<sv->data.ho<<" "<<sv->data.ten;
			gotoxy(26, 3);
			cout<<sv->data.maSinhVien;
			gotoxy(26, 4);
			cout<<maLop<<" - "<<tenLop;
			gotoxy(58, 7);
			cout<<layTenMH(dsmh,dt.maMonHoc);
			textcolor(4);
			gotoxy(116,3);
			cout<<dt.diem;
			NodeMonHoc* monHoc = layMonHoc(dsmh, dt.maMonHoc);
			for(int i = 0; i< dt.soCau; i++){
				hienThiCauHoiLS(monHoc, dt.chiTietDe[i].maCauHoi,i);
				textcolor(10);
				if(dt.chiTietDe[i].svChon=='A'){
					gotoxy(13,11+7*i);
					cout<<"A. ";
				}
				else if(dt.chiTietDe[i].svChon=='B'){
					gotoxy(13,12+7*i);
					cout<<"B. ";
				}
				else if(dt.chiTietDe[i].svChon=='C'){
					gotoxy(13,13+7*i);
					cout<<"C. ";
				}
				else if(dt.chiTietDe[i].svChon=='D'){
					gotoxy(13,14+7*i);
					cout<<"D. ";
				}
			}
			khungDuoiLSThi(dt.soCau);
			x='\0';
			gotoxy(1,1);
			while((x=getch())!=27){}
			goto quay2;
		}
}
void thucThiXemLichSuThi(DSLop dsl, treemh dsmh){
	string maLop;
	string tenLop;
	NodeSinhVien* sv;
quay:	sv = nhapSinhVien(dsl,maLop, tenLop);
	if(sv!=NULL){
		lichSuThi(sv,maLop, tenLop, dsmh);
		goto quay;
	}
}
	
bool nhapThongTinXemDSDiem(char* maMonHoc, string &maLop, treemh dsmh, DSLop dsl){
	Nocursortype(TRUE);
	char k;
	bool t = true; // true: con tro dang o o ma mon hoc
	strcpy(maMonHoc,"");
	maLop = "";
	int i =0;
quay:	system("cls");
	textcolor(10);
	docFile(20,"logobangdiem.txt");
	textcolor(6);
	gotoxy(24,12);
	cout<<"*** Nhap ma mon hoc:";
	khungNhap("", 45, 11, 40, 1,6,0);
	gotoxy(24,15);
	cout<<"*** Nhap ma lop:";
	khungNhap("", 45, 14, 40, 1,6,0);
	hoTroNhapThi();
	gotoxy(111,19);
	cout<<"Xem diem";
	gotoxy(47,5);
	cout<<maLop;
	//thongbao("*** MA TOI DA 15 KY TU, BAO GOM KY TU CHU, SO", 35,14,10,7);
	thongbao("*** F5 - XEM DANH SACH MON HOC", 48,18,10,7);
	gotoxy(47,12);
	cout<<maMonHoc;
	while(1){
		k = _getch();
		if(k==13){
			if(strcmp(maMonHoc,"")==0 ){
				thongbao("MA MON HOC KHONG DUOC RONG!!!", 48,28,4,7);
				Sleep(2000);
				xoahang(28); 
				thongbao("*** F5 - XEM DANH SACH MON HOC", 48,18,10,7);
				gotoxy(47,12);
				t=true;
			}
			else if(kt_TrungMaMH(dsmh, maMonHoc)==false){
				thongbao("MA MON HOC KHONG TON TAI !!!", 48,28,4,7);
				Sleep(2000);
				xoahang(28); 
				thongbao("*** F5 - XEM DANH SACH MON HOC", 48,18,10,7);
				gotoxy(47,12);
				cout<<maMonHoc;
				t = true;
			}
			else if(maLop==""){
				thongbao("MA LOP KHONG DUOC RONG!!!", 48,28,4,7);
				Sleep(2000);
				xoahang(28);
				xoahang(18); 
				gotoxy(47,15);
				t=false;
			}
			else if(kt_TrungMaLop(dsl,maLop)==false){
				thongbao("MA LOP KHONG TON TAI !!!", 48,28,4,7);
				Sleep(2000);
				xoahang(28); 
				gotoxy(47+maLop.length(),15);
				t = false;
			}
			else if(layLop(dsl,maLop)->dsSinhVien.phead == NULL){
				thongbao("LOP KHONG TON TAI SINH VIEN !!!", 48,28,4,7);
				Sleep(2000);
				xoahang(28); 
				gotoxy(47+maLop.length(),15);
				t = false;
			}
			else {
				Nocursortype(FALSE);
				system("cls");
				return true;
			}
		}
		else if(k==27) {
			Nocursortype(FALSE);
			system("cls");
			return false;
		}
		else if(k==72){ //len
			if(t == false){
				t=true;
				thongbao("*** F5 - XEM DANH SACH MON HOC", 48,18,10,7);
				gotoxy(47+i,12);
			}
		}
		else if(k==80){ //xuong
			if(t = true){
				xoahang(18);
				t=false;
				gotoxy(47+maLop.length(),15);
			}
		}
		else if(k==8){
			if(t==true && i>0){
				maMonHoc[i-1] = '\0';
				for(int k = 47; k<=47+i;k++){
					gotoxy(k, 12);
					cout<<" ";
				}
				i--;
				gotoxy(47, 12);
				cout<<maMonHoc;
			}
			else if(t==false && maLop.length()>0){
				maLop.erase( maLop.length()-1,1);
				gotoxy(47+maLop.length(), 15);
				cout<<" ";
				gotoxy(47+maLop.length(), 15);
			}
		}
		else if(k == 63){
			if(t == true){
				char* matam;
				DStheoTen ds;
				int slmh = 0;
				xoaDSSapxep(ds);
				copyDS(dsmh,ds,slmh);
				matam = XemMonHoc(ds,slmh, dsmh);
				if(matam != NULL) {
					strcpy(maMonHoc, matam);
					i = strlen(maMonHoc);
				}
				delete matam;
				goto quay;
			}
		}
		else if(k>=97 && k<=122){
			if(i < 15 && t == true){
				k=k-32;
				maMonHoc[i]= k;
				i++;
				cout<<k;
			}
			else if(t== false){
				k=k-32;
				maLop.push_back(k);
				cout<<k;
			}
		}
		else if((k>=65 && k <=90) || (k>=48 && k <=57)){
			if(i < 15 && t == true){
				maMonHoc[i]= k;
				i++;
				cout<<k;
			}
			else if( t== false){
				maLop.push_back(k);
				cout<<k;
			}
		}	
	}
}



void copyDSSinhVien(DSSinhVien dssv, DSSapXep &ds){
	xoaDSSapxep2(ds);
	for(NodeSinhVien* k = dssv.phead; k!=NULL; k=k->next){
		NodeSapXep* nodeSX = new NodeSapXep();
		nodeSX->maSinhVien= k->data.maSinhVien;
		nodeSX->tenSinhVien= k->data.ten;
		nodeSX->next = NULL;
		if (ds.phead == NULL){
			ds.phead = nodeSX;
		}
		else{
			nodeSX->next = ds.phead;
			ds.phead = nodeSX;
		}
	}
	// Sap xep
	sapXepDSSapXep(ds);
}
void copyDSLop(DSLop dsl, DSSapXep &ds){
	xoaDSSapxep2(ds);
	for(int i=0;i<dsl.sl;i++){
		NodeSapXep* nodeSX = new NodeSapXep();
		nodeSX->maSinhVien= dsl.dsLop[i]->maLop;
		nodeSX->tenSinhVien= dsl.dsLop[i]->tenLop;
		nodeSX->next = NULL;
		if (ds.phead == NULL){
			ds.phead = nodeSX;
		}
		else{
			nodeSX->next = ds.phead;
			ds.phead = nodeSX;
		}
	}
	sapXepDSSapXep(ds);
}

bool layDiem(DSDiemThi dsdt, char* maMonHoc, float &diem){
	for(NodeDiemThi* k = dsdt.phead; k!=NULL; k = k->next){
		if(strcmp(k->data.maMonHoc, maMonHoc) == 0) {
			diem = k->data.diem;
			return true;
		}
	}
	return false;
}
void thucThiXemDSDiem(DSLop dsl, treemh dsmh){
	char maMonHoc[15];
	string maLop;
	Lop* lop;
	char c;
	DSSapXep ds;
	int i;
quay: if(nhapThongTinXemDSDiem(maMonHoc,maLop,dsmh,dsl)==true){// nhâp thanh cong vao, neu esc thi thoat luon
		i=1;
		lop = layLop(dsl, maLop);
		float diem;
		copyDSSinhVien(lop->dsSinhVien,ds);
		textcolor(15);
		gotoxy(50,8);
		cout<<lop->maLop<<" - "<<lop->tenLop;
		gotoxy(50,9);
		cout<<maMonHoc<<" - "<<layTenMH(dsmh,maMonHoc);
		for(NodeSapXep* k = ds.phead; k!=NULL; k=k->next){
			for(NodeSinhVien* l = lop->dsSinhVien.phead; l!=NULL; l= l->next ){
				if(k->maSinhVien==l->data.maSinhVien){
					textcolor(15);
					gotoxy(18, 13+i);
					cout<<i;
					gotoxy(25,13+i);
					cout<<l->data.maSinhVien;
					gotoxy(45,13+i);
					cout<<l->data.ho<<" "<<l->data.ten;
					if(layDiem(l->data.dsDiem,maMonHoc, diem)==true){
						gotoxy(95,13+i);
						cout<<diem;
					}
					else{
						textcolor(4);
						gotoxy(92,13+i);
						cout<<"Chua thi";
					}
					i++;
					break;
				}
			
			}
		}
		giaoDienBangDiem(i);
		c='\0';
		while(c!=27) c = _getch();
		goto quay;
	}
}
void xoaSinhVien(DSSinhVien &ds, string ma){
	NodeSinhVien* sv;
	if(ds.phead->data.maSinhVien == ma){
		sv = ds.phead;
		ds.phead = ds.phead->next;
	}
	else{
		for(NodeSinhVien* k = ds.phead; k->next!=NULL; k= k->next){
			if(k->next->data.maSinhVien == ma){
				sv = k->next;
				k->next = k->next->next;
				break;
			}
		}
	}
	delete sv;
}
void xoaLop(DSLop &dsl, string ma){
	int vt;
	for( vt= 0; vt<dsl.sl;vt++){
		if(dsl.dsLop[vt]->maLop==ma) break;
	}
	Lop* tam = dsl.dsLop[vt];
	for(int i = vt; i<dsl.sl-1;i++) dsl.dsLop[i] = dsl.dsLop[i+1];
	dsl.sl--;
	delete tam;
}
int laySTT(DSSapXep ds, string malop){
	int i = 1;
	for(NodeSapXep* k = ds.phead; k!=NULL; k = k->next){
		if(k->maSinhVien==malop) return i;
		i++;
	}
}
void capNhatTenLop(DSLop &dsl, string ma, string ten){
	for(int i = 0 ; i< dsl.sl; i++){
		if(dsl.dsLop[i]->maLop == ma){
			dsl.dsLop[i]->tenLop = ten;
			break;
		}
	}
}
void tachHoTen(string s, string &ho, string &ten){
	ho.clear();
	ten.clear();
	for(int i = s.length() - 1; i>0; i--){
		if(s[i] == ' ') {
			ten = s.substr(i+1);
			ho = s.substr(0,i);
			return;
		}
	}
}
void thucThiThemSinhVien(DSSinhVien &dssv, Lop* lop, DSLop dsl){
	system("cls");
	char k;
	giaoDienSinhVien();
	xoaBangHoTro();
	hoTroThem();
	textcolor(6);
	gotoxy(39,6);
	cout<<lop->maLop<<" - "<<lop->tenLop;
	DSSapXep ds;
	copyDSSinhVien(dssv,ds);
	int slsv = laySoLuongSinhVien(dssv);
	int chon;
	int trang = slsv/15 +1;
	loadDSSinhVien(ds,trang,dssv);
	int t=1; // vi tri con tro: 1: masv, 2: ho ten sv, 3: phai, 4: mat khau
	Nocursortype(TRUE);
	SinhVien sv;
	string hoten;
quaylai:	hoten.clear();
	sv.maSinhVien.clear();
	sv.ho.clear();
	sv.ten.clear();
	sv.phai.clear();
	sv.matKhau.clear();
	chon = slsv+1-(trang-1)*15;
	if(chon!=0) xoahang(chon +13); // xóa dòng gach ngang cuoi
	gotoxy(16,13+chon);
	if(slsv>8) gotoxy(15,13+chon);
	cout<<slsv+1; // in san stt
	bangSinhVien(chon+1);
	t=1;
	thongbao("* MA SINH VIEN TOI DA 15 KY TU *", 38, 34, 10,7);
	gotoxy(20,13+chon);
	while(k!=27){
		k = _getch();
		if(k==13){
			ChuanHoaTen(hoten, "");
			ChuanHoaTen(sv.phai,"");
			tachHoTen(hoten, sv.ho, sv.ten);
			if(sv.maSinhVien == ""){
				thongbao("MA SINH VIEN KHONG DUOC RONG!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				thongbao("* MA SINH VIEN TOI DA 15 KY TU *", 38, 34, 10,7);
				gotoxy(20,13+chon);
				t=1;
			}
			else if(kt_TrungSV(sv.maSinhVien, dsl)==true){
				thongbao("MA SINH VIEN DA TON TAI!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				thongbao("* MA SINH VIEN TOI DA 15 KY TU *", 38, 34, 10,7);
				gotoxy(20+sv.maSinhVien.length(),13+chon);
				t=1;
			}
			else if(hoten == ""){
				thongbao("TEN SINH VIEN KHONG DUOC RONG!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				gotoxy(38,13+chon);
				t=2;
			}
			else if(sv.ten ==""){
				thongbao("HO TEN KHONG HOP LE !!! (Bao gom: Ho + Ten)", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				gotoxy(38 + hoten.length(),13+chon);
				t=2;
			}
			else if(sv.phai == ""){
				thongbao("PHAI KHONG DUOC RONG!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				thongbao("* PHAI CHI NHAN \"NAM\" HOAC \"NU\" *",38, 34,10,7);
				gotoxy(72,13+chon);
				t=3;
			}
			else if(sv.phai != "Nam" && sv.phai != "Nu"){
				thongbao("PHAI KHONG KHONG HOP LE!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				thongbao("* PHAI CHI NHAN \"NAM\" HOAC \"NU\" *",38, 34,10,7);
				gotoxy(72+sv.phai.length(),13+chon);
				t=3;
			}
			else if(sv.matKhau == ""){
				thongbao("MAT KHAU KHONG DUOC RONG!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				thongbao("* MAT KHAU TOI THIEU 6 KY TU, TOI DA 10 KY TU *", 38,34,10,7);
				gotoxy(79,13+chon);
				t=4;
			}
			else if(sv.matKhau.length()<6){
				thongbao("MAT KHAU KHONG HOP LE!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				thongbao("* MAT KHAU TOI THIEU 6 KY TU, TOI DA 10 KY TU *", 38,34,10,7);
				gotoxy(79+sv.matKhau.length(),13+chon);
				t=4;
			}
			else{
				themSinhVien(dssv, sv);
				slsv++;
				DrawButtonSinhVien(laySinhVien2(dssv, sv.maSinhVien),14, 13+chon, slsv, ButtonOFF);
				if(chon == 15){
					trang++;
					xoaBangMH();
					loadDSSinhVien(ds, trang, dssv);
				}
				xoahang(34);
				goto quaylai;
			}
		}
		else if(k == 27){
			khungConfirm("Ban co chac chan muon dung nhap them sinh vien ???", 7,4);
			while(1){
			 	k = _getch();
				if(k == 89 || k == 121){
					k = 27;	
					Nocursortype(FALSE);	
					break;
				}
				else if(k == 78 || k == 110){
					xoaKhungConfirm();
					if(t = 1){
						xoahang(34);
						thongbao("* MA SINH VIEN TOI DA 15 KY TU *", 38, 34, 10,7);
						gotoxy(20 + sv.maSinhVien.length(),13+chon);
					}
					else if(t==2){
						xoahang(34);
						gotoxy(38 + hoten.length(),13+chon);
					}
					else if(t==3){
						xoahang(34);
						thongbao("* PHAI CHI NHAN \"NAM\" HOAC \"NU\" *",38, 34,10,7);
						gotoxy(72+sv.phai.length(),13+chon);
					}
					else{
						xoahang(34);
						thongbao("* MAT KHAU TOI THIEU 6 KY TU, TOI DA 10 KY TU *", 38,34,10,7);
						gotoxy(79+sv.matKhau.length(),13+chon);
					}
					break;
				}	
			}
		}
		else if(k==75){ // trai
			if(t > 1){ // tro nam o o hoten tro qua phai moi thuc hien
				t--;
				if(t == 1){
					xoahang(34);
					thongbao("* MA SINH VIEN TOI DA 15 KY TU *", 38, 34, 10,7);
					gotoxy(20 + sv.maSinhVien.length(),13+chon);
				}
				else if(t==2){
					xoahang(34);
					gotoxy(38 + hoten.length(),13+chon);
				}
				else if(t==3){
					xoahang(34);
					thongbao("* PHAI CHI NHAN \"NAM\" HOAC \"NU\" *",38, 34,10,7);
					gotoxy(72+sv.phai.length(),13+chon);
				}
			}
		}
		else if(k==77){ // phai
			if(t<4) { // tro nam o o Phai tro qua trai moi thuc hien
				t++;
				if(t==2){
					xoahang(34);
					gotoxy(38 + hoten.length(),13+chon);
				}
				else if(t==3){
					xoahang(34);
					thongbao("* PHAI CHI NHAN \"NAM\" HOAC \"NU\" *",38, 34,10,7);
					gotoxy(72+sv.phai.length(),13+chon);
				}
				else if(t==4){
					xoahang(34);
					thongbao("* MAT KHAU TOI THIEU 6 KY TU, TOI DA 10 KY TU *", 38,34,10,7);
					gotoxy(79+sv.matKhau.length(),13+chon);
				}
			}
		}
		else if(k == 8){
			if(t == 1 && sv.maSinhVien.length()>0){
				sv.maSinhVien.pop_back();
				gotoxy(20 + sv.maSinhVien.length(), 13+chon);
				cout<<" ";
				gotoxy(20 + sv.maSinhVien.length(), 13+chon);
			}
			else if(t == 2 && hoten.length()>0){
				hoten.pop_back();
				gotoxy(38 + hoten.length(), 13+chon);
				cout<<" ";
				gotoxy(38 + hoten.length(), 13+chon);
			}
			else if(t == 3 && sv.phai.length()>0){
				sv.phai.pop_back();
				gotoxy(72 + sv.phai.length(), 13+chon);
				cout<<" ";
				gotoxy(72 + sv.phai.length(), 13+chon);
			}
			else if(t == 4 && sv.matKhau.length()>0){
				sv.matKhau.pop_back();
				gotoxy(79 + sv.matKhau.length(), 13+chon);
				cout<<" ";
				gotoxy(79 + sv.matKhau.length(), 13+chon);
			}
		}
		else if(t==2 && ((k>=65 && k <=90) || (k>=97 && k <=122) || k == 32) && hoten.length()<32){
			hoten.push_back(k);
			cout<<k;
		}
		else if(t==3 && ((k>=65 && k <=90) || (k>=97 && k <=122)) && sv.phai.length()<3){
			sv.phai.push_back(k);
			cout<<k;
		}
		else if((k>=32 && k<=122) && t == 4 && sv.matKhau.length()<10){
			sv.matKhau.push_back(k);
			cout<<k;
		}
		else if(k>=97 && k<=122 && t == 1 && sv.maSinhVien.length()<15){
			k=k-32;
			sv.maSinhVien.push_back(k);
			cout<<k;
		}
		else if(t==1 && sv.maSinhVien.length()<15 && ((k>=65 && k <=90) || (k>=48 && k <=57))){
			sv.maSinhVien.push_back(k);
			cout<<k;
		}	
	}
	xoaDSSapxep2(ds);
}
bool nhapThongTinSinhVien(SinhVien &sv, int x, int y){
	xoaBangHoTro();
	hoTroThem();
	int t=1; // vi tri con tro: 1: ho ten sv, 2: phai, 3: mat khau
	string hoten = sv.ho+" "+sv.ten;
	for(int i =38; i<=69; i++){ // xóa cot ho ten dang co khoang cach giua ho va ten
		gotoxy(i,y);
		cout<<" ";
	}
	gotoxy(38,y);
	cout<<hoten;
	Nocursortype(TRUE);
	char k;
	gotoxy(38+hoten.length(), y);
	while(k!=27){
		k = _getch();
		if(k==13){
			ChuanHoaTen(hoten, "");
			ChuanHoaTen(sv.phai,"");
			tachHoTen(hoten, sv.ho, sv.ten);
			if(hoten == ""){
				thongbao("TEN SINH VIEN KHONG DUOC RONG!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				gotoxy(38,y);
				t=1;
			}
			else if(sv.ten ==""){
				thongbao("HO TEN KHONG HOP LE !!! (Bao gom: Ho + Ten)", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				gotoxy(38 + hoten.length(),y);
				t=1;
			}
			else if(sv.phai == ""){
				thongbao("PHAI KHONG DUOC RONG!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				thongbao("* PHAI CHI NHAN \"NAM\" HOAC \"NU\" *",38, 34,10,7);
				gotoxy(72,y);
				t=2;
			}
			else if(sv.phai != "Nam" && sv.phai != "Nu"){
				thongbao("PHAI KHONG KHONG HOP LE!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				thongbao("* PHAI CHI NHAN \"NAM\" HOAC \"NU\" *",38, 34,10,7);
				gotoxy(72+sv.phai.length(),y);
				t=2;
			}
			else if(sv.matKhau == ""){
				thongbao("MAT KHAU KHONG DUOC RONG!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				thongbao("* MAT KHAU TOI THIEU 6 KY TU, TOI DA 10 KY TU *", 38,34,10,7);
				gotoxy(79,y);
				t=3;
			}
			else if(sv.matKhau.length()<6){
				thongbao("MAT KHAU KHONG HOP LE!!!", 40,31,4,7);
				Sleep(2000);
				xoahang(31); 
				xoahang(34);
				thongbao("* MAT KHAU TOI THIEU 6 KY TU, TOI DA 10 KY TU *", 38,34,10,7);
				gotoxy(79+sv.matKhau.length(),y);
				t=3;
			}
			else{
				Nocursortype(FALSE);
				xoahang(34);
				return true;
			}
		}
		else if(k == 27){
			Nocursortype(FALSE);
			return false;
		}
		else if(k==75){ // trai
			if(t > 1){ // tro nam o o hoten tro qua phai moi thuc hien
				t--;
				if(t==1){
					xoahang(34);
					gotoxy(38 + hoten.length(),y);
				}
				else if(t==2){
					xoahang(34);
					thongbao("* PHAI CHI NHAN \"NAM\" HOAC \"NU\" *",38, 34,10,7);
					gotoxy(72+sv.phai.length(),y);
				}
			}
		}
		else if(k==77){ // phai
			if(t<3) { // tro nam o o Phai tro qua trai moi thuc hien
				t++;
				if(t==2){
					xoahang(34);
					thongbao("* PHAI CHI NHAN \"NAM\" HOAC \"NU\" *",38, 34,10,7);
					gotoxy(72+sv.phai.length(),y);
				}
				else if(t==3){
					xoahang(34);
					thongbao("* MAT KHAU TOI THIEU 6 KY TU, TOI DA 10 KY TU *", 38,34,10,7);
					gotoxy(79+sv.matKhau.length(),y);
				}
			}
		}
		else if(k == 8){
			if(t == 1 && hoten.length()>0){
				hoten.pop_back();
				gotoxy(38 + hoten.length(), y);
				cout<<" ";
				gotoxy(38 + hoten.length(), y);
			}
			else if(t == 2 && sv.phai.length()>0){
				sv.phai.pop_back();
				gotoxy(72 + sv.phai.length(), y);
				cout<<" ";
				gotoxy(72 + sv.phai.length(), y);
			}
			else if(t == 3 && sv.matKhau.length()>0){
				sv.matKhau.pop_back();
				gotoxy(79 + sv.matKhau.length(), y);
				cout<<" ";
				gotoxy(79 + sv.matKhau.length(), y);
			}
		}
		else if((k>=32 && k<=122)){
			if(t==1 && ((k>=65 && k <=90) || (k>=97 && k <=122) || k == 32) && hoten.length()<32){ // dài toi da 32 ky tu
				hoten.push_back(k);
				cout<<k;
			}
			else if(t==2 && sv.phai.length()<3 && ((k>=65 && k <=90) || (k>=97 && k <=122))){
				sv.phai.push_back(k);
				cout<<k;
			}
			else if(t==3 && sv.matKhau.length()<10){
				sv.matKhau.push_back(k);
				cout<<k;
			}
		}	
	}
}
void capNhatSinhVien(NodeSinhVien* sv, SinhVien x){
	sv->data.ho = x.ho;
	sv->data.ten = x.ten;
	sv->data.phai = x.phai;
	sv->data.matKhau = x.matKhau;
}
void thucThiSinhVien(Lop* lop, treemh dsmh, DSLop dsl){
	system("cls");
	char kytu;
	int stt;
	NodeSinhVien* sv = NULL;
	string timkiem;
	int f =1;
	int slsv = laySoLuongSinhVien(lop->dsSinhVien);
	int chon = 1; // lua chontren 1 trang
	int maxTrang; // so trang toi da de chua het mon hoc
	int trangHienTai = 1;  //trang hien tai dang in tren manhinh
	textcolor(6);
	gotoxy(39,6);
	cout<<lop->maLop<<" - "<<lop->tenLop;
	giaoDienSinhVien();
	DSSapXep ds;
	copyDSSinhVien(lop->dsSinhVien, ds);
	stt=chon+15*(trangHienTai-1);
quaylai:	maxTrang = slsv/15 +((slsv%15==0) ? 0:1);
	loadDSSinhVien(ds,trangHienTai, lop->dsSinhVien);
	gotoxy(48,31);
	cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
	if(slsv > 0) DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonON);
	while(kytu!=27 || f!=0){
		kytu = _getch();
		switch (kytu){
			case 72:{ //len
				if(trangHienTai>1&&chon ==1){
					chon = 15;
					trangHienTai--;
					loadDSSinhVien(ds,trangHienTai, lop->dsSinhVien);
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
				}
				else if(chon>1){
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonOFF);
					chon --;
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonON);
				}
			}
			break;
			case 80:{ //xuong
				if(chon+15*(trangHienTai-1) == slsv){ // so chon hien tai == so luong mon hoc
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonOFF);
					chon = 1;
					trangHienTai = 1;
					loadDSSinhVien(ds,trangHienTai, lop->dsSinhVien);
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
				}
				else if(chon<15&&slsv>0){
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonOFF);
					chon ++;
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonON);
				}
				else if(chon == 15) { // nut chon o cuoi trang
					chon = 1;
					trangHienTai++;
					loadDSSinhVien(ds,trangHienTai, lop->dsSinhVien);
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
				}
			}
			break;
			case 75:{ //trai
				if(trangHienTai>1){
					chon = 1;
					trangHienTai -- ;
					loadDSSinhVien(ds,trangHienTai, lop->dsSinhVien);
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
				}
			}
			break;
			case 77:{ //phai
				if(trangHienTai<maxTrang){
					chon = 1;
					trangHienTai++ ;
					loadDSSinhVien(ds,trangHienTai, lop->dsSinhVien);
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
				}
			}
			break;
			case 82:{ //insert
				
				thucThiThemSinhVien(lop->dsSinhVien, lop, dsl);
				copyDSSinhVien(lop->dsSinhVien, ds);
				slsv = laySoLuongSinhVien(lop->dsSinhVien);
				system("cls");
				textcolor(6);
				gotoxy(39,6);
				cout<<lop->maLop<<" - "<<lop->tenLop;
				giaoDienSinhVien();
				goto quaylai;
			}
			break;
			case 83:{ //delete
				if(slsv == 0) break;
				sv = laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt));
				if(sv->data.dsDiem.phead != NULL){
					thongbao("SINH VIEN DA THAM GIA THI KHONG THE XOA !!!", 40,32,4,7);
					Sleep(2000);
					xoahang(32);
				}
				else{
					khungConfirm("Ban co chac chan xoa hay khong ?",7,4);
					while(1){
						kytu = _getch();
						if(kytu == 89 || kytu == 121){
							xoaSinhVien(lop->dsSinhVien, sv->data.maSinhVien);
							chon--;
							if(chon==0){
								chon = 1;
								if(chon+15*(trangHienTai-1)>slsv){
									chon=15;
									trangHienTai--;
								}
							}	
							xoaKhungConfirm();
							thongbao("XOA SINH VIEN THANH CONG !!!", 40 , 32, 4,7);
							Sleep(2000);
							xoahang(32);
							gotoxy(33,8);
							for(int m =0;m<timkiem.size();m++ ) cout<<" ";
							timkiem="";
							f=1;
							copyDSSinhVien(lop->dsSinhVien,ds);
							slsv =laySoLuongSinhVien(lop->dsSinhVien);
							stt=chon+15*(trangHienTai-1);
							goto quaylai;
						}
						else if(kytu == 78 || kytu == 110 ){
							xoaKhungConfirm();
							break;
						}
					}
				}
			}
			break;
			case 62:{ //f4
				if(slsv == 0) break;
				SinhVien x;
				sv = laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt));
				x.maSinhVien = sv->data.maSinhVien;
				x.ho = sv->data.ho;
				x.ten = sv->data.ten;
				x.phai = sv->data.phai;
				x.matKhau = sv->data.matKhau;
				xoahang(chon+13);
				inSinhVien(x,13+chon,stt);
				thongbao("KHONG DUOC PHEP CHINH SUA MA SINH VIEN", 40,35,10,7);
				if(nhapThongTinSinhVien(x,38,13+chon)==true){
					capNhatSinhVien(sv,x);
					thongbao("CHINH SUA THONG TIN SINH VIEN THANH CONG !!!", 35,32,4,7);
					Sleep(2000);
					xoahang(32);
					gotoxy(33,8);
					for(int m =0;m<timkiem.size();m++ ) cout<<" ";
					timkiem="";
					f=1;
					copyDSSinhVien(lop->dsSinhVien, ds);
					slsv=laySoLuongSinhVien(lop->dsSinhVien);
					stt = laySTT(ds,x.maSinhVien);
					trangHienTai = stt/15 +((stt%15==0) ? 0:1);
					chon = stt%15;
					if(chon==0) chon = 15;
					xoahang(35);
					xoaBangHoTro();
					hoTroMonHoc("sv");
					goto quaylai;
				}
				xoaBangHoTro();
				hoTroMonHoc("sv");
				xoahang(35);
				DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonON);
			}
			break;
			case 6:{ //ctrl + f
				if(nhapTenMonHoc(timkiem,33,8)==true){
					taoDSTmKiemSV(lop->dsSinhVien, ds, timkiem, slsv);
					f = 2; // chuyen sang man hinh tim kiem
					cout<<slsv;
					if(slsv==0){
						thongbao("KHONG TON TAI THONG TIN SINH VIEN !!!",40,31,4,7);
						Sleep(2000);
						xoahang(31);
						gotoxy(33,8);
						for(int m =0;m<timkiem.length();m++ ) cout<<" ";
						timkiem="";
						copyDSSinhVien(lop->dsSinhVien,ds);
						slsv = laySoLuongSinhVien(lop->dsSinhVien);
						f=1;
					}
					trangHienTai = 1;
					chon = 1;
					stt=chon+15*(trangHienTai-1);
					goto quaylai;
				}
				else { // khi dang nhap ma nhan esc
					f = 1;
					gotoxy(33,8);   // xoa chu tren o tim kiem
					for(int m =0;m<timkiem.length();m++ ) cout<<" ";
					timkiem="";
					copyDSSinhVien(lop->dsSinhVien,ds);
					slsv = laySoLuongSinhVien(lop->dsSinhVien);
					loadDSSinhVien(ds,trangHienTai, lop->dsSinhVien);
					stt=chon+15*(trangHienTai-1);
					DrawButtonSinhVien(laySinhVien2(lop->dsSinhVien, layMaDuaVaoSTT2(ds, stt)),14,13+chon,stt, ButtonON);
				}
			}
			break;
			case 13:{ //enter
				if(slsv == 0) break;
				lichSuThi(laySinhVien2(lop->dsSinhVien,layMaDuaVaoSTT2(ds, stt)),lop->maLop,lop->tenLop,dsmh);
				giaoDienSinhVien();
				textcolor(6);
				gotoxy(39,6);
				cout<<lop->maLop<<" - "<<lop->tenLop;
				goto quaylai;
			}
			break;
			case 27: 
				if(f==2) {
					gotoxy(33,8);
					for(int m =0;m<timkiem.size();m++ ) cout<<" ";
					timkiem="";
					copyDSSinhVien(lop->dsSinhVien,ds);
					slsv = laySoLuongSinhVien(lop->dsSinhVien);
					chon = 1;
					trangHienTai = 1;
					stt=chon+15*(trangHienTai-1);
					f=1;
					goto quaylai;
				}
				else if(f==1){
					f=0;
					xoaDSSapxep2(ds);
				}
				break;
		}
	}
}
void thucThiLopHoc(DSLop &dsl, treemh dsmh){
	system("cls");
	char kytu = '\0';
	int stt;
	string timkiem;
	int f = 1;
	int sll = dsl.sl;
	Lop lop;
	int chon = 1; // lua chontren 1 trang
	int maxTrang; // so trang toi da de chua het mon hoc
	int trangHienTai = 1;  //trang hien tai dang in tren manhinh
	giaoDienLop();
	DSSapXep ds;
	copyDSLop(dsl,ds);
	stt=chon+15*(trangHienTai-1);
quaylai:	maxTrang = sll/15 +((sll%15==0) ? 0:1);
	loadDSLop(ds,trangHienTai, dsl);
	gotoxy(48,31);
	cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
	DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
	while(kytu!=27 || f!=0){
		kytu = _getch();
		switch(kytu){
			case 72:{ //len
				if(trangHienTai>1&&chon ==1){
					chon = 15;
					trangHienTai--;
					loadDSLop(ds,trangHienTai, dsl);
					stt=chon+15*(trangHienTai-1);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
				}
				else if(chon>1){
					stt=chon+15*(trangHienTai-1);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonOFF);
					chon --;
					stt=chon+15*(trangHienTai-1);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
				}
			}
			break;
			case 80:{ //xuong
				if(chon+15*(trangHienTai-1) == sll){ // so chon hien tai == so luong mon hoc
					chon = 1;
					trangHienTai = 1;
					loadDSLop(ds,trangHienTai, dsl);
					stt=chon+15*(trangHienTai-1);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
					}
				else if(chon<15){
					stt=chon+15*(trangHienTai-1);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonOFF);
					chon ++;
					stt=chon+15*(trangHienTai-1);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
					}
				else if(chon == 15 && trangHienTai<maxTrang) { // nut chon o cuoi trang
					chon = 1;
					trangHienTai++;
					loadDSLop(ds,trangHienTai, dsl);
					stt=chon+15*(trangHienTai-1);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
					}
			}
			break;
			case 75:{ //trai
				if(trangHienTai>1){
					chon = 1;
					trangHienTai -- ;
					loadDSLop(ds,trangHienTai, dsl);
					stt=chon+15*(trangHienTai-1);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
				}
			}
			break;
			case 77:{ //phai
				if(trangHienTai<maxTrang){
					chon = 1;
					trangHienTai++ ;
					loadDSLop(ds,trangHienTai, dsl);
					stt=chon+15*(trangHienTai-1);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
					gotoxy(48,31);
					cout<<"Trang "<<trangHienTai<<"/"<<maxTrang;
				}
			}
			break;
			case 82:{ //insert
				loadDSLop(ds,maxTrang, dsl); // neu sl kh chia het 15 thì them vào ô cuoi cùng
				gotoxy(48,31);
				cout<<"Trang "<<maxTrang<<"/"<<maxTrang;
				chon = sll+1-(maxTrang-1)*15;
				xoahang(chon +13); // xóa dòng gach ngang cuoi
				gotoxy(16, 13+chon);
				cout<<sll+1; //  in san so thu tu
				bangLop(chon+1); // ke them 1 hàng moi
				if(nhapThongTinLop(24, 13+chon,lop,dsl)==0){ //khi ng dung nhan ESC dung viec them
					xoahang(chon+14);
					bangLop(chon);
					chon = sll%15;
					if(chon == 0) chon =15;
					trangHienTai = maxTrang;
					stt=chon+15*(trangHienTai-1);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
					xoaBangHoTro();
					hoTroMonHoc("l");
				}
				else{
					Lop* l = new Lop();
					l->maLop = lop.maLop;
					l->tenLop = lop.tenLop;
	
					thongbao("THEM LOP THANH CONG !!!", 40,32,4,7);
					Sleep(2000);
					xoahang(32);
					gotoxy(33,8);
					for(int m =0;m<timkiem.length();m++ ) cout<<" ";
					timkiem="";
					f=1;
					khungConfirm("Ban co muon them sinh vien khong ???",7,4);
					kytu = '\0';
					while(1){
						kytu = _getch();
						if(kytu == 89 || kytu == 121){
							thucThiThemSinhVien(l->dsSinhVien, l, dsl);
							system("cls");
							giaoDienLop();
							break;
						}
						else if(kytu == 78 || kytu == 110){
							xoaKhungConfirm();
							break;
						}
					}
					themLop(dsl,l);
					copyDSLop(dsl,ds);
					sll = dsl.sl;
					stt = laySTT(ds, lop.maLop);
					trangHienTai =stt/15 +((stt%15==0) ? 0:1);
					chon = stt%15;
					if(chon==0) chon = 15;
					//luuDSMonHoc(dsmh,"monhoc.txt");
					xoaBangHoTro();
					hoTroMonHoc("l");
					goto quaylai;
				}
			}
			break;
			case 83:{ //delete
				if(sll == 0) break;
				if(layLop(dsl,layMaDuaVaoSTT2(ds,stt))->dsSinhVien.phead != NULL){
					thongbao("LOP DANG TON SINH VIEN KHONG THE XOA !!!", 40,32,4,7);
					Sleep(2000);
					xoahang(32);
					break;
				}
				khungConfirm("Ban co chac chan xoa hay khong ?",7,4);
				kytu='\0';
				while(1){
					kytu = _getch();
					if(kytu == 89 || kytu == 121){
						xoaLop(dsl, layMaDuaVaoSTT2(ds,stt));
						chon--;
						if(chon==0){
							chon = 1;
							if(chon+15*(trangHienTai-1)>dsl.sl){
								chon=15;
								trangHienTai--;
							}
						}	
						xoaKhungConfirm();
						//luuDSMonHoc(dsmh,"monhoc.txt");
						thongbao("XOA LOP HOC THANH CONG !!!",  40,32,4,7);
						Sleep(2000);
						xoahang(32);
						gotoxy(33,8);
						for(int m =0;m<timkiem.length();m++ ) cout<<" ";
						timkiem="";
						f=1;
						copyDSLop(dsl,ds);
						sll = dsl.sl;
						stt=chon+15*(trangHienTai-1);
						goto quaylai;
					}
					else if(kytu == 78 || kytu == 110 ){
						xoaKhungConfirm();
						break;
					}
				}
			}
			break;
			case 62:{ //f4
				if(sll == 0) break;
				Nocursortype(TRUE);
				xoaBangHoTro();
				hoTroSuaMonHoc();
				lop = *layLop(dsl,layMaDuaVaoSTT2(ds,stt));
				xoahang(chon+13);
				inLop(lop,13+chon, stt);
				thongbao("CHI CHO PHEP CHINH SUA TEN LOP", 40,34,10,7);
				if(nhapTenMonHoc(lop.tenLop,43,13+chon)==true){
					capNhatTenLop(dsl,lop.maLop,lop.tenLop);
					thongbao("CHINH SUA MON HOC THANH CONG !!!", 40,32,4,7);
					Sleep(2000);
					xoahang(32);
					gotoxy(33,8);
					for(int m =0;m<timkiem.size();m++ ) cout<<" ";
					timkiem="";
					f=1;
					copyDSLop(dsl,ds);
					sll=dsl.sl;
					stt = laySTT(ds,lop.maLop);
					trangHienTai = stt/15 +((stt%15==0) ? 0:1);
					chon = stt%15;
					if(chon==0) chon = 15;
					xoaBangHoTro();
					hoTroMonHoc("l");
					goto quaylai;
				}
				DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
				xoahang(34);
				xoaBangHoTro();
				hoTroMonHoc("l");
				Nocursortype(FALSE);
			}
			break;
			case 6:{ //ctrl + f
				if(nhapTenMonHoc(timkiem,33,8)==true){
					taoDSTmKiemLop(dsl,ds,timkiem,sll);
					f = 2; // chuyen sang man hinh tim kiem
					if(sll==0){
						thongbao("KHONG TON TAI LOP !!!",40,31,4,7);
						Sleep(2000);
						xoahang(31);
						gotoxy(33,8);
						for(int m =0;m<timkiem.length();m++ ) cout<<" ";
						timkiem="";
						copyDSLop(dsl,ds);
						sll = dsl.sl;
						f=1;
					}
					trangHienTai = 1;
					chon = 1;
					stt=chon+15*(trangHienTai-1);
					goto quaylai;
				}
				else { // khi dang nhap ma nhan esc
					f=1;
					gotoxy(33,8);   // xoa chu tren o tim kiem
					for(int m =0;m<timkiem.length();m++ ) cout<<" ";
					timkiem="";
					copyDSLop(dsl,ds);
					sll = dsl.sl;
					loadDSLop(ds,trangHienTai,dsl);
					DrawButtonLop(layLop(dsl,layMaDuaVaoSTT2(ds,stt)),14,13+chon,stt,ButtonON);
				}
			}
			break;
			case 13:{ //enter
				if(sll == 0) break;
				thucThiSinhVien(layLop(dsl, layMaDuaVaoSTT2(ds,stt)), dsmh, dsl);
				system("cls");
				giaoDienLop();
				goto quaylai;
			}
			break;
			case 27: 
				if(f==2) {
					gotoxy(33,8);
					for(int m =0;m<timkiem.size();m++ ) cout<<" ";
					timkiem="";
					copyDSLop(dsl,ds);
					sll = dsl.sl;
					chon = 1;
					trangHienTai = 1;
					stt=chon+15*(trangHienTai-1);
					f=1;
					goto quaylai;
				}
				else if(f==1){
					f=0;
					luuDSLop(dsl,"lop.txt");
				}
				break;
		}
	}
}
int kt_DangNhap(string user, string pass, DSLop dsl){
	for(int i=0; i < dsl.sl; i++){
		for(NodeSinhVien* k = dsl.dsLop[i]->dsSinhVien.phead; k != NULL; k = k->next){
			if(k->data.maSinhVien == user){
				if(k->data.matKhau == pass) return true;
				return false;
			}
		}
	}
	return false;
}
int nhapDangNhap(string &user, string pass, DSLop dsl){ // return -1: nhan esc, 0: gv, 1: sv
	VEKHUNGMAIN(2,1,"LogoThiTracNghiem.txt");
	Ve_Vien_Doi(49, 15, 30, 3, 10, "LOGIN");
	textcolor(10);
	gotoxy(52, 18); cout << "USER";
	gotoxy(52, 22); cout << "PASSWORD";
	khungNhap("", 52, 19, 24, 1,6,0);
	
	khungNhap("",52, 23, 24, 1, 6, 0);
	textcolor(10);
	user = "";
	pass = "";
	bool t = true; // con tro dang tren user
	gotoxy(54,20);
	char k;
	while(1){
		k = _getch();
		switch (k){
			case 13:{
				if(user == ""){
					thongbao("TEN DANG NHAP KHONG DUOC RONG", 52,28,4,7);
					Sleep(2000);
					xoahang(28);
					gotoxy(54,20);
					t = true;
				}
				else if (pass == ""){
					thongbao("MAT KHAU KHONG DUOC RONG", 52,28,4,7);
					Sleep(2000);
					xoahang(28);
					gotoxy(54,24);
					t = false;
				}
				else if(user == "GV" && pass == "GV") return 0;
				else if(kt_DangNhap(user, pass, dsl)==false){
					thongbao("THONG TIN DANG NHAP KHONG CHINH XAC", 50,28,4,7);
					Sleep(2000);
					xoahang(28);
					gotoxy(54+user.length(),20);
					t = true;
				}
				else return 1;
			}
				break;
			case 27: return -1;
			break;
			case 72: { // len
				if(t == false){
					t = true;
					gotoxy(54+user.length(),20);
				}
				break;
			}
			case 80:{ // xuong
				if(t == true){
					t = false;
					gotoxy(54+pass.length(),24);
				}
				break;
			}
			case 8:{
				if(t == true&&user.length()>0){
					user.erase(user.length()-1,1);
					gotoxy(54+user.length(),20);
					cout<<" ";
					gotoxy(54+user.length(),20);
				}
				else if(t == false&&pass.length()>0){
					pass.erase(pass.length()-1,1);
					gotoxy(54+pass.length(),24);
					cout<<" ";
					gotoxy(54+pass.length(),24);
				}
			}
				break;
			default:{
				if((k>= 48 && k<=57)||(k>=65 && k<=90)){
					if(t == true){
						user.push_back(k);
						cout<<k;
					}
					else{
						pass.push_back(k);
						cout<<"*";
					}
				}
				else if(k>=97 && k<=122){
					if(t == true){
						k = k-32;
						user.push_back(k);
						cout<<k;
					}
					else{
						k = k-32;
						pass.push_back(k);
						cout<<"*";
					}
				}
			}
			break;
		}	
	}
}
int MenuDong(char **&td){
	BangThongTinSV(50,15);
	BangChuThich(28,34);
	int chon=0;Button tmp;
	for(int i=0;i<6;i++) {
	 	tmp=CreateButton(3,30,td[i]);
		DrawButton(tmp,3,8+i*3,ButtonOFF);
	}
	tmp=CreateButton(3,30,td[chon]);
	DrawButton(tmp,3,8+chon*3,ButtonON);
	char kytu;
	while(1){
		kytu=_getch();
		//if(kytu==-32) kytu=_getch();
		switch(kytu)
			{
			case 72: if(chon>0)
			{
				tmp=CreateButton(3,30,td[chon]);
				DrawButton(tmp,3,8+chon*3,ButtonOFF);
				chon--;
				tmp=CreateButton(3,30,td[chon]);
				DrawButton(tmp,3,8+chon*3,ButtonON);
			}
				break;
			case 80: if(chon+1<6)
			{
          		tmp=CreateButton(3,30,td[chon]);
				DrawButton(tmp,3,8+chon*3,ButtonOFF);
           		chon ++;
           		tmp=CreateButton(3,30,td[chon]);
				DrawButton(tmp,3,8+chon*3,ButtonON);
			}
				break;
			case 13: return chon+1;
			case 27: return 6;
			}
			
		}
}
	

void RunMenu(string user, DSLop &dsl, treemh &dsmh) {
	
	int chon;
	char **thucdon = new char*[6];//các chuc nang
	thucdon[0] = "Quan ly Lop hoc & Sinh vien";
	thucdon[1] = "Quan ly Mon hoc & Cau hoi";
	thucdon[2] = "Thi trac nghiem thu";
	thucdon[3] = "Xem chi tiet de da thi";
	thucdon[4] = "Xem bang diem";
	thucdon[5] = "Thoat chuong trinh";
quay: system("cls");
	VEKHUNGMAIN(2,1,"LogoThiTracNghiem.txt");	
	chon = MenuDong(thucdon);
	textcolor(10);
	SetBGColor(0);
	switch(chon) {
		case 1: {
			thucThiLopHoc(dsl, dsmh);
			goto quay;
			break;
		}
		case 2: {
			thucThiMonHoc(dsmh);
			goto quay;
			break;
		}
		case 3: {
			thucThiThiTracNghiem(user, dsl,dsmh);
			goto quay;
			break;
		}
		case 4:
		{
			thucThiXemLichSuThi(dsl,dsmh);
			goto quay;
			break;	
		}
		case 5:
		{
			thucThiXemDSDiem(dsl, dsmh);
			goto quay;
			break;	
		}
	}
}
