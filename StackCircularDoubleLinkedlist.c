#include <stdio.h>
#include <malloc.h>
#define STACK_LENGTH  5              // ������ ���� ����

struct NODE
{ // ����Ʈ�� ��� ����ü ����
	struct NODE *previousNodePointer;    // ���� ��� �ּ� ����
	char data;                       // ���� ����� ��
	struct NODE *nextNodePointer;        // ���� ��� �ּ� ����
};

// �������� ����
struct NODE *previousNodeTmp;        // ���� ���(= ���� ��尡 ���ԵǱ� ���� top������ ��)�� �ӽ� �������
struct NODE *topPointer = NULL;      // ������ top������
int topIndex = -1;                   // top�����Ͱ� ����Ű�� �ִ� ��尡 �� ��° ������� �����ϴ� ����(0���� ���� ����)

struct NODE * createStack()
{ // ���� ���� �Լ�
	// �������� ����
	struct NODE *bottomPointer;
	struct NODE *node = NULL;     // �����Ҵ��� ��带 �����ϴ� ����
	struct NODE *nodeTmp = NULL;  // ���߸�ũ�帮��Ʈ�� ����� ���� ���� ����� �ӽ� �������
	int i = 0;

	while (i < STACK_LENGTH)
	{ // STACK_LENGTH�� ���� ��ŭ �ݺ��ؼ� ������ ��� ����
		node = (struct NODE *)malloc(sizeof(struct NODE)); // node�� �����Ҵ�(= ���� ���)

		if (i == 0)
		{ // ù ��° ����� ���
			bottomPointer = node;             // ù ��° ���� bottom �����Ϳ� ����
			node->nextNodePointer = NULL;     // ù ��° ����̹Ƿ� ���� ��尡 ����.
			node->previousNodePointer = NULL; // ù ��° ����̹Ƿ� ���� ��尡 ����.
		}
		else
		{ // �� ��° �̻��� ����� ���
			node->nextNodePointer = bottomPointer;     // ������ ���(= ���� ���)�� ���� ��带 ù ��° ���� �����ؼ� ȯ��ũ�帮��Ʈ�� ����
			bottomPointer->previousNodePointer = node; // ù ��° ����� ���� ��带 ������ ���(= ���� ���)�� �����ؼ� ȯ�����߸�ũ�帮��Ʈ�� ����
			node->previousNodePointer = nodeTmp;       // ���� ����� ���� ��带 nodeTmp�� �ּҷ� �����ؼ� ���߸�ũ�帮��Ʈ ����
			nodeTmp->nextNodePointer = node;           // nodeTmp(= ���� ���)�� ���� ��带 ���� ����� �ּҷ� �����ؼ� ��ũ�帮��Ʈ ����
		}

		node->data = '\0';                         // ���� �Էµ� ���� �����Ƿ� ������ ������ �ʱ�ȭ
		nodeTmp = node;                            // ���� ��带 nodeTmp�� �ӽ�����(why? ���߸�ũ�帮��Ʈ�� ����� ���ؼ�...)
		i++;
	}

	return bottomPointer;
}

void stackResultDisplay(struct NODE *resultNodeTmp)
{ // ���� �޸� �� topPointer������ ��� �Լ�
	extern int topIndex;

	printf("[���]\n");
	// stack ���ȣ ���
	for (int i = 0; i < STACK_LENGTH; i++)
	{
		printf("%3d", i + 1);                           // �ڵ������� 0������� ����, �˰���(���)�󿡼��� 1������� ����
	}
	printf("  TOP\n");

	// stack �� ���
	for (int i = 0; i < STACK_LENGTH; i++)
	{
		printf("%3c", resultNodeTmp->data);             // ���� ����� ������ ���
		resultNodeTmp = resultNodeTmp->nextNodePointer; // resultNodeTmp�� ���� ����� �ּҷ� �ٲ�.
	}
	printf("%4d\n", topIndex + 1);                      // top ������ �� ��ȣ ���(�˰��� ����)
}

void insertNode(struct NODE *bottomPointer)
{ // ����Ʈ�� ��� �Է�(= ����) �Լ�
	extern struct NODE *previousNodeTmp;
	extern struct NODE *topPointer;
	extern int topIndex;

	// �������� ����
	char data; // ����ڰ� �Է��� ������ ����

	// ����ڰ� ������ �Է�
	printf("\n�Է� : ");
	fflush(stdin);
	scanf("%c", &data);

	// �����÷ο� ó��
	if (topIndex >= (STACK_LENGTH - 1))
	{ // topIndex�� (������ ���� -1)���� ũ�ų� ������ �� �� �����̹Ƿ� �����÷ο�!!
		printf("�����÷ο��Դϴ�. �����͸� ��� �� �ٽ� �Է����ּ���.\n");
		return;
	}

	// ������ �Է�
	if (topPointer == NULL)
	{ // ������ ������� �� �Է�(= ����) ó��
		topIndex += 1;                   // �˰��򿡼��� ������� Ȯ��
		topPointer = bottomPointer;      // ���� ���������� ������� Ȯ��

		topPointer->data = data;         // �Էµ� ������ ����

		previousNodeTmp = bottomPointer; // ���� ����� �ּҸ� previousNodeTmp�� �ӽ�����
	}
	else
	{ // ���ÿ� �����Ͱ� �� ���̻� ������ �� �Է�(= ����) ó��
		topIndex += 1;                                 // �˰��򿡼��� ������� Ȯ��
		topPointer = previousNodeTmp->nextNodePointer; // ���� ���������� ������� Ȯ��

		topPointer->data = data;                       // Ȯ���� ��������� ������ �Է�

		previousNodeTmp = topPointer;                  // ���� ��带 �����ϴ� ������ top �����Ͱ� ����Ű�� �ִ� ��� ����
	}

	// ������ ���� ���� ���
	stackResultDisplay(bottomPointer);
}

void deleteNode(struct NODE *bottomPointer)
{ // ����Ʈ�� ��� ���(= ����) �Լ�
	extern struct NODE *previousNodeTmp;
	extern struct NODE *topPointer;
	extern int topIndex;

	printf("\n���(top������)\n");

	// ����÷ο� ó��
	if (topIndex <= -1)
	{ // topIndex�� -1�̸� �����Ͱ� ����ִ°��̹Ƿ� ����÷ο�!!
		printf("����÷ο��Դϴ�. �����͸� �Է� �� �ٽ� ����ϼ���.\n");
		return;
	}

	// ������ ���
	topPointer->data = '\0';                      // top �����Ͱ� ����Ű�� �ִ� ���(= ���� ���߿� �Էµ� �����͸� ������ �ִ� ���)�� ������ ����

	topIndex -= 1;                                // �˰��򿡼����� ������� ����
	topPointer = topPointer->previousNodePointer; // ���� ���������� ������� ����

	previousNodeTmp = topPointer;                 // previousNodeTmp�� ���� �� ���� ������ ������ ���(= topPointer)�� �ּҸ� �ӽ�����

	// ������ ���� ���� ���
	stackResultDisplay(bottomPointer);
}