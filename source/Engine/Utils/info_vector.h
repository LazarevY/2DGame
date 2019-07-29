#pragma once

typedef  struct info_vector3{

	int value_1;
	int value_2;
	int value_3;

	info_vector3(): value_1(0), value_2(0),value_3(0)
	{
		
	}

}info_vector3;

typedef struct info_vector4{

	int value_1;
	int value_2;
	int value_3;
	int value_4;

	info_vector4() : value_1(0), value_2(0), value_3(0), value_4(0)
	{

	}

}info_vector4;

typedef struct unsigned_info_vector4{

	unsigned int value_1;
	unsigned int value_2;
	unsigned int value_3;
	unsigned int value_4;

	unsigned_info_vector4(unsigned int value_1 = 0 , unsigned int value_2 = 0, unsigned int value_3 = 0, unsigned int value_4 = 0) :
	value_1(value_1), value_2(value_2), value_3(value_3), value_4(value_4)
	{

	}

}uinfo_vector4;