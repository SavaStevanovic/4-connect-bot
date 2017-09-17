
// SPDialogDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <unordered_map>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
// CSPDialogDlg dialog
class CSPDialogDlg : public CDialogEx
{
private:
	int mat[6][7];
	int niz[7];
	CBrush boje[2];
	int brojac = 1;
	int bot = 0;
	static   int vrednosti[7];
	int ocenat = 0;
	int gotovo = false;
	static int redosled[7];
	int kljuc;
	int stepen3[21];
	long ran[6][7][2];
	long nothelper = 0;
	long helper = 0;
	map<int, int> table;
// Construction
public:
	CSPDialogDlg(CWnd* pParent = NULL);	// standard constructor
	int minmax(int i, int nivo, bool maxi,int &alpha,int beta,int granica){
		int poma = alpha;
		
		mat[niz[i]][i] = -(brojac == 1) + (brojac == 0);
		
		brojac = -brojac + 1;
		kljuc ^= ran[niz[i]][i][brojac];
		bool  pommax;
		if (maxi == true)   maxi = false;
		else maxi = true;
		int niz1[7];
		if (gg(i)){ 
			kljuc ^= ran[niz[i]][i][brojac];
			mat[niz[i]][i] = 0;
			brojac = -brojac + 1;
			return (-(brojac == 1) + (brojac == 0)) * 5000; }

		if (nivo == 0 ){
			int pom;
			/*int pom = ocena(1)
				- ocena(-1);*/
			map<int, int > ::iterator  t = table.find(kljuc);
			if (t != table.end()){ pom = t->second; helper++; }
			else {
				pom = ocena(1)
					- ocena(-1);
				nothelper++;
				table.insert(make_pair(kljuc, pom));
			}
			kljuc ^= ran[niz[i]][i][brojac];
			mat[niz[i]][i] = 0;
			brojac = -brojac + 1;
			return pom;
		}



		niz[i]++;
		for (int j = 0; j < 7; j++)
		{
			if (niz[redosled[j]] < 6){

				niz1[redosled[j]] = minmax(redosled[j], nivo - 1, maxi, poma, beta, granica);
				if (maxi == true){
					if (niz1[redosled[j]] >= beta){
						niz[i]--;
						kljuc ^= ran[niz[i]][i][brojac];
						mat[niz[i]][i] = 0;
						brojac = -brojac + 1;
						return 50000;
					}
					else if (niz1[redosled[j]]>=poma) poma = niz1[redosled[j]];
				}
				else
					if (maxi == false){
						if (niz1[redosled[j]] <=poma){
							niz[i]--;
							kljuc ^= ran[niz[i]][i][brojac];
							mat[niz[i]][i] = 0;
							brojac = -brojac + 1;
							return -50000;
						}
						else if (niz1[redosled[j]] <= beta) beta = niz1[redosled[j]];
					}
			}
			else niz1[redosled[j]] = (-(brojac == 0) + (brojac == 1)) * 5000;
		}
		
		niz[i]--;
		kljuc ^= ran[niz[i]][i][brojac];
		mat[niz[i]][i] = 0;
		brojac = -brojac + 1;
		if (nivo == granica){
			alpha = poma;
		
		}
		if (maxi == 1)
			return maxim(niz1);
		else return  minim(niz1);
	}



	int maxim(int niz[7]){
		int max = -50000;
		for (int i = 0; i < 7; i++)
		{
			if (max < niz[i]) max = niz[i];
		}
		return max;
	}
	int minim(int niz[7]){
		int min = 50000;
		for (int i = 0; i < 7; i++)
		{
			if (min > niz[i]) min = niz[i];
		}
		return min;
	}

	int ocena(int brojac){ return dirirectionValue( 1,0, brojac) + dirirectionValue( 1,1, brojac) + dirirectionValue( 0,1, brojac) + dirirectionValue( -1,1, brojac); }


	int dirirectionValue(int xDir, int yDir, int brojac) {
		int suma = 0;
		for (int i = (yDir == -1) * 3; i < 6 - (yDir == 1) * 3; i++) {
			for (int j = (xDir == -1) * 3; j < 7 - (xDir == 1) * 3; j++) {
				int s = 0;
				bool pro = true;
				for (int z = 0; z < 4; z++) {
					s += (mat[i + z*yDir][j + z*xDir] == brojac);
					if (mat[i + z*yDir][j + z*xDir] == -brojac)
					{
						pro = false; 
						j += (yDir == 0)*z;
						i += (xDir == 0)*z;
						z += 4;
					}
				}
				suma += vrednosti[s*pro];
			}
		}
		return suma;
	}

	bool gg(int i){
		int y = i;
		int x = niz[i];
		int h,v,dl,dd;
		h = v = dl = dd = 0;
		int j = 1;
		int check = mat[x][y];
		while (mat[x - j][y] == mat[x][y] && x- j>=0)
		{
			j++;
			v++;
		}
		j = 1;
		while (mat[x][y+j] == mat[x][y]&& y+j<7)
		{
			j++;
			h++;
		}
		j = 1;
		while (mat[x][y - j] == mat[x][y] && y - j>=0)
		{
			j++;
			h++;
		}

		j = 1;
		while (mat[x - j][y - j] == mat[x][y] && y - j >= 0 && x - j >= 0)
		{
			j++;
			dl++;
		}	
		j = 1;
		while (mat[x + j][y + j] == mat[x][y] && y + j<7 && x + j<6)
		{
			j++;
			dl++;
		}

		j = 1;
		while (mat[x - j][y + j] == mat[x][y] && y + j<7 && x - j>=0)
		{
			j++;
			dd++;
		}
		j = 1;
		while (mat[x + j][y - j] == mat[x][y] && x + j<6 && y - j >= 0)
		{
			j++;
			dd++;
		}
		if (h > 2 || v > 2 || dl > 2 || dd > 2)
			return true;
		return false;

	}
// Dialog Data
	enum { IDD = IDD_SPDIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public: 
	int izbor;
	bool drawOnClick;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedNew();

	
	afx_msg void OnBnClickedBot();
	afx_msg void OnStnClickedRezultat();
};
