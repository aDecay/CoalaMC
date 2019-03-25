#include <CoalaMOD.h>
#pragma comment(lib, "CoalaMOD.lib")

#include <math.h>

#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

int y;

void circlePoints(BlockID block, int cx, int cz, int dx, int dz)
{
	if (dx == 0) {
		locateBlock(block, cx, y, cz + dz);
		locateBlock(block, cx, y, cz - dz);
		locateBlock(block, cx + dz, y, cz);
		locateBlock(block, cx - dz, y, cz);
	}
	else if (dx == dz) {
		locateBlock(block, cx + dx, y, cz + dz);
		locateBlock(block, cx - dx, y, cz + dz);
		locateBlock(block, cx + dx, y, cz - dz);
		locateBlock(block, cx - dx, y, cz - dz);
	}
	else if (dx < dz) {
		locateBlock(block, cx + dx, y, cz + dz);
		locateBlock(block, cx - dx, y, cz + dz);
		locateBlock(block, cx + dx, y, cz - dz);
		locateBlock(block, cx - dx, y, cz - dz);
		locateBlock(block, cx + dz, y, cz + dx);
		locateBlock(block, cx - dz, y, cz + dx);
		locateBlock(block, cx + dz, y, cz - dx);
		locateBlock(block, cx - dz, y, cz - dx);
	}
}

void circleMidpoint(BlockID block, int cx, int cz, int r) {
	int dx = 0, dz = r, p = (5 - r * 4) / 4;

	circlePoints(block, cx, cz, dx, dz);
	while (dx < dz) {
		dx++;
		y++;
		if (p < 0) {
			p += 2 * dx + 1;
		}
		else {
			dz--;
			p += 2 * (dx - dz) + 1;
		}
		circlePoints(block, cx, cz, dx, dz);
	}
}

int main() {
	int px, py, pz;
	int cx, cz, r;
	BlockID wool[2];
	wool[0] = createWool(COLOR_GREEN);
	wool[1] = createWool(COLOR_LIME);
	double theta = getPlayerDirection() * M_PI / 180;

	getPlayerLocation(&px, &py, &pz);

	//스크린샷에서는 20으로 진행
	scanf("%d", &r);

	cx = px - (r + 10) * sin(theta);
	cz = pz + (r + 10) * cos(theta);

	for (int i = 4; i < 2 * r + 4; i++) {
		locateBlock(wool[1], cx, i, cz);
	}

	for (int i = 0; i <= r; i++) {
		y = 2 * r + 4;
		circleMidpoint(wool[i % 2], cx, cz, i);
	}
}