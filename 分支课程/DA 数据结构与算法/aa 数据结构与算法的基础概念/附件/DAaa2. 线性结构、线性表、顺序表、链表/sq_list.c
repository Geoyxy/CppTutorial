#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_SIZE 10000

// 页表项 
typedef struct {
	int page_id;       // 页ID 
	int page_frame_id; // 页框ID 
} PTE;

typedef PTE ElementPack;

// 比较两个元素包装的内容是否相等 
int ElementPackEquiv(ElementPack element, ElementPack* element_p) {
	// 参数是否非法
	if (!element_p) return 0; 
	return (element.page_id == element_p->page_id) && (element.page_frame_id == element_p->page_frame_id);
}

// 获取元素包装的字符串表示到 buf
void ElementPackToString(const ElementPack* element, char* buf, size_t buf_size) {
	// 参数是否非法 
	if (!element || !buf || buf_size == 0) return;
	snprintf(buf, buf_size, "页ID：%d\t页框ID：%d", element->page_id, element->page_frame_id);
} 

// ========================= 顺序表的核心实现 ==================== 

// 状态 
typedef enum {
	OK = 1,       // 成功 
	ERROR = 0,    // 通用错误 
	OVERFLOW = -2 // 申请堆内存失败 
} Status;

// 顺序表 
typedef struct {
	ElementPack* elements; // 列表 
	int length;            // 当前长度 
} SqList; 

// 初始化列表 
// 参数 list：存储列表地址的指针 
Status InitList(SqList* list) {
	// 判断列表是否无效 
	if (list == NULL) return ERROR;
	
	list->elements = (ElementPack*)malloc(MAX_SIZE * sizeof(ElementPack));
	if (list->elements == NULL) return OVERFLOW;
	list->length = 0;
	return OK;
}

// 销毁列表
// 参数 list： 要操作的列表 
Status DestroyList(SqList* list) {
	// 判断列表是否无效 
	if (list == NULL) return ERROR;
	
	free(list->elements);
	list->elements = NULL;
	list->length = 0;
	return OK;
}

// 获取元素
// 参数 list：要操作的顺序表
// 参数 i：要获取到的元素的位序（位序从1开始）
// 参数 element：获取到的元素 
Status GetElement(SqList* list, int i, ElementPack* element) {
	// 判断列表是否无效 
	if (list == NULL || element == NULL) return ERROR;
	
	// 检查访问是否越界 
	if (i < 1 || i > list->length) return ERROR;
	
	*element = list->elements[i - 1];
	return OK;
}

// 获取要查找到元素的位序  
// 参数 list：要操作的顺序表
// 参数 element：要匹配的元素 
// 返回：若 list 为空则返回0,；若找到与 element 的值相同的元素，则返回其位序；否则返回0 
int LocateElement(SqList* list, ElementPack* element) {
	// 判断列表是否无效 
	if (list == NULL || element == NULL) return 0;
	
	for (int i = 0; i < list->length; ++i) {
		if (ElementPackEquiv(list->elements[i], element)) return i + 1;
	}
	return 0;
}

// 将 element 插入位序为 i 的元素前 
// 参数 list：要操作的顺序表
// 参数 i：要插入到的位序
// 参数 element：要插入的元素 
Status ListInsert(SqList* list, int i, ElementPack element) {
	// 判断列表是否无效 
	if (list == NULL) return ERROR;
	
	// 检查访问是否越界（这里允许访问 length+1 以在列表末尾插入）
	if (i < 1 || i > list->length + 1) return ERROR;
	
	// 检查存储空间是否已满
	if (list->length == MAX_SIZE) return ERROR; 
	
	// 将位序为 i 及其以后的元素后移一位 
	for (int j = list->length - 1; j >= i - 1; --j) {
		list->elements[j + 1] = list->elements[j];
	}
	
	// 插入
	list->elements[i - 1] = element;
	++list->length;
	return OK; 
}

// 删除位序为 i 的元素 
// 参数 list：要操作的顺序表
// 参数 i：要删除的元素的位序 
Status ListDelete(SqList* list, int i) {
	// 判断列表是否无效 
	if (list == NULL) return ERROR;
	
	// 检查访问是否越界 
	if (i < 1 || i > list->length) return ERROR;
	
	// 将位序为 i+1 及其以后的元素前移一位 
	for (int j = i; j < list->length; ++j) {
		list->elements[j-1] = list->elements[j]; 
	} 
	--list->length;
	return OK;
}

