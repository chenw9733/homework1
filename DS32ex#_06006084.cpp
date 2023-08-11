//06006084 陳玟錡 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    int id;                 // 代表節點的識別號
    char school[100];       // 學校名稱，最多可以存放 100 個字元
    char department[100];   // 學系名稱，最多可以存放 100 個字元
    char dayNight[100];     // 日間或夜間制，最多可以存放 100 個字元
    char level[100];        // 學位層級，最多可以存放 100 個字元
    char studentCount[100]; // 學生人數，最多可以存放 100 個字元
    struct TreeNode *left;   // 左子節點的指標
    struct TreeNode *middle; // 中間子節點的指標
    struct TreeNode *right;  // 右子節點的指標
} TreeNode;

TreeNode *insert(TreeNode *root, int id, const char *school, const char *department, const char *dayNight, const char *level, const char *studentCount) {
    // 如果根節點為空，表示樹是空的，可以直接插入新節點
    if (root == NULL) {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));  // 分配新節點的記憶體空間
        newNode->id = id;
        strcpy(newNode->school, school);  // 複製字串到新節點的成員
        strcpy(newNode->department, department);
        strcpy(newNode->dayNight, dayNight);
        strcpy(newNode->level, level);
        strcpy(newNode->studentCount, studentCount);
        newNode->left = newNode->middle = newNode->right = NULL;  // 初始化子節點指標
        return newNode;  // 返回新節點作為新的根節點
    }

    // 比較新節點的學校名稱和當前節點的學校名稱，以決定插入的方向
    if (strcmp(school, root->school) == 0) {
        // 如果學校名稱相同，將新節點插入到當前節點的中間子節點位置
        root->middle = insert(root->middle, id, school, department, dayNight, level, studentCount);
    } else if (strcmp(school, root->school) < 0) {
        // 如果新節點的學校名稱小於當前節點的學校名稱，插入到左子節點位置
        root->left = insert(root->left, id, school, department, dayNight, level, studentCount);
    } else {
        // 否則，插入到右子節點位置
        root->right = insert(root->right, id, school, department, dayNight, level, studentCount);
    }

    return root;  // 返回修改後的樹的根節點
}

void printTree(TreeNode *root) {
    // 如果根節點不為空，執行遞迴印出節點的操作
    if (root != NULL) {
        printTree(root->left);  // 遞迴印出左子樹的節點
        // 使用 printf 函式輸出節點的資訊，包括識別號和各種屬性
        printf("%d: [%d] %s, %s, %s, %s, %s\n", root->id, root->id, root->school, root->department, root->dayNight, root->level, root->studentCount);
        printTree(root->middle);  // 遞迴印出中間子樹的節點
        printTree(root->right);   // 遞迴印出右子樹的節點
    }
}

int main() {
	int choice;
    int fileNumber;
	
	do{
		printf("*** Search Tree Utilities **\n");
	    printf("* 0. QUIT                  *\n");
	    printf("* 1. Build 2-3 tree        *\n");
	    printf("* 2. Build AVL tree        *\n");
	    printf("* 3. Intersection Query    *\n");
	    printf("*************************************\n");
	    printf("Input a choice(0, 1, 2, 3): ");
	    scanf("%d", &choice);
	    
	    switch(choice){
	    	case 0:
	    		return 0;
	    	case 1:
	    		printf("Input a file number ([0] Quit): ");
		        scanf("%d", &fileNumber);
		
		        if (fileNumber == 0) {
		            printf("Exiting...\n");
		            return 0;
		        } 
				else {
		            char fileName[20];
		            sprintf(fileName, "input%d.txt", fileNumber);
		            FILE *file = fopen(fileName, "r");
		            
		            if (file == NULL) {
		                printf("Error opening file.\n");
		                return 1;
		            }
		
		            TreeNode *root = NULL;
		            int recordCount = 0;
		            char schoolName[100];
		            char line[1000];
		
		            while (fgets(line, sizeof(line), file) != NULL) {
					    char *token = strtok(line, "\t");
					    if (token != NULL) {
					        recordCount++;
					        if (recordCount > 3) {  // 跳過前三筆記錄
					            token = strtok(NULL, "\t");  // 跳過學校代碼
					            char department[100];
					            char dayNight[100];
					            char level[100];
					            char studentCount[100];
					            if (token != NULL) {  // 確保有token
					                strcpy(schoolName, token);  // 更新學校名稱
					                for (int i = 0; i < 5; i++) {
					                    token = strtok(NULL, "\t");
					                    if (i == 0) {
					                        strcpy(department, token);
					                    } else if (i == 1) {
					                        strcpy(dayNight, token);
					                    } else if (i == 2) {
					                        strcpy(level, token);
					                    } else if (i == 3) {
					                        strcpy(studentCount, token);
					                    }
					                }
					                root = insert(root, recordCount - 3, schoolName, department, dayNight, level, studentCount);
					            }
					        }
					    }
					}
		
		            fclose(file);
		
		            if (root == NULL) {
		                printf("Tree is empty.\n");
		            } 
					else {
		                printTree(root);
		            }
		        }
			    break;
			default:
				printf("Command does not exist!\n");
		}	
	}while(choice!=0);
	
    return 0;
}
