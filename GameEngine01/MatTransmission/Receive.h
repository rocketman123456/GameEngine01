/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  基于OpenCV和Winsock的图像传输（接收）
//
//	By 彭曾 , at CUST, 2016.08.06
//
//	website: www.pengz0807.com  email: pengz0807@163.com
//
//M*/

#ifndef _RECEIVE_
#define _RECEIVE_

#include "WinsockMatTransmissionServer.h"

void Receive() {
	WinsockMatTransmissionServer socketMat;
	if (socketMat.socketConnect(6666) < 0) {
		return;
	}

	cv::Mat image;
	while (1) {
		if (socketMat.receive(image) > 0) {
			cv::imshow("", image);
			cv::waitKey(30);
		}
	}

	socketMat.socketDisconnect();
	return;
}

#endif
