#include "chapter3_part1.h"
#include "src/utils/tool.h"
#include "src/03_String/mystring.h"

/*
串demo1
*/
String string_test1()
{
    String tmp;
    tmp.append('c');
    tmp.append('o');
    tmp.append('n');
    DEBUG<<"tmp:"<<tmp;
    tmp.append('g');
    return tmp;
}
void Chapter3_Part1::practice_000()
{
//    String s1;
//    String s2 = "apple";
//    String s3 = s2;//调用拷贝构造
//    String s4 = std::move(string_test1());//调用移动拷贝构造，在有左常引用拷贝构造的时候，移动拷贝会很少调用，除非用move函数转成右引用

//    String s4 = string_test1().append('y');
//    s4.append('x');

//    String s4;
//    s4 = string_test1();//调用移动赋值

//    String s5;
//    s5.append('c');
//    s5.append('o');
//    s5.append('n');
//    s5.append('g');

//    DEBUG<<"s1:"<<s1<<", ref:"<<s1.getRefCount()<<", len:"<<s1.length();
//    DEBUG<<"s2:"<<s2<<", ref:"<<s2.getRefCount()<<", len:"<<s2.length();
//    DEBUG<<"s3:"<<s3<<", ref:"<<s3.getRefCount()<<", len:"<<s3.length();

//    DEBUG<<"s4:"<<s4<<", ref:"<<s4.getRefCount()<<", len:"<<s4.length();
//    DEBUG<<"s5:"<<s5<<", ref:"<<s5.getRefCount()<<", len:"<<s5.length();

    String s6 = "apple";//调用构造2 const char *
    DEBUG<<s6;
    s6 = "ubyvy";//先用构造2生成匿名对象，再用移动赋值
    DEBUG<<s6;
}

