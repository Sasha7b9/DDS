#pragma once
#include "Display/Colors.h"


struct Text
{
    /*************** ����� ������ � ������� ������ **************************/


    static int DrawTextInColumnWithTransfersDiffColors(const int left, const int top, const int width, pString text, const Color colorDif, const Color = Color::NUMBER);

    // ������� ��������������� ����� � ������� ������� width. ��� ���� ����, ����������� � ������� �������, ��������� ������ color
    static int DrawFormatTextInColumnWithTransfersDiffColors(int x, int y, int width, Color color, pString text, ...);

    // ����� ������ ������ � ������ �������(x, y, width, height)������ ColorText �� �������������� � ������� ������� widthBorder ����� colorBackground
    static void DrawStringInCenterRectOnBackground(int x, int y, int width, int height, pString text, Color colorText, int widthBorder, Color colorBackground);
    
    static int DrawStringInCenterRectAndBoundIt(int x, int y, int width, int height, pString text, Color colorBackground, Color colorFill);

    static char *GetWord(const char *firstSymbol, int *length, char buffer[20]);

    // ���� draw == false, �� �������� ������ �� ����, ������ ������������ ������ ��� ����������
    static int DrawPartWord(char *word, int x, int y, int xRight, bool draw);

private:

    static uint *BreakWord(char *word);
    
    // ���������� ����� ����� �� ����� numSyllable(�����������) ������ �� ������ ��������
    static char *PartWordForTransfer(const char *word, const uint *lengthSyllables, int numSyllable, char buffer[30]);
    
    // \brief ������� ��������� �������. C letters ���������� ����� �����, ��� ����� ����� �������, � lettersInSyllable ����� �������� ����� ���� � 
    // ��������� �����. ���� ����� �����������, ������� ���������� false
    static bool FindNextTransfer(const char *letters, uint *lettersInSyllable);

    static bool IsConsonant(char symbol);

    static bool CompareArrays(const bool *array1, const bool *array2, int numElems);

private:
};


class Char
{
public:
    Char(char s) : symbol(s) { }
    int Draw(int x, int y, Color color = Color::NUMBER);
    void Draw4InRect(int x, int y, Color color = Color::NUMBER);
    void Draw2Horizontal(int x, int y, Color color = Color::NUMBER);
    bool IsLetter();
private:
    char symbol;
};


class BigChar
{
public:
    BigChar(char s, int _size) : symbol(s), size(_size) { }
    int Draw(int eX, int eY);
private:
    char symbol;
    int size;
};


class BigText
{
public:
    BigText(pString t, int s) : text(t), size(s) {}
    void Draw(int x, int y, Color color = Color::NUMBER);
private:
    pString text;
    int size;
};


struct TypeConversionString
{
    enum E
    {
        None,           // �������������� ������ �� ������������
        FirstUpper      // ������ ������ - � ������ ��������, ��������� - � ������
    };
};


class String // -V690
{
public:
    explicit String();
    String(const String &);
    explicit String(char symbol);
    explicit String(const char *format, ...);
    ~String();

    void Set(TypeConversionString::E conv, const char *format, ...);

    char *c_str() const;

    int Draw(int x, int y, Color color = Color::NUMBER) const;
    int DrawInCenterRect(int x, int y, int width, int height, Color color = Color::NUMBER);
    void DrawRelativelyRight(int xRight, int y, Color color = Color::NUMBER);
    void DrawInColumn(int x, int y, int width);
    // ���������� ������ ���������� ��������������
    int DrawInBoundedRectWithTransfers(int x, int y, int width, Color colorBack, Color colorRect, Color colorText);
    // ����� ����� � ����������
    int DrawInColumnWithTransfers(const int left, const int top, const int width, const Color color = Color::NUMBER);

    int Length() const;

    void Free();

    void Append(const char *str);

    void Append(const char *str, uint numSymbols);

    void Append(char symbol);
    // ������� numSymbols �� ������ ������
    void RemoveFromBegin(uint numSymbols);

    void RemoveFromEnd();

    uint Size() const;

    char &operator[](uint i);

private:

    char *buffer;

    bool Allocate(uint size);

    void Conversion(TypeConversionString::E conv);

    int DrawSubString(int x, int y, pString t);
    int DrawSpaces(int x, int y, pString t, int *numSymbols);
    // ���������� ������ ������, ������� ����� ����� text, ��� ������ �� left �� right � ���������� height. ���� bool == false, �� ����� �� ������ �� ����� 
    bool GetHeightTextWithTransfers(int left, int top, int right, int *height);
};