// ========================= 顺序表的核心实现 ==================== 

// 打印顺序表的元素 
void PrintList(SqList* list) {
	// 检查参数是否非法 
	if(!list) return;
	for (int i = 0; i < list->length; ++i) {
		char buf[128];
		ElementPackToString(&list->elements[i], buf, sizeof(buf));
		printf("%s\n", buf);
	}
}

// 向顺序表中追加元素 
Status ListAppend(SqList* list, const ElementPack* element) {
	// 检查参数是否非法 
	if(!list || !element) return;
	return ListInsert(list, list->length + 1, *element);
}

void test1(void) {
	SqList list;
	InitList(&list);
	
	ElementPack element1;
	element1.page_id = 2;
	element1.page_frame_id = 1;
	
	ListInsert(&list, 1, element1);
	PrintList(&list);
	DestroyList(&list);
}

void test2(void) {
	// 程序依赖的变量 
	SqList list;
	size_t page_id_counter = 0;
	size_t page_frame_id_counter = 0;
	// 检查是否初始化列表失败 
	if (InitList(&list) == OVERFLOW) {
		printf("程序异常退出，错误原因：堆内存分配失败\n");
		exit(2);
	}
	
	// ==================== 程序主循环 ==================== 
	while (1) {
		// =============== 主菜单 =============== 
		printf("\n");
		printf("╔══════════════════════════════╗\n");
		printf("║        进程管理器            ║\n");
		printf("╠══════════════════════════════╣\n");
		printf("║  0. 退出程序                 ║\n");
		printf("║  1. 申请 4KB 虚拟内存        ║\n");
		printf("║  2. 释放 4KB 虚拟内存        ║\n");
		printf("║  3. 查找虚拟内存中的页表项   ║\n");
		printf("║  4. 打印页表                 ║\n");
		printf("╚══════════════════════════════╝\n");
		
		// =============== 获取有效输入 =============== 
		printf("请输入您的选择> ");
		char input = '\0';
		scanf(" %c", &input);
		while (1) {
			if (input >= '0' && input <= '4') {
				break;
			}
			printf("\n%c 不是有效的选择，请重新输入> ", input);
			input = '\0';
			scanf(" %c", &input);
		}
		
		// =============== 处理输入 ===============
		switch (input) {
			case '0': 
				DestroyList(&list);
				printf("\n进程已推出，虚拟内存已释放\n");
				exit(0);
				break;
			case '1': {
				ElementPack element;
				element.page_id = page_id_counter++;
				element.page_frame_id = page_frame_id_counter++;
				
				if (ListAppend(&list, &element)) {
					char buf[128];
					ElementPackToString(&element, buf, sizeof(buf));
					printf("\n已申请 4KB 虚拟内存\n%s\n\n", buf);
				} else {
					printf("\n申请内存失败，错误原因：无可分配的页表项\n\n");
				}
				break;
			}
			case '2': {
				printf("\n请输入要释放的内存对应的页ID或页框ID> ");
				int target_id = 0;
				scanf(" %d", &target_id);
				
				ElementPack element;
				element.page_id = target_id;
				element.page_frame_id = target_id;
				size_t pos = 0;
				char buf[128];
				
				if (pos = LocateElement(&list, &element)) {
					ListDelete(&list, pos);
					ElementPackToString(&element, buf, sizeof(buf));
					printf("虚拟内存已释放\n%s\n\n", buf);
				} else {
					ElementPackToString(&element, buf, sizeof(buf));
					printf("页表项 %s 不存在\n\n", buf);
				}
				break;
			}
			case '3': {
				printf("\n请输入要查找的页表项对应的页ID或页框ID> ");
				int target_id = 0;
				scanf(" %d", &target_id);
				
				ElementPack element;
				element.page_id = target_id;
				element.page_frame_id = target_id;
				size_t pos = 0;
				char buf[128];
				
				if (pos = LocateElement(&list, &element)) {
					ElementPackToString(&element, buf, sizeof(buf));
					printf("页表项 %s 存在，位序为 %d\n\n", buf, pos);
				} else {
					ElementPackToString(&element, buf, sizeof(buf));
					printf("页表项 %s 不存在\n\n", buf);
				}
				break;
			}
			case '4': {
				printf("\n");
				PrintList(&list);
				printf("\n");
				break;
			}
		}
	}
}

int main(void) {
	test2();
	return 0;
}