/*
串demo2
*/
void Chapter3_Part1::practice_001()
{
    String str;
    DEBUG<<str.isEmpty();
    str.insert(0, String("789"));
    DEBUG<<str.isEmpty();
    DEBUG<<str[0];
    DEBUG<<str[2];
    DEBUG<<str.prepend("111");
    DEBUG<<str.at(1);
    DEBUG<<str.fill('c');
    DEBUG<<str.capacity();
    str.resize(50);
    DEBUG<<str.capacity();
    DEBUG<<str;
    String str2 = "13bdu283gtbd21BDss";
    str.swap(str2);
    DEBUG<<str;
    DEBUG<<str2;
    DEBUG<<"--------------------------";
    DEBUG<<str.indexOf('D', 0, true);
    DEBUG<<str.indexOf('D', 0, false);
    DEBUG<<str.indexOf('e');
    DEBUG<<str.indexOf("");
    DEBUG<<str.indexOf("bD", 0, true);
    DEBUG<<str.indexOf("BD", 0, true);
    DEBUG<<str.indexOf("bD", 0, false);
    DEBUG<<str.indexOf(String());
    DEBUG<<str.indexOf(String("bD"), 0, true);
    DEBUG<<str.indexOf(String("BD"), 0, true);
    DEBUG<<str.indexOf(String("bD"), 0, false);
    DEBUG<<"--------------------------";
    DEBUG<<str.lastIndexOf("");
    DEBUG<<str.lastIndexOf("bD", 0, true);
    DEBUG<<str.lastIndexOf("BD", 0, true);
    DEBUG<<str.lastIndexOf("bD", 0, false);
    DEBUG<<str.lastIndexOf(String());
    DEBUG<<str.lastIndexOf(String("bD"), 0, true);
    DEBUG<<str.lastIndexOf(String("BD"), 0, true);
    DEBUG<<str.lastIndexOf(String("bD"), 0, false);
    DEBUG<<str.contains('S', true);
    DEBUG<<str.contains('S', false);
    DEBUG<<str.contains("21bd", true);
    DEBUG<<str.contains("21bd", false);
    DEBUG<<str.contains(String("21bd"), true);
    DEBUG<<str.contains(String("21bd"), false);
    DEBUG<<"--------------------------";
    DEBUG<<str.left(6);
    DEBUG<<str.right(6);
    DEBUG<<str.mid(6);
    DEBUG<<str.mid(6, 4);
    DEBUG<<str.startsWith("13bdU", true);
    DEBUG<<str.startsWith("13bdU", false);
    DEBUG<<str.endsWith("21BDSS", true);
    DEBUG<<str.endsWith("21BDSS", false);
    DEBUG<<str.compare("13bdu284");
    DEBUG<<str.compare("13bdu283");
    DEBUG<<str.compare(String("13bdu284"));
    DEBUG<<str.compare(String("13bdu283"));
    DEBUG<<str.toLower();
    DEBUG<<str.toUpper();
    str.prepend(" \n  ");
    DEBUG<<str.trimmed();
    DEBUG<<"--------------------------";
    str = "1234";
    DEBUG<<str;
    bool ret;
    DEBUG<<str.toShort(&ret);
    DEBUG<<ret;
    DEBUG<<str.toUShort();
    DEBUG<<str.toInt();
    DEBUG<<str.toUInt();
    DEBUG<<str.toLong();
    DEBUG<<str.toULong();
    DEBUG<<str.toLongLong();
    DEBUG<<str.toULongLong();
    str = "3.1415926";
    DEBUG<<str.toFloat();
    DEBUG<<str.toDouble();
    str = "1010";
    DEBUG<<str.toInt(NULL, 2);
    DEBUG<<"--------------------------";
    str = "12d";
    DEBUG<<str.insert(1, 'a');
    DEBUG<<str.insert(2, "hehe", 2);
    DEBUG<<str.insert(3, String("kk"));
    DEBUG<<str.append('e');
    DEBUG<<str.append("r");
    DEBUG<<str.append(String("Q"));
    DEBUG<<str.prepend('A');
    DEBUG<<str.prepend("T");
    DEBUG<<str.prepend(String("V"));
    DEBUG<<str.remove(5, 2);
    DEBUG<<str.remove('q', false);
    DEBUG<<str.remove("V");
    DEBUG<<str.replace(2, 2, 's');
    DEBUG<<str.replace(2, 2, "apple");
    DEBUG<<str.replace(2, 2, "haha");
    DEBUG<<str.replace('a', 'v');
    DEBUG<<str.replace("hv", 2, "qwer", 3);
    DEBUG<<str.replace(String("qwe"), String("poi"));
    DEBUG<<str.setNum(255, 2);
    DEBUG<<str.setNum(3.1415926);
    DEBUG<<str.toDouble();
    DEBUG<<str.setNum(1564412.223);
    DEBUG<<str.toDouble();
    DEBUG<<"--------------------------";
    str = "aBcDeFg";
    DEBUG<<(str == "aBcDeFg");
    DEBUG<<("aBcDeFG" == str);
    DEBUG<<(str == String("aBcDeFg"));
    DEBUG<<(String("aBcDeFG") == str);
    DEBUG<<(str > "aBcDeFg");
    DEBUG<<("aBcDeFG" < str);
    DEBUG<<(str > String("aBcDeFg"));
    DEBUG<<(String("aBcDeFG") < str);
    DEBUG<<(str >= "aBcDeFG");
    DEBUG<<("aBcDeFa" >= str);
    DEBUG<<(str >= String("aBcDeFG"));
    DEBUG<<(String("aBcDeFa") >= str);
    DEBUG<<(str > "aBcDeF");
    DEBUG<<(String("aBcDeF") > str);
    DEBUG<<"--------------------------";
    str.clear();
    DEBUG<<str;
    DEBUG<<(str += 'c');
    DEBUG<<(str += "NN");
    DEBUG<<(str += str);
    DEBUG<<("lost" + str + "hap");

}

/*
串demo3
*/
void Chapter3_Part1::practice_002()
{
    String str1 = " ewd wd w2s21 dw3";
    StringList list1 = str1.split(' ');
    DEBUG<<list1.getLength();
    for (int i = 0; i < list1.getLength(); i++)
        DEBUG<<list1.at(i);
    StringList list2 = list1;
    DEBUG<<list2.getLength();
    for (int i = 0; i < list2.getLength(); i++)
        DEBUG<<list2.at(i);
}

