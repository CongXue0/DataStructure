#include "classicalgorithm_part1.h"
#include <string.h>
#include "src/utils/tool.h"

/*
最长公共子序列(Longest common subsequence)
最长公共子序列的问题常用于解决字符串的相似度，是一个非常实用的算法。
解决方法：动态规划
最长公共子序列问题的子问题的解是可以重复使用的，也就是说，更高级别的子问题通常会重用低级子问题的解。拥有这个两个属性的问题可以使用动态规划算法来解决，这样子问题的解就可以被储存起来，而不用重复计算。这个过程需要在一个表中储存同一级别的子问题的解，因此这个解可以被更高级的子问题使用
1. 构建辅助数组lcsBuf，lcsBuf[i][j] 表示 strA[0]~strA[i - 1]的字串和strB[0]-strB[j - 1]的字串的LCS长度
2. 通过lcsBuf从后往前递推LCS
时间复杂度：构建矩阵我们花费了O(MN)的时间，回溯时我们花费了O（M+N)的时间，两者相加最终我们花费了O(MN)的时间。
空间复杂度：构建矩阵我们花费了O(MN)的空间，标记函数也花费了O(MN)的空间，两者相加最终我们花费了O(MN)的空间。
*/
char *p000_longestCommonSubsequence(const char *strA, const char *strB, char *retBuf)
{
    int i, j, lcsMaxLen;
    int lena = strlen(strA), lenb = strlen(strB);
    if (lena == 0 || lenb == 0)
    {
        retBuf[0] = '\0';
        return retBuf;
    }
    int **lcsBuf = new int *[lena + 1];
    for (i = 0; i <= lena; i++)
    {
        lcsBuf[i] = new int[lenb + 1];
    }
    for (i = 0; i <= lena; i++)
        lcsBuf[i][0] = 0;
    for (i = 0; i <= lenb; i++)
        lcsBuf[0][i] = 0;

    for (i = 1; i <= lena; i++)
    {
        for (j = 1; j <= lenb; j++)
        {
            if (strA[i - 1] == strB[j - 1])//遇到相同的字符，LCS长度加1
            {
                lcsBuf[i][j] = lcsBuf[i - 1][j - 1] + 1;
            }
            else//遇到不同的字符，LCS长度从左边和上边一个LCS中选出最大者
            {
                lcsBuf[i][j] = (lcsBuf[i - 1][j] >= lcsBuf[i][j - 1] ? lcsBuf[i - 1][j] : lcsBuf[i][j - 1]);
            }
        }
    }
    lcsMaxLen = lcsBuf[lena][lenb];//lcsMaxLen就是LCS的最大长度

    retBuf[lcsMaxLen--] = '\0';
    i = lena, j = lenb;
    while (lcsMaxLen >= 0)
    {
        if (strA[i - 1] == strB[j - 1])//相等字符时加入子序列
        {
            retBuf[lcsMaxLen--] = strA[i - 1];
            i--, j--;
        }
        else
        {
            if (lcsBuf[i - 1][j] >= lcsBuf[i][j - 1])//不相等字符时往左边和上边中较大方向移动
            {
                i--;
            }
            else
            {
                j--;
            }
        }
    }

    for (i = 0; i <= lena; i++)
    {
        delete[] lcsBuf[i];
    }
    delete[] lcsBuf;

    return retBuf;
}
void ClassicAlgorithm_Part1::practice_000()
{
    char retBuf[300];
    DEBUG<<p000_longestCommonSubsequence("abbecij", "aceefg", retBuf);
    DEBUG<<p000_longestCommonSubsequence("acgbfhk", "cegefkh", retBuf);
    DEBUG<<p000_longestCommonSubsequence("cegefkh", "acgbfhk", retBuf);
}

/*
最长公共子串(Longest common substring)
*/
char *p001_longestCommonSubstring(const char *strA, const char *strB, char *retBuf)
{
    int k, i, j, d, starta, startb, longestLen = 0;
    int lena = strlen(strA), lenb = strlen(strB);
    if (lena == 0 || lenb == 0)
    {
        retBuf[0] = '\0';
        return retBuf;
    }

    int maxLen = (lena < lenb ? lena : lenb);//公共字串的自大长度等于两个字符串中较短者
    for (k = -(lenb - 1); k < lena; k++)//以滑动方式查找
    {
        i = (k < 0 ? 0 : k), j = (k < 0 ? (-k) : 0);
        d = 0;
        while (i < lena && j < lenb)
        {
            if (strA[i] == strB[j])
            {
                d++;
                if (d > longestLen)
                {
                    longestLen = d;
                    starta = i - d + 1;
                    startb = j - d + 1;
                    if (longestLen == maxLen)
                        break;
                }
            }
            else
                d = 0;
            i++, j++;
        }
        if (longestLen == maxLen)
            break;
    }
    for (i = 0; i < longestLen; i++)
        retBuf[i] = strA[starta + i];
    retBuf[i] = '\0';
    return retBuf;
}
void ClassicAlgorithm_Part1::practice_001()
{
    char retBuf[300];
    DEBUG<<p001_longestCommonSubstring("adabcdw", "acabcfg", retBuf);
    DEBUG<<p001_longestCommonSubstring("aasdw", "", retBuf);
    DEBUG<<p001_longestCommonSubstring("apple", "apple", retBuf);
    DEBUG<<p001_longestCommonSubstring("awdwaw", "92d8d", retBuf);
}
