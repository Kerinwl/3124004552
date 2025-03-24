#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;
//栈结点结构

typedef struct {
    Node* top;
} Stack;

void initStack(Stack* stack) {
    stack->top = NULL;
}//栈的初始化

void push(Stack* stack, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}//入栈

int pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty\n");
        return -1;
    }
    Node* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}//出栈

int peek(Stack* stack) {
    if (stack->top == NULL) {
        printf("栈为空，无法出栈\n");
        return -1;
    }
    return stack->top->data;
}//获取栈顶元素

int isEmpty(Stack *stack){
    return stack->top==NULL;
}//判断是否为空

/*Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}//栈的创建
*/
/*--------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}//优先级判断

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}//四则运算

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}


int evaluate(char *exp) {
    Stack values, operators;
    initStack(&values);
    initStack(&operators);

    int i = 0;
    while (exp[i] != '\0') {
        if (isdigit(exp[i])) {
            int val = 0;
            while (isdigit(exp[i])) {
                val = (val * 10) + (exp[i] - '0');
                i++;
            }
            push(&values, val);
            i--;
        } else if (exp[i] == '(') {
            push(&operators, exp[i]);
        } else if (exp[i] == ')') {
            while (peek(&operators) != '(')
                push(&values, applyOp(pop(&values), pop(&values), pop(&operators)));
            pop(&operators); 
        } else if (isOperator(exp[i])) {
            while (!isEmpty(&operators) && precedence(peek(&operators)) >= precedence(exp[i]))
                push(&values, applyOp(pop(&values), pop(&values), pop(&operators)));
            push(&operators, exp[i]);
        }
        i++;
    }

    while (!isEmpty(&operators))
        push(&values, applyOp(pop(&values), pop(&values), pop(&operators)));

    return pop(&values);
}

int main() {
    char expression[100];
    printf("Enter an expression: ");
    fgets(expression, sizeof(expression), stdin);
    //expression[strspn(expression, "\n")] = 0; // 去除换行符

    int result = evaluate(expression);
    printf("Result: %d\n", result);

    return 0;
}

   