#include <stdio.h>
#include <string.h>

#define MAX_MESSAGES 100
#define MAX_WORDS 100
#define MAX_WORD_LEN 20

typedef struct {
    char text[MAX_WORDS * MAX_WORD_LEN];
    int isSpam; // 1 for spam, 0 for not spam
} Message;

// Function to count word occurrences in messages
void trainModel(Message messages[], int messageCount, char *vocab[], int vocabSize, int spamCounts[], int notSpamCounts[]) {
    for (int i = 0; i < messageCount; i++) {
        char *token = strtok(messages[i].text, " ,.-
");
        while (token != NULL) {
            for (int j = 0; j < vocabSize; j++) {
                if (strcmp(token, vocab[j]) == 0) {
                    if (messages[i].isSpam)
                        spamCounts[j]++;
                    else
                        notSpamCounts[j]++;
                }
            }
            token = strtok(NULL, " ,.-
");
        }
    }
}

// Function to classify a message
int classifyMessage(char *message, char *vocab[], int vocabSize, int spamCounts[], int notSpamCounts[], int spamTotal, int notSpamTotal) {
    char *token = strtok(message, " ,.-
");
    double spamProb = 1.0, notSpamProb = 1.0;

    while (token != NULL) {
        for (int i = 0; i < vocabSize; i++) {
            if (strcmp(token, vocab[i]) == 0) {
                spamProb *= ((double)spamCounts[i] + 1) / (spamTotal + vocabSize); // Add-1 smoothing
                notSpamProb *= ((double)notSpamCounts[i] + 1) / (notSpamTotal + vocabSize); // Add-1 smoothing
            }
        }
        token = strtok(NULL, " ,.-
");
    }

    return spamProb > notSpamProb ? 1 : 0; // 1 for spam, 0 for not spam
}

int main() {
    // Training data
    Message messages[] = {
        {"Win cash prize now", 1},
        {"Free offer just for you", 1},
        {"Meeting at 5 pm", 0},
        {"Let's catch up tomorrow", 0},
        {"Claim your free prize now", 1}
    };
    int messageCount = 5;

    // Vocabulary
    char *vocab[] = {"win", "cash", "prize", "free", "offer", "meeting", "catch", "tomorrow", "claim", "you"};
    int vocabSize = 10;

    // Word counts for spam and not spam
    int spamCounts[MAX_WORDS] = {0};
    int notSpamCounts[MAX_WORDS] = {0};

    // Train the model
    trainModel(messages, messageCount, vocab, vocabSize, spamCounts, notSpamCounts);

    // Calculate total words in spam and not spam messages
    int spamTotal = 0, notSpamTotal = 0;
    for (int i = 0; i < vocabSize; i++) {
        spamTotal += spamCounts[i];
        notSpamTotal += notSpamCounts[i];
    }

    // Input message to classify
    char input[MAX_WORDS * MAX_WORD_LEN];
    printf("Enter a message to classify: ");
    fgets(input, sizeof(input), stdin);

    // Classify the message
    int result = classifyMessage(input, vocab, vocabSize, spamCounts, notSpamCounts, spamTotal, notSpamTotal);

    // Output the result
    if (result == 1)
        printf("The message is classified as: SPAM
");
    else
        printf("The message is classified as: NOT SPAM
");

    return 0;
}
