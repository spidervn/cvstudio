#ifndef EXTRACTTEXT_APP_IMPL_GENERAL_CCVCONSOLE_H_
#define EXTRACTTEXT_APP_IMPL_GENERAL_CCVCONSOLE_H_

#include <iostream>

class CCVConsole
{
public:
	CCVConsole();
	~CCVConsole();
	
	template<typename T>
	static void printMatrix(cv::Mat m)
	{
		for (int y=0; y < m.rows; ++y)
		{
			for (int x=0; x < m.cols; ++x)
			{
				std::cout << m.at<T>(y,x) << " ";
			}
			std::cout << std::endl;
		}
	}
};

#endif