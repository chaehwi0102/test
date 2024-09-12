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

void init(LinkedStackType* s) {
    s->top = NULL;
}

int is_empty(LinkedStackType* s) {
    return s->top == NULL;
}

void push(LinkedStackType* s, TreeNode* node) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->treeNode = node;
    temp->next = s->top;
    s->top = temp;
    printf("push(%d) ", node->data);
}

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

TreeNode* create_node(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

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
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 5);

    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 6);

    PlaceNode(root->right, 0, 7);
    PlaceNode(root->right, 1, 8);

    PlaceNode(root->left->left, 0, 4);
}

void LinkPreOrder(TreeNode* root) {
    printf("전위 순회의 출력 예\n");
    LinkedStackType s;
    init(&s);
    if (root == NULL) return;

    push(&s, root);
    while (!is_empty(&s)) {
        TreeNode* node = pop(&s);
        printf("visit(%d)\n", node->data);

        if (node->right) push(&s, node->right);
        if (node->left) push(&s, node->left);
    }
    printf("\n");
}

void LinkInOrder(TreeNode* root) {
    printf("중위 순회의 출력 예\n");
    LinkedStackType s;
    init(&s);
    TreeNode* node = root;

    while (node != NULL || !is_empty(&s)) {
        while (node != NULL) {
            push(&s, node);
            node = node->left;
        }
        node = pop(&s);
        printf("visit(%d)\n", node->data);
        node = node->right;
    }
    printf("\n");
}

void LinkPostOrder(TreeNode* root) {
    printf("후위 순회의 출력 예\n");
    LinkedStackType s1, s2;
    init(&s1);
    init(&s2);

    if (root == NULL) return;
    push(&s1, root);

    while (!is_empty(&s1)) {
        TreeNode* node = pop(&s1);
        push(&s2, node);

        if (node->left) push(&s1, node->left);
        if (node->right) push(&s1, node->right);
    }

    while (!is_empty(&s2)) {
        TreeNode* node = pop(&s2);
        printf("visit(%d)\n", node->data);
    }
    printf("\n");
}

void LinkOrders(TreeNode* root) {
    LinkPreOrder(root);
    LinkInOrder(root);
    LinkPostOrder(root);
}

int main() {
    TreeNode* root = create_node(1);
    GenerateLinkTree(root);
    LinkOrders(root);
    return 0;
}
