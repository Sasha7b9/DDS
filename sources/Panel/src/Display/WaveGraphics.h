#pragma once
#pragma once
#include "Settings/SettingsTypes.h"

class Parameter;


class WaveGraphics
{
public:
    
    // ���������� ���������� � ���������� ������� �� ������
    static void Draw(Chan::E ch);
    
    // ������� x ������� ��������� �������
    static int X();
    
    // ������� y ������� ��������� �������
    static int Y(Chan::E ch);
    
    // ������ ������� ��������� �������
    static int Width();
    
    // ������ ������� ��������� �������
    static int Height();


    static Parameter *GetParameterForDraw(Chan::E ch, int i);

private:

    static void DrawParameters(Chan::E chan, int y0);
};
