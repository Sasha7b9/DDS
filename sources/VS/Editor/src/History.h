#pragma once
#include "Form.h"


struct History
{
	/// ��������� ����� � �������
	static void Add(Form *form);
	/// ��������� ���������� ����� �� �������
	static Form* Prev();
	/// ��������� ��������� ����� �� �������
	static Form* Next();
};
