#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>


// usually prime numbers are used to minimize collisions on modulo 
#define HASH_TABLE_SIZE 47



typedef struct Person{
    const char *name;
    const char *address;
    int age;
}Person;


typedef struct HashTable{
    struct ValueStruct{
        const char *key;
        
        Person p;
        bool occupied;
    }values[HASH_TABLE_SIZE];
}HashTable;


// the hash function: https://en.wikipedia.org/wiki/Adler-32
uint32_t adler32(unsigned char *data, size_t len) 
{
    const uint32_t MOD_ADLER = 65521;
    
    uint32_t a = 1, b = 0;
    size_t index;
    
    for (index = 0; index < len; ++index)
    {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
    
    return (b << 16) | a;
}


void insertKeyValue(HashTable *h, const char *key, Person value){
    // hash the key using the hash function
    uint32_t hashedValue = adler32((unsigned char *)key, strlen(key));

    // mod the hash value so that the index lies within the array bounds
    uint32_t index = hashedValue % HASH_TABLE_SIZE;

    // if index isnt occupied, ie, is free
    if (!h->values[index].occupied){
        h->values[index].p = value;
        h->values[index].occupied = true;
        h->values[index].key = key;
    }
    // else resolve collision
    // here closed chaining is used with linear probing to find new index 
    else{
        for (int i=1; i< HASH_TABLE_SIZE; i++){
            // find new index
            uint32_t newIndex = (index + i) % HASH_TABLE_SIZE;
        
            // if new index is free, add and return 
            if (!h->values[newIndex].occupied){
                h->values[newIndex].p = value;
                h->values[newIndex].occupied = true;        
                h->values[newIndex].key = key;
                return;
            }
        }
        printf("Cant add new value: Hash table is completely full\n");
    }

}


void removeKeyValue(HashTable *h, const char *key){
    // hash the key using the hash function
    uint32_t hashedValue = adler32((unsigned char *)key, strlen(key));

    uint32_t index = hashedValue % HASH_TABLE_SIZE;

    // if key is at index
    if (h->values[index].occupied && h->values[index].key == key){
        h->values[index].occupied = false;
    }
    else{
        for (int i=1; i< HASH_TABLE_SIZE; i++){
            // find new index
            uint32_t newIndex = (index + i) % HASH_TABLE_SIZE;
        
            // if new index is free, remove and return 
            if (!h->values[newIndex].occupied && h->values[index].key == key){
                h->values[newIndex].occupied = false;        
                return;
            }
        }
        printf("Cant delete key value: Not found\n");
    }
}



Person* getValue(HashTable *h, const char *key){
    // hash the key using the hash function
    uint32_t hashedValue = adler32((unsigned char *)key, strlen(key));

    // mod the hash value so that the index lies within the array bounds
    uint32_t index = hashedValue % HASH_TABLE_SIZE;

    // if key matches the one stored at index
    if (h->values[index].occupied && h->values[index].key == key){
        return &h->values[index].p;
    }
    // else there was collision when adding
    // check new indices to find the key 
    else{
        for (int i=1; i< HASH_TABLE_SIZE; i++){
            // find new index
            uint32_t newIndex = (index + i) % HASH_TABLE_SIZE;
        
            // if key matches
            if (h->values[newIndex].key == key){
                return &h->values[newIndex].p;
            }
        }
        printf("Cant find key\n");

        return NULL;
    }
}







int main(){
    // init to zero
    HashTable h = {0};

    insertKeyValue(&h, "Ram", (Person){.name = "Ram", .age = 19, .address = "Kathmandu"});
    insertKeyValue(&h, "Shyam", (Person){.name = "Shyam", .age = 20, .address = "Bhaktapur"});
    insertKeyValue(&h, "Hari", (Person){.name = "Hari", .age = 19, .address = "Pokhara"});

    // get data of Shyam
    Person *ShyamData = getValue(&h, "Shyam");
    printf("Name: %s Address: %s Age: %d\n", ShyamData->name, ShyamData->address, ShyamData->age);

    // change data of shyam
    ShyamData->address = "Lalitpur";
    printf("Name: %s Address: %s Age: %d\n", ShyamData->name, ShyamData->address, ShyamData->age);

    // remove a key
    removeKeyValue(&h, "Ram");
    Person *RamData = getValue(&h, "Ram");
    if (RamData == NULL){
        printf("Cant find key %s", "Ram");
    }

    return 0;
}
