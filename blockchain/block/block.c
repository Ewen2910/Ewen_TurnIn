#include "block.h"

// typedef struct Block {
// 	int index;
// 	// array holding the hash off the previous block
// 	BYTE preHash[SHA256_BLOCK_SIZE]; 	//macros provided in header
// 	//  array holding hash of data within block
// 	BYTE dataHash[SHA256_BLOCK_SIZE];
// 	Data *data; 	// pointer to data stored in this block
// 	int nonce; 	// int representing the proof of work validating this block
// 	time_t timestamp;
// 	struct Block *next; 	// next block in the chain
// } Block;

// typedef struct Blockchain {
// 	Block * base; 		//genesis block of the chain, unchanged once chain is initialized
// 	Block *cur;		// the current top of the chain, used for addition of new blocks
// 	int len;			// the number of blocks in the chain
// }Blockchain;

Block *makeBlock(Data *d, Block *pre) {
    //This is where we create a block. For the creation of single block we hash the previous block and store it in this new block. For the genesis block we hash some arbitrary data and store that. Then we fill up the new block struct (everything except the dataHash) start its nonce at 0, we increment the nonce until the hash result satisfies our proof of work condition. For this function I made 2 helper functions hashBlock(Block *bm BYTE *buff) and hashBlockData(Block *b, BYTE *buff). hashBlock hashes the whole block and stores it in the buff. hashBlockData hashes a block without its dataHash. hashBlock is used to generate the preHash and hashBlockData iss used to generate the dataHash.
    Block *bl = malloc(sizeof(Block));

    bl->data = d;
    bl->index = pre->index + 1;
    bl->nonce = 0;
    bl->timestamp = time(NULL);
    bl->next = NULL;
    hashBlock(pre, bl->preHash);
    hashBlockData(bl, bl->dataHash);

    return bl;

}

Blockchain *makeBlockchain() {
    //creates struct and initializes the chain with genesis block
    Blockchain *bc = malloc(sizeof(Blockchain));
    bc->base = malloc(sizeof(Block));
    bc->base->data = malloc(sizeof(Data));
    // bc->base->data->data = 0;
    // bc->base->data->next = NULL;
    bc->base->index = 0;
    bc->base->nonce = 0;
    bc->base->timestamp = time(NULL);
    bc->base->next = NULL;
    hashBlockData(bc->base, bc->base->dataHash);
    bc->cur = bc->base;
    bc->len = 1;

    return bc;
}
    //creates struct and initializes the chain with genesis block



bool addBlock(Blockchain *bc, Block *b) {
    if (bc->cur->index + 1 != b->index) {
        return false;
    }
    if (bc->cur->next != NULL) {
        return false;
    }
    bc->cur->next = b;
    bc->cur = b;
    bc->len++;

    return true;
}

bool validateChain(Blockchain *bc) {
    Block *cur = bc->base;
    BYTE *buff = malloc(sizeof(BYTE) * SHA256_BLOCK_SIZE);
    while (cur->next != NULL) {
        hashBlock(cur, buff);
        if (memcmp(buff, cur->next->preHash, SHA256_BLOCK_SIZE) != 0) {
            return false;
        }
        cur = cur->next;
    }
    return true;
}

void printBlock(Block *block) {
    printf("Block %d\n", block->index);
    printf("Timestamp: %s", ctime(&block->timestamp));
    printf("Nonce: %d\n", block->nonce);
    printf("Previous Hash: ");
    for (int i = 0; i != SHA256_BLOCK_SIZE; i++) {
        printf("%02x", block->preHash[i]);
    }
    printf("\n");
    printf("Data Hash: ");
    for (int i = 0; i != SHA256_BLOCK_SIZE; i++) {
        printf("%02x", block->dataHash[i]);
    }
    printf("\n");
    // printf("Data: %s\n", block->data->data);
}

void printChain(Blockchain *bc, void (*printFunc)(Block*)) {
    Block *cur = bc->base;
    while (cur != NULL) {
        printFunc(cur);
        cur = cur->next;
    }
}

void freeBlockchain(Blockchain *bc) {
    Block *cur = bc->base;
    Block *next = cur->next;
    while (next != NULL) {
        free(cur);
        cur = next;
        next = cur->next;
    }
    free(cur);
    free(bc);
}

void saveBlockchain(char *file, Blockchain *bc) {
    FILE *fp = fopen(file, "w");
    Block *cur = bc->base;
    while (cur != NULL) {
        fprintf(fp, "%d\n", cur->index);
        fprintf(fp, "%d\n", cur->nonce);
        // fprintf(fp, "%s\n", cur->data->data);
        fprintf(fp, "%s\n", ctime(&cur->timestamp));
        for (int i = 0; i != SHA256_BLOCK_SIZE; i++) {
            fprintf(fp, "%02x", cur->preHash[i]);
        }
        fprintf(fp, "\n");
        for (int i = 0; i != SHA256_BLOCK_SIZE; i++) {
            fprintf(fp, "%02x", cur->dataHash[i]);
        }
        fprintf(fp, "\n");
        cur = cur->next;
    }
    fclose(fp);
}

Block *loadBlockchain(char *file, Blockchain *bc) {
    Block *b = malloc(sizeof(Block));
    return b;
}