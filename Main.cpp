#include "main.h"

// �Ϸ���
// pfIn1: ��߼�
void FractalUp(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    pfOut[1] = 0;
    pfOut[2] = 0;
    pfOut[3] = 0;
    for (int i = 4; i < nCount; i++)
    {
        pfOut[i] = 0;
        if (pfIn1[i - 4] <= pfIn1[i - 2] && pfIn1[i - 3] <= pfIn1[i - 2] && pfIn1[i - 2] > pfIn1[i - 1] && pfIn1[i - 2] > pfIn1[i])
        {
            pfOut[i - 2] = pfIn1[i - 2];
        }
    }
}

// �·���
// pfIn1: ��ͼ�
void FractalDown(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    pfOut[1] = 0;
    pfOut[2] = 0;
    pfOut[3] = 0;
    for (int i = 4; i < nCount; i++)
    {
        pfOut[i] = 0;
        if (pfIn1[i - 4] >= pfIn1[i - 2] && pfIn1[i - 3] >= pfIn1[i - 2] && pfIn1[i - 2] < pfIn1[i - 1] && pfIn1[i - 2] < pfIn1[i])
        {
            pfOut[i - 2] = pfIn1[i - 2];
        }
    }
}

// ��������
// pfIn1: ƽ����, pfIn2: �Ϸ����ź�, pfIn3: ���̼�
void FractalBuy(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    int nBuyPosition = 0;
    pfOut[0] = 0;
    pfOut[1] = 0;
    pfOut[2] = 0;
    pfOut[3] = 0;
    pfOut[4] = 0;
    for (int i = 5; i < nCount; i++)
    {
        pfOut[i] = 0;
        int j = i - 1;
        for (; j >= 0; j--)
        {
            if (pfIn2[j] > 0)
            {
                break;
            }
        }
        if (j >= 0)
        {
            if (pfIn3[i] > pfIn2[j] && pfIn3[i] > pfIn1[i] && (pfIn3[i - 1] <= pfIn2[j] || pfIn3[i - 1] <= pfIn1[j]))
            {
                pfOut[i] = 1;
                if (nBuyPosition == 0)
                {
                    nBuyPosition = 1;
                }
            }
        }
        if (nBuyPosition == 1)
        {
            if (pfOut[i] == 0)
            {
                pfOut[i] = 2;
            }
            if (pfIn3[i] < pfIn1[i] && pfIn3[i - 1] >= pfIn1[i - 1])
            {
                pfOut[i] = -1;
                nBuyPosition = 0;
            }
        }
    }
}

// ��������
// pfIn1: ƽ���ߣ�pfIn2: �·����źţ�pfIn3: ���̼�
void FractalSell(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    int nSellPosition = 0;
    pfOut[0] = 0;
    pfOut[1] = 0;
    pfOut[2] = 0;
    pfOut[3] = 0;
    pfOut[4] = 0;
    for (int i = 5; i < nCount; i++)
    {
        pfOut[i] = 0;
        int j = i - 1;
        for (; j >= 0; j--)
        {
            if (pfIn2[j] > 0)
            {
                break;
            }
        }
        if (j >= 0)
        {
            if (pfIn3[i] < pfIn2[j] && pfIn3[i] < pfIn1[i] && (pfIn3[i - 1] >= pfIn2[j] || pfIn3[i - 1] >= pfIn1[j]))
            {
                pfOut[i] = 1;
                if (nSellPosition == 0)
                {
                    nSellPosition = 1;
                }
            }
        }
        if (nSellPosition == 1)
        {
            if (pfOut[i] == 0)
            {
                pfOut[i] = 2;
            }
            if (pfIn3[i] > pfIn1[i] && pfIn3[i - 1] <= pfIn1[i - 1])
            {
                pfOut[i] = -1;
                nSellPosition = 0;
            }
        }
    }
}

