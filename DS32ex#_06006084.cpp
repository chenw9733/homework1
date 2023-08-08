//06006084�����B 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �`�I����Ƶ��c
typedef struct TreeNode {
    int id;
    char school[100];
    char department[100];
    char dayNight[100];
    char level[100];
    int studentCount;
    int height;  // �s�W�@�Ӱ������
    struct TreeNode *left;
    struct TreeNode *middle;
    struct TreeNode *right;
} TreeNode;

// �N��ƴ��J2-3��
TreeNode *insert(TreeNode *root, int id, const char *school, const char *department, const char *dayNight, const char *level, int studentCount) {
    if (root == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->id = id;
        strcpy(newNode->school, school);
        strcpy(newNode->department, department);
        strcpy(newNode->dayNight, dayNight);
        strcpy(newNode->level, level);
        newNode->studentCount = studentCount;
        newNode->left = newNode->middle = newNode->right = NULL;
        return newNode;
    }

    if (strcmp(school, root->school) == 0) {
        root->middle = insert(root->middle, id, school, department, dayNight, level, studentCount);
    } else if (strcmp(school, root->school) < 0) {
        root->left = insert(root->left, id, school, department, dayNight, level, studentCount);
    } else {
        root->right = insert(root->right, id, school, department, dayNight, level, studentCount);
    }

    return root;
}

// ���ǹM���æL�X2-3�𪺸`�I
void printTree(TreeNode *node) {
    if (node != NULL) {
        printTree(node->left);
        printf("%d: [%d] %s, %s, %s, %s, %s, %d\n", node->id, node->id, node->school, node->department, node->dayNight, node->level, node->studentCount);
        printTree(node->middle);
        if (node->middle != NULL) {
            printTree(node->middle->right);
        }
        printTree(node->right);
    }
}

// ��s�C�Ӹ`�I������
int updateHeight(TreeNode *node) {
    if (node == NULL) {
        return -1;
    }
    int leftHeight = updateHeight(node->left);
    int middleHeight = updateHeight(node->middle);
    int rightHeight = updateHeight(node->right);
    node->height = 1 + ((leftHeight >= middleHeight) ? leftHeight : middleHeight) + ((middleHeight >= rightHeight) ? middleHeight : rightHeight);
    return node->height;
}

int main() {
    int fileNumber;

    printf("*** Search Tree Utilities **\n");
    printf("* 0. QUIT                  *\n");
    printf("* 1. �إ� 2-3 ��           *\n");
    printf("* 2. �إ� AVL ��           *\n");
    printf("* 3. �涰�d��              *\n");
    printf("*************************************\n");
    printf("��J�ﶵ(0, 1, 2, 3): ");
    int choice;
    scanf("%d", &choice);

    if (choice == 0) {
        printf("�h�X...\n");
        return 0;
    } else if (choice == 1) {
        printf("��J�ɮ׽s���]��J 0 �h�h�X�^: ");
        scanf("%d", &fileNumber);

        if (fileNumber == 0) {
            printf("�h�X...\n");
            return 0;
        } else {
            char fileName[20];
            sprintf(fileName, "input%d.txt", fileNumber);
            FILE *file = fopen(fileName, "r");
            if (file == NULL) {
                printf("���~�G�L�k�}���ɮסC\n");
                return 1;
            }

            TreeNode *root = NULL;
            int recordCount = 0;
            char schoolName[100];
            char line[1000];

            // ���L�e�T��
            for (int i = 0; i < 3; i++) {
                fgets(line, sizeof(line), file);
            }

            while (fgets(line, sizeof(line), file) != NULL) {
                char *token = strtok(line, "\t");
                if (token != NULL) {
                    recordCount++;
                    if (recordCount > 3) {  // ���L�e�T���O��
                        token = strtok(NULL, "\t");  // ���L�ǮեN�X
                        token = strtok(NULL, "\t");  // ���o�ǮզW��
                        strcpy(schoolName, token);
                        char department[100];
                        char dayNight[100];
                        char level[100];
                        int studentCount;
                        for (int i = 0; i < 5; i++) {
                            token = strtok(NULL, "\t");
                            if (i == 0) {
                                strcpy(department, token);
                            } else if (i == 1) {
                                strcpy(dayNight, token);
                            } else if (i == 2) {
                                strcpy(level, token);
                            } else if (i == 3) {
                                studentCount = atoi(token);
                            }
                        }
                        root = insert(root, recordCount - 3, schoolName, department, dayNight, level, studentCount);
                    }
                }
            }

            fclose(file);

            // ��s�`�I����
            updateHeight(root);

            if (root == NULL) {
                printf("�𬰪šC\n");
            } else {
                printTree(root);
            }

        }
    } else {
        printf("�L�Ŀﶵ�C�п�ܦ��Ŀﶵ�C\n");
    }

    return 0;
}

