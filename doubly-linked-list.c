#include<stdio.h>
#include<stdlib.h>



typedef struct Node {//Node 구조체 선언
	int key;//int형 변수 key 선언
	struct Node* llink;//Node 포인터 llink 선언
	struct Node* rlink;//Node 포인터 rlink 선언 
} listNode;//구조체 별칭 listNode



typedef struct Head {//Head 구조체 선언
	struct Node* first;//Node 포인터 first 선언
}headNode;//구조체 별칭 headNode

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음 */
int initialize(headNode** h);//이중포인터를 매개변수로 하는 headnode의 메모리를 할당하여 초기화하는 함수 선언

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);//포인터를 매개변수로 하는 할당된 메모리 해제하는 함수 선언

int insertNode(headNode* h, int key);//포인터 h와 int형 변수 key를 매개변수로 하는 int형 함수 insertNode선언
int insertLast(headNode* h, int key);//포인터 h와 int형 변수 key를 매개변수로 하는 int형 함수 insertLast선언
int insertFirst(headNode* h, int key);//포인터 h와 int형 변수 key를 매개변수로 하는 int형 함수 insertFirst선언
int deleteNode(headNode* h, int key);//포인터 h와 int형 변수 key를 매개변수로 하는 int형 함수 deleteNode선언
int deleteLast(headNode* h);//포인터 h를 매개변수로 하는 int형 함수 deleteLast 선언
int deleteFirst(headNode* h);//포인터 h를 매개변수로 하는 int형 함수 deleteFirst 선언
int invertList(headNode* h);//포인터 h를 매개변수로 하는 int형 함수 invertList 선언

void printList(headNode* h);//포인터 h를 매개변수로 하는 void형 printList 함수 선언


int main()
{
	char command;//char형 변수 command 선언
	int key;//int형 변수 key 선언
	headNode* headnode=NULL;//headNode의 포인터 headnode를 NULL로 초기화

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
        printf("--------------[-- [Kimdongwoo] [2020039058] ----]---------------\n");
        printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {//command 값에 따른 switch조건문
		case 'z': case 'Z'://z 대소문자 입력받았을 때
			initialize(&headnode);//headnode의 주소를 매개변수로 하는 initialize 함수 호출하여 메모리 할당
			break;
		case 'p': case 'P'://p 대소문자 입력받았을 때
			printList(headnode);//printList 함수 실행
			break;
		case 'i': case 'I'://i 대소문자 입력받았을 때
			printf("Your Key = ");//key 입력을 위한 출력
			scanf("%d", &key);//입력받은 값 key에 할당
			insertNode(headnode, key);//key에 대한 노드 추가
			break;
		case 'd': case 'D'://d 대소문자 입력받았을 때
			printf("Your Key = ");//key 입력을 위한 출력
			scanf("%d", &key);//입력받은 값 key에 할당
			deleteNode(headnode, key);//key에 대한 노드 삭제
			break;
		case 'n': case 'N'://n 대소문자 입력받았을 때
			printf("Your Key = ");//key 입력을 위한 출력
			scanf("%d", &key);//입력받은 값 key에 할당
			insertLast(headnode, key);//list의 마지막에 노드 하나 추가
			break;
		case 'e': case 'E'://e 대소문자 입력받았을 때
			deleteLast(headnode);//list의 마지막 노드 삭제
			break;
		case 'f': case 'F'://f 대소문자 입력받았을 때
			printf("Your Key = ");//key 입력을 위한 출력
			scanf("%d", &key);//입력받은 값 key에 할당
			insertFirst(headnode, key);//list의 첫 부분에 노드 하나 추가
			break;
		case 't': case 'T'://t 대소문자 입력받았을 때
			deleteFirst(headnode);//list의 첫 노드 삭제
			break;
		case 'r': case 'R'://r 대소문자 입력받았을 때
			invertList(headnode);//list 재배열
			break;
		case 'q': case 'Q'://q 대소문자 입력받았을 때
			freeList(headnode);//할당된 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//q 대소문자 입력받기 전까지 반복

	return 1;
}


int initialize(headNode** h) {//headNode 이중포인터 h를 매개변수로 int형 함수 initialize

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)//포인터 h가 가르키는 값이 NULL이 아니라면
		freeList(*h);//할당된 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));//포인터 h에 headNode의 크기만큼 메모리 할당
	(*h)->first = NULL;//h의 first에 NULL값 할당
	return 1;
}

int freeList(headNode* h){//headNode의 포인터h를 매개변수로 하는 int형 freeList함수
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;//listNode의 포인터 p 에 h의 first 노드에 연결

	listNode* prev = NULL;//listNode의 포인터 prev에 NULL값 할당
	while(p != NULL) {//p가 NULL이 아닐 동안
		prev = p;//prev에 p값 할당
		p = p->rlink;//p에 p의 rlink 값 할당
		free(prev);//prev에 할당된 메모리 해제
	}
	free(h);//h에 할당된 메모리 해제
	return 0;
}