// AO�Ӳ��źŵĻ�׼�۸�
// pfIn1: FractalBuy, pfIn2: AO, pfIn3: ��߼�
void AoBuyPrice(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    pfOut[1] = 0;
    for (int i = 2; i < nCount; i++)
    {
        pfOut[i] = pfOut[i - 1];
        if (pfIn1[i] >= 1)
        {
            // ��������۸�
            if (pfIn2[i - 2] > 0 && pfIn2[i - 1] > 0 && pfIn2[i] > 0 && pfIn2[i - 2] > pfIn2[i - 1] && pfIn2[i - 1] < pfIn2[i])
            {
                pfOut[i] = pfIn3[i];
            }
            // ��Խ����۸�
            if (pfIn2[i - 1] < 0 && pfIn2[i] > 0)
            {
                pfOut[i] = pfIn3[i];
            }
            // ˫������۸�
            int peek1 = 0;
            if (pfIn2[i - 2] < 0 && pfIn2[i - 1] < 0 && pfIn2[i] < 0 && pfIn2[i - 2] > pfIn2[i - 1] && pfIn2[i - 1] < pfIn2[i])
			{
				peek1 = i - 1;
			}
			int peek2 = 0;
            if (peek1 > 0)
            {
                for (int j = peek1 - 2; j >= 0; j--)
                {
                    if (j >= 2)
                    {
                        if (pfIn2[j - 2] >= 0 || pfIn2[j - 1] >= 0 || pfIn2[j] >= 0)
                        {
                            break;
                        }
                        if (pfIn2[j - 2] > pfIn2[j - 1] && pfIn2[j - 1] < pfIn2[j])
                        {
                            peek2 = j - 1;
                            break;
                        }
                    }
                }
            }
            if (peek1 > 0 && peek2 > 0 && pfIn2[peek1] > pfIn2[peek2])
            {
                pfOut[i] = pfIn3[i];
            }
        }
        else if (pfIn1[i] == -1)
        {
            pfOut[i] = 0;
        }
    }
}

// AO�Ӳ��ź�
// pfIn1: FractalBuy, pfIn2: AoBuyPrice, pfIn3: C
void AoBuy(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    for (int i = 1; i < nCount; i++)
    {
        pfOut[i] = 0;
        if (pfIn1[i] >= 1)
        {
            if (pfIn3[i - 1] <= pfIn2[i - 1] && pfIn3[i] > pfIn2[i])
            {
                pfOut[i] = 1;
            }
        }
    }
}

// AO�Ӳ��źŵĻ�׼�۸�
// pfIn1: FractalSell, pfIn2: AO, pfIn3: L
void AoSellPrice(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    pfOut[1] = 0;
    for (int i = 2; i < nCount; i++)
    {
        pfOut[i] = pfOut[i - 1];
        if (pfIn1[i] >= 1)
        {
            // ���������۸�
            if (pfIn2[i - 2] < 0 && pfIn2[i - 1] < 0 && pfIn2[i] < 0 && pfIn2[i - 2] < pfIn2[i - 1] && pfIn2[i - 1] > pfIn2[i])
            {
                pfOut[i] = pfIn3[i];
            }
            // ��Խ�����۸�
            if (pfIn2[i - 1] > 0 && pfIn2[i] < 0)
            {
                pfOut[i] = pfIn3[i];
            }
            // ˫�������۸�
            int peek1 = 0;
            if (pfIn2[i - 2] > 0 && pfIn2[i - 1] > 0 && pfIn2[i] > 0 && pfIn2[i - 2] < pfIn2[i - 1] && pfIn2[i - 1] > pfIn2[i])
			{
				peek1 = i - 1;
			}
			int peek2 = 0;
            if (peek1 > 0)
            {
                for (int j = peek1 - 2; j >= 0; j--)
                {
                    if (j >= 2)
                    {
                        if (pfIn2[j - 2] <= 0 || pfIn2[j - 1] <= 0 || pfIn2[j] <= 0)
                        {
                            break;
                        }
                        if (pfIn2[j - 2] < pfIn2[j - 1] && pfIn2[j - 1] > pfIn2[j])
                        {
                            peek2 = j - 1;
                            break;
                        }
                    }
                }
            }
            if (peek1 > 0 && peek2 > 0 && pfIn2[peek1] < pfIn2[peek2])
            {
                pfOut[i] = pfIn3[i];
            }
        }
        else if (pfIn1[i] == -1)
        {
            pfOut[i] = 0;
        }
    }
}

