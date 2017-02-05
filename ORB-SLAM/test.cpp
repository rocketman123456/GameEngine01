#include "RGBD-SLAM.h"

int main() {

	using namespace SLAM;
	char *path[] = { "Vocabulary/ORBvoc.txt", "xtion.yaml" };
	RGBD_SLAM(2, path);

	return 0;
}