/*
KMP算法
*/
/*
暴力匹配
*/
int match_normal(const char *s, int low, int high, const char *t, int tlen)
{
    int i = low, j = 0;
    while (i <= high && j < tlen)
    {
        if (s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == tlen)
        return i - tlen;
    else
        return -1;
}

/*
Knuth-Morris-Pratt 字符串查找算法，简称为 “KMP算法”，常用于在一个文本串S内查找一个模式串P 的出现位置，这个算法由Donald Knuth、Vaughan Pratt、James H. Morris三人于1977年联合发表，故取这3人的姓氏命名此算法。
next数组由初始位置-1（i等于0），和相同前缀的下一个位置组成
例如：abvabc，c位置的相同前缀是v，所以next[5]=2，没有相同位置next[i]=0
匹配的时候，遇到不相同的位置，匹配位置j退回到与i相同的前缀位置继续比对，如果j退回到-1，说明该位置i与j没有相同前缀，之后i++ j++，继续比对
*/
int match_KMP1(const char *s, int low, int high, const char *t, int tlen)
{
    static int *next = nullptr;
    static int nextLen = 128;
    if (nextLen < tlen)
    {
        while (nextLen < tlen)
            nextLen = 2 * nextLen;
        if (next != NULL)
            delete next;
        next = new int[nextLen];
    }
    else
    {
        if (next == nullptr)
        {
            next = new int[nextLen];
        }
    }

    int i, j;
    i = 0, j = -1;
    next[0] = -1;
    while (i < tlen - 1)//生成next数组
    {
        if (j == -1 || t[i] == t[j])//从前往后递推数组
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];//减少相同前缀的长度，寻找更短的前缀是否能匹配的上，直到j等于-1，再次匹配 例:"aacvnaaax"
    }
//    i = 1, j = 0;
//    next[0] = -1;
//    while (i < tlen)//生成next数组
//    {
//        if (j == 0 || t[i] == t[j])
//        {
//            next[i] = j;
//            if (t[i] == t[j])
//            {
//                j++;
//            }
//            i++;
//        }
//        else
//        {
//            next[i] = j;
//            i++;
//            j = 0;
//        }
//    }
    DEBUG<<"next : "<<Tool::printArr(next, 0, tlen - 1);

    i = low, j = 0;
    while (i <= high && j < tlen)
    {
        if (j == -1 || s[i] == t[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];//回到相同前缀处如果j>0，说明i与j位置有相同的前缀
    }
    if (j == tlen)
        return i - tlen;
    else
        return -1;
}

/*
改进版KMP算法，区别在于next数组不同
例子：模式串"abcabcabc" 如果在 匹配 "xxabcabcabvxw" 时在v位置不匹配，j会从8回到5再回到2，再到-1，
    因为t的8 5 2的字符都相同，再次匹配还是失败，所以只需一步即可，具体在next数组生成时与之前不同
如果当前i==j，next[i]沿用之前的next[j]；如果当前i!=j，next[i]取累计的j
*/
int match_KMP2(const char *s, int low, int high, const char *t, int tlen)
{
    static int *next = nullptr;
    static int nextLen = 128;
    if (nextLen < tlen)
    {
        while (nextLen < tlen)
            nextLen = 2 * nextLen;
        if (next != NULL)
            delete next;
        next = new int[nextLen];
    }
    else
    {
        if (next == nullptr)
        {
            next = new int[nextLen];
        }
    }

    int i, j;
    i = 0, j = -1;
    next[0] = -1;
    while (i < tlen - 1)//生成next数组
    {
        if (j == -1 || t[i] == t[j])//从前往后递推数组
        {
            i++;
            j++;
            //较之前next数组求法，改动在下面4行
            if (t[i] != t[j])
                next[i] = j; //之前只有这一行
            else
            //因为不能出现t[j] = t[ next[j ]]，所以当出现时需要继续递归，j = next[j] = next[next[j]]
                next[i] = next[j];
        }
        else
            j = next[j];//减少相同前缀的长度，寻找更短的前缀是否能匹配的上，直到j等于-1，再次匹配
    }
    DEBUG<<"next : "<<Tool::printArr(next, 0, tlen - 1);

    i = low, j = 0;
    while (i <= high && j < tlen)
    {
        if (j == -1 || s[i] == t[j])
        {
            i++;
            j++;
        }
        else
            j = next[j];//回到相同前缀处如果j>0，说明i与j位置有相同的前缀
    }
    if (j == tlen)
        return i - tlen;
    else
        return -1;
}
void Chapter3_Part1::practice_010()
{
//    const char *str = "abc2ddscabcabx10uddn";
    const char *str = "xxgbcabx10udabcabidn";
//    const char *str2 = "abcabx";
//    const char *str2 = "aaaccc";
//    const char *str2 = "abcabxvn";
//    const char *str2 = "aacvnaaax";
    const char *str2 = "abcwdabi";
    int index1 = match_KMP1(str, 0, strlen(str) - 1, str2, strlen(str2));
    int index2 = match_KMP2(str, 0, strlen(str) - 1, str2, strlen(str2));
    DEBUG<<"index1:"<<index1;
    DEBUG<<"index2:"<<index2;
}