// AO�Ӳ��ź�
// pfIn1: FractalSell, pfIn2: AoSellPrice, pfIn3: C
void AoSell(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    for (int i = 1; i < nCount; i++)
    {
        pfOut[i] = 0;
        if (pfIn1[i] >= 1)
        {
            if (pfIn3[i - 1] >= pfIn2[i - 1] && pfIn3[i] < pfIn2[i])
            {
                pfOut[i] = 1;
            }
        }
    }
}

// AC�Ӳ��źŵĻ�׼�۸�
// pfIn1: FractalBuy, pfIn2: AC, pfIn3: ��߼�
void AcBuyPrice(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    pfOut[1] = 0;
    pfOut[2] = 0;
    for (int i = 3; i < nCount; i++)
    {
        pfOut[i] = pfOut[i - 1];
        if (pfIn1[i] >= 1)
        {
            if (pfIn2[i - 3] > 0 && pfIn2[i - 2] > 0 && pfIn2[i - 1] > 0 && pfIn2[i] > 0 && pfIn2[i - 3] > pfIn2[i - 2] && pfIn2[i - 2] < pfIn2[i - 1] && pfIn2[i - 1] < pfIn2[i])
            {
                pfOut[i] = pfIn3[i];
            }
            if (i > 3 && pfIn2[i - 4] < 0 && pfIn2[i - 3] < 0 && pfIn2[i - 2] < 0 && pfIn2[i - 1] < 0 && pfIn2[i] < 0 && pfIn2[i - 4] > pfIn2[i - 3] && pfIn2[i - 3] < pfIn2[i - 2] && pfIn2[i - 2] < pfIn2[i - 1] && pfIn2[i - 1] < pfIn2[i])
            {
                pfOut[i] = pfIn3[i];
            }
            if (pfIn2[i - 3] < 0 && pfIn2[i - 2] < 0 && pfIn2[i - 1] < 0 && pfIn2[i] > 0 && pfIn2[i - 3] > pfIn2[i - 2] && pfIn2[i - 2] < pfIn2[i - 1] && pfIn2[i - 1] < pfIn2[i])
            {
                pfOut[i] = pfIn3[i];
            }
        }
        else if (pfIn1[i] == -1)
        {
            pfOut[i] = 0;
        }
    }
}

// Ac�Ӳ��ź�
// pfIn1: FractalBuy, pfIn2: AcBuyPrice, pfIn3: C
void AcBuy(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    for (int i = 1; i < nCount; i++)
    {
        pfOut[i] = 0;
        if (pfIn1[i] >= 1)
        {
            if (pfIn3[i - 1] <= pfIn2[i - 1] && pfIn3[i] > pfIn2[i])
            {
                pfOut[i] = 1;
            }
        }
    }
}

// AC�Ӳ��źŵĻ�׼�۸�
// pfIn1: FractalSell, pfIn2: AC, pfIn3: ��ͼ�
void AcSellPrice(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    pfOut[1] = 0;
    pfOut[2] = 0;
    for (int i = 3; i < nCount; i++)
    {
        pfOut[i] = pfOut[i - 1];
        if (pfIn1[i] >= 1)
        {
            if (pfIn2[i - 3] < 0 && pfIn2[i - 2] < 0 && pfIn2[i - 1] < 0 && pfIn2[i] < 0 && pfIn2[i - 3] < pfIn2[i - 2] && pfIn2[i - 2] > pfIn2[i - 1] && pfIn2[i - 1] > pfIn2[i])
            {
                pfOut[i] = pfIn3[i];
            }
            if (i > 3 && pfIn2[i - 4] > 0 && pfIn2[i - 3] > 0 && pfIn2[i - 2] > 0 && pfIn2[i - 1] > 0 && pfIn2[i] > 0 && pfIn2[i - 4] < pfIn2[i - 3] && pfIn2[i - 3] > pfIn2[i - 2] && pfIn2[i - 2] > pfIn2[i - 1] && pfIn2[i - 1] > pfIn2[i])
            {
                pfOut[i] = pfIn3[i];
            }
            if (pfIn2[i - 3] > 0 && pfIn2[i - 2] > 0 && pfIn2[i - 1] > 0 && pfIn2[i] < 0 && pfIn2[i - 3] < pfIn2[i - 2] && pfIn2[i - 2] > pfIn2[i - 1] && pfIn2[i - 1] > pfIn2[i])
            {
                pfOut[i] = pfIn3[i];
            }
        }
        else if (pfIn1[i] == -1)
        {
            pfOut[i] = 0;
        }
    }
}

