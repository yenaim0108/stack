#include <stdio.h>
#include <malloc.h>
#define STACK_LENGTH  5              // 스택의 길이 지정

struct NODE
{ // 리스트의 노드 구조체 정의
	struct NODE *previousNodePointer;    // 이전 노드 주소 저장
	char data;                       // 현재 노드의 값
	struct NODE *nextNodePointer;        // 다음 노드 주소 저장
};

// 전역변수 선언
struct NODE *previousNodeTmp;        // 이전 노드(= 새로 노드가 삽입되기 전의 top포인터 값)의 임시 저장공간
struct NODE *topPointer = NULL;      // 스택의 top포인터
int topIndex = -1;                   // top포인터가 가리키고 있는 노드가 몇 번째 노드인지 저장하는 변수(0번방 부터 시작)

struct NODE * createStack()
{ // 스택 생성 함수
	// 지역변수 선언
	struct NODE *bottomPointer;
	struct NODE *node = NULL;     // 동적할당한 노드를 저장하는 변수
	struct NODE *nodeTmp = NULL;  // 이중링크드리스트를 만들기 위한 현재 노드의 임시 저장공간
	int i = 0;

	while (i < STACK_LENGTH)
	{ // STACK_LENGTH의 길이 만큼 반복해서 스택의 노드 생성
		node = (struct NODE *)malloc(sizeof(struct NODE)); // node에 동적할당(= 현재 노드)

		if (i == 0)
		{ // 첫 번째 노드일 경우
			bottomPointer = node;             // 첫 번째 노드는 bottom 포인터에 저장
			node->nextNodePointer = NULL;     // 첫 번째 노드이므로 다음 노드가 없다.
			node->previousNodePointer = NULL; // 첫 번째 노드이므로 이전 노드가 없다.
		}
		else
		{ // 두 번째 이상의 노드일 경우
			node->nextNodePointer = bottomPointer;     // 마지막 노드(= 현재 노드)의 다음 노드를 첫 번째 노드로 저장해서 환상링크드리스트로 생성
			bottomPointer->previousNodePointer = node; // 첫 번째 노드의 이전 노드를 마지막 노드(= 현재 노드)로 저장해서 환상이중링크드리스트로 생성
			node->previousNodePointer = nodeTmp;       // 현재 노드의 이전 노드를 nodeTmp의 주소로 저장해서 이중링크드리스트 생성
			nodeTmp->nextNodePointer = node;           // nodeTmp(= 이전 노드)의 다음 노드를 현재 노드의 주소로 저장해서 링크드리스트 생성
		}

		node->data = '\0';                         // 아직 입력된 값이 없으므로 스택의 데이터 초기화
		nodeTmp = node;                            // 현재 노드를 nodeTmp에 임시저장(why? 이중링크드리스트를 만들기 위해서...)
		i++;
	}

	return bottomPointer;
}

void stackResultDisplay(struct NODE *resultNodeTmp)
{ // 스택 메모리 및 topPointer포인터 출력 함수
	extern int topIndex;

	printf("[결과]\n");
	// stack 방번호 출력
	for (int i = 0; i < STACK_LENGTH; i++)
	{
		printf("%3d", i + 1);                           // 코딩에서는 0번방부터 시작, 알고리즘(출력)상에서는 1번방부터 시작
	}
	printf("  TOP\n");

	// stack 값 출력
	for (int i = 0; i < STACK_LENGTH; i++)
	{
		printf("%3c", resultNodeTmp->data);             // 현재 노드의 데이터 출력
		resultNodeTmp = resultNodeTmp->nextNodePointer; // resultNodeTmp를 다음 노드의 주소로 바꿈.
	}
	printf("%4d\n", topIndex + 1);                      // top 포인터 방 번호 출력(알고리즘 기준)
}

void insertNode(struct NODE *bottomPointer)
{ // 리스트의 노드 입력(= 삽입) 함수
	extern struct NODE *previousNodeTmp;
	extern struct NODE *topPointer;
	extern int topIndex;

	// 지역변수 선언
	char data; // 사용자가 입력한 데이터 저장

	// 사용자가 데이터 입력
	printf("\n입력 : ");
	fflush(stdin);
	scanf("%c", &data);

	// 오버플로우 처리
	if (topIndex >= (STACK_LENGTH - 1))
	{ // topIndex가 (지정한 길이 -1)보다 크거나 같으면 꽉 찬 상태이므로 오버플로우!!
		printf("오버플로우입니다. 데이터를 출력 후 다시 입력해주세요.\n");
		return;
	}

	// 데이터 입력
	if (topPointer == NULL)
	{ // 스택이 비어있을 때 입력(= 삽입) 처리
		topIndex += 1;                   // 알고리즘에서의 저장공간 확보
		topPointer = bottomPointer;      // 실제 구현에서의 저장공간 확보

		topPointer->data = data;         // 입력된 데이터 저장

		previousNodeTmp = bottomPointer; // 현재 노드의 주소를 previousNodeTmp에 임시저장
	}
	else
	{ // 스택에 데이터가 한 개이상 존재할 때 입력(= 삽입) 처리
		topIndex += 1;                                 // 알고리즘에서의 저장공간 확보
		topPointer = previousNodeTmp->nextNodePointer; // 실제 구현에서의 저장공간 확보

		topPointer->data = data;                       // 확보한 저장공간에 데이터 입력

		previousNodeTmp = topPointer;                  // 이전 노드를 저장하는 공간에 top 포인터가 가리키고 있는 노드 저장
	}

	// 스택의 현재 상태 출력
	stackResultDisplay(bottomPointer);
}

void deleteNode(struct NODE *bottomPointer)
{ // 리스트의 노드 출력(= 삭제) 함수
	extern struct NODE *previousNodeTmp;
	extern struct NODE *topPointer;
	extern int topIndex;

	printf("\n출력(top포인터)\n");

	// 언더플로우 처리
	if (topIndex <= -1)
	{ // topIndex가 -1이면 데이터가 비어있는것이므로 언더플로우!!
		printf("언더플로우입니다. 데이터를 입력 후 다시 출력하세요.\n");
		return;
	}

	// 데이터 출력
	topPointer->data = '\0';                      // top 포인터가 가리키고 있는 노드(= 가장 나중에 입력된 데이터를 가지고 있는 노드)의 데이터 삭제

	topIndex -= 1;                                // 알고리즘에서의의 저장공간 삭제
	topPointer = topPointer->previousNodePointer; // 실제 구현에서의 저장공간 삭제

	previousNodeTmp = topPointer;                 // previousNodeTmp에 삭제 후 새로 지정된 마지막 노드(= topPointer)의 주소를 임시저장

	// 스택의 현재 상태 출력
	stackResultDisplay(bottomPointer);
}