#include <stdio.h>
#include "CircularDoubleLinkedlist.h"

#define TRUE  1
#define FALSE 0

void main()
{
	// 지역변수 선언
	struct NODE *bottomPointer = NULL;   // 스택의 bottom포인터
	int option = 0;                      // 입력, 출력, 종료 중에서 사용자가 선택한 옵션 저장
	int no_match = FALSE;                // 해당하는 옵션이 없으면 다시 입력받기.
	int exit = FALSE;                    // 프로그램 종료 여부 확인

	printf("\n스택 : 환상이중링크드리스트로 표현\n");
	bottomPointer = createStack();       // 스택을 생성

	while (1)
	{
		printf("\n   <번호를 선택하세요.>\n1. 입력  2. 출력  3. 종료\n선택 : ");
		scanf("%d", &option); // 사용자가 옵션 선택

		// 사용자가 선택한 옵션
		switch (option)
		{
		case 1:
			insertNode(bottomPointer); break; // 노드의 데이터 삽입
		case 2:
			deleteNode(bottomPointer); break; // 노드의 데이터 삭제	
		case 3:
			printf("프로그램을 종료합니다.\n");
			exit = TRUE;
			break;
		default:
			printf("해당하는 옵션이 없습니다.\n");
			no_match = TRUE;
		}

		if (no_match)
		{
			no_match = FALSE;
			continue;            // 해당하는 옵션이 없으면 다시 입력받기
		}

		if (exit)
		{
			break;               // 사용자가 종료를 원하면 프로그램 종료
		}
	}
}