// Ac�Ӳ��ź�
// pfIn1: FractalSell, pfIn2: AcSellPrice, pfIn3: C
void AcSell(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    for (int i = 1; i < nCount; i++)
    {
        pfOut[i] = 0;
        if (pfIn1[i] >= 1)
        {
            if (pfIn3[i - 1] >= pfIn2[i - 1] && pfIn3[i] < pfIn2[i])
            {
                pfOut[i] = 1;
            }
        }
    }
}

// ƽ���߻�׼�۸�
// pfIn1: FractalBuy, pfIn2: H, pfIn3: C
void BalanceBuy(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    for (int i = 1; i < nCount; i++)
    {
        pfOut[i] = 0;
        if (pfIn1[i] >= 1)
        {
            int base = i;
            int j;
		    for (j = i - 1; j >= 0; j--)
		    {
			    if (pfIn2[j] <= pfIn2[base])
			    {
				    // ǰһ���۸�����߼۸��͵Ļ���׼��ǰ��
				    base = j;
			    }
			    else if (pfIn2[j] > pfIn2[base])
			    {
				    // �Ѿ��ҵ���׼��
				    break;
			    }
		    }
		    if (pfIn3[i - 1] <= pfIn2[j] && pfIn3[i] > pfIn2[j])
            {
                pfOut[i] = 1;
            }
        }
    }
}

// ƽ���߻�׼�۸�
// pfIn1: FractalSell, pfIn2: L, pfIn3: C
void BalanceSell(int nCount, float *pfOut, float *pfIn1, float *pfIn2, float *pfIn3)
{
    pfOut[0] = 0;
    for (int i = 1; i < nCount; i++)
    {
        pfOut[i] = 0;
        if (pfIn1[i] >= 1)
        {
            int base = i;
            int j;
		    for (j = i - 1; j >= 0; j--)
		    {
			    if (pfIn2[j] >= pfIn2[base])
			    {
				    // ǰһ���۸�����߼۸��͵Ļ���׼��ǰ��
				    base = j;
			    }
			    else if (pfIn2[j] < pfIn2[base])
			    {
				    // �Ѿ��ҵ���׼��
				    break;
			    }
		    }
		    if (pfIn3[i - 1] >= pfIn2[j] && pfIn3[i] < pfIn2[j])
            {
                pfOut[i] = 1;
            }
        }
    }
}

static PluginTCalcFuncInfo Info[] =
{
    {   1, (pPluginFUNC)&FractalUp              },
    {   2, (pPluginFUNC)&FractalDown            },
    {   3, (pPluginFUNC)&FractalBuy             },
    {   4, (pPluginFUNC)&FractalSell            },
    {   5, (pPluginFUNC)&AoBuyPrice             },
    {   6, (pPluginFUNC)&AoBuy                  },
    {   7, (pPluginFUNC)&AoSellPrice            },
    {   8, (pPluginFUNC)&AoSell                 },
    {   9, (pPluginFUNC)&AcBuyPrice             },
    {  10, (pPluginFUNC)&AcBuy                  },
    {  11, (pPluginFUNC)&AcSellPrice            },
    {  12, (pPluginFUNC)&AcSell                 },
    {  13, (pPluginFUNC)&BalanceBuy             },
    {  14, (pPluginFUNC)&BalanceSell            },
    {   0,  NULL                                }
};

BOOL RegisterTdxFunc(PluginTCalcFuncInfo **pInfo)
{
    if (*pInfo == NULL)
    {
        *pInfo = Info;
        return TRUE;
    }
    return FALSE;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}
