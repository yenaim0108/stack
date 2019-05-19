struct NODE * createStack();                         // 스택을 STACK_LENGTH만큼 생성
void stackResultDisplay(struct NODE *resultNodeTmp); // 스택 메모리 및 top 포인터 출력 함수
void insertNode(struct NODE *bottomPointer);         // 리스트의 노드 입력(= 삽입) 함수
void deleteNode(struct NODE *bottomPointer);         // 리스트의 노드 출력(= 삭제) 함수