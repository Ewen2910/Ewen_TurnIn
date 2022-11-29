// these globals should only be accessible within this file and used only on this thread
Blockchain *myChain;
ContactBook *contacts;

Blockchain *initBlockchain();

Blockchain *getBlockchain();

ContactBook *get Contacts();

welcomeToBlockchain();

void parseCommand(char *str);

void processData(void *buffer, bool onServer);

Data *writeDataMessage(int mes, Data *d);

Data *parseDataMessage(void *buffer);

Data*chainLengthMessage(Blockchain *chain);

Data *myContactMessage();

Data *newBlockMessage();
 
Data *newTransactionMessage(char *com);

Data *BlockchainMessage(Blockchain *chain);