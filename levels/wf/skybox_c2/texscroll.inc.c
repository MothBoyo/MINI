void scroll_skybox_c2_skybox_mesh_vtx_0() {
	int i = 0;
	int count = 125;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int currentY = 0;
	int deltaY;
	static int timeY;
	float amplitudeY = 1.5;
	float frequencyY = 0.25;
	float offsetY = 0.0;
	Vtx *vertices = segmented_to_virtual(skybox_c2_skybox_mesh_vtx_0);

	deltaX = (int)(0.5 * 0x20) % width;
	deltaY = (int)(amplitudeY * frequencyY * coss((frequencyY * timeY + offsetY) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}
	if (absi(currentY) > height) {
		deltaY -= (int)(absi(currentY) / height) * height * signum_positive(deltaY);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
		vertices[i].n.tc[1] += deltaY;
	}
	currentX += deltaX;	currentY += deltaY;	timeY += 1;
}

void scroll_wf_level_dl_skybox_c2() {
	scroll_skybox_c2_skybox_mesh_vtx_0();
};
