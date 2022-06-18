#include<iostream>
using namespace std;


class CNode {

public:
	string C[8][8];
	int info;
	CNode* pNext;
};

class CStack {

public:
	CNode* pHead;
	CNode* pTail;

	CStack()
	{
		pHead = NULL;
		pTail = NULL;
	}

	~CStack()
	{
		CNode* pTrav = pHead;
		while (pTrav != NULL)
		{
			pHead = pHead->pNext;
			delete pTrav;
			pTrav = pHead;
		}
	}

	void Push(CNode* pnn)
	{
		if (pHead == NULL)
		{
			pHead = pnn;
			pTail = pnn;
			pTail->pNext = NULL;

		}
		else
		{
			pnn->pNext = pHead;
			pHead = pnn;
		}
	}

	CNode* Pop()
	{
		CNode* pTrav = pHead;
		if (pTrav == NULL)
		{
			return NULL;
		}
		else
		{
			pHead = pTrav->pNext;
			pTrav->pNext = NULL;
		}
		return pTrav;
	}

	int CheckBK(CNode* pnn)
	{
		int F = 0;
		int R = 1;
		CNode* pTemp = pHead;
		while (pTemp != NULL)
		{
			F = 0;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (pnn->C[i][j] == pTemp->C[i][j])
					{
						F++;
						if (F == 64)
						{
							R = 0;
							break;
						}
					}
				}
			}
			pTemp = pTemp->pNext;
			if (R == 0)
			{
				return R;
			}
		}
		return R;
	}
};

class CList {

public:
	CNode* pHead;
	CNode* pTail;

	CList()
	{
		pHead = NULL;
		pTail = NULL;
	}

	~CList()
	{
		CNode* pTrav = pHead;
		while (pTrav != NULL)
		{
			pHead = pHead->pNext;
			pTrav = NULL;
			pTrav = pHead;
		}
	}

	void Attach(CNode* pnn)
	{
		if (pHead == NULL)
		{

			pHead = pnn;
			pTail = pnn;
		}
		else
		{
			pTail->pNext = pnn;
			pTail = pnn;
		}
	}


	void Remove(int v)
	{
		CNode* pTrav = pHead;
		CNode* pB = NULL;
		while (pTrav != NULL)
		{
			if (pTrav->info == v)
			{
				break;
			}
			pB = pTrav;
			pTrav = pTrav->pNext;
		}
		if (pB != NULL)
		{
			pB->pNext = pTrav->pNext;
			if (pTail == pTrav)
			{
				pTail = pB;
			}
		}
		else
		{
			pHead = pTrav->pNext;
		}

		delete pTrav;
	}

	
};

CNode* CreateInitState()
{
	CNode* pnn = new CNode;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pnn->C[i][j] = '-';
		}
	}
	pnn->C[0][6] = "F1";
	pnn->C[1][1] = "F2";
	pnn->C[2][3] = "T2";
	pnn->C[3][2] = "A2";
	pnn->C[3][6] = "A1";
	pnn->C[3][7] = "A2";
	pnn->C[4][4] = "K2";
	pnn->C[4][5] = "H1";
	pnn->C[4][7] = "T1";
	pnn->C[5][4] = "H1";
	pnn->C[7][3] = "Q2";
	pnn->C[7][6] = "F1";
	pnn->C[7][7] = "K1";
	pnn->pNext = NULL;
	return pnn;

}

