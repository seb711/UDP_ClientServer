#pragma once

namespace Asset
{
	class Data
	{
	private:
		int number;
		float gpa;
	public:
		Data(int number, float gpa);
		void print();
		int getNumber();
		int getGpa();
	};
}


