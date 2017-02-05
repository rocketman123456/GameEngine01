/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  基于OpenCV和Winsock的图像传输（发送）
//
//	By 彭曾 , at CUST, 2016.08.06
//
//	website: www.pengz0807.com  email: pengz0807@163.com
//
//M*/

#ifndef _SEND_
#define _SEND_

#include "WinsockMatTransmissionClient.h"

void Send() {
	WinsockMatTransmissionClient socketMat;
	if (socketMat.socketConnect("192.168.1.101", 6666) < 0) {
		return;
	}

	cv::VideoCapture capture(0);
	cv::Mat image;

	while (1) {
		if (!capture.isOpened())
			return;

		capture >> image;

		if (image.empty())
			return;

		socketMat.transmit(image);
	}

	socketMat.socketDisconnect();
	return;
}

#endif