void Display(CNode* pnn)
{
	for (int i = 0; i < 8; i++)
	{
		cout << " ";
		for (int j = 0; j < 8; j++)
		{
			cout <<  pnn->C[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
}

int IsVisited(CNode* pnn, CList& Visit)		// NOT USED
{
	
	CNode* pTrav = Visit.pHead;
	int F = 0;
	int R = 1;
	
	
	//pTrav = Visit.pHead;
	//while (pTrav != NULL)
	//{
		//cout << "Visited up:   " << pTrav->S1[0] << pTrav->S1[1] << pTrav->S1[2] << pTrav->S1[3] << pTrav->S1[4] << pTrav->S1[5] << " boat: "<<pTrav->boat << endl;
		//cout << "Visited down: " << pTrav->S2[0] << pTrav->S2[1] << pTrav->S2[2] << pTrav->S2[3] << pTrav->S2[4] << pTrav->S2[5] <<  endl << endl;
		//pTrav = pTrav->pNext;
	//}

	pTrav = Visit.pHead;
	//Visit.pTail->pNext = NULL;
	while (pTrav != NULL)
	{
		F = 0;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (pTrav->C[i][j] == pnn->C[i][j])
				{
					F++;
					if (F == 64)
					{

						R = 0;
						break;

					}
				}
			}
		}
		pTrav = pTrav->pNext;
		if (R == 0)
		{
			return R;
			break;
		}
	}
	
	return R;
}

int Checkalive(CNode* pnn, int a, int b)
{
	int R = 1;
	// T & Q
	for (int i = a + 1; i < 8; i++)
	{
		if (pnn->C[i][b] != "-")
		{
			if (pnn->C[i][b] == "T2" || pnn->C[i][b] == "Q2")
			{
				cout << " ( error code 1 )\n\n";
				R = 0;
				return R;
			}
			else
			{
				break;
			}
		}
	}

	for (int i = a - 1; i >= 0; i--)
	{
		if (pnn->C[i][b] != "-")
		{
			if (pnn->C[i][b] == "T2" || pnn->C[i][b] == "Q2")
			{
				cout << " ( error code 2 )\n\n";
				R = 0;
				return R;
			}
			else
			{
				break;
			}
		}
	}

	for (int i = b + 1; i < 8; i++)
	{
		if (pnn->C[a][i] != "-")
		{
			if (pnn->C[a][i] == "T2" || pnn->C[a][i] == "Q2")
			{
				cout << " ( error code 3 )\n\n";
				R = 0;
				return R;
			}
			else
			{
				break;
			}
		}
	}

	for (int i = b - 1; i >= 0; i--)
	{
		if (pnn->C[a][i] != "-")
		{
			if (pnn->C[a][i] == "T2" || pnn->C[a][i] == "Q2")
			{
				cout << " ( error code 4 )\n\n";
				R = 0;
				return R;
			}
			else
			{
				break;
			}
		}
	}
	/////////////////////////////////////

	// F & Q
	for (int i = a - 1, j = b + 1; i >= 0 && j < 8; i--, j++)
	{
		if (pnn->C[i][j] != "-")
		{
			if (pnn->C[i][j] == "F2" || pnn->C[i][j] == "Q2")
			{
				cout << " ( error code 5 )\n\n";
				R = 0;
				return R;
			}
			else
			{
				break;
			}
		}
	}

	for (int i = a - 1, j = b - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (pnn->C[i][j] != "-")
		{
			if (pnn->C[i][j] == "F2" || pnn->C[i][j] == "Q2")
			{
				cout << " ( error code 6 )\n\n";
				R = 0;
				return R;
			}
			else
			{
				break;
			}
		}

	}

	for (int i = a + 1, j = b + 1; i < 8 && j < 8; i++, j++)
	{
		if (pnn->C[i][j] != "-")
		{
			if (pnn->C[i][j] == "F2" || pnn->C[i][j] == "Q2")
			{
				R = 0;
				cout << " ( error code 7 )\n\n";
				return R;
			}
			else
			{
				break;
			}
		}

	}

	for (int i = a + 1, j = b - 1; i < 8 && j >= 0; i++, j--)
	{
		if (pnn->C[i][j] != "-")
		{
			if (pnn->C[i][j] == "F2" || pnn->C[i][j] == "Q2")
			{
				cout << " ( error code 8 )\n\n";
				R = 0;
				return R;
			}
			else
			{
				break;
			}
		}
	}
	/////////////////////////////////////

	 H
	if (pnn->C[a - 1][b + 2] == "H2" || pnn->C[a - 1][b - 2] == "H2" || pnn->C[a + 1][b + 2] == "H2" || pnn->C[a + 1][b - 2] == "H2" ||
		pnn->C[a - 2][b - 1] == "H2" || pnn->C[a - 2][b + 1] == "H2" || pnn->C[a + 2][b - 1] == "H2" || pnn->C[a + 2][b + 1] == "H2")
	{
		R = 0;
		return R;
	}

	// K
	if ((b < 7 && b > 0) && (a > 0 && a < 7))
	{
		if (pnn->C[a + 1][b + 1] == "K2" || pnn->C[a + 1][b] == "K2" || pnn->C[a + 1][b - 1] == "K2" || pnn->C[a][b + 1] == "K2" ||
			pnn->C[a - 1][b + 1] == "K2" || pnn->C[a + 1][b - 1] == "K2")
		{
			cout << " ( error code 9 )\n\n";
			R = 0;
			return R;
		}
	}

	return R;
}

int CheckKingIsAlive(CNode* pnn)
{
	int R = 0;
	int a, b;
	int ct = 0, ct2 = 0;
	for (int i = 4 + 1; i < 8; i++)
	{
		if (pnn->C[i][4] != "-")
		{
			if (pnn->C[i][4] == "T1" || pnn->C[i][4] == "Q1" || pnn->C[i][4] == "T01" || pnn->C[i][4] == "Q01")
			{
				return 0;
			}
			else
			{
				break;
			}
		}
	}

	for (int i = 4 - 1; i >= 0; i--)
	{
		if (pnn->C[i][4] != "-")
		{
			if (pnn->C[i][4] == "T1" || pnn->C[i][4] == "Q1" || pnn->C[i][4] == "T01" || pnn->C[i][4] == "Q01")
			{
				return 0;
			}
			else
			{
				break;
			}
		}
	}

	for (int i = 4 + 1; i < 8; i++)
	{
		if (pnn->C[4][i] != "-")
		{
			if (pnn->C[4][i] == "T1" || pnn->C[4][i] == "Q1" || pnn->C[4][i] == "T01" || pnn->C[4][i] == "Q01")
			{
				return 0;
			}
			else
			{
				break;
			}
		}
	}

	for (int i = 4 - 1; i >= 0; i--)
	{
		if (pnn->C[4][i] != "-")
		{
			if (pnn->C[4][i] == "T1" || pnn->C[4][i] == "Q1" || pnn->C[4][i] == "T01" || pnn->C[4][i] == "Q01")
			{
				return 0;
			}
			else
			{
				break;
			}
		}
	}
	/////////////////////////////////////

	// F & Q
	for (int i = 4 - 1, j = 4 + 1; i >= 0 && j < 8; i--, j++)
	{
		if (pnn->C[i][j] != "-")
		{
			if (pnn->C[i][j] == "F1" || pnn->C[i][j] == "Q1" || pnn->C[i][j] == "Q01")
			{
				return 0;
			}
			else
			{
				break;
			}
		}

	}

	for (int i = 4 - 1, j = 4 - 1; i >= 0 && j >= 0; i--, j--)
	{
		if (pnn->C[i][j] != "-")
		{
			if (pnn->C[i][j] == "F1" || pnn->C[i][j] == "Q1" || pnn->C[i][j] == "Q01")
			{
				return 0;
			}
			else
			{
				break;
			}
		}

	}

	for (int i = 4 + 1, j = 4 + 1; i < 8 && j < 8; i++, j++)
	{
		if (pnn->C[i][j] == "-")
		{
			if (pnn->C[i][j] == "F1" || pnn->C[i][j] == "Q1" || pnn->C[i][j] == "Q01")
			{
				return 0;
			}
			else
			{
				break;
			}
		}

	}

	for (int i = 4 + 1, j = 4 - 1; i < 8 && j >= 0; i++, j--)
	{
		if (pnn->C[i][j] != "-")
		{
			if (pnn->C[i][j] == "F1" || pnn->C[i][j] == "Q1" || pnn->C[i][j] == "Q01")
			{
				return 0;
			}
			else
			{
				break;
			}
		}
	}
	/////////////////////////////////////

	// H
	if (pnn->C[4 - 1][4 + 2] == "H1" || pnn->C[4 - 1][4 - 2] == "H1" || pnn->C[4 + 1][4 + 2] == "H1" || pnn->C[4 + 1][4 - 2] == "H1" ||
		pnn->C[4 - 2][4 - 1] == "H1" || pnn->C[4 - 2][4 + 1] == "H1" || pnn->C[4 + 2][4 - 1] == "H1" || pnn->C[4 + 2][4 + 1] == "H1")
	{
		return 0;
	}

	for (int w = 0; w < 8; w++)
	{
		R = 0;
		if (w == 0)
		{
			a = 3;
			b = 3;
		}
		if (w == 1)
		{
			a = 3;
			b = 4;
		}
		if (w == 2)
		{
			a = 3;
			b = 5;
		}
		if (w == 3)
		{
			a = 4;
			b = 3;
		}
		if (w == 4)
		{
			a = 4;
			b = 5;
		}
		if (w == 5)
		{
			a = 5;
			b = 3;
		}
		if (w == 6)
		{
			a = 5;
			b = 4;
		}
		if (w == 7)
		{
			a = 5;
			b = 5;
		}
		// T & Q
		for (int i = a + 1; i < 8; i++)
		{
			if (pnn->C[i][b] != "-")
			{
				if (pnn->C[i][b] == "T1" || pnn->C[i][b] == "Q1" || pnn->C[i][b] == "T01" || pnn->C[i][b] == "Q01")
				{
					R++;
					break;
				}
				else
				{
					break;
				}
			}
		}

		for (int i = a - 1; i >= 0; i--)
		{
			if (pnn->C[i][b] != "-")
			{
				if (pnn->C[i][b] == "T1" || pnn->C[i][b] == "Q1" || pnn->C[i][b] == "T01" || pnn->C[i][b] == "Q01")
				{
					R++;
					break;
				}
				else
				{
					break;
				}
			}
		}

		for (int i = b + 1; i < 8; i++)
		{
			if (pnn->C[a][i] != "-")
			{
				if (pnn->C[a][i] == "T1" || pnn->C[a][i] == "Q1" || pnn->C[a][i] == "T01" || pnn->C[a][i] == "Q01")
				{
					R++;
					break;
				}
				else
				{
					break;
				}
			}
		}

		for (int i = b - 1; i >= 0; i--)
		{
			if (pnn->C[a][i] != "-")
			{
				if (pnn->C[a][i] == "T1" || pnn->C[a][i] == "Q1" || pnn->C[a][i] == "T01" || pnn->C[a][i] == "Q01")
				{
					R++;
					break;
				}
				else
				{
					break;
				}
			}
		}
		/////////////////////////////////////

		// F & Q
		for (int i = a - 1, j = b + 1; i >= 0 && j < 8; i--, j++)
		{
			if (pnn->C[i][j] != "-")
			{
				if (pnn->C[i][j] == "F1" || pnn->C[i][j] == "Q1" || pnn->C[i][j] == "Q01")
				{
					R++;
					break;
				}
				else
				{
					break;
				}
			}

		}

		for (int i = a - 1, j = b - 1; i >= 0 && j >= 0; i--, j--)
		{
			if (pnn->C[i][j] != "-")
			{
				if (pnn->C[i][j] == "F1" || pnn->C[i][j] == "Q1" || pnn->C[i][j] == "Q01")
				{
					R++;
					break;
				}
				else
				{
					break;
				}
			}

		}

		for (int i = a + 1, j = b + 1; i < 8 && j < 8; i++, j++)
		{
			if (pnn->C[i][j] == "-")
			{
				if (pnn->C[i][j] == "F1" || pnn->C[i][j] == "Q1" || pnn->C[i][j] == "Q01")
				{
					R++;
					break;
				}
				else
				{
					break;
				}
			}

		}

		for (int i = a + 1, j = b - 1; i < 8 && j >= 0; i++, j--)
		{
			if (pnn->C[i][j] != "-")
			{
				if (pnn->C[i][j] == "F1" || pnn->C[i][j] == "Q1" || pnn->C[i][j] == "Q01")
				{
					R++;
					break;
				}
				else
				{
					break;
				}
			}
		}
		/////////////////////////////////////

		// H
		if (pnn->C[a - 1][b + 2] == "H1" || pnn->C[a - 1][b - 2] == "H1" || pnn->C[a + 1][b + 2] == "H1" || pnn->C[a + 1][b - 2] == "H1" ||
			pnn->C[a - 2][b - 1] == "H1" || pnn->C[a - 2][b + 1] == "H1" || pnn->C[a + 2][b - 1] == "H1" || pnn->C[a + 2][b + 1] == "H1")
		{
			R++;
		}

		if (R > 0)
		{
			ct++;
		}
		
		
	}

	return ct;
}

void ExpandChildren(CNode* pCurr, CStack& S, CList& Results, int& C, int& SN)
{
	int Result = 1;
	int Result2 = 1;
	int L = 2;
	C = 0;
	//Visit.Attach(pCurr);

	for (int a = 0; a < 8; a++)
	{
		//-------------------------------------//
		  CNode* pnn = new CNode;
		  for (int r = 0; r < 8; r++)
		{
			for (int c = 0; c < 8; c++)
			{
				pnn->C[r][c] = pCurr->C[r][c];
				pnn->C[r][c] = pCurr->C[r][c];
			}
		}
		  pnn->pNext = NULL;
		//-------------------------------------//

		for (int b = 0; b < 8; b++)
		{
			//-----------------------------------//
			  pnn = new CNode;
			  for (int r = 0; r < 8; r++)
			{
				for (int c = 0; c < 8; c++)
				{
					pnn->C[r][c] = pCurr->C[r][c];
					pnn->C[r][c] = pCurr->C[r][c];
				}
			}
			  pnn->pNext = NULL;
			//----------------------------------//

			  if (pnn->C[a][b] == "-")
			  {
				  L = 0;
				  L = Checkalive(pnn, a, b);

				  if (L == 1)
				  {
					  pnn->C[a][b] = "Q01";
					  Display(pnn);
					  cout << " (Q01) ARE ALIVE :)" << endl;
					  cout << "_______________________________________________________________________________________________________" << endl << endl;
					  L = 0;
					  for (int i = 0; i < 8; i++)
					  {
						  //-----------------------------------------//
						  CNode* pnn2 = new CNode;
						  for (int r = 0; r < 8; r++)
						  {
							  for (int c = 0; c < 8; c++)
							  {
								  pnn2->C[r][c] = pnn->C[r][c];
								  pnn2->C[r][c] = pnn->C[r][c];
							  }
						  }
						  pnn2->pNext = NULL;
						  //----------------------------------------//

						  for (int j = 0; j < 8; j++)
						  {
							  //------------------------------------//
							  pnn2 = new CNode;
							  for (int r = 0; r < 8; r++)
							  {
								  for (int c = 0; c < 8; c++)
								  {
									  pnn2->C[r][c] = pnn->C[r][c];
									  pnn2->C[r][c] = pnn->C[r][c];
								  }
							  }
							  pnn2->pNext = NULL;
							  //-----------------------------------//

							  if (pnn2->C[i][j] == "-")
							  {
								  L = 0;
								  L = Checkalive(pnn2, i, j);
								  if (L == 1)
								  {
									  pnn2->C[i][j] = "T01";
									  Display(pnn2);
									  L = 0;
									  cout << " (T01) ARE ALIVE :)" << endl;
									  int X = CheckKingIsAlive(pnn2);
									  if (X >= 8)
									  {
										  SN++;
										  Results.Attach(pnn2);
										  cout << "----------------------------------------MABROOOOOOOOK!!!!!!!!!!!!!!------------------------------------" << endl << endl;
										 
									  }
									  cout << "_______________________________________________________________________________________________________" << endl << endl;
									

								  }
								  else
								  {
									  pnn2->C[i][j] = "()";
									  Display(pnn2);
									  cout << " (T01) CANNOT LIVE HERE :(" << endl;
									  cout << "_______________________________________________________________________________________________________" << endl << endl;
									  pnn2->C[i][j] = "-";
								  }

							  }
						  }
					  }
				  }
				  else
				  {
					  pnn->C[a][b] = "()";
					  Display(pnn);
					  cout << " (Q01) CANNOT LIVE HERE :(" << endl;
					  cout << "_______________________________________________________________________________________________________" << endl << endl;
					  pnn->C[a][b] = "-";
				  }
			  }
			
			
		}
	}
}

void BackTrack(int& SN, CList& Results)
{
	CStack S;
	CNode* pnn = CreateInitState();
	S.Push(pnn);
	cout << endl;
	Display(pnn);
	cout << "_______________________________________________________________________________________________________" << endl << endl;
	int C = 0;
	int R = 0;
	
	while (S.pHead != NULL)
	{
		CNode* pCurr = S.Pop();
		ExpandChildren(pCurr, S, Results, C, SN);
	}
}


void main()
{
	int SN = 0;
	int S = 0;
	CList Results;
	BackTrack(SN, Results);
	cout << "\n-------------------------------------------------------------------------------------------------------\n";
	cout << "\t\t\t\t\t  The Solutions (" << SN << ")\n";
	cout << "\n-------------------------------------------------------------------------------------------------------\n\n";
	CNode* pTrav = Results.pHead;
	while (pTrav != NULL)
	{
		S++;
		for (int i = 0; i < 8; i++)
		{
			cout << " ";
			for (int j = 0; j < 8; j++)
			{
				cout << pTrav->C[i][j] << " ";
			}
			cout << endl;
		}

		cout << endl << " Solution number " << S << endl;
		cout << "_______________________________________________________________________________________________________" << endl << endl;
		pTrav = pTrav->pNext;
	}
	cout << "\n-------------------------------------------------------------------------------------------------------Number of solutions (" << SN <<")";
	cout << "\n\n\n";
	system("pause");
}

