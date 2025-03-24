#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;
//ջ���ṹ

typedef struct {
    Node* top;
} Stack;

void initStack(Stack* stack) {
    stack->top = NULL;
}//ջ�ĳ�ʼ��

void push(Stack* stack, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}//��ջ

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
}//��ջ

int peek(Stack* stack) {
    if (stack->top == NULL) {
        printf("ջΪ�գ��޷���ջ\n");
        return -1;
    }
    return stack->top->data;
}//��ȡջ��Ԫ��

int isEmpty(Stack *stack){
    return stack->top==NULL;
}//�ж��Ƿ�Ϊ��

/*Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}//ջ�Ĵ���
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
}//���ȼ��ж�

int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}//��������

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
    //expression[strspn(expression, "\n")] = 0; // ȥ�����з�

    int result = evaluate(expression);
    printf("Result: %d\n", result);

    return 0;
}

   