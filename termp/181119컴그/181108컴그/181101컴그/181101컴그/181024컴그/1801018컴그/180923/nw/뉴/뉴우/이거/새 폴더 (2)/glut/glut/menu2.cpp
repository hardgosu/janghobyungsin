void main(int argc, char *argv[])
{
	int SubMenu1, SubMenu2, SubMenu3;
	int MainMenu;
	glutInit(&argc, argv);
	SubMenu1 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry(¡°Teapot¡±, 1);
	glutAddMenuEntry(¡°Torus¡±, 2);
	glutAddMenuEntry(¡°Cone¡±, 3);
	glutAddMenuEntry(¡°Cube¡±, 4);
	glutAddMenuEntry(¡°Sphere¡±, 5);
	SubMenu2 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry(¡°Red¡±, 11);
	glutAddMenuEntry(¡°Green¡±, 22);
	SubMenu3 = glutCreateMenu(MenuFunc);
	glutAddMenuEntry(¡°Wire¡±, 111);
	glutAddMenuEntry(¡°Solid¡±, 222);
	MainMenu = glutCreateMenu(MenuFunc);
	glutAddSubMenu(¡°Shape¡±, SubMenu1);
	glutAddsubMenu(¡°Color¡±, SubMenu2);
	glutAddsubMenu(¡°State¡±, SubMenu3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MenuFunc(int button)
{
	switch (button) {
	case 1: ¡¦;
		break;
	case 2: ¡¦;
		break;
	case 11: ¡¦;
		break;
	}
	glutPostRedisplay();
}