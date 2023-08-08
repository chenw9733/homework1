//06006084陳玟錡 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 節點的資料結構
typedef struct TreeNode {
    int id;
    char school[100];
    char department[100];
    char dayNight[100];
    char level[100];
    int studentCount;
    int height;  // 新增一個高度欄位
    struct TreeNode *left;
    struct TreeNode *middle;
    struct TreeNode *right;
} TreeNode;

// 將資料插入2-3樹中
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

// 中序遍歷並印出2-3樹的節點
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

// 更新每個節點的高度
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
    printf("* 1. 建立 2-3 樹           *\n");
    printf("* 2. 建立 AVL 樹           *\n");
    printf("* 3. 交集查詢              *\n");
    printf("*************************************\n");
    printf("輸入選項(0, 1, 2, 3): ");
    int choice;
    scanf("%d", &choice);

    if (choice == 0) {
        printf("退出...\n");
        return 0;
    } else if (choice == 1) {
        printf("輸入檔案編號（輸入 0 則退出）: ");
        scanf("%d", &fileNumber);

        if (fileNumber == 0) {
            printf("退出...\n");
            return 0;
        } else {
            char fileName[20];
            sprintf(fileName, "input%d.txt", fileNumber);
            FILE *file = fopen(fileName, "r");
            if (file == NULL) {
                printf("錯誤：無法開啟檔案。\n");
                return 1;
            }

            TreeNode *root = NULL;
            int recordCount = 0;
            char schoolName[100];
            char line[1000];

            // 跳過前三行
            for (int i = 0; i < 3; i++) {
                fgets(line, sizeof(line), file);
            }

            while (fgets(line, sizeof(line), file) != NULL) {
                char *token = strtok(line, "\t");
                if (token != NULL) {
                    recordCount++;
                    if (recordCount > 3) {  // 跳過前三筆記錄
                        token = strtok(NULL, "\t");  // 跳過學校代碼
                        token = strtok(NULL, "\t");  // 取得學校名稱
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

            // 更新節點高度
            updateHeight(root);

            if (root == NULL) {
                printf("樹為空。\n");
            } else {
                printTree(root);
            }

        }
    } else {
        printf("無效選項。請選擇有效選項。\n");
    }

    return 0;
}

