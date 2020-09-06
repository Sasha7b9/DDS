#pragma once
#include "defines.h"
#include "Editor/Painter/Canvas.h"
#include "Utils/MyMath.h"
#include <vector>
#pragma warning(push, 0)
#include <wx/textfile.h>
#pragma warning(pop)

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

    static const uint16 MIN = static_cast<uint16>(0);
	static const uint16 MAX = static_cast<uint16>((1 << 12) - 1);
	static const uint16 AVE = static_cast<uint16>((MAX) / 2);

	static const uint NUM_POINTS = 8192;

	Point(int mouseX, int mouseY)
	{
		pos = Math::Round<uint16>(static_cast<float>(mouseX) / ScaleX());
		data = static_cast<uint16>(Point::MAX - Math::Round<uint16>(static_cast<float>(mouseY - Grid::Y()) / ScaleY()));
	}
	Point(uint16 p, uint16 d) : pos(p), data(d) {};
	void SetY(int mouseY)
	{
		data = static_cast<uint16>(Point::MAX - Math::Round<uint16>(static_cast<float>(mouseY) / ScaleY()));
	}

	uint16 pos;
	uint16 data;
	bool operator < (const Point& point) const
	{
		return (pos < point.pos);
	}
	// ���������� true, ���� ������ ���� ��������� ��� ���� ������
	double DistanceFromMouse(int mouseX, int mouseY)
	{
        int dX = mouseX - static_cast<int>(pos);

        int dY = mouseY - static_cast<int>(Point::MAX - data);

        return std::sqrt(dX * dX + dY * dY);
	}
	// ������� �� �����������
	static float ScaleX()
	{
		return static_cast<float>(Grid::Width()) / static_cast<float>(NUM_POINTS);
	}
	// ������� �� ���������
	static float ScaleY()
	{
		return static_cast<float>(Grid::Height()) / static_cast<float>(MAX);
	}

	// ����������� ���������� ���� � ����� [0 ... (Point::NUM_POINTS - 1)]
	static int MouseToPointX(int mouseX)
	{
		return Math::Round<int>(static_cast<float>(mouseX) / ScaleX());
	}

	static int PointToMouseX(int x)
	{
		return Math::Round<int>(static_cast<float>(x) * ScaleX());
	}
};


class Form
{
public:
    Form();
    ~Form();
    // �������� ������
    void Clear();

	// �������� ������ � ������������ ����
    void SetMarkerInMouseCoord(int mouseX, int mouseY);

	// �������� ����� � ����������� ����������
    void SetPointInRealCoord(uint16 pos, uint16 data);

	// ������� ����� ���� �������
    void SetPoint(Point point);

	// �������� ����� � ������� pos
    void SetPointInPosition(uint16 pos);

	// ���������� true, ���� ������ ���� ��������� ��� ������������ ������. Pressed - ������ �� ������ ����
	bool ExistMarker(int mouseX, int mouseY, bool pressed, uint16 *index = nullptr, uint16 *value = nullptr);

	// ������� ����� � ������� ����
    void RemovePoint();

	// ����������� ����� � ����� �������
    void MovePoint(int mouseX, int mouseY);

	// ��������� �����
    void AlignPoint(Align::E align);

    void Draw();

	void UndoHistory();

	void RedoHistory();

	// ���������� �������������� �����, ������� ����� ���������� ������ ��������. 
    void SetAdditionForm(const uint16 data[Point::NUM_POINTS]);

	// ���������� �������� �����
    void SetMainForm(const uint16 data[Point::NUM_POINTS], const std::vector<Point> *points);

    bool IsEquals(const Form *form) const;

    void SaveToFile(wxTextFile &file);

    void LoadFromFile(wxTextFile &file);

private:

	// ������, ������� ��� �������� � ������
	uint16 data[Point::NUM_POINTS];

	// �����, ������������ �����. �������� � ������� ��������� ������� (pos = [0 ... Point::NUM_POINTS], data = [Point::MIN ... Point::MAX])
	std::vector<Point> markers;

	// ����� �������� ������ �����, ������� ��������� � ������� ������
	uint iCurPoint = 0;

	// ���������� index ����� � ������� pos. 0xFFFFFFFF, ���� ����� � ���� ������� ���
	uint PointInPosition(uint16 pos);

	// ���������� �������� � point �����
	void CalculateNeighboringPoints(const Point& point);

	// ������� ��������������� �����, ������������� ����� pos1 � pos2
	void LinearInterpolation(uint16 pos1, uint16 pos2);

	// ��������������� ����� ����� �� ����� � �������� index �� points
	void LinearInterpolationLeft(uint index);

	// ��������������� ����� ������ �� ����� � �������� index �� points
	void LinearInterpolationRight(uint index);
};


extern Form *TheForm;
