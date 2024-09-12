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

// ���� �ʱ�ȭ
void init(LinkedStackType* s) {
    s->top = NULL;
}

// ������ ������� Ȯ��
int is_empty(LinkedStackType* s) {
    return s->top == NULL;
}

// ���� push �Լ�
void push(LinkedStackType* s, TreeNode* node) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->treeNode = node;
    temp->next = s->top;
    s->top = temp;
    printf("push(%d) ", node->data);
}

// ���� pop �Լ�
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

// Ʈ�� ��� ����
TreeNode* create_node(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// ��带 Ʈ���� ��ġ�ϴ� �Լ� (0: ����, 1: ������)
void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* new_node = create_node(data);
    if (direction == 0) {
        node->left = new_node;
    }
    else {
        node->right = new_node;
    }
}

// Ʈ�� ����
void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);  // root�� ���ʿ� 2 �߰�
    PlaceNode(root, 1, 5);  // root�� �����ʿ� 5 �߰�

    PlaceNode(root->left, 0, 3);  // 2�� ���ʿ� 3 �߰�
    PlaceNode(root->left, 1, 6);  // 2�� �����ʿ� 6 �߰�

    PlaceNode(root->right, 0, 7);  // 5�� ���ʿ� 7 �߰�
    PlaceNode(root->right, 1, 8);  // 5�� �����ʿ� 8 �߰�

    PlaceNode(root->left->left, 0, 4);  // 3�� ���ʿ� 4 �߰�
}

// ���� ��ȸ (Pre-order Traversal)
void LinkPreOrder(TreeNode* root) {
    printf("���� ��ȸ�� ��� ��\n");
    LinkedStackType s;
    init(&s);
    if (root == NULL) return;

    push(&s, root);
    while (!is_empty(&s)) {
        TreeNode* node = pop(&s);
        printf("visit(%d)\n", node->data);

        if (node->right) push(&s, node->right);  // ������ �ڽ� ����
        if (node->left) push(&s, node->left);    // ���� �ڽ� ���߿�
    }
    printf("\n");
}

// ���� ��ȸ (In-order Traversal)
void LinkInOrder(TreeNode* root) {
    printf("���� ��ȸ�� ��� ��\n");
    LinkedStackType s;
    init(&s);
    TreeNode* node = root;

    while (node != NULL || !is_empty(&s)) {
        while (node != NULL) {
            push(&s, node);   // ���� �ڽĵ� �� push
            node = node->left;
        }
        node = pop(&s);
        printf("visit(%d)\n", node->data);  // �湮
        node = node->right;  // ������ �ڽ����� �̵�
    }
    printf("\n");
}

// ���� ��ȸ (Post-order Traversal)
void LinkPostOrder(TreeNode* root) {
    printf("���� ��ȸ�� ��� ��\n");
    LinkedStackType s1, s2;
    init(&s1);
    init(&s2);

    if (root == NULL) return;
    push(&s1, root);

    while (!is_empty(&s1)) {
        TreeNode* node = pop(&s1);
        push(&s2, node);  // ���� ��ȸ �������� ���ÿ� ����

        if (node->left) push(&s1, node->left);
        if (node->right) push(&s1, node->right);
    }

    // ����2���� pop�Ͽ� ���
    while (!is_empty(&s2)) {
        TreeNode* node = pop(&s2);
        printf("visit(%d)\n", node->data);
    }
    printf("\n");
}

// ��ȸ ����
void LinkOrders(TreeNode* root) {
    LinkPreOrder(root);
    LinkInOrder(root);
    LinkPostOrder(root);
}

// ���� �Լ�
int main() {
    TreeNode* root = create_node(1);  // ��Ʈ ��� ����
    GenerateLinkTree(root);  // Ʈ�� ����
    LinkOrders(root);        // ����, ����, ���� ��ȸ ����
    return 0;
}
