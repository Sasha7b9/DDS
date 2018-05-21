#pragma once
#include "defines.h"
#include "Display/Colors.h"
#include "Display/DisplayTypes.h"


class Text
{
public:
    static void SetFont(TypeFont typeFont);

    static int DrawChar(int x, int y, char symbol, Color color = Color::NUMBER);

    static void Draw4SymbolsInRect(int x, int y, char eChar, Color color = Color::NUMBER);

    static int DrawText(int x, int y, const char *text, Color color = Color::NUMBER);
    /// ���������� ������ ���������� ��������������
    static int DrawTextInBoundedRectWithTransfers(int x, int y, int width, const char *text, Color colorBackground, Color colorFill);

    static int DrawTextInRectWithTransfersC(int x, int y, int width, int height, const char *text, Color color);
    /// ����� ����� � ����������
    static int DrawTextInRectWithTransfers(int x, int y, int width, int height, const char *text);

    static int DrawBigChar(int eX, int eY, int size, char symbol);

    static void DrawBigText(int x, int y, int size, const char *text, Color color = Color::NUMBER);

    static void DrawTextRelativelyRight(int xRight, int y, const char *text, Color color = Color::NUMBER);

private:

    static bool ByteFontNotEmpty(int eChar, int byte);

    static bool BitInFontIsExist(int eChar, int numByte, int bit);
    /// ���������� ������ ������, ������� ����� ����� text, ��� ������ �� left �� right � ���������� height. ���� bool == false, �� ����� �� ������ �� ����� 
    static bool GetHeightTextWithTransfers(int left, int top, int right, const char *text, int *height);

    static char *GetWord(const char *firstSymbol, int *length, char buffer[20]);

    static bool IsLetter(char symbol);
    /// ���� draw == false, �� �������� ������ �� ����, ������ ������������ ������ ��� ����������
    static int DrawPartWord(char *word, int x, int y, int xRight, bool draw);

    static int8 *BreakWord(char *word);
    /// ���������� ����� ����� �� ����� numSyllable(�����������) ������ �� ������ ��������
    static char *PartWordForTransfer(char *word, int8 *lengthSyllables, int numSyllable, char buffer[30]);
    /// \brief ������� ��������� �������. C letters ���������� ����� �����, ��� ����� ����� �������, � lettersInSyllable ����� �������� ����� ���� � 
    /// ��������� �����. ���� ����� �����������, ������� ���������� false
    static bool FindNextTransfer(const char *letters, int8 *lettersInSyllable);

    static bool IsConsonant(char symbol);

    static bool CompareArrays(const bool *array1, const bool *array2, int numElems);
};
