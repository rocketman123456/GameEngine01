#include "RGBD-SLAM.h"

namespace SLAM {

	void showdevice() {
		// ��ȡ�豸��Ϣ  
		Array<DeviceInfo> aDeviceList;
		OpenNI::enumerateDevices(&aDeviceList);

		cout << "������������ " << aDeviceList.getSize() << " ������豸." << endl;

		for (int i = 0; i < aDeviceList.getSize(); ++i) {
			cout << "�豸 " << i << endl;
			const DeviceInfo& rDevInfo = aDeviceList[i];
			cout << "�豸���� " << rDevInfo.getName() << endl;
			cout << "�豸Id�� " << rDevInfo.getUsbProductId() << endl;
			cout << "��Ӧ������ " << rDevInfo.getVendor() << endl;
			cout << "��Ӧ��Id: " << rDevInfo.getUsbVendorId() << endl;
			cout << "�豸URI: " << rDevInfo.getUri() << endl;

		}
	}

	Status initstream(Status& rc, Device& xtion, VideoStream& streamDepth, VideoStream& streamColor) {
		rc = STATUS_OK;

		// �������������
		rc = streamDepth.create(xtion, SENSOR_DEPTH);
		if (rc == STATUS_OK) {
			// �������ͼ����Ƶģʽ
			VideoMode mModeDepth;
			// �ֱ��ʴ�С
			mModeDepth.setResolution(640, 480);
			// ÿ��30֡
			mModeDepth.setFps(30);
			// ���ظ�ʽ
			mModeDepth.setPixelFormat(PIXEL_FORMAT_DEPTH_1_MM);

			streamDepth.setVideoMode(mModeDepth);
			streamDepth.setMirroringEnabled(false);      //����

														 // �����������
			rc = streamDepth.start();
			if (rc != STATUS_OK) {
				cerr << "�޷��������������" << OpenNI::getExtendedError() << endl;
				streamDepth.destroy();
			}
		}
		else {
			cerr << "�޷����������������" << OpenNI::getExtendedError() << endl;
		}

		// ������ɫͼ��������
		rc = streamColor.create(xtion, SENSOR_COLOR);
		if (rc == STATUS_OK) {
			// ͬ�������ò�ɫͼ����Ƶģʽ
			VideoMode mModeColor;
			mModeColor.setResolution(640, 480);
			mModeColor.setFps(30);
			mModeColor.setPixelFormat(PIXEL_FORMAT_RGB888);

			streamColor.setVideoMode(mModeColor);
			streamColor.setMirroringEnabled(false);   //����
													  // �򿪲�ɫͼ��������
			rc = streamColor.start();
			if (rc != STATUS_OK) {
				cerr << "�޷��򿪲�ɫͼ����������" << OpenNI::getExtendedError() << endl;
				streamColor.destroy();
			}
		}
		else {
			cerr << "�޷�������ɫͼ����������" << OpenNI::getExtendedError() << endl;
		}

		if (!streamColor.isValid() || !streamDepth.isValid()) {
			cerr << "��ɫ��������������Ϸ�" << endl;
			OpenNI::shutdown();
			rc = STATUS_ERROR;
			return rc;
		}

		// ͼ��ģʽע��,��ɫͼ�����ͼ����
		if (xtion.isImageRegistrationModeSupported(
			IMAGE_REGISTRATION_DEPTH_TO_COLOR)) {
			xtion.setImageRegistrationMode(IMAGE_REGISTRATION_DEPTH_TO_COLOR);
		}

		return rc;
	}

	void RGBD_SLAM(int argc, char **argv) {
		if (argc != 2) {
			cerr << endl << "Usage: ./rgbd_cc path_to_vocabulary path_to_settings" << endl;
			return;
		}

		// ����ORB_SLAMϵͳ. (����1��ORB�ʴ��ļ�  ����2��xtion�����ļ�)
		ORB_SLAM2::System SLAM(argv[0], argv[1], ORB_SLAM2::System::RGBD, true);

		cout << endl << "-------" << endl;
		cout << "Openning Xtion ..." << endl;

		Status rc = STATUS_OK;
		// ��ʼ��OpenNI����
		OpenNI::initialize();
		showdevice();
		// ��������Device�豸��
		Device xtion;
		const char * deviceURL = openni::ANY_DEVICE;  //�豸��
		rc = xtion.open(deviceURL);

		VideoStream streamDepth;
		VideoStream streamColor;
		if (initstream(rc, xtion, streamDepth, streamColor) == STATUS_OK)     // ��ʼ��������
			cout << "Open Xtion Successfully!" << endl;
		else {
			cout << "Open Xtion Failed!" << endl;
			return;
		}

		// Main loop
		cv::Mat imRGB, imD;
		bool continueornot = true;
		// ѭ����ȡ��������Ϣ��������VideoFrameRef��
		VideoFrameRef  frameDepth;
		VideoFrameRef  frameColor;
		namedWindow("RGB Image", CV_WINDOW_AUTOSIZE);
		for (double index = 1.0; continueornot; index += 1.0) {
			rc = streamDepth.readFrame(&frameDepth);
			if (rc == STATUS_OK) {
				imD = cv::Mat(frameDepth.getHeight(), frameDepth.getWidth(), CV_16UC1, (void*) frameDepth.getData());   //��ȡ���ͼ
			}
			rc = streamColor.readFrame(&frameColor);
			if (rc == STATUS_OK) {
				const Mat tImageRGB(frameColor.getHeight(), frameColor.getWidth(), CV_8UC3, (void*) frameColor.getData());   //��ȡ��ɫͼ
				cvtColor(tImageRGB, imRGB, CV_RGB2BGR);
				imshow("RGB Image", imRGB);
			}
			SLAM.TrackRGBD(imRGB, imD, index);   // ORB_SLAM�������ͼ�Ͳ�ɫͼ
			char c = cv::waitKey(5);
			switch (c) {
				case 'q':
				case 27:         //�˳�
					continueornot = false;
					break;
				case 'p':         //��ͣ
					cv::waitKey(0);
					break;
				default:
					break;
			}
		}
		// Stop all threads
		SLAM.Shutdown();
		SLAM.SaveTrajectoryTUM("trajectory.txt");
		cv::destroyAllWindows();
		return;
	}

}