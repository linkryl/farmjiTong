#ifndef ztz11
#define ztz11
#include<iostream> 
#endif 
#include<cstring>
class Pic_map
{
	public:
		std::string make_pic(int num,int step);
}; 
std::string Pic_map::make_pic(int num,int step)
{
	std::string pic_name;
	pic_name.clear();
	pic_name+="/";
	switch(num)
	{
		case 1111:
			pic_name+="corn/";
			break;
		case 1110:
			pic_name+="vegetable/";
			break;
	}
	pic_name+=('0'+step);
	pic_name+=".png";
	return pic_name; 
}
#undef ztz11
