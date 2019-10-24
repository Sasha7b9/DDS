#include "defines.h"
#include "Canvas.h"
#include "Form.h"
#include "MyMath.h"
#include <vector>


using namespace MyMath;


Form *TheForm = nullptr;

#define NUM_POINTS  (8192)
#define MAX_VALUE   ((1 << 12) - 1)
#define AVE_VALUE   ((MAX_VALUE) / 2)

// ������, ������� ��� �������� � ������
uint16 data[NUM_POINTS];

struct Point
{
    Point(uint16 p, uint16 d) : pos(p), data(d) {};
    uint16 pos;
    uint16 data;
    bool operator < (const Point &point) const
    {
        return (pos < point.pos);
    }
};


bool operator==(const Point &left, const Point &right)
{
    return (left.pos == right.pos) && (left.data == right.data);
}


std::vector<Point> points;

/// ���������� �������� � point �����
static void CalculateNeighboringPoints(const Point &point);
/// ������� ��������������� �����, ������������� ����� pos1 � pos2
static void LinearInterpolation(uint16 pos1, uint16 pos2);


Form::Form()
{
    for (int i = 0; i < NUM_POINTS; i++)
    {
        data[i] = AVE_VALUE;
    }

    points.clear();
}


void Form::SetPoint(int mouseX, int mouseY)
{
    wxSize size = TheCanvas->GetSize();

    uint16 x = Round<uint16>(static_cast<float>(NUM_POINTS) / size.x * mouseX);

    uint16 y = Round<uint16>(static_cast<float>(MAX_VALUE) / size.y * mouseY);

    data[x] = static_cast<uint16>(y);

    Point point(x, y);

    points.push_back(point);

    std::sort(points.begin(), points.end());

    CalculateNeighboringPoints(point);
}


void CalculateNeighboringPoints(const Point &point)
{
    uint index = 0;

    for (; index < points.size(); index++)
    {
        if (point == points[index])
        {
            break;
        }
    }

    if (index == 0)                     // ���� ����� ����� ������
    {
        if (point.pos > 0)
        {
            LinearInterpolation(0, point.pos);
        }
    }
    else if (index < points.size())
    {
        LinearInterpolation(points[index - 1].pos, point.pos);
    }
}


void Form::Draw()
{
    TheCanvas->SetColor(Color::WHITE);

    wxSize size = TheCanvas->GetSize();

    float scaleX = size.x / static_cast<float>(NUM_POINTS);
    float scaleY = size.y / static_cast<float>(MAX_VALUE);

    for (int i = 0; i < NUM_POINTS; i++)
    {
        int x = Round<int>(scaleX * i);
        int y = Round<int>(scaleY * data[i]);

        TheCanvas->SetPoint(x, y, 5);
    }
}


static void LinearInterpolation(uint16 pos1, uint16 pos2)
{
    uint16 data1 = data[pos1];
    uint16 data2 = data[pos2];

    float delta = static_cast<float>(data2 - data1) / (pos2 - pos1);  // �������� �������� ����� ��������� �������
    
    float value = data[pos1] + delta;                                  // �������� � ������� �������
    
    for (int i = pos1 + 1; i < pos2; i++)
    {
        data[i] = Round<uint16>(value);
        value += delta;
    }
}
