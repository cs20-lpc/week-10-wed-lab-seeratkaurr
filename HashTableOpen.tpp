template <typename Key, typename Val>
HashTableOpen<Key, Val>::HashTableOpen(int size) {
    M = size;
    ht = new LinkedList<Record>*[M];
    for (int i = 0; i < M; i++) {
        ht[i] = new LinkedList<Record>();
    }
}

template <typename Key, typename Val>
HashTableOpen<Key, Val>::~HashTableOpen() {
    for (int i = 0; i < M; i++) {
        delete ht[i];
    }
    delete[] ht;
}

// FIND
template <typename Key, typename Val>
Val HashTableOpen<Key, Val>::find(const Key& k) const {
    int slot = hash(k);
    LinkedList<Record>* list = ht[slot];

    int len = list->getLength();
    for (int i = 0; i < len; i++) {
        Record r = list->getElement(i);
        if (r.k == k) {
            return r.v;
        }
    }
    throw string("find: key not found");
}

// INSERT
template <typename Key, typename Val>
void HashTableOpen<Key, Val>::insert(const Key& k, const Val& v) {
    int slot = hash(k);
    LinkedList<Record>* list = ht[slot];

    // check for duplicates
    int len = list->getLength();
    for (int i = 0; i < len; i++) {
        Record r = list->getElement(i);
        if (r.k == k) {
            throw string("insert: duplicate key not allowed");
        }
    }

    // append new record (O(1))
    Record newRec(k, v);
    list->append(newRec);
}

// REMOVE
template <typename Key, typename Val>
void HashTableOpen<Key, Val>::remove(const Key& k) {
    int slot = hash(k);
    LinkedList<Record>* list = ht[slot];

    int len = list->getLength();
    for (int i = 0; i < len; i++) {
        Record r = list->getElement(i);
        if (r.k == k) {
            list->remove(i);
            return;
        }
    }
    throw string("remove: key not found");
}

// SIZE
template <typename Key, typename Val>
int HashTableOpen<Key, Val>::size() const {
    int total = 0;
    for (int i = 0; i < M; i++) {
        total += ht[i]->getLength();
    }
    return total;
}
