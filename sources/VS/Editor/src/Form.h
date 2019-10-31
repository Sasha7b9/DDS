#pragma once
#include "defines.h"
#include "Canvas.h"
#include "MyMath.h"
#include <vector>

/*
    ����� ������������� ����� �������
*/


struct Align
{
    enum E
    {
        Left,
        Right,
        LeftTop,
        LeftDown,
        RightTop,
        RightDown
    };
};


struct Point
{
	static const uint SIZE = 5;

	static const uint16 MAX_VALUE = static_cast<uint16>((1 << 12) - 1);
	static const uint16 AVE_VALUE = static_cast<uint16>((MAX_VALUE) / 2);

	static const uint NUM_POINTS = 8192;

	Point(int mouseX, int mouseY)
	{
		pos = MyMath::Round<uint16>(mouseX / ScaleX());
		data = MyMath::Round<uint16>(mouseY / ScaleY());
	}
	Point(uint16 p, uint16 d) : pos(p), data(d) {};
	void SetY(int mouseY)
	{
		data = MyMath::Round<uint16>(mouseY / ScaleY());
	}

	uint16 pos;
	uint16 data;
	bool operator < (const Point& point) const
	{
		return (pos < point.pos);
	}
	/// ���������� true, ���� ������ ���� ��������� ��� ���� ������
	bool UnderMouse(int mouseX, int mouseY)
	{
		return (MyMath::Abs(mouseX - static_cast<int>(pos)) <= SIZE * 5) && (MyMath::Abs(mouseY - static_cast<int>(data)) <= SIZE * 5);
	}
	/// ������� �� �����������
	static float ScaleX()
	{
		return TheCanvas->GetSize().x / static_cast<float>(NUM_POINTS);
	}
	/// ������� �� ���������
	static float ScaleY()
	{
		return TheCanvas->GetSize().y / static_cast<float>(MAX_VALUE);
	}
};


class Form
{
public:
    Form();
    /// �������� ������
    void Clear();
    /// �������� ����� � ������������ ����
    void SetPoint(int mouseX, int mouseY);
    /// �������� ����� � ����������� ����������
    void SetPoint(uint16 pos, uint16 data);
    /// ���������� true, ���� ������ ���� ��������� ��� ������������ ������. Pressed - ������ �� ������ ����
    bool ExistPoint(int mouseX, int mouseY, bool pressed);
    /// ������� ����� � ������� ����
    void RemovePoint();
    /// ����������� ����� � ����� �������
    void MovePoint(int mouseX, int mouseY);
    /// ��������� �����
    void AlignPoint(Align::E align);

    void Draw();

	void UndoHistory();

	void RedoHistory();

    void CreateSine();

private:

	/// ������, ������� ��� �������� � ������
	uint16 data[Point::NUM_POINTS];

	std::vector<Point> points;
	/// ����� �������� ������ �����, ������� ��������� � ������� ������
	uint iCurPoint = 0;
	/// ���������� index ����� � ������� pos. 0xFFFFFFFF, ���� ����� � ���� ������� ���
	uint PointInPosition(uint16 pos);
	/// ������� ����� ���� �������
	void SetPoint(Point point);
	/// ���������� �������� � point �����
	void CalculateNeighboringPoints(const Point& point);
	/// ������� ��������������� �����, ������������� ����� pos1 � pos2
	void LinearInterpolation(uint16 pos1, uint16 pos2);
	/// ��������������� ����� ����� �� ����� � �������� index �� points
	void LinearInterpolationLeft(uint index);
	/// ��������������� ����� ������ �� ����� � �������� index �� points
	void LinearInterpolationRight(uint index);
};


extern Form *TheForm;