void printList(headNode* h) {//headNode의 포인터 h 매개변수로 하는 printList 함수
	int i = 0;//int형 변수 i 0으로 초기화
	listNode* p;//listNode 포인터 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) {//h가 NULL이라면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;//p에 h의 first 값 할당

	while(p != NULL) {//p가 NULL이 아닐동안
		printf("[ [%d]=%d ] ", i, p->key);//p의 key 출력
		p = p->rlink;//p에 p의 rlink 값 할당
		i++;
	}

	printf("  items = %d\n", i);//i 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {//headNode의 포인터 h, int형 변수 key를 매개변수로 하는 insertLast 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//listNode 포인터 node에 listNode 크기만큼 메모리 할당
	node->key = key;//node의 key에 key값 할당
	node->rlink = NULL;//node의 rlink에 NULL 할당
	node->llink = NULL;//node으 llink에 NULL 할당

	if (h->first == NULL)//h의 first가 NULL이라면
	{
		h->first = node;//h의 first에 node 값 할당
		return 0;
	}

	listNode* n = h->first;//listNode의 포인터 n에 h의 first값 할당
	while(n->rlink != NULL) {//n의 rlink가 NULL이 아닐 동안 반복
		n = n->rlink;//n에 n의 rlink 값 할당
	}
	n->rlink = node;//n의 rlink에 node 값 할당
	node->llink = n;//node의 llink에 n값 할당
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {//headnode의 포인터 h 매개변수로 하는 int형 deleteLast함수

	if (h->first == NULL)//h의 first가 NULL이라면면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;//listNode의 포인터 n에 h의 first 값 할당
	listNode* trail = NULL;//listNode의 포인터 trail에 NULL 값 할당

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {//n의 rlink에 NULL 값 할당
		h->first = NULL;//h의 first에 NULL 값 할당
		free(n);//n에 할당된 메모리 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {//n의 rlink가 NULL이 아닐동안 반복
		trail = n;//trail에 n값 할당
		n = n->rlink;//n에 n의 rlink값 할당
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;//trail의 rlink에 NULL 값 할당
	free(n);//n에 할당된 메모리 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {//headNode의 포인터 h와 int형 변수 key 를 매개변수로 하는 int형 변수 insertFirst함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//listNode의 포인터 node에 listNode의 사이즈 만큼 메모리 할당
	node->key = key;//node의 key에 key의 값 할당
	node->rlink = node->llink = NULL;//node의 rlink와 node의 llink의 NULL값 할당

	if(h->first == NULL)//h의 first에 NULL값 할당
	{
		h->first = node;//h의 first에 node 값 할당
		return 1;
	}

	node->rlink = h->first;//node의 rlink에 h의 first값 할당
	node->llink = NULL;//node의 llink에 NULL값 할당

	listNode *p = h->first;//listNode의 포인터 p에 h의 first 값 할당
	p->llink = node;//p의 llink에 node 값 할당
	h->first = node;//h의 first에 node 값 할당

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {//headNode 포인터 h를 매개변수로 하는 int형 deleteFirst함수

	if (h->first == NULL)//h의 first가 NULL이라면
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;//listNode의 포인터 n에 h의 first의 값 할당
	h->first = n->rlink;//h의 first에 n의 rlink 값 할당

	free(n);//n의 할당된 메모리 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {//headNode 포인터 h를 매개변수로 하는 int형 invertList 함수


	if(h->first == NULL) {//h의 first가 NULL 일 때
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;//listNode의 포인터 n에 h의 first값 할당
	listNode *trail = NULL;//listNode의 포인터 trail에 NULL 할당
	listNode *middle = NULL;//listNode의 포인터 middle에 NULL 할당

	while(n != NULL){//n이 NULL이 아닐동안
		trail = middle;//trail에 middle 값 할당
		middle = n;//middle에 n값 할당
		n = n->rlink;//n에 n의 rlink 값 할당
		middle->rlink = trail;//middle의 rlink에 trail값 할당
		middle->llink = n;//middle의 llink에 n값 할당
	}

	h->first = middle;//h의 first에 middle 값 할당

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {//headNode의 포인터 h, int형 변수 key를 매개변수로 하는 int형 insertNode함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//listNode의 크기만큼 listNode의 포인터 node에 메모리 할당
	node->key = key;//node의 key에 key 값 할당
	node->llink = node->rlink = NULL;//node의 llink와 node의 rlink에 NULL 값 할당

	if (h->first == NULL)//h의 first가 NULL 이라면
	{
		h->first = node;//h의 first에 node 값 할당
		return 0;
	}

	listNode* n = h->first;//listNode의 포인터 n에 h의 first 값 할당

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {//n이 NULL이 아닐동안
		if(n->key >= key) {//n의 key가 key보다 크거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {//n과 h의 first가 같다면
				insertFirst(h, key);//h와key를 매개변수로 insertFirst 함수 실행
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;//node의 rlink에 n값 할당
				node->llink = n->llink;//node의 llink에 n의 llink 값 할당
				n->llink->rlink = node;//n의 llink의 rlink에 node 값 할당
			}
			return 0;
		}

		n = n->rlink;//n에 n의 rlilnk값 할당
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);//h와 key을 매개변수로 insertLast 함수 실행
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {//headNode의 포인터 h와 int형 변수 key 로 매개변수로 하는 int형 함수 deleteNode

	if (h->first == NULL)//h의 first가 NULL와 같다면
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;//listNode의 포인터 n에 h의 first값 할당

	while(n != NULL) {//n이 NULL이 아닐동안
		if(n->key == key) {//n의 key가 key와 같다면
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);//h을 매개변수로 deleteFirst함수 실행
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);//h을 매개변수로 deleteFirst함수 실행
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;//n의 llink의 rlink에 n의 rlink값 할당
				n->rlink->llink = n->llink;//n의 rlinlk의 llink에 n의 llink값 할당
				free(n);//n에 할당된 메모리 해제
			}
			return 1;
		}

		n = n->rlink;//n에 n의 rlink값 할당
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


