    Queue *temp = initialize();

    // Pop elements to temp while printing
    while (!isEmpty(q)) {
        int val = dequeue(q);
        printf("%d -> ", val);
        enqueue(temp, val);
    }
    printf("NULL\n");

    // Restore original stack
    while (!isEmpty(temp)) {
        enqueue(q, dequeue(temp));
    }