    int i = q->front;
    while (1)
    {
        printf("%d ", q->items[i]);
        if (i == q->rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");