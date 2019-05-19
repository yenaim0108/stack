#include <stdio.h>
#include "CircularDoubleLinkedlist.h"

#define TRUE  1
#define FALSE 0

void main()
{
	// �������� ����
	struct NODE *bottomPointer = NULL;   // ������ bottom������
	int option = 0;                      // �Է�, ���, ���� �߿��� ����ڰ� ������ �ɼ� ����
	int no_match = FALSE;                // �ش��ϴ� �ɼ��� ������ �ٽ� �Է¹ޱ�.
	int exit = FALSE;                    // ���α׷� ���� ���� Ȯ��

	printf("\n���� : ȯ�����߸�ũ�帮��Ʈ�� ǥ��\n");
	bottomPointer = createStack();       // ������ ����

	while (1)
	{
		printf("\n   <��ȣ�� �����ϼ���.>\n1. �Է�  2. ���  3. ����\n���� : ");
		scanf("%d", &option); // ����ڰ� �ɼ� ����

		// ����ڰ� ������ �ɼ�
		switch (option)
		{
		case 1:
			insertNode(bottomPointer); break; // ����� ������ ����
		case 2:
			deleteNode(bottomPointer); break; // ����� ������ ����	
		case 3:
			printf("���α׷��� �����մϴ�.\n");
			exit = TRUE;
			break;
		default:
			printf("�ش��ϴ� �ɼ��� �����ϴ�.\n");
			no_match = TRUE;
		}

		if (no_match)
		{
			no_match = FALSE;
			continue;            // �ش��ϴ� �ɼ��� ������ �ٽ� �Է¹ޱ�
		}

		if (exit)
		{
			break;               // ����ڰ� ���Ḧ ���ϸ� ���α׷� ����
		}
	}
}