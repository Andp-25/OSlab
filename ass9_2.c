#include <stdio.h>
#include <stdlib.h>

// Define a node structure to represent key-value pairs
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

// Define the MRU Cache structure
typedef struct {
    int capacity;
    Node* head;
} MRUCache;

MRUCache* createMRUCache(int capacity) {
    MRUCache* cache = (MRUCache*)malloc(sizeof(MRUCache));
    cache->capacity = capacity;
    cache->head = NULL;
    return cache;
}

int get(MRUCache* cache, int key) {
    Node* current = cache->head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
            if (prev != NULL) {
                prev->next = current->next;
                current->next = cache->head;
                cache->head = current;
            }
            return current->value;
        }
        prev = current;
        current = current->next;
    }

    return -1;
}

void set(MRUCache* cache, int key, int value) {
    int existingValue = get(cache, key);
    Node* current = cache->head;
    if (existingValue != -1) {
        // Key exists, update its value
        
        while (current != NULL) {
            if (current->key == key) {
                current->value = value;
                break;
            }
            current = current->next;
        }
    } else {
        // Key does not exist, add it
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->value = value;
        newNode->next = cache->head;
        cache->head = newNode;

        // If the cache exceeds capacity, remove the least recently used item
        if (cache->capacity > 0) {
            Node* tailPrev = NULL;
            current = cache->head;
            while (current->next != NULL) {
                tailPrev = current;
                current = current->next;
            }
            if (tailPrev != NULL) {
                tailPrev->next = NULL;
            }
            free(current);
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int cap, q;
        scanf("%d", &cap);
        scanf("%d", &q);

        MRUCache* cache = createMRUCache(cap);

        for (int i = 0; i < q; i++) {
            char type;
            int key, value;
            scanf(" %c", &type); // Read 's' or 'g'
            if (type == 's') {
                scanf("%d %d", &key, &value);
                set(cache, key, value);
            } else if (type == 'g') {
                scanf("%d", &key);
                int result = get(cache, key);
                printf("%d\n", result);
            }
        }
    }

    return 0;
}

