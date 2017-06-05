#include <stdio.h>
#include <stdlib.h>
#include <termio.h>

int i = -1, j, k, stage;
char get;
int map_current[5][30][30];
int pl_x, pl_y;
int map_file[5][30][30] = {};
char name[20];
char ch = 0;

int getch(void) {
	int ch;

	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;

	buf.c_lflag &= ~(ICANON | ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;

	tcsetattr(0, TCSAFLUSH, &buf);

	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);


	return ch;
}

int main(void) {
	system("clear");
	printf("Start....\n");
	printf("input name : ");
	scanf("%s", name);	//�̸� �Է¹���

	FILE *file = fopen("map.txt", "r");

	while (ch != 'e') {
		for (k = 0; k<30; k++) {
			fscanf(file, "%c", &ch);
			if (ch == 'm') {
				i++;
				j = 0;
				k = -1;
				continue;
			}
			if (ch == 'a' || ch == 'p') {
				k--;
				continue;
			}
			if (ch == 'e') {
				break;
			}
			if (ch == '\n') {
				j++;
				k = -1;
				continue;
			}
			else {
				switch (ch) {
				case ' ':	//������ ��� 0���� ����
					map_file[i][j][k] = 0;
					break;
				case '#':	//���� ��� 1�� ����
					map_file[i][j][k] = 1;
					break;
				case '$':	//�ڽ��� ��� 2�� ����
					map_file[i][j][k] = 2;
					break;
				case 'O':	//�ڽ� ���°��� ��� 4�� ����
					map_file[i][j][k] = 4;
					break;
				case '@':	//�÷��̾��� ��� 5�� ����
					map_file[i][j][k] = 5;
					break;
				default:
					break;
				}
			}
		}
	}

	for (i = 0; i<5; i++) {
		for (j = 0; j<30; j++) {
			for (k = 0; k<30; k++) {
				map_current[i][j][k] = map_file[i][j][k];
			}
		}
	}
	fclose(file);

	while (1) {
		system("clear");
		printf("Hello, ");
		for (i = 0; i<20; i++) {
			printf("%c", name[i]);
		}
		printf("\n");
		stage = 0;
		for (j = 1; j<30; j++) {
			for (k = 0; k<30; k++) {
				switch (map_current[stage][j][k]) {
				case 0:
					printf(" ");
					break;
				case 1:
					printf("#");
					break;
				case 2:
					printf("$");
					break;
				case 4:
					printf("O");
					break;
				case 5:
					printf("@");
					pl_x = k;
					pl_y = j;
					break;
				default:
					break;
				}
			}
			printf("\n");
		}
		get = getch();
		switch (get) {
		case 'l':
			if (map_file[0][pl_y][pl_x] == 4) {	//�ִ� �ڸ��� �ڽ� ���� ��ġ�� ���
				if (map_current[0][pl_y][pl_x + 1] == 2) {	//�������� �ڽ��� ���
					if (map_current[0][pl_y][pl_x + 2] != 1 || map_current[0][pl_y][pl_x + 2] != 2) {//�ǳ����� �ڽ��� ���� �ƴ� ���
						map_current[0][pl_y][pl_x + 1] = 5;	//�÷��̾� ������ �̵�
						map_current[0][pl_y][pl_x + 2] = 2; //�ǳ��� �ڽ�
						map_current[0][pl_y][pl_x] = 4;
					}
					else {
						break;
					}
				}
				else if (map_current[0][pl_y][pl_x + 1] == 1) {	//�������� ���� ���
					break;
				}
				else if (map_current[0][pl_y][pl_x + 1] == 0) {
					map_current[0][pl_y][pl_x + 1] = 5;
					map_current[0][pl_y][pl_x] = 4;
				}
			}
			else {	//�ִ� �ڸ��� ������ ���
				if (map_current[0][pl_y][pl_x + 1] == 2) {	//�������� �ڽ��� ���
					if (map_current[0][pl_y][pl_x + 2] != 1 || map_current[0][pl_y][pl_x + 2] != 2) {//�ǳ����� �ڽ��� ���� �ƴ� ���
						map_current[0][pl_y][pl_x + 1] = 5;	//�÷��̾� ������ �̵�
						map_current[0][pl_y][pl_x + 2] = 2; //�ǳ��� �ڽ�
						map_current[0][pl_y][pl_x] = 0;
					}
					else {
						break;
					}
				}
				else if (map_current[0][pl_y][pl_x + 1] == 1) {	//�������� ���� ���
					break;
				}
				else if (map_current[0][pl_y][pl_x + 1] == 0) {
					map_current[0][pl_y][pl_x + 1] = 5;
					map_current[0][pl_y][pl_x] = 0;
				}
			}
			break;
		case 'h':
			if (map_file[0][pl_y][pl_x] == 4) {	//�ִ� �ڸ��� �ڽ� ���� ��ġ�� ���
				if (map_current[0][pl_y][pl_x - 1] == 2) {	//�������� �ڽ��� ���
					if (map_current[0][pl_y][pl_x - 2] != 1 || map_current[0][pl_y][pl_x - 2] != 2) {//�ǳ����� �ڽ��� ���� �ƴ� ���
						map_current[0][pl_y][pl_x - 1] = 5;	//�÷��̾� ������ �̵�
						map_current[0][pl_y][pl_x - 2] = 2; //�ǳ��� �ڽ�
						map_current[0][pl_y][pl_x] = 4;
					}
					else {
						break;
					}
				}
				else if (map_current[0][pl_y][pl_x - 1] == 1) {	//�������� ���� ���
					break;
				}
				else if (map_current[0][pl_y][pl_x - 1] == 0) {
					map_current[0][pl_y][pl_x - 1] = 5;
					map_current[0][pl_y][pl_x] = 4;
				}
			}
			else {	//�ִ� �ڸ��� ������ ���
				if (map_current[0][pl_y][pl_x - 1] == 2) {	//�������� �ڽ��� ���
					if (map_current[0][pl_y][pl_x - 2] != 1 || map_current[0][pl_y][pl_x - 2] != 2) {//�ǳ����� �ڽ��� ���� �ƴ� ���
						map_current[0][pl_y][pl_x - 1] = 5;	//�÷��̾� ������ �̵�
						map_current[0][pl_y][pl_x - 2] = 2; //�ǳ��� �ڽ�
						map_current[0][pl_y][pl_x] = 0;
					}
					else {
						break;
					}
				}
				else if (map_current[0][pl_y][pl_x - 1] == 1) {	//�������� ���� ���
					break;
				}
				else if (map_current[0][pl_y][pl_x - 1] == 0) {
					map_current[0][pl_y][pl_x - 1] = 5;
					map_current[0][pl_y][pl_x] = 0;
				}
			}
			break;
		case 'j':
			if (map_file[0][pl_y][pl_x] == 4) {	//�ִ� �ڸ��� �ڽ� ���� ��ġ�� ���
				if (map_current[0][pl_y + 1][pl_x] == 2) {	//�������� �ڽ��� ���
					if (map_current[0][pl_y + 2][pl_x] != 1 || map_current[0][pl_y + 2][pl_x] != 2) {//�ǳ����� �ڽ��� ���� �ƴ� ���
						map_current[0][pl_y + 1][pl_x] = 5;	//�÷��̾� ������ �̵�
						map_current[0][pl_y + 2][pl_x] = 2; //�ǳ��� �ڽ�
						map_current[0][pl_y][pl_x] = 4;
					}
					else {
						break;
					}
				}
				else if (map_current[0][pl_y + 1][pl_x] == 1) {	//�������� ���� ���
					break;
				}
				else if (map_current[0][pl_y + 1][pl_x] == 0) {
					map_current[0][pl_y + 1][pl_x] = 5;
					map_current[0][pl_y][pl_x] = 4;
				}
			}
			else {	//�ִ� �ڸ��� ������ ���
				if (map_current[0][pl_y + 1][pl_x] == 2) {	//�������� �ڽ��� ���
					if (map_current[0][pl_y + 2][pl_x] != 1 || map_current[0][pl_y + 2][pl_x] != 2) {//�ǳ����� �ڽ��� ���� �ƴ� ���
						map_current[0][pl_y + 1][pl_x] = 5;	//�÷��̾� ������ �̵�
						map_current[0][pl_y + 2][pl_x] = 2; //�ǳ��� �ڽ�
						map_current[0][pl_y][pl_x] = 0;
					}
					else {
						break;
					}
				}
				else if (map_current[0][pl_y + 1][pl_x] == 1) {	//�������� ���� ���
					break;
				}
				else if (map_current[0][pl_y + 1][pl_x] == 0) {
					map_current[0][pl_y + 1][pl_x] = 5;
					map_current[0][pl_y][pl_x] = 0;
				}
			}
			break;
		case 'k':
			if (map_file[0][pl_y][pl_x] == 4) {	//�ִ� �ڸ��� �ڽ� ���� ��ġ�� ���
				if (map_current[0][pl_y - 1][pl_x] == 2) {	//�������� �ڽ��� ���
					if (map_current[0][pl_y - 2][pl_x] != 1 || map_current[0][pl_y - 2][pl_x] != 2) {//�ǳ����� �ڽ��� ���� �ƴ� ���
						map_current[0][pl_y - 1][pl_x] = 5;	//�÷��̾� ������ �̵�
						map_current[0][pl_y - 2][pl_x] = 2; //�ǳ��� �ڽ�
						map_current[0][pl_y][pl_x] = 4;
					}
					else {
						break;
					}
				}
				else if (map_current[0][pl_y - 1][pl_x] == 1) {	//�������� ���� ���
					break;
				}
				else if (map_current[0][pl_y - 1][pl_x] == 0) {
					map_current[0][pl_y - 1][pl_x] = 5;
					map_current[0][pl_y][pl_x] = 4;
				}
			}
			else {	//�ִ� �ڸ��� ������ ���
				if (map_current[0][pl_y - 1][pl_x] == 2) {	//�������� �ڽ��� ���
					if (map_current[0][pl_y - 2][pl_x] != 1 || map_current[0][pl_y - 2][pl_x] != 2) {//�ǳ����� �ڽ��� ���� �ƴ� ���
						map_current[0][pl_y - 1][pl_x] = 5;	//�÷��̾� ������ �̵�
						map_current[0][pl_y - 2][pl_x] = 2; //�ǳ��� �ڽ�
						map_current[0][pl_y][pl_x] = 0;
					}
					else {
						break;
					}
				}
				else if (map_current[0][pl_y - 1][pl_x] == 1) {	//�������� ���� ���
					break;
				}
				else if (map_current[0][pl_y - 1][pl_x] == 0) {
					map_current[0][pl_y - 1][pl_x] = 5;
					map_current[0][pl_y][pl_x] = 0;
				}
			}
			break;
		default:
			break;
		}

	}
	return 0;
}
