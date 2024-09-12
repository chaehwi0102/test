#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

// 스택 초기화
void init(LinkedStackType* s) {
    s->top = NULL;
}

// 스택이 비었는지 확인
int is_empty(LinkedStackType* s) {
    return s->top == NULL;
}

// 스택 push 함수
void push(LinkedStackType* s, TreeNode* node) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->treeNode = node;
    temp->next = s->top;
    s->top = temp;
    printf("push(%d) ", node->data);
}

// 스택 pop 함수
TreeNode* pop(LinkedStackType* s) {
    if (is_empty(s)) {
        printf("Stack is empty!\n");
        exit(1);
    }
    StackNode* temp = s->top;
    TreeNode* poppedNode = temp->treeNode;
    s->top = temp->next;
    free(temp);
    printf("pop(%d) ", poppedNode->data);
    return poppedNode;
}

// 트리 노드 생성
TreeNode* create_node(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// 노드를 트리에 배치하는 함수 (0: 왼쪽, 1: 오른쪽)
void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* new_node = create_node(data);
    if (direction == 0) {
        node->left = new_node;
    }
    else {
        node->right = new_node;
    }
}

// 트리 생성
void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);  // root의 왼쪽에 2 추가
    PlaceNode(root, 1, 5);  // root의 오른쪽에 5 추가

    PlaceNode(root->left, 0, 3);  // 2의 왼쪽에 3 추가
    PlaceNode(root->left, 1, 6);  // 2의 오른쪽에 6 추가

    PlaceNode(root->right, 0, 7);  // 5의 왼쪽에 7 추가
    PlaceNode(root->right, 1, 8);  // 5의 오른쪽에 8 추가

    PlaceNode(root->left->left, 0, 4);  // 3의 왼쪽에 4 추가
}

// 전위 순회 (Pre-order Traversal)
void LinkPreOrder(TreeNode* root) {
    printf("전위 순회의 출력 예\n");
    LinkedStackType s;
    init(&s);
    if (root == NULL) return;

    push(&s, root);
    while (!is_empty(&s)) {
        TreeNode* node = pop(&s);
        printf("visit(%d)\n", node->data);

        if (node->right) push(&s, node->right);  // 오른쪽 자식 먼저
        if (node->left) push(&s, node->left);    // 왼쪽 자식 나중에
    }
    printf("\n");
}

// 중위 순회 (In-order Traversal)
void LinkInOrder(TreeNode* root) {
    printf("중위 순회의 출력 예\n");
    LinkedStackType s;
    init(&s);
    TreeNode* node = root;

    while (node != NULL || !is_empty(&s)) {
        while (node != NULL) {
            push(&s, node);   // 왼쪽 자식들 다 push
            node = node->left;
        }
        node = pop(&s);
        printf("visit(%d)\n", node->data);  // 방문
        node = node->right;  // 오른쪽 자식으로 이동
    }
    printf("\n");
}

// 후위 순회 (Post-order Traversal)
void LinkPostOrder(TreeNode* root) {
    printf("후위 순회의 출력 예\n");
    LinkedStackType s1, s2;
    init(&s1);
    init(&s2);

    if (root == NULL) return;
    push(&s1, root);

    while (!is_empty(&s1)) {
        TreeNode* node = pop(&s1);
        push(&s2, node);  // 후위 순회 역순으로 스택에 저장

        if (node->left) push(&s1, node->left);
        if (node->right) push(&s1, node->right);
    }

    // 스택2에서 pop하여 출력
    while (!is_empty(&s2)) {
        TreeNode* node = pop(&s2);
        printf("visit(%d)\n", node->data);
    }
    printf("\n");
}

// 순회 실행
void LinkOrders(TreeNode* root) {
    LinkPreOrder(root);
    LinkInOrder(root);
    LinkPostOrder(root);
}

// 메인 함수
int main() {
    TreeNode* root = create_node(1);  // 루트 노드 생성
    GenerateLinkTree(root);  // 트리 생성
    LinkOrders(root);        // 전위, 중위, 후위 순회 실행
    return 0;
